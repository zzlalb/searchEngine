# save source files(*.cpp/*.cc)

## to generate dict index(dictIndex.dat)
### use g++ testCreateIndex.cc SplitToolCppJieba.cc Configuration.cc DictProducer.cc

## to generate webpaglib(newripeage.dat) and offsetlib(newoffset.dat)
### all of them will be removed of redunctant part
### use g++ testCreateWebPageLib.cc Configuration.cc WebPage.cc tinyxml2.cc PageLibPreprocessor.cc -g


## to generate invertindexLib(invertIndex.dat)
### all of web pages were cleaned
### use g++ testCreateInvertIndex.cc Configuration.cc InvertIndexBuilder.cc -g


## To test Dictionary(single ton class)
### use g++ testDictionary.cc Dictionary.cc

## 
###
### g++ Acceptor.cc InetAddress.cc TaskQueue.cc TestEchoServer.cc EchoServer.cc Socket.cc TcpConnection.cc ThreadPool.cc EventLoop.cc SocketIO.cc TcpServer.cc Dictionary.cc SplitToolCppJieba.cc -g