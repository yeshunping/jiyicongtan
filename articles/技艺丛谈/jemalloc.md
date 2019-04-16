【译与注】使用jemalloc实现可扩展的内存分配

原作者：Jason Evans
译者：叶顺平
原文链接：https://www.facebook.com/notes/facebook-engineering/scalable-memory-allocation-using-jemalloc/480222803919

```cpp
译者注：
大家在编程中经常使用 malloc() 函数，很多工程师可能觉得这个是一个系统调用，其实不是的，mmap(), sbrk() 等才是系统调用，malloc() 是 glibc 中实现的内存分配函数，是用户态的函数。
如果大家对 malloc 的实现比较感兴趣，可以去下载 glibc 的源代码阅读。malloc 的 glibc 实现，有不少不足之处，其中就包括内存峰值比较高，线程多的时候内存分配比较慢等问题。工业界常用的还有 tcmalloc 和 jemalloc, 前者在谷歌内存广泛使用，后者在 Facebook 内部广泛使用。这篇文章是 jemalloc 的作者写的，内容比较切中要害，因此翻译出来，和读者分享。文中根据我理解的理解和经验，补充了一定的译注，希望对读者阅读有帮助。
以后找个时间可以写一两篇介绍谷歌 tcmalloc 的文章。目前我们公司内部使用tcmalloc 更多一些，我本人也详细阅读过 tcmalloc, 并根据项目需求，做过一定的改造，以解决一些难搞的内存问题。
值得一提的是，tcmalloc的作者，就是和Jeff Dean齐名的谷歌大神 Sanjay Ghemawat，最近有几篇文章讲他们的传奇故事的。jeaf dean 的代码，可以看看开源的leveldb, Sanjay的代码，我搜索了下，似乎就只有tcmalloc 是开源的了。
```

Facebook 网站包括不同类型的服务，这些服务大部分运行在8核CPU和8G内存以上的特定服务器中。这些服务程序一般使用POSIX线程来实现并发，通过最大化利用CPU和内存来实现最大化吞吐的目标。这样的运行环境给内存分配带来的很大的挑战，特别是以下几点：

- 分配和释放必须**快**。理想情况下，在程序的稳定状态下，只需要做少量的内存分配，但是实现远非如此，现实中对于动态变化的输入，往往需要分配和释放大量的动态数据结构。（译注：一般数据结构会在初始化的时候就构造出来，并有较长的生命周期）
-   活跃的内存和内存使用必须有稳定的关系。（译注：使用tcmalloc的术语就是，in use by application 不变的情况下，total memory 需要保持基本不变，否则内存分配器本身的overhead就越来越大了）。换言之，内存分配器引入的内存碎片的实际代价是非常重要的。想象一下，如果内存碎片使得内存使用每天增加1G，一个设计的时候剩余不多内存的话，将会来几天内就挂了。（译注：比如预计是4G，机器才8G，4天就因为内存不够挂了）
-   内存剖析是非常重要的功能。如果一切都找计划进行，那么检测内存泄露并解决之，是一个常规的开发任务。但是即便如此，动态输入也可能会带来异常的内存使用峰值，而这只能通过在线服务的行为来分析。（译注：也就是只能做online profiling，因为问题往往不容易离线复现，这就要求heap profiling需要足够轻量级，否则会严重影响在线服务）

2009年那会，现有的内存分配器最多满足上面三条中的两条，因此我们给jemalloc添加了内存剖析的功能，并做了大量的优化，因此jemmlloc 目前已经很好地解决了上面的三个问题。下文先是调查了jemalloc的核心算法和数据结构，然后再介绍了Facebook贡献的众多改进细节，最后附上了一份跑分记录，在在线的Web服务器负载下，比较了六个内存分配器的表现。

# 核心算法与数据结构

C 和 C++ 编程语言依赖于一个非常基础的类型无关的分配器API，它只有包括五个函数：malloc(), posix_memalign(), calloc(),realloc(), 和 free()。 不少 malloc 的实现也提供了一些简单的内省能力（译注：也就是查看内存的内部详细使用状态等），比如函数malloc_usable_size()。虽然 API 本身很简单，但是高并发下的高吞吐量和规避内存碎片，却需要相当复杂的内部实现。jemalloc 采用了一些原创的想法，而更多的想法则被其它内存分配器先验证过的。以下是那些想法的概述，以及内存分配哲学，正是它们构成了jemalloc。

