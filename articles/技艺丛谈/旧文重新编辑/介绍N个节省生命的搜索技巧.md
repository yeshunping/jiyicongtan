时间就是金钱，效率就是生命。掌握一些有价值的搜索技巧，可以帮你的工作效率更高，网络生活更高效便捷。  

搜索引擎是大家日常工作生活中用来解决疑问的工具，所谓“百度一下，你就知道”，有什么问题，百度一下，几乎已经成为了中国网民的习惯性动作。除了百度，国内常用的搜索引擎还有搜狗，360的好搜，当然前几天还有网易有道，人民搜索，盘古搜索，腾讯搜搜等。微信里目前虽然还不是全网搜索，不过前段时间推出的“搜一搜”，也基本能满足日常的阅读类搜索了。

下面就先来给大家介绍下平时使用搜索引擎的一些技巧。

## 高级搜索指令

先放一个表格，比较下百度和谷歌对以下提到的几个搜索指令的支持。  

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIpRdokIC95zfx0lSKhfWwViaSUlZN6vwnGqLfp1a4qYrR1pJIcrpdRuA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 如何使用网页版高级搜索技巧？

这个很简单，谷歌和百度都提供了高级搜索的页面，可以点击进去直接搜索。

进入方法如下：
谷歌：
首页右下侧，点击“设置”，然后点击“高级搜索”，就进入高级搜索页面啦。
页面的网址为：
https://www.google.com.hk/advanced_search
页面如下：

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oId3qqjI2g1s5WYYa8ZmtoDsn0FdHhexxphcZkQ9cDSEr9dTTbrIbglA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

接下来看百度：
按照“首页 -> 设置 -> 高级搜索”的步骤，就可以接入到百度的高级搜索页面啦啦，页面效果如下：

![](data:image/gif;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAADUlEQVQImWNgYGBgAAAABQABh6FO1AAAAABJRU5ErkJggg==)

当然，对于有经验的人来说，直接在输入框中输入对应的指令，效率更高。因此下面我们分别介绍一下，希望读者在掌握这些命令后，能提高搜索效率，将节省下来的时候花在更有意义的事情上。

## 文档格式  

我们在搜索的时候，希望能够找到对应的文档类型。比如找论文的时候，很多时候我们希望直接搜索到pdf格式的论文本身，而不是和论文相关的一些网页。这种场景，使用文档格式的相关指令就很方便了。

比如，你可以使用常规的搜索词，配合以下指令

> **filetype:pdf**
> **filetype:doc**
> **filetype:ppt**
> **filetype:xls**

去搜索pdf,doc,ppt,xls等不同的文档。

**有图有真相：**

举个例子，假设我们想要找和公安部相关的PDF文件，可以这么搜索

“公安部 filetype:pdf”

以下是搜索结果的截图，可以看到，搜到的都是pdf文件，而不是普通的网页。

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIfPH3vkf6ia95JBdWOWuht7jBMibBMTM5eFSFUAyJdZbosg8TXllcAg2Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)  

### 关键词位置

搜索的时候，我们有时候希望目前关键词出现中标题中，或者是出现在URL中，或者是出现在锚文本中。使用以下命令，可以得到这个效果。

> intitle:出门问问
> inurl:about
> inanchor: 出门问问

释义：

intitle: 所有的关键词出现在标题中。一般网页是一个html, 标题放在<title>这个标签中。标题一般是网页的核心信息。假如我们只想找标题中含有某个词的网页，就可以在查询词前加上"intitle:"这个指令。

inurl: URL 就是网页的链接。比如百度的链接为
http://www.baidu.com/

如果搜索 "inurl:baidu",将会找到在URL中包括“baidu”这个词的所有网页。网页正文和标题倒是不一定会出现"baidu"。

