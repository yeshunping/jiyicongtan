原作者：by M. Tim Jones
译者：叶顺平

```
性能优化这个事情，主要从几个维度进行：
1，硬件能力的充分发挥，比如存储器的各个层次结构，比如特定的指令集（SSE，AVX等），比如CPU pipeline的充分利用。
2，编译器的选择与编译选项的熟练使用。
3，应用程序的熟悉与优化（语言层面，算法层面等）。

了解编译器提供的优化选项，不仅可以直接使用编译器提供的能力，为你的程序直接进行加速，还可以让你知道通用的程序加速手段。因为很明显，搞编译器的人，更清楚性能角度的common case何在。假如掌握了编译器的一些优化手段，应用程序层面的优化就很好开展了。

最近看了篇文章，顺手翻译为中文，一来锻炼下自己翻译水平，二来让自己更加熟悉，三来希望对读者朋友也有所帮助。

以下是译文部分，要阅读英文原文，请点击文末“阅读原文”的链接。
```

本文中，我们将一起来看看GCC编译工具链提供的性能优化的不同级别，包括各个级别包括的优化选项。我们也会指出需要显式添加的优化选项，其中有一些依赖于特定的体系结构。本文讨论以GCC 3.2.2 版本为例（2003年2月发版），不过这也适用于当前的发行版本3.3.2.（译者注：目前GCC版本比这个高多了，不过不妨碍我们了解编译器的常用优化选项）


## 优化级别

首先让我们来看看GCC对不同的优化选项进行归类，看看程序员如何来控制启用什么编译选项，当然有时候如何禁用否则优化选项更为重要。GCC提供了大量的优化选项。大部分都被归类到三个不同的级别中，不过有一些在各个级别都启用。有一些优化会降低生成的机器代码的大小，而有一些则志在提高执行速度，甚至以增大机器代码为代价。为了保持程序的原始状态（译者注：比如调试信息等），默认的编译级别为0，这个级别并不提供任何优化。0级也可以使用-O 或者 -O0 来显式指定。

### 优化级别1 (-O1)

