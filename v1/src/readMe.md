# save source files(*.cpp/*.cc)

## to generate webpaglib(newripeage.dat) and offsetlib(newoffset.dat)
### all of them will be removed of redunctant part
### use g++ testCreateWebPageLib.cc Configuration.cc WebPage.cc tinyxml2.cc PageLibPreprocessor.cc -g


## to generate invertindexLib(invertIndex.dat)
### all of web pages were cleaned
### use g++ testCreateInvertIndex.cc Configuration.cc InvertIndexBuilder.cc -g