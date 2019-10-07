常用的对象序列化与反序列化方式，除了使用 XML , Json 外，二进制格式的有 Google 开源的 Protobuf , Facebook 开源的 Thrift 等，当然最广为人知的恐怕是 Java 的对象序列化了。有关各个格式的编码方式，我们在未来再分专文论述。这里引用并翻译 protobuf 官方的文档，说明下为什么有了 XML 等广为使用的互联网对象描述协议，还需要引入 Protobuf 协议。

### 相比 XML 的优势

相比 XML ， Protocol buffers 在序列化结构化数据方面，有很多优势。包括：

-   **更简单**
    
-   **更小**。压缩效率在3到10倍以上
    
-   **更快**。速度在20到100倍以上
    
-   **更少歧义**
    
-   **更易编程**。编译器直接生成相关的数据操作类，编程中可直接使用。
    

  

比如要表示人这个对象，它带有名字和邮件信息。

  

XML格式表示如下：

  

1.  `<person>`
    
2.   `<name>John Doe</name>`
    
3.   `<email>jdoe@example.com</email>`
    
4.  `</person>`
    

protocol buffer 的 IDL 定义如下：

1.  `message Person  {`
    
2.   `required string name =  1;`
    
3.   `optional string email =  2;`
    
4.  `}`
    

protocol buffer 的文本格式如下：

1.  `person {`
    
2.   `name:  "John Doe"`
    
3.   `email:  "jdoe@example.com"`
    
4.  `}`
    

  

而如果使用 protocol buffer 的二进制编码格式，对象大小才 28 字节，耗时大约 100-200 纳秒。相对地，XML 格式表示，至少需要 69 字节（移除掉空格后），解析该对象的时间，至少在 5,000-10,000 纳秒以上。

  

编程中操作 Protobuf 消息非常简单，如下：

  

1.  `cout <<  "Name: "  << person.name()  << endl;`
    
2.  `cout <<  "E-mail: "  << person.email()  << endl;`
    

而操作 XML 的话，则较为繁琐，大概如下：

1.  `cout <<  "Name: "  << person.getElementsByTagName("name")->item(0)->innerText()  << endl;`
    
2.  `cout <<  "E-mail: "  << person.getElementsByTagName("email")->item(0)->innerText()  << endl;`
    

  

**相比XML的劣势**

当然，尺有所短寸有所长，XML 也有自己的优势。

1.  比如对带有标记语言的文本文档（比如 HTML ），protobuf 就不是一个好的建模语言。
    
2.  此外，XML 方便用户阅读，并可直接编辑修改，而 protobuf 则不行，至少它的二进制格式不行（有一些开源的项目，可以直接在浏览器编辑修改 protobuf 对象，并直接发起 RPC 请求。使用 protobuf 提供的反射功能，实现这个并不算太难）。
    
3.  XML文档在某种程度上也是自描述的。而 protobuf 只有在你知道消息定义的时候才有意义，也就是对应的 .proto 文件。
    

  

**Protobuf 示例**

protobuf 目前提供了两个版本的语法支持，包括 proto2 和 proto3。proto3 是新近才支持的，语法更为丰富。后续我们再专文论述 proto3 相比 proto2 带来的改变。

  

以下是一个典型的 protobuf 文件，大家可以注意到，这里使用了 syntax 关键字，使用到了required, optional , repeated 等不同的修饰符，使用到了 string ,int32, enum, 嵌套消息等不同的数据类型。

  

source file : address.proto

1.  `syntax =  "proto2";`
    

3.  `package tutorial;`
    

5.  `message Person  {`
    
6.   `required string name =  1;`
    
7.   `required int32 id =  2;`
    
8.   `optional string email =  3;`
    

10.   `enum  PhoneType  {`
    
11.   `MOBILE =  0;`
    
12.   `HOME =  1;`
    
13.   `WORK =  2;`
    
14.   `}`
    

16.   `message PhoneNumber  {`
    
17.   `required string number =  1;`
    
18.   `optional PhoneType type =  2  [default  = HOME];`
    
19.   `}`
    

21.   `repeated PhoneNumber phones =  4;`
    
22.  `}`
    

24.  `message AddressBook  {`
    
25.   `repeated Person people =  1;`
    
26.  `}`
    

使用 protoc 工具，也就是 protobuf IDL 语言的编译器，编译 address.proto 文件，会得到 address.pb.h 和 address.pb.cc 两个文件。（这里指的是 C++ 语言。protoc 也可以输出各种不同的语言文件，包括 Java , PHP, Python, Go 等主流语言。）当然，在编程中，我们一般使用 bazel 编译工具，配合 proto_library 编译出不同的语言文件。以下是 Person 消息对应的几个接口。

1.   `// name`
    
2.   `inline  bool has_name()  const;`
    
3.   `inline  void clear_name();`
    
4.   `inline  const  ::std::string& name()  const;`
    
5.   `inline  void set_name(const  ::std::string& value);`
    
6.   `inline  void set_name(const  char* value);`
    
7.   `inline  ::std::string* mutable_name();`
    
8.  

10.   `// id`
    
11.   `inline  bool has_id()  const;`
    
12.   `inline  void clear_id();`
    
13.   `inline  int32_t id()  const;`
    
14.   `inline  void set_id(int32_t value);`
    
15.  

17.   `// email`
    
18.   `inline  bool has_email()  const;`
    
19.   `inline  void clear_email();`
    
20.   `inline  const  ::std::string& email()  const;`
    
21.   `inline  void set_email(const  ::std::string& value);`
    
22.   `inline  void set_email(const  char* value);`
    
23.   `inline  ::std::string* mutable_email();`
    
24.  

26.   `// phones`
    
27.   `inline  int phones_size()  const;`
    
28.   `inline  void clear_phones();`
    
29.   `inline  const  ::google::protobuf::RepeatedPtrField<  ::tutorial::Person_PhoneNumber  >& phones()  const;`
    
30.   `inline  ::google::protobuf::RepeatedPtrField<  ::tutorial::Person_PhoneNumber  >* mutable_phones();`
    
31.   `inline  const  ::tutorial::Person_PhoneNumber& phones(int index)  const;`
    
32.   `inline  ::tutorial::Person_PhoneNumber* mutable_phones(int index);`
    
33.   `inline  ::tutorial::Person_PhoneNumber* add_phones();`
    

以下代码示范了下如何使用生成的接口，直接操作 Person 对象。可以看到，相比 XML writer , protobuf 的对象读写更为方便。

1.  `Person person;`
    
2.  `person.set_name("John Doe");`
    
3.  `person.set_id(1234);`
    
4.  `person.set_email("jdoe@example.com");`
    
5.  `fstream output("myfile", ios::out | ios::binary);`
    
6.  `person.SerializeToOstream(&output);`
    

而对象的反序列化也很简单，示例代码如下：  

1.  `Person john;`
    
      
    
2.  `fstream input(argv[1], ios::in  | ios::binary);`
    
3.  `john.ParseFromIstream(&input);`
    
4.  `id = john.id();`
    
5.  `name = john.name();`
    
6.  `email = john.email();`
    

当然，在代码中，我们一般会封装一个函数，比如 ReadTextFileToProto。值得一提的是，项目的配置文件，使用 protobuf 的文本格式来表示，也非常方便，我呆过的很多团队，就经常使用 protobuf 的文本格式来存储项目配置信息，可读性高，编辑方便，解析和访问方便。

本文大概介绍了 protobuf 的 IDL 基础，生成的接口，如何使用 protobuf 进行对象的构造，对象的序列化与反序列化。同时简单比较了 protobuf 与 XML 的优劣势。在后续文章中，我们将深入介绍 protobuf 的消息编码算法，揭秘为什么其序列化后的对象比 XML 更小，编码效率更高。在后续文章中，也会将其与 Facebook Thrift 的消息编码格式进行对比。欢迎大家关注「技艺丛谈」公众号，阅读后续分享。

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTMzMDk4ODM4NV19
-->