-   按照大小类别（译注：不是大小，但是不同大小的类别，比如16 , 32, 48, 64, 128, 256字节）隔离不同的小对象。并且**重复利用时倾向于选择低地址**，这个布局策略来源于phkmalloc, 这个也是 jemalloc 预期会有较低的内存碎片行为的关键所在。

-  **精挑细选大小类别**（一定程度上受到 Vam 的启发）。如果类别大小间隔很大，对象往往会有过多的不可用的尾随空间（内部碎片）。（译注：比如连续的大小为32字节和64字节，要分配33字节的话，就需要使用64字节的内存块，浪费了31字节）而如果不同大小的类别过多，专用于某个大小对象的未使用内存，也就是随着增加（外部碎片）。（译注：也就是说，没被使用到的类别就会变多，比如给32,33,34,35,36,37,38,39,40字节的对象分别创建了一个对象链表，但是实际程序中只是使用到了32, 40字节的对象，那么33-39字节的对象是被创建了，但是却没有被使用到）

-   **严格控制分配器metadata 本身的额外代价**。除了内存碎片，jemalloc 控制metadata 的额外代价在总内存使用的2%以内，用于存储不同大小的类别。(译注：主要是内存分配器本身使用的内存，比如用于存储缓存对象的链接等数据结构)

-   **最小化活跃的页面集**。操作系统内存按照页面（一般一个页面4K）来管理虚拟内存，因此尽可能集中所有数据到几个页面里就非常重要。phkmalloc 验证了这一宗旨，曾经有段时间，应用程序经常相互竞争活跃页面（已经被交换到磁盘中）（译注：以前内存比较小），然而这点尽管在完全避免交换的现代背景下仍然很重要。

-   **最小化锁争用**。jemalloc 的独立的 arenas 受到 lkmalloc 的启发，但是随着时间的推移，tcmalloc 让这点更加明确，它指出完全避免同步甚至会更好，因此 jemalloc 也实现了线程局部缓存。(译注：tcmalloc 里叫做thread local cache，通过 TLS 来访问，如果 cache 不足，则加锁从 central cache 获取)

-  **若非通用则不够好用**。当 jemallo 第一次合并到 FreeBSD 时，在某些程序中，它存在严重的内存碎片问题，这时有人建议在操作系统中包含多个分配器，该观点认为开发人员有权根据应用程序特征做出明智的选择。正确的解决方案是，大力简化 jemalloc 的布局算法，以提高性能和可预测性。

过去几年，这个哲学理念激发了 jemalloc 的众多重大性能改进，随着不足被不断发现，它也将继续指导 jemalloc 的开发。

jemalloc 实现了三个主要的大小类别，分别如下（假设 jemalloc 用的是64位系统的默认配置）

-   **小:** [8], [16, 32, 48, ..., 128], [192, 256, 320, ..., 512], [768, 1024, 1280, ..., 3840]
-   **大:** [4 KiB, 8 KiB, 12 KiB, ..., 4072 KiB]
-   **超大:** [4 MiB, 8 MiB, 12 MiB, ...]

虚拟内存子在逻辑上被分区为大小为2的指数的块（默认为4M）。因此可以在常数时间内，为小/大对象，通过指针操作查找到分配器的metadata（内部指针）,而通过全局红黑树，则可以在对数时间内查找到超大对象的metadata。 （译注：前两类，根据申请的内存大小，计算最接近的size class ，然后直接通过索引来查找即可。超大对象的话，使用红黑树来存储，key 为 size, 查找时间是log(N)，下文会解释Facebook 内部优化了红黑树的查找和删除操作，想必就是优化超大对象的内存分配）

首次分配小/大对象时，应用程序线程通过轮询的方式来分配 arenas。Arenas 彼此之间相互独立。他们维护自己的块，在块中它们为小/大对象们分配 page runs (译注：翻译为连续的页面不知道准确不准确)。释放的内存则总是返还到分配它的 arena，不管是哪个线程执行了释放操作。

