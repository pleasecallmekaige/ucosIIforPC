## 环境:
minGW  
(MinGW安装目录\mingw64\bin 下的x86_64-w64-mingw32-make 重命名为 make)  
cmake >= 3.7.2  
Git >= 2.20

## 运行
更改makefile文件中的第四行
MinGWPath = D:/App/MinGW
把这的路径改为自己的安装路径

在git的bash命令行窗口下（安装好git后，在这个工程的目录下右键鼠标，然后点击Git Bush Here）
运行
$ make all
目录下生成可执行文件uCOSII.exe