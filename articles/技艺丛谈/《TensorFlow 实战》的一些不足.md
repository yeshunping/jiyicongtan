最近比较忙，更新很少了。这几天在系统学习机器学习，随手做点笔记，一部分思考放到这里，不成章法，类似随笔吧，有相似学习方向的可以参考下。

《TensorFlow 实战》是国内比较早的有关tf的书籍，花了半天时间通读了一遍，可以说写得还比较简单易懂，可以类比到python版本的《机器学习实战》吧，不过大量的官方代码堆积，也有不少不足之处，列举几个：

1. 代码没重点，堆积代码，经常是各种import , load data, config , reader满篇，毫无价值，且影响阅读进度。这就和写代码缺乏代码复用一样让人痛苦。

2. 缺乏更多的理论梳理，也少一些历史讲解。

3. 缺乏必要的benchmark , 尤其是横向对比，比如RNN LM， 缺乏和Ngram model 的对比。另外，各种MNIST task的model，虽然也有一些零散的对比，不过如果有各种方面的表格形式的对比，会好很多，对比可以从收敛速度，泛化能力，测试集表现，训练时间等维度进行。李航的《统计机器学习》这方面做的不错。

4. 讲解代码前缺乏整体的网络设计思路，假如把各个model对应的Graph 贴出来，阅读代码就容易得多了。因为本书使用的是tf low level api 进行讲解，因此graph 构造的可读性和宏观性较差，不如配置文件或者是keras 直观明白。

5. 本书往往先讲代码细节，再上代码，和程序员的习惯不符，一般先上代码，再讲解代码中的细节会更好。另外，每章的代码分散在讲解中，而没有完整的代码列表，阅读起来效率也低。

6. 缺乏一些模型的改进思路。往往是讲解完官方的example model就结束了，切换到下一个网络结构。

7. 缺乏model deploy ／ tensor serving 章节。

8. 不知道是否是因为写作本书时keras 还不成熟，虽然在第二章中DL框架对比提到了keras, 但是却没有章节开展介绍。而这个对刚接触DL 的人来说，却蛮有帮助的，因为layer的搭建更加直观明了。

9. 配图不少是英文说明，估计是网上找来的，没来记得重新制作／翻译。

10. 未涉及tf lite。

11. 缺乏白皮书解读。

假如写一本深入浅出tf，从keras讲解各种模型和tensor board开始，然后讲各种经典的cnn网络架构，讲分布式训练，模型部署，讲tf源码实现细节，讲各种优化器的演进和差异，讲不同的激活函数的设计思路和benchmark ，我觉得价值会远高于本书。

cnn本书还可以，当然<深度学习>那本书讲得更透彻。rnn我觉得不妨从nb,hmm讲起，延伸到有向和无向概率图模型，顺便再比较下tf crf实现(基于rnn cell)和crf++的异同等。

<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE3Njk0Njk3ODUsMTU0ODg5OTk1M119
-->