inanchor: 比如百度的首页，一般不会出现“搜索引擎”。但是我们找到“搜索引擎”的时候，百度一般都出现在结果中。这个就是因为有大量指向百度首页的anchor 包含“搜索引擎”这些词汇。anchor 就是锚文本的意思。比如“[C++基础库](http://mp.weixin.qq.com/s?__biz=MzI3NzE1NDcyNQ==&mid=2247483802&idx=1&sn=3b8f0f1716eb3f72f766b02931a03fc4&chksm=eb6bdf50dc1c5646fc9d0cdecaca8d03fcb1a9e0e04ed2051beb259e3db6bd2e88da8ef1ec9f&scene=21#wechat_redirect)”，这里的“C++基础库”就是锚文本，用于描述目标网页的内容。一般会取目标网页的标题，或者是一些描述能力强的摘要信息。锚文本指向的链接，就是link了。微信近期放开了公众号内的链接，我这里举的例子，指向的就是我之前写的《不要再重复造轮子了，造牢固的地基吧》那篇文章的地址。

**有图有真相：**

搜索：“intitle:出门问问”，会搜索出来网页标题里，包含出门问问的所有网页。结果如下图：

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIBA92j0W8VjficJCllLVHdgCsPJ7vO9S3QtXyvBMkFYyXHOF92CjXawQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 站内搜索

有时候我们希望搜某个特定网站的内容。比如你自己开了一个博客，你希望搜索一下百度上索引了你博客的多少文章，你就可以使用站内搜索这个功能啦。

当然，前几年很多人通过这个技能，找一些网盘资源等，也算是活学活用。

你浏览某个论坛，但是非会员无法使用搜索功能，或者是搜索一次就被禁用一分钟，很不爽怎么办？这时候也是这个技能发挥作用的时候。当然网页搜索的爬虫并非万能的，有时候目标网站，百度或者谷歌爬虫收录也不是很全就是了。

**有图有真相：**

示例：搜索出门问问投资的相关文章，仅搜索bbs.ticwear.com 这个网站。

query :  “投资 site:bbs.ticwear.com”

搜索结果如下图，可以看到搜索到的网页，都是bbs.ticwear.com这个论坛上的。

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIyQ19KPyNjeCg0hickFkFDNI84z5YxMSDstiaKgkLIDs5wZdRVjWAIzLw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)


再举个例子，最近人工智能这么火，我想看看36kr这个网站上有关人工智能的相关文章，涨涨知识。

该怎么办？ 看下图吧。

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIiceWRhDXbGcMUjqKv2ZUIt9R59UDMoBby6hHtt0OpDhk2WHhS40w38Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### 关键词信息

一般我们搜索的时候，想到几次词，都是几个词放在一起搜索。比如我们想找一些和公安部培训相关的网页，我们一般搜索  公安部培训  这几个字。搜索结果如下图所示：

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIhtKPfWWFRs8AAKjNpbiacKWKKIQfguFZ2VeRApL9hdgEsHjdQAqDPHQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

可以看到，搜索结果中，公安部 和 培训 两个词不一定都挨在一起。如果我们想找到“公安部”和“培训”两个词挨在一起，怎么办呢？

这个时候，可以使用引号，将两个词放在引号中，query :  “公安部培训”  

搜索结果如下图，可以看到，搜索到的网页，公安部和培训两个字都是挨在一起的。

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIlSv8vyibZUoslEW1r8tfdAVISbpC5ibQywaYod9WAP6PG0XQ15Zozgag/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

有时候，我们搜索一些词，只是希望几个词命中了其中一个就可以，应该怎么办呢？这时候可以使用 OR 这个指令，注释需要全部大写。另外，百度的查询方式不太一样，需要使用括号括起来。  

**有图有真相：**

> query : 
> 谷歌：树木 OR 种子 OR 草 
> 百度：(树木种子草)

搜索结果如下图，可以看到有一些结果包含树木，有一些结果包含草，有一些结果包含两个到三个关键词

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIH7BsVbsxKNDdbuUEYlPgwibtuL3ZNyzQkmtTwGR0HLib9pPTcA79gwjw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)


如果我们搜索某个词的时候，经常出现相关的另一个词，但是这不是我们想要的，这个时候在不需要的字词前添加一个减号，就可以过滤掉不包含该词的结果啦。

**有图有真相**：

query： 搜索引擎，结果中会出现不少和谷歌有关的网页。
query：  搜索引擎 -谷歌，搜索结果中，有关谷歌的网页会被过滤掉。

如下图，搜索“搜索引擎”，第三条和第五条包含谷歌这个关键词

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oI5UOv4vOYKY9UdbE1OQnDGBw8EtkbXJ79XTQK2nLwtKkuTskGAfDoPg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

接着，我们搜索“搜索引擎 -谷歌”，搜索结果中都不包括“谷歌”这个关键词。结果如下图：

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oI31esHdgrweLrqvlYenewwYaoxG54IQZvnZu06I5NMrFvEOwZlJAkRg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

### cache指令 

有时候一个网页暂时挂了，成为死链了，你又想看，怎么办？可以使用cache指令，查看搜索引擎的缓存。（百度的话，搜索结果中，有“百度快照”这个链接，点击即可访问）