## Arena 块布局

每个 arena 块包含元数据（主要是页面映射），后面是一到多个连续页（译注：page runs，找不到合适的翻译词，这里翻译为连续页)。小对象被组织到一起，在每个连续页的起始地址存放额外的元数据。而大对象是彼此独立的，他们的元数据完全存放在 arena 块的头部。每个 arena 块使用红黑树来记录未使用完的小对象连续页（每个大小的列表使用一棵红黑树），当有内存分配请求的时候，优先使用该大小的类别对应的未使用完的连续页，从低地址开始。每个 arena 使用两棵红黑树来追踪可使用的连续页——一个记录干净的/未被使用的连续页，一个记录脏的/被使用过的连续页。连续页优先从脏树中分配，使用浪费最小的最佳匹配（译注：也就是挑选大小最合适的，以避免浪费）。

## Arena和线程缓存布局

每个线程维护一个小对象的缓存，以及最大到一定大小的大对象（默认是32K）。因此大部分分配请求，首先检测是否有可获取的缓存对象，然后再访问 arena。通过线程缓存的分配，是不需要任何锁的，而通过arena 来分配是需要锁住一个 arena 箱子（每个小的大小类别一个箱子），和（或）arena 整体。

线程缓存的主要目的在于降低同步事件的数量。因此，每个大小类别所缓存的对象最大数量，应该限制在一个允许在实践中减少同步事件10-100倍的水平。更高的缓存限制也许能为某些应用带来进一步的分配加速，但是一般会带来不可接受的内存碎片代价。为了进一步限制内存碎片，线程缓存会进行增量的“垃圾回收”（GC），其执行时间间隔是使用分配请求次数来衡量的。在一次到多次GC操作中未被回收的缓存对象，将使用指数衰减方法，逐渐放回到各自的 arena。

# Facebook的原创改进

2009年那会，一位Facebook的工程师可能会这么总结jemalloc的优缺点：“jemalloc的一致性和可靠性都很赞，但是不够快，另外我们需要更好的方法去监控程序到底在干什么”

## 速度

我们做了很多改进，解决了性能问题。以下是一些比较重要的改进：

-   我们重写了**线程缓存**。大部分性能的提升来自于降低了常数比例的代价（它们在关键路径中很重要），但是我们也观察到，更严格地控制缓存大小，可以提高数据局部性，而这会冲淡缓存填充和刷新带来的代价上升。因此，在设计时，我们选择一个非常简单的数据结构（每个不同大小的类别，使用单向链接的LIFO结构）和大小控制策略（给不同大小的类别设置硬限制，加上完全独立于其他线程的增量GC）

-   我们**增加锁粒度**，并重构同步逻辑，使得**系统调用期间，完全不使用锁**。在之前，jemalloc 使用非常简单的锁策略——一个arena一把锁——但我们认识到，在mmap(), munmap(), 或者 madvise() 系统调用期间，持有arena的锁会有严重的序列化代价。尤其是2.6.27之前的内核版本。因此，我们将arena锁降级，仅用于保护和arena chunks 和 page runs 相关的所有操作。每个arena中，我们给每个不同大小的类别加了一把锁，以保护相关的数据结构，一般是由于轻量的内存和释放而被访问的。不过这些补救的措施依然不足，因此我们重写了脏页面的清除工具，在调用madvise()之前，释放所有的锁。这个改动彻底解决了锁序列化问题，包括Linux 内核 2.6.27 和更新的版本。
    
-   我们重写了**脏页面清除**模块，使得最大的脏页面数和内存总使用量成比例，而不是一个常数。我们也将干净的和未使用的脏页面进行隔离，而不是合并它们，目的是优先使用脏页面，降低脏页面清除的总量。虽然这个改动一定程度上增加了虚拟内存使用量，但是对吞吐量却有显著的正面作用。
    
-  我们**开发了一个新的红黑树实现**，该实现有着同样的低内存代价（每个节点两个指针），但是插入和删除操作大概快了30%左右。这个固定比例的改进对我们的一两个应用有着蛮大的作用。（译注：后面省略一部分，是关于红黑树实现的性能分析和改进思路的，这部分比较专业，并且和内存分配器的实现关系不大，翻译了反而影响整体阅读。感兴趣的朋友可以阅读英文原文）