第一级的优化目的在于在尽可能快的编译时间内生成优化的代码。这些优化措施一般不会耗费大量的编译时间。O1偶尔也会有两个相互冲突的目标——这些目标是既要降低生成的文件大小，又要提高性能。O1级别的优化措施大部分都可以达到这两个目标。表格1标记为-O1的一列，就是O1 级别的优化选项。
![enter image description here](https://www.linuxjournal.com/files/linuxjournal.com/linuxjournal/articles/072/7269/7269t1.jpg)
表格 1. GCC 优化措施以及对应的打开级别

O1级别的优化使用以下方式打开：

```
gcc -O1 -o test test.c
```

在任何优化级别之外，任何优化选项都可以使用优化名和 -f 前缀打开。如下：

```
gcc -fdefer-pop -o test test.c
```
我们也可以打开O1级别，并禁用任意优化策略，方法是使用 -fno- 前缀。比如：

```
gcc -O1 -fno-defer-pop -o test test.c
```
这句编译命令会打开所有第一级的优化策略，但是禁用其中的 defer-pop 优化策略。
(译者注： 在最新的8.2.0版本中，-O1级别包含以下编译选项：
```
-fauto-inc-dec
-fbranch-count-reg
-fcombine-stack-adjustments
-fcompare-elim
-fcprop-registers
-fdce
-fdefer-pop
-fdelayed-branch
-fdse
-fforward-propagate
-fguess-branch-probability
-fif-conversion2
-fif-conversion
-finline-functions-called-once
-fipa-pure-const
-fipa-profile
-fipa-reference
-fmerge-constants
-fmove-loop-invariants
-fomit-frame-pointer
-freorder-blocks
-fshrink-wrap
-fshrink-wrap-separate
-fsplit-wide-types
-fssa-backprop
-fssa-phiopt
-ftree-bit-ccp
-ftree-ccp
-ftree-ch
-ftree-coalesce-vars
-ftree-copy-prop
-ftree-dce
-ftree-dominator-opts
-ftree-dse
-ftree-forwprop
-ftree-fre
-ftree-phiprop
-ftree-sink
-ftree-slsr
-ftree-sra
-ftree-pta
-ftree-ter
-funit-at-a-time
```
)

### 优化级别2 (-O2)

第二级优化执行所有指定平台支持的所有其它优化方法，只是不包括以空间换时间的方法，以取得两个目标（译者注：也就是降低目标文件大小和提高执行速度）之间的平衡。比如，循环展开和函数内联就不会执行，因为它们虽然可能带来代码性能的提升，也会以增大代码大小为代价。第二级优化使用以下方式打开：
```
gcc -O2 -o test test.c
```
表格1显示了-O2 级别的优化方法。-O2优化级别包含-O1级别的所有优化方法，并增加了其它不少优化。
(译者注：在8.2.0 版本中，-O2 级别包括以下编译选项：
```
-fthread-jumps
-falign-functions  -falign-jumps
-falign-loops  -falign-labels
-fcaller-saves
-fcrossjumping
-fcse-follow-jumps  -fcse-skip-blocks
-fdelete-null-pointer-checks
-fdevirtualize -fdevirtualize-speculatively
-fexpensive-optimizations
-fgcse  -fgcse-lm
-fhoist-adjacent-loads
-finline-small-functions
-findirect-inlining
-fipa-cp
-fipa-bit-cp
-fipa-vrp
-fipa-sra
-fipa-icf
-fisolate-erroneous-paths-dereference
-flra-remat
-foptimize-sibling-calls
-foptimize-strlen
-fpartial-inlining
-fpeephole2
-freorder-blocks-algorithm=stc
-freorder-blocks-and-partition -freorder-functions
-frerun-cse-after-loop
-fsched-interblock  -fsched-spec
-fschedule-insns  -fschedule-insns2
-fstore-merging
-fstrict-aliasing
-ftree-builtin-call-dce
-ftree-switch-conversion -ftree-tail-merge
-fcode-hoisting
-ftree-pre
-ftree-vrp
-fipa-ra
```
)

### 优化级别2.5 (-Os)

除了那些会增大代码大小的优化方法，这个特殊的优化级别(-Os, s 是size 的首字母)会打开所有的-O2级别的优化方法。这个级别更强调优化代码大小而不是速度。它包括所有第二级别的优化方法，除了对齐相关的优化。对齐优化跳过了一些空间，以对齐函数、循环、跳转和标签到某个2的幂的倍数的地址，具体取决于对应的体系结构。跳过这些边界会提高执行速度（译者注：主要是Cache是按照字对齐的方式取数据和指令的），但同时也会增大编译生成的代码段大小和数据段大小（译者注：可以参考ELF文件格式），因此这些优化方法在-Os 级别会被禁用。-Os 级别使用以下方式打开：
```
gcc -Os -o test test.c
```
在GCC 3.2.2 版本中，reorder-blocks 在-Os级别中会被打开，但在3.3.2版本中不会打开。
（译者注：在最新的8.2.0版本中，会禁用掉以下选项：
```
-falign-functions  -falign-jumps  -falign-loops
-falign-labels  -freorder-blocks  -freorder-blocks-algorithm=stc
-freorder-blocks-and-partition  -fprefetch-loop-arrays
```
）

### 优化级别 3 (-O3)

第三级（也是最高级别）优化会启用更多的优化方法（见表格1），相比代码大小，该级别更侧重执行速度。它包括-O2启用的所有优化选项，以及寄存器重命名。函数内联也会在这个级别启用，它会提高执行速度，但是也有可能较大增加目标文件的大小，这取决于被内联函数的情况。第三级优化使用以下方式打开：
```
gcc -O3 -o test test.c
```
虽然-O3能生成更快的代码，但是代码大小的增加，也可能对代码性能有相反的作用。比如，代码大小超过可以获得的指令缓存的大小，就可能导致严重的性能下降。因此，也许更保险的方式是使用-O2进行编译，以增大代码大小适合指令缓存的概率。

(在最新的 8.2.0版本中，该级别包含：
```
-finline-functions
-funswitch-loops
-fpredictive-commoning
-fgcse-after-reload
-ftree-loop-vectorize
-ftree-loop-distribution
-ftree-loop-distribute-patterns
-floop-interchange
-floop-unroll-and-jam
-fsplit-paths
-ftree-slp-vectorize
-fvect-cost-model
-ftree-partial-pre
-fpeel-loops
-fipa-cp-clone
```
)

## 体系结构规格

上文讨论的优化可以在软件性能和目标文件大小方面获得重要的改进，不过指定目标架构也可以获得一些可观的收益。gcc 的 -march 选项用于指定CPU类型（见表格2）。

**表格2. x86 体系架构**
![enter image description here](https://github.com/yeshunping/jiyicongtan/raw/master/articles/images/x86_arch.png)

默认的体系架构是 i386, GCC 也可以运行在其它 i386/x86 体系架构中，不过在更新的处理器中，可能性能会有所下降。如果你关注二进制文件的可移植性，你应该使用默认参数进行编译。如果你对性能更感兴趣，指定对应的体系架构。

现在让我们看一个例子，以看清如何通过指定目标机器的体系结构提高执行速度。让我们写一个简单的程序，该程序对1万个元素的数组进行冒泡排序。数组元素是倒序的，以让冒泡排序算法的性能最差。编译和计时过程显示如下：

**清单1. 指定体系结构如何影响简单程序的性能**
```
[mtj@camus]$ gcc -o sort sort.c -O2
[mtj@camus]$ time ./sort

real    0m1.036s
user    0m1.030s
sys     0m0.000s
[mtj@camus]$ gcc -o sort sort.c -O2 -march=pentium2
[mtj@camus]$ time ./sort

real    0m0.799s
user    0m0.790s
sys     0m0.010s
[mtj@camus]$
```
通过指定体系结构（本例中是633MHz 的Celeron处理器），编译器可以生成特定架构的指令，同时启用该平台特有的优化方法。如清单1所示，指定体系结构后，我们看到程序获得了237毫秒的提升（提升23%）。
从清单1看，性能获得了提升，但是缺点是程序大小也有了小幅度增大。使用size 命令（见清单2），我们来看一看二进制文件各个section的大小。

**清单2. 清单1中程序的大小变化**
```
[mtj@camus]$ gcc -o sort sort.c -O2
[mtj@camus]$ size sort
   text    data     bss     dec     hex filename
    842     252       4    1098     44a sort
[mtj@camus]$ gcc -o sort sort.c -O2 -march=pentium2
[mtj@camus]$ size sort
   text    data     bss     dec     hex filename
    870     252       4    1126     466 sort
[mtj@camus]$
```
从清单2中，我们可以看到程序的指令大小（代码段）增大了28字节。不过在这个例子中，获得性能提升的代价蛮小的。

## Math Unit Optimizations

Some specialized optimizations require explicit definition by the developer. These optimizations are specific to the i386 and x86 architectures. A math unit, for one, can be specified, although in many cases it is automatically defined based on the specification of a target architecture. Possible units for the -mfpmath= option are shown in Table 3.

**表格3. 数学相关优化**
选项 | 描述 
------------ | ------
387 | Standard 387 Floating Point Coprocessor
sse | Streaming SIMD Extensions (Pentium III, Athlon 4/XP/MP)
sse2 | Streaming SIMD Extensions II (Pentium 4)

The default choice is -mfpmath=387. An experimental option is to specify both sse and 387 (-mfpmath=sse,387), which attempts to use both units.

## Alignment Optimizations

In the second optimization level, we saw that a number of alignment optimizations were introduced that had the effect of increasing performance but also increasing the size of the resulting image. Three additional alignment optimizations specific to this architecture are available. The -malign-int option allows types to be aligned on 32-bit boundaries. If you're running on a 16-bit aligned target, -mno-align-int can be used. The -malign-double controls whether doubles, long doubles and long-longs are aligned on two-word boundaries (disabled with -mno-align-double). Aligning doubles provides better performance on Pentium architectures at the expense of additional memory.

Stacks also can be aligned by using the option -mpreferred-stack-boundary. The developer specifies a power of two for alignment. For example, if the developer specified  -mpreferred-stack-boundary=4, the stack would be aligned on a 16-byte boundary (the default). On the Pentium and Pentium Pro targets, stack doubles should be aligned on 8-byte boundaries, but the Pentium III performs better with 16-byte alignment.

## Speed Optimizations

For applications that utilize standard functions, such as memset, memcpy or strlen, the -minline-all-stringops option can increase performance by inlining string operations. This has the side effect of increasing the size of the image.

Loop unrolling occurs in the process of minimizing the number of loops by doing more work per iteration. This process increases the size of the image, but it also can increase its performance. This option can be enabled using the -funroll-loops option. For cases in which it's difficult to understand the number of loop iterations, a prerequisite for -funroll-loops, all loops can be unrolled using the -funroll-all-loops optimization.

A useful option that has the disadvantage of making an image difficult to debug is -momit-leaf-frame-pointer. This option keeps the frame pointer out of a register, which means less setup and restore of this value. In addition, it makes the register available for the code to use. The optimization -fomit-frame-pointer also can be useful.

When operating at level -O3 or having -finline-functions specified, the size limit of the functions that may be inlined can be specified through a special parameter interface. The following command illustrates capping the size of the functions to inline at 40 instructions:
```
gcc -o sort sort.c --param max-inline-insns=40
```
This can be useful to control the size by which an image is increased using -finline-functions.

## Code Size Optimizations

The default stack alignment is 4, or 16 words. For space-constrained systems, the default can be minimized to 8 bytes by using the option -mpreferred-stack-boundary=2. When constants are defined, such as strings or floating-point values, these independent values commonly occupy unique locations in memory. Rather than allow each to be unique, identical constants can be merged together to reduce the space that's required to hold them. This particular optimization can be enabled with -fmerge-constants.

## Graphics Hardware Optimizations

Depending on the specified target architecture, certain other extensions are enabled. These also can be enabled or disabled explicitly. Options such as -mmmx and -m3dnow are enabled automatically for architectures that support them.

## Other Possibilities

We've discussed many optimizations and compiler options that can increase performance or decrease size. Let's now look at some fringe optimizations that may provide a benefit to your application.

The -ffast-math optimization provides transformations likely to result in correct code but it may not adhere strictly to the IEEE standard. Use it, but test carefully.

When global common sub-expression elimination is enabled (-fgcse, level -O2 and above), two other options may be used to minimize load and store motions. Optimizations -fgcse-lm and -fgcse-sm can migrate loads and stores outside of loops to reduce the number of instructions executed within the loop, therefore increasing the performance of the loop. Both -fgcse-lm (load-motion) and -fgcse-sm (store-motion) should be specified together.

The -fforce-addr optimization forces the compiler to move addresses into registers before performing any arithmetic on them. This is similar to the -fforce-mem option, which is enabled automatically in optimization levels -O2, -Os and -O3.

A final fringe optimization is -fsched-spec-load, which works with the -fschedule-insns optimization, enabled at -O2 and above. This optimization permits the speculative motion of some load instructions to minimize execution stalls due to data dependencies.

## Testing for Improvements

Earlier we used the time command to identify how much time was spent in a given command. This can be useful, but when we're profiling our application, we need more insight into the image. The gprof utility provided by GNU and the GCC compiler meets this need. Full coverage of gprof is outside the scope of this article, but Listing 3 illustrates its use.

**Listing 3. Simple Example of gprof**
```
[mtj@camus]$ gcc -o sort sort.c -pg -O2 -march=pentium2
[mtj@camus]$ ./sort
[mtj@camus]$ gprof --no-graph -b ./sort gmon.out
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total
 time   seconds   seconds    calls  ms/call  ms/call  name
100.00      0.79     0.79        1   790.00   790.00  bubbleSort
  0.00      0.79     0.00        1     0.00     0.00  init_list
[mtj@camus]$
```
The image is compiled with the -pg option to include profiling instructions in the image. Upon execution of the image, a gmon.out file results that can be used with the gprof utility to produce human-readable profiling data. In this use of gprof, we specify the -b and --no-graph options. For brief output (excludes the verbose field explanations), we specify -b. The --no-graph option disables the emission of the function call-graph; it identifies which functions call which others and the time spent on each.

Reading the example from Listing 3, we can see that bubbleSort was called once and took 790ms. The init_list function also was called, but it took less than 10ms to complete (the resolution of the profile sampling), so its value was zero.

If we're more interested in changes in the size of the object than speed, we can use the size command. For more specific information, we can use the objdump utility. To see a list of the functions in our object, we can search for the .text sections, as in:
```
objdump -x sort | grep .text
```
From this short list, we can identify the particular function we're interested in understanding better.

## Examining Optimizations

The GCC optimizer is essentially a black box. Options and optimization flags are specified, and the resulting code may or may not improve. When they do improve, what exactly happened within the resulting code? This question can be answered by looking at the resulting code.

To emit target instructions from the compiler, the -S option can be specified, such as:
```
gcc -c -S test.c
```
which tells gcc to compile the source only (-c) but also to emit assembly code for the source (-S). The resulting assembly output will be contained in the file test.s.

The disadvantage of the previous approach is you see only assembly code, no aspect of the size of the actual instructions is given. For this, we can use objdump to emit both assembly and native instructions, like so:
```
gcc -c -g test.c
objdump -d test.o
```
For gcc, we specify compile with only -c, but we also want to include debug information in the object (-g). Using objdump, we specify the -d option to disassemble the instructions in the object. Finally, we can get assembly-interspersed source listings with:
```
gcc -c -g -Wa,-ahl,-L test.c
```
This command uses the GNU assembler to emit the listing. The -Wa option is used to pass the -ahl and -L options to the assembler to emit a listing to standard-out that contains the high-level source and assembly. The -L option retains the local symbols in the symbol table.

## 结论

应用程序都互不相同，所以并不存在神奇的优化配置和选项开关能生成最好的结果。达到较好的性能的最简单方式是使用-O2级别的优化。如果你对可移植性不感兴趣，可以使用 -march= 指定特定的体系架构。对空间受限的应用，应该首先考虑使用-Os 优化级别。如果你一定要将你的程序的性能优化到极致，那你可以考虑尝试不同的优化级别，然后使用不同的工具来检测生成代码的性能。打开或禁用特定的优化，也可以帮助优化器得到最佳性能表现。

## 本文相关资料：
GCC 项目首页:  http://gcc.gnu.org/
GCC 在线文档:  gcc.gnu.org/onlinedocs/gcc-3.2.2/gcc

作者介绍：
M. Tim Jones ([mtj@mtjones.com](mailto:mtj@mtjones.com)) is a senior principal engineer with Emulex Corp. in Longmont, Colorado. In addition to being an embedded firmware engineer, Tim recently finished writing the book  _BSD Sockets Programming from a Multilanguage Perspective_. He has written kernels for communications and research satellites and now develops embedded firmware for networking products.
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTI1NzE4OTM3NCwxNTE4NDQwNTQwLC0xNT
g1NzE5NzQ4LC0xNjg3MDMzODQ2LDExNDI5NzQzNTksLTYzODYx
OTk0NF19
-->