**有图有真相：**

搜索"cache:www.sohu.com"，谷歌会直接重定向到缓存页面，并显示是什么时候的快照。截图如下：


![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIomW1OYwZl9ib3qWicDSHPbSl2ADNMbpmXFzfKrh1YtPdYkLMh8wbNueg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

  

info指令  

  

Google还提供了 info指令，其会显示和快照，相似网页，指向某个网页的网页，包含全部关键词的网页等几个链接。

比如我们搜索"info:youku.com"，出来的结果中，会包含四个链接信息。点击的话，分别相当于

cache:youku.com

related:youku.com

site:youku.com  

"youku.com"

这四个搜索。

  

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIsUvsQneee8vG732sjib358XNAqtQ57BPL1VAegHyTRNgHlblhZAFgmA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

其中几个上面都有所介绍。相似网页我这里介绍下。我们发现某个网站比较好玩，想要找相似的网站，就可以使用这个功能了。比如找和花瓣之类的看图网站类似的网站。

  

下面我们使用“related:youku.com”，搜索下和优酷相似的网站有哪些？如下图所示，我们可以很方便地找到土豆，爱奇艺，百度视频，凤凰视频，腾讯视频，搜狐视频等相似网站。

  

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIaSj4cxvwWwr6ibI6XJUY6VzOoGXO7vIrB1ngVa8bAL7Gk05yIkL0rNg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

  

限制网页的最后更新时间

  

这个没有对应的指令，只能在网页界面中选择。比如要找一天内的有关刘德华的新网页，可以如下图选择“一天内”，然后点击搜索。

  

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oILBh4ZLLfD9f7mvkFRwLqmY8GZiau9KmDXXMSxwFQtUNIsEWODIWAS6A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)  

  

搜索出来的网页，我们可以从摘要信息中看到，都是一天内的。

  

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oIoRctedAaZibjIbHCuJgbmybLxbDyptLgfwv6JGQGW3WgGPYnQsfuQfQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)  

  

一页显示更多的搜索结果数

  

有时候我们在搜索某个资料，需要经常翻页，不够高效，怎么办呢？这个时候可以在搜索设置中，将每页搜索结果数调整到20条设置50条等。

  

![](http://mmbiz.qpic.cn/mmbiz_png/qX2ED6UwyKGzZvp4XK8pnLiadYuuA03oI6aV9lnNJBfINrjtecGqkgvfDFO9RCr3GAz6ukNk6ibzs9RDAH39xqqg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

  

举一些需要翻页的场景：搜索你感兴趣的论文，搜索你感兴趣的人物资料。

  

程序员写爬虫，抓取百度等搜索结果页，也可以考虑调整这个对应的URL参数，一次性抓取更多的搜索结果。

  

搜索经验

  

介绍了这么多搜索指令，有时候没有谷歌也是白搭。最后再附上一些搜索经验，作为补充。

  

-   技术搜索最好能访问谷歌。
    
-   学会挑选搜索关键词，尝试变换关键词。比如少一个词，多一个词，换个说法，换个同义词，换个别名，换个英文名等。
    
-   技术问题可以使用"site:"指令，搜索下stackoverflow.com这个网站上的问答。
    
-   不知道怎么使用谷歌，搜索下“VPN”相关网页。
    
-   学好英文。一些问题，能用英文搜就不要用中文。
    
-   英文不好也没问题，使用下谷歌翻译，翻译为英文单词，再使用英文搜索。  
    
-   谷歌无法使用，那就试试必应吧。
    
-   尝试使用谷歌或百度的高级搜索框的各个输入框，熟能生巧。
    
-   英文网页看不懂，可以试试谷歌翻译插件。
    
-   程序员编译错误不知道怎么解决，把编译错误在谷歌搜索下。如果编译错误是中文的，那么先调为中文的，不知道怎么调的，先搜索下。
    
-   专业领域，了解下有没有更专业的垂直搜索。比如搜视频种子，最好使用种子搜索。当然搜索种子搜索网站，可以使用通用搜索。
    
-   花半小时搜索免费资源，有时候不如花钱买个会员。时间就是金钱，省时间就是省钱，省生命。
    

  

大家有什么其他的搜索技巧需要了解，或者分享的，欢迎留言交流。

<!--stackedit_data:
eyJoaXN0b3J5IjpbNzUwNjQ3NTU0XX0=
-->