## 自我检查

jemalloc 一直都会在程序退出的时候，以可读的格式，打印详细的内部统计信息，但是这对于长期运行的服务程序来说是用处有限了，所以我们新增了malloc_stats_print() 这个函数，它可以在程序中被任意次调用。（译注：tcmalloc更进一步，改写了malloc_stats() 这个函数的实现）不足的是，这个函数的输出，对使用者来说还需要进行解析（以拿到各个字段），因此我们添加了themallctl*() 系列 API（接口参考参考BSD的 sysctl() 系统调用）用于获取各个统计信息。（译注：tcmalloc也提供了类似的接口）我们根据 mallctl*()重新实现了malloc_stats_print() 函数，以确保完全覆盖这些信息，随着时间的推移，我们也扩展了这个工具函数，以提供不同的控制，比如线程缓存刷新和强制性脏页清除等。

诊断内存泄露是一个很大的挑战，尤其是在线服务需要输出泄露信息。谷歌的tcmalloc 提供了很出色的内存剖析工具，可以用于生产环境，我们发现这个工具的作用简直是无价的。然而，在一些应用上，我们不断碰到这样的困境：只有jemalloc能够重复控制内存使用，但是只有tcmalloc 提供了适当的工具同于理解内部的内存占用情况（译注：一般用于定位离线很难付现的内存泄露）。因此，我们在jemalloc中实现了兼容的内存剖析工具。这样我们就可以利用tcmalloc内置的后处理工具了。（译注：gperftools 实现的heap profiling 是和tcmalloc实现绑定的，官方说有计划独立出去，但是至今还没有接耦，因此jemalloc 只能在 jemalloc 项目内部实现一个heap profiling 工具）

## 实验

Research and development of untried algorithms is in general a risky proposition; the majority of experiments fail. Indeed, a vast graveyard of failed experiments bears witness to jemalloc's past, despite its nature  
as a practical endeavor. That hasn't stopped us from continuing to try new things though. Specifically, we developed two innovations that have the potential for broader usefulness than our current applications.

-   Some of the datasets we work with are huge, far beyond what can fit in RAM on a single machine. With the recent increased availability of solid state disks (SSDs), it is tempting to expand datasets to scale with SSD rather than RAM. To this end we added   the **ability to explicitly map one or more files**, rather than using anonymous mmap(). Our experiments thus far indicate that this is a promising approach for applications with working sets that fit in RAM, but we are still analyzing  whether we can take sufficient advantage of this approach to justify the cost of SSD.

