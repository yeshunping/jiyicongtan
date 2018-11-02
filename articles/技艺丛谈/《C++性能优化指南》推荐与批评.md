最近因为工作需要，阅读了大量性能优化方面的书籍，论文和资料。也算是有一些心得。本篇想向C++程序员们推荐一本2017年才出版的书籍，目前国内也已经有了翻译版本。（不过我没阅读过翻译版，因此对翻译质量无法进行评价）

以下是书籍链接：
http://shop.oreilly.com/product/0636920038030.do

以下是书籍目录：

> Chapter 1 An Overview of Optimization 
> Chapter 2 Computer Behavior Affecting Optimization 
> Chapter 3 Measure Performance
>  Chapter 4 Optimize String Use: A Case Study
>  Chapter 5 Optimize Algorithms
> Chapter 6 Optimize Dynamically Allocated Variables
>  Chapter 7 Optimize Hot Statements
>  Chapter 8 Use Better Libraries
>  Chapter 9 Optimize Searching and Sorting
>  Chapter 10 Optimize Data Structures
>  Chapter 11 Optimize I/O
>  Chapter 12 Optimize Concurrency
>   Chapter 13 Optimize Memory Management

先介绍下作者，作者其实不是什么知名程序员，不过是以为有超过35年工作经验的软件开发人员，频繁使用C++进行开发的年份有25年左右。

引用下出版社的介绍：

> Author Kurt Guntheroth provides several running examples that
> demonstrate how to apply these principles incrementally to improve
> existing code so it meets customer requirements for responsiveness and
> throughput. The advice in this book will prove itself the first time
> you hear a colleague exclaim, “Wow, that was fast. Who fixed
> something?”
> 
> -   Locate performance hot spots using the profiler and software timers
> -   Learn to perform repeatable experiments to measure performance of code changes
> -   Optimize use of dynamically allocated variables
> -   Improve performance of hot loops and functions
> -   Speed up string handling functions
> -   Recognize efficient algorithms and optimization patterns
> -   Learn the strengths—and weaknesses—of C++ container classes
> -   View searching and sorting through an optimizer’s eye
> -   Make efficient use of C++ streaming I/O functions
> -   Use C++ thread-based concurrency features effectively

## 本书特色

- 循序渐进，提供了大量的例子，一步步修改代码，使得性能不断提高。
- 介绍了一些定位性能热点的工具和思路。
-  介绍了一些算法方面的改进思路。不过比较粗浅，主要是简单的排序查找。
- 介绍了C++ 对并发编程的支持，以及一些性能方面容易遇到的坑。
- 较为详尽分析了C++ string方面的性能问题。
- 介绍了一些广为人知的性能优化模式（optimization patterns），比如缓存，比如make common case fast 等。
- 较为详细剖析了C++容器的性能问题。
- 介绍了内存，IO，线程并发和同步等方面的性能问题和经验。

总体而已，本书的定位绝对不是性能优化的圣经宝典，更像是容易实操学习的指南。本书每个章节一般围绕着一段性能不够理想的代码，通过不断分析（不够深入和本质的分析）、改进，从而达到更优的性能，在优化的过程中讲解知识点和经验。

本书值得没有性能优化经验的程序员阅读，是非常好的入门书籍。如果是已经是编程高手，那么本书也不妨买来翻翻，因为翻翻书里的例子，也可以让你重新梳理你的性能优化经验。

## 不足之处

 - 很多时候性能是变好了，却没有分析清楚变好的原因。
 -  缺乏对数据结构，C++容器内存分配次数，空间大小的精确分析，也就是没有能够从内而外，而是从外部表现而推测内部实现。
- 多从外围着手，而不是从源代码入手。因此不免有点盲人摸象，或者有点随机梯度学习的味道（改动的版本性能波动不小，有的变快，有的变慢），最后基本都能收敛到接近最优解，但是不够高效，或者可解释性不强。
 - 不少精华的主题没有展开，比如图二中的Optimization patterns。我觉得这些才是性能优化的精华所在。
  - 本书侧重cpu优化，而缺乏对内存优化的总结和案例分析。而很多时候内存优化了，性能也能带来优化。尤其是嵌入式设备，对内存要求很高的时候，如果内存不足，往往大部分使用空间换时间的策略都无从下手。这方面我倒是做过不少总结。
  - benchmark虽然好，但是如果能结合cpu profiler来讲，也许更能有洞见，虽然cpu profiler并不是屡屡奏效。
  - 缺乏比知名的几个性能分析工具的介绍，以及工具背后的原理。比如google perftools, OProfile, linux perf, gprof等。
  - 缺乏对计算机体系架构的深入介绍。比如CPU pipeline, L1 cache, L2 cache, L3 cache, SIMD等。缺乏对指令并行和数据并行的深入介绍。
  - 缺乏对编译器行为的原因分析。也就是说，性能优化如果离开计算机体系结构，操作系统和编译器来谈论的话，往往落入盲人摸象。

好吧，说了这么多不足，其实这本书还是很不错的，瑕不掩瑜。很明显，我写文章的目的是鼓励大家去阅读本书，收获性能优化方面的一些经验。当然，不足之处恐怕阅读的时候不容易看出来，因为我在几个月前阅读的时候就觉得书写得很不错，很多介绍的内容于我都是心有戚戚焉，心里想着，挖槽，怎么作者都想到了。

希望在以后的文章有，有机会慢慢展开上面提点的一些不足点，也算是给自己的性能优化学习之旅画上一个休止符。

<!--stackedit_data:
eyJoaXN0b3J5IjpbNDQzNDQ3OTcwLC0xMDA1Mjc1NjRdfQ==
-->