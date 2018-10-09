# How to setup env for batch online test

- 从以下文档中选择一个模型链接。目前除了CNS 模型是CLG，其它都是HCLG。
https://docs.google.com/spreadsheets/d/1A1Jzluo5QuNBkrf0P1wghhIdgRWGLA9rcE1J5q6__gM
- 选择模型后，下载该模型，比如 选择 VPA 的一个模型
  wget http://mobvoi-oss/v1/ufile/mobvoi-speech-private/mobvoi-recognizer-server/ticwatch/2018-05-18-ticwatch-release_updateITN.tar.bz2
- 解压模型， "tar -xvf modelname". 比如
- 
- 创建软链接 model 到下载后的模型目录。比如
  ln -sf 
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTUwMjExOTk4NSwtMTE1MTg1MTU3OF19
-->