-   The venerable malloc API is quite limited: malloc(), calloc(), realloc(), andfree(). Over the years, various extensions have been bolted on, like valloc(),memalign(), posix_memalign(), recalloc(),  
    and malloc_usable_size(), just to name a few. Of these, only posix_memalign() has been standardized, and its bolt-on limitations become apparent when attempting to reallocate aligned memory. Similar issues exist for various combinations of  alignment, zeroing, padding, and extension/contraction with/without relocation. We **developed a new *allocm()API** that supports all reasonable combinations. For API details, see the [jemalloc manual page](http://www.facebook.com/l.php?u=http%3A%2F%2Fwww.canonware.com%2Fdownload%2Fjemalloc%2Fjemalloc-latest%2Fdoc%2Fjemalloc.html&h=QAQEamCGj&s=1). We are currently using this feature for an optimized C++ string class that depends on reallocation succeeding only if it can be done in place. We also have imminent plans to use it for aligned reallocation in a hash table implementation, which  will simplify the existing application logic.

# Facebook内部的成功应用

Some of jemalloc's practical benefits for Facebook are difficult to quantify. For example, we have on numerous occasions used heap profiling on production systems to diagnose memory issues before they could cause  service disruptions, not to mention all the uses of heap profiling for development/optimization purposes. More generally, jemalloc's consistent behavior has allowed us to make more accurate memory utilization projections, which aids operations as well as long  
term infrastructure planning. All that said, jemalloc does have one very tangible benefit: it is fast.

Memory allocator microbenchmark results are notoriously difficult to extrapolate to real-world applications (though that doesn't stop people from trying). Facebook devotes a significant portion of its infrastructure  
to machines that use [HipHop](http://www.facebook.com/note.php?note_id=280583813919) to serve Web pages to users. Although this is just one of many ways in which jemalloc is used  
at Facebook, it provides a striking real-world example of how much allocator performance can matter. We used a set of six identical machines, each with 8 CPU cores, to compare total server throughput. The machines served similar, though not identical, requests,  
over the course of one hour. We sampled at four-minute intervals (15 samples total), measured throughput as inversely related to CPU consumption, and computed relative averages. For one machine we used the default malloc implementation that is part of [glibc](http://www.facebook.com/l.php?u=http%3A%2F%2Fwww.gnu.org%2Fsoftware%2Flibc%2F&h=GAQGZXXmm&s=1) 2.5,  
and for the other five machines we used the LD_PRELOAD environment variable to load[ptmalloc3](http://www.facebook.com/l.php?u=http%3A%2F%2Fwww.malloc.de%2Fen%2F&h=1AQHW9CeR&s=1), [Hoard](http://www.facebook.com/l.php?u=http%3A%2F%2Fwww.hoard.org%2F&h=tAQGBgjNu&s=1) 3.8, [concur](http://www.facebook.com/l.php?u=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fconcur%2F&h=lAQFTULHF&s=1) 1.0.2, [tcmalloc](http://www.facebook.com/l.php?u=http%3A%2F%2Fcode.google.com%2Fp%2Fgoogle-perftools%2F&h=RAQFrSg9n&s=1) 1.4,  
and [jemalloc](http://www.facebook.com/l.php?u=http%3A%2F%2Fwww.canonware.com%2Fjemalloc%2F&h=KAQFbRdsr&s=1) 2.1.0. Note that newer versions of  
glibc exist (we used the default for [CentOS](http://www.facebook.com/l.php?u=http%3A%2F%2Fwww.centos.org%2F&h=cAQGiRnEM&s=1) 5.2), and that the  
newest version of tcmalloc is 1.6, but we encountered undiagnosed application instability when using versions 1.5 and 1.6.

Web server throughput

glibc derives its allocator from ptmalloc, so their performance similarity is no surprise. The Hoard allocator appears to spend a great deal of time contending on a spinlock, possibly as a side effect of its blowup avoidance algorithms. The concur allocator appears to scale well, but it does not implement thread caching, so it incurs a substantial synchronization cost even though contention is low. tcmalloc under-performs jemalloc by about 4.5%.

The main point of this experiment was to show the huge impact that allocator quality can have, as in glibc versus jemalloc, but we have performed numerous experiments at larger scales, using various hardware and  client request loads, in order to quantify the performance advantage of jemalloc over tcmalloc. In general we found that as the number of CPUs increases, the performance gap widens. We interpret this to indicate that jemalloc will continue to scale as we deploy  
new hardware with ever-increasing CPU core counts.

# 未完成的工作

jemalloc目前已经比较成熟，但是也依然存在已知的不足，大部分涉及到arenas 如何分配给线程。比如，某个程序创建了一个线程池去构造一个很大的静态数据结构，然后使用单线程进行后续操作。除非程序采取特殊的动作来控制 arenas 怎么分配（或者仅仅是简单地限制arenas的数量），那么初始化阶段很容易留下不少利用率很差的arenas（也就是说，内存碎片率高）。解决办法是有的，但是我们指出这个和其他问题，因为它们是由于不可预见的程序行为来出现的。（译注：这里说的问题其实是，开始的时候使用了大量的线程，那个线程都有thread cache，但是后续却无法快速释放内存，因为线程池还在，对应的thread cache还无法回收。一个解决办法是，降低thread pool size，或者是初始化的时候使用线程池，初始化完毕，删除线程池，这样线程退出后，对应的thread cache也就能够及时释放。如果是tcmalloc, 因为实现了borrow 内存的策略，所以只要后续的线程使用固定的线程，而不是每次从线程池中随机Pop一个线程来处理，那么也可以较快释放非活跃线程的内存）。

# 致谢

略。
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTYxMDIwMjUzMywtNTY5MDY4MTIwLDExND
Q1NTIyMDFdfQ==
-->