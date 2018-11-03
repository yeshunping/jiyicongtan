原作者：by M. Tim Jones
译者：叶顺平

```cpp
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

```cpp
gcc -O1 -o test test.c
```

在任何优化级别之外，任何优化选项都可以使用优化名和 -f 前缀打开。如下：

```cpp
gcc -fdefer-pop -o test test.c
```
我们也可以打开O1级别，并禁用任意优化策略，方法是使用 -fno- 前缀。比如：

```cpp
gcc -O1 -fno-defer-pop -o test test.c
```
这句编译命令会打开所有第一级的优化策略，但是禁用其中的 defer-pop 优化策略。
(译者注： 在最新的8.2.0版本中，-O1级别包含以下编译选项：
```cpp
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
```cpp
gcc -O2 -o test test.c
```
表格1显示了-O2 级别的优化方法。-O2优化级别包含-O1级别的所有优化方法，并增加了其它不少优化。
(译者注：在8.2.0 版本中，-O2 级别包括以下编译选项：
```cpp
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
```cpp
gcc -Os -o test test.c
```
在GCC 3.2.2 版本中，reorder-blocks 在-Os级别中会被打开，但在3.3.2版本中不会打开。
（译者注：在最新的8.2.0版本中，会禁用掉以下选项：
```cpp
-falign-functions  -falign-jumps  -falign-loops
-falign-labels  -freorder-blocks  -freorder-blocks-algorithm=stc
-freorder-blocks-and-partition  -fprefetch-loop-arrays
```
）

### 优化级别 3 (-O3)

第三级（也是最高级别）优化会启用更多的优化方法（见表格1），相比代码大小，该级别更侧重执行速度。它包括-O2启用的所有优化选项，以及寄存器重命名。函数内联也会在这个级别启用，它会提高执行速度，但是也有可能较大增加目标文件的大小，这取决于被内联函数的情况。第三级优化使用以下方式打开：
```cpp
gcc -O3 -o test test.c
```
虽然-O3能生成更快的代码，但是代码大小的增加，也可能对代码性能有相反的作用。比如，代码大小超过可以获得的指令缓存的大小，就可能导致严重的性能下降。因此，也许更保险的方式是使用-O2进行编译，以增大代码大小适合指令缓存的概率。

(在最新的 8.2.0版本中，该级别包含：
```cpp
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
```cpp
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
```cpp
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

## 数学单元优化

有一些特殊的优化需要开发者显式指定。这些优化是i386和x86 体系结构特有的。（译者注：其它系统结构也有SIMD指令集，比如ARM的neon）数学计算单元可以手工指定，但是在很多时候，它可以通过指定目标体系结构来自动设定。-fpmatch= 选项可能的数学单元如表格3所示：

**表格3. 数学相关优化**
选项 | 描述 
------------ | ------
387 | 标准 387 浮点计算处理器
sse | 流式 SIMD 扩展 (Pentium III, Athlon 4/XP/MP)
sse2 | 流式 SIMD 扩展 II (Pentium 4)

默认选择是-mfpmath=387。一个实验性的选择是，指定SSE 和 387 (-mfpmath=sse,387),，这将尝试使用两个计算单元。

## 对齐优化

在第二级优化中，我们已经看到，有一些优化方法会提高性能，但是也会增加程序大小。该体系结构还有特殊的三个其它对齐优化。-malign-int 选项会让数据类型对齐到32比特。如果你的程序允许在16比特机器，则可以使用-mno-align-int。-malign-double选项用于控制doubles, long doubles 和 long-longs是否对齐到双字边界（禁用的话则使用 -mno-align-double）。对齐双精度浮点数在奔腾处理器上能获得更好的性能，但是会耗费更多的内存。

栈也可以进行对齐，使用 -mpreferred-stack-boundary 选项即可。开发者可以指定2的幂作为对齐大小。比如，开发者指定 -mpreferred-stack-boundary=4, 栈会对齐到16字节（这是默认大小）。在奔腾和奔腾Pro 处理器上，栈上的双精度会对齐到8字节边界，但是奔腾III 处理器使用16字节对齐表现更好。

## 速度优化

对那些使用了标准库函数的应用程序，比如使用了memset, memcpy 或者 strlen，-minline-all-stringops 选项可以通过内联这些字符串操作函数来提高性能。当然这个会增大二进制文件大小。

循环展开是这么一个过程：它通过在每次迭代中做更多的工作来最小化循环次数。该过程会增加程序大小，但是也能提升性能。该选项可以使用 -funroll-loops 来启用。碰到难以计算循环迭代次数的情况（这是 -funroll-loops 的必要条件），可以使用 -funroll-all-loops 优化选项来展开所有循环。

-momit-leaf-frame-pointer 是一个有用的选项，但是却会让程序难以调试的。此选项使得帧指针不再使用寄存器，这意味着减少了存储和恢复该值的工作。（译者注：一般在函数调用的时候，先将该值保持到stack局部地址中，退出函数的时候恢复该值）。此外，这样做会使得该寄存器可以为代码所用（译者注：相当于多了一个可用寄存器）。-fomit-frame-pointer 选项也同样有用。

当使用 -O3 优化级别，或者是手动指定 -finline-functions 时，被内联的函数的大小限制可以使用特殊的参数来设定。以下命令展示了将内联函数的大小限制在40条指令以内。
```cpp
gcc -o sort sort.c --param max-inline-insns=40
```
如果使用 -finline-functions 时程序却增大了，这时使用这个参数来控制程序大小就会很有用。

## 代码大小优化

默认的栈对齐大小为4字或者16字。对于空间受限的系统，默认值可以调整到8字节，使用 -mpreferred-stack-boundary=2 选项即可。定义常量（如字符串或浮点值）时，这些独立值通常在内存中占用唯一的地址。与其让它们使用不同的地址，相同的常量可以合并到一起，以降低存储它们的空间。这个优化可以使用 -fmerge-constants 启用。

## 显卡硬件优化

依赖于特定的体系结构，一些其它的扩展会被启用。这些扩展也可以被显式启用或禁用。诸如 -mmmx 和 -m3dnow 的选项，会在支持它们的平台中自动启用。

## 其它可能性

至此，我们已经讨论了很多优化方法和编译器选项，它们要么可以提高性能，要么可以减小程序大小。现在让我们来看一下其它较为少用的优化，它们可能也会让你的程序获益。

-ffast-math 优化提供了某种转换，它生成的代码很可能是正确的，但并不严格遵守IEEE标准。使用它们，但是请仔细测试它们。（译者注：比如将a = a * a * a * a * a * a * a * a 转换为 a = (a * a) * (a * a) * (a * a * a * a) , 从而转换为 a *=  a, a *= a, a *= a, 从而7次浮点计算变为3次浮点计算）

当全局公共子表达式消除被启用时 （-fgcse 选项,  -O2 或以上），可以考虑启用另外两个选项，以减少读取和存储操作的次数。-fgcse-lm 和 -fgcse-sm 优化可以将循环内的读取和存储移到循环外，以降低循环内的指令数，提高循环的执行性能。-fgcse-lm (读取) 和 -fgcse-sm (存储) 两个选项需要一起设置。

-fforce-addr 优化选项强制编译器将存储器内存先拷贝到寄存器，然后再执行任何数学运算。 -fforce-mem 也类似，它在优化级别-O2, -Os 和 -O3中自动开启。

最后一个不常用的优化是 -fsched-spec-load， 它和 -fschedule-insns 优化一起工作，在 -O2 以上级别启用。该优化通过预测读取指令
A final fringe optimization is -fsched-spec-load, which works with the -fschedule-insns optimization, enabled at -O2 and above. This optimization permits the speculative motion of some load instructions to minimize execution stalls due to data dependencies.

## 测试性能改进

Earlier we used the time command to identify how much time was spent in a given command. This can be useful, but when we're profiling our application, we need more insight into the image. The gprof utility provided by GNU and the GCC compiler meets this need. Full coverage of gprof is outside the scope of this article, but Listing 3 illustrates its use.

**Listing 3. Simple Example of gprof**
```cpp
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
```cpp
objdump -x sort | grep .text
```
From this short list, we can identify the particular function we're interested in understanding better.

## 检查优化结果
GCC编译器如同黑盒子。指定优化选项和优化级别后，程序也许变快了，也许变慢了。当结果变好了，编译生成的代码究竟用了什么黑科技？我们看到生成的汇编代码，会可以揭晓答案啦。
指定 -S 编译选项，就可以让编译器输出目标机器的指令了，比如：
```cpp
gcc -c -S test.c
```
告诉编译器进行只源码编译（-c）(译者注：而不进行链接)，但是输出源码对应的汇编代码(-S)。生成的汇编代码在 test.s 文件中。
上述方法的不足之处在于，你可能看到汇编代码，真实指令大小方面的信息并没有提供（译者注：因为一些平台的指令是变长的，因此指令个数和指令大小不完全相同。也有一些体系结构的指令的定长的，比如MIPS）。为此，我们可以使用 objdump 工具，以输出汇编和原始指令，比如：
```cpp
gcc -c -g test.c
objdump -d test.o
```
我们指定了 -c 进行编译，但是我们也想在目标文件中包含调试信息，这可以使用 -g 选项。
使用objdump工具，我们指定 -d 参数以反汇编目标文件中的指令。最后，我们可以使用汇编和源码交错的文件列表：
```cpp
gcc -c -g -Wa,-ahl,-L test.c
```
该命令使用GNU汇编器输出列表。-Wa 选项用于 传递 -ahl 和 -L 选项给汇编器，以输出列表到标准输出，列表中包含高级语言源码和汇编代码。-L 选项则会保留符号表中的局部符号信息。

（译者注：比如如下代码
```
#include <stdio.h>

int add(int a, int b) {
  return a + b;
}
```
输出的信息包括如下源码和汇编代码交错出现的片段：
```
   1:test.cc       **** #include <stdio.h>
   2:test.cc       ****
   3:test.cc       **** int add(int a, int b) {
   9                            .loc 1 3 0
  10                            .cfi_startproc
  11 0000 55                    pushq   %rbp
  12                            .cfi_def_cfa_offset 16
  13                            .cfi_offset 6, -16
  14 0001 4889E5                movq    %rsp, %rbp
  15                            .cfi_def_cfa_register 6
  16 0004 897DFC                movl    %edi, -4(%rbp)
  17 0007 8975F8                movl    %esi, -8(%rbp)
   4:test.cc       ****   return a + b;
  18                            .loc 1 4 0
  19 000a 8B45F8                movl    -8(%rbp), %eax
  20 000d 8B55FC                movl    -4(%rbp), %edx
  21 0010 01D0                  addl    %edx, %eax
   5:test.cc       **** }
```
)


## 结论

应用程序都互不相同，所以并不存在神奇的优化配置和选项开关能生成最好的结果。达到较好的性能的最简单方式是使用-O2级别的优化。如果你对可移植性不感兴趣，可以使用 -march= 指定特定的体系架构。对空间受限的应用，应该首先考虑使用-Os 优化级别。如果你一定要将你的程序的性能优化到极致，那你可以考虑尝试不同的优化级别，然后使用不同的工具来检测生成代码的性能。打开或禁用特定的优化，也可以帮助优化器得到最佳性能表现。

## 本文相关资料：
GCC 项目首页:  http://gcc.gnu.org/
GCC 在线文档:  gcc.gnu.org/onlinedocs/gcc-3.2.2/gcc

作者介绍：
M. Tim Jones ([mtj@mtjones.com](mailto:mtj@mtjones.com)) is a senior principal engineer with Emulex Corp. in Longmont, Colorado. In addition to being an embedded firmware engineer, Tim recently finished writing the book  _BSD Sockets Programming from a Multilanguage Perspective_. He has written kernels for communications and research satellites and now develops embedded firmware for networking products.
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTI2Njc4NTYxMSwtMTUzNzA5Mjc5Myw4ND
I0NjM5ODUsMTI1NzE4OTM3NCwxNTE4NDQwNTQwLC0xNTg1NzE5
NzQ4LC0xNjg3MDMzODQ2LDExNDI5NzQzNTksLTYzODYxOTk0NF
19
-->