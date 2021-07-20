>该项目是嵌入式课程实训内容

<font size=3>**==项目源码==:**</font>[https://download.csdn.net/download/weixin_43624626/20368957](https://download.csdn.net/download/weixin_43624626/20368957)
其中QT界面不是自己写的，当时实训时间有限，老师直接给的一个打包好的Qt实现的界面，在实训中主要完成的是服务端的实现。
@[TOC](目录)
# 1实训准备
## 1.1硬件资源
### 1.1.1智能家居终端
所提供的FS_11C14开发板，基于NXP LPC11C14微控制器(ARM Cortex-M0 内核)，如下图1.1所示。集成多种传感器、RFID、ZigBee、OLED 显示模块等。该平台有丰富的硬件资源及物联网相关实验程序，适合于物联网教学及工程师作为研发参考平台。还配套有开放的FS_CoLink仿真器，使用者可以在不另外配置仿真器的情况下进入开发。为使用者提供了一个简洁方便可以快速上手的良好开发环境，可以为应用开发节省时间，提高效率。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221709678.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

模拟智能家居终端，使用 cortex-M0 处理器，带有重力、光照、温度 等多种传感器，负责家庭环境信息采集。
### 1.1.2 ZigBee 模块简介
FS_CC2530 ZigBee 模块采用的是 Ti 公司 CC2530 模块。带有USB转串口芯片，可以方便的连接 PC 机或其它带有 USB 主机接口的设备，从而实现和 FS_11C14 组网通讯。FS_CC2530 模块的扩展资源包含电位器、按键中断、LED 灯等外设。
### 1.1.3 ZigBee协调器
Zigbee 协调器（如图1.2），负责采集终端和 FS4412 数据透传，协调器采用 USB 延长线连接到 FS4412，最终数据通过 Zigbee 传给 FS4412。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221640446.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

## 1.2 软件资源
### 1.2.1 Linux操作系统
本次实训会有服务端的实现，服务端一般会在Linux操作系统上实现，并部署在上面。为了服务端代码编写和调试的相对方便，这里选择了VMware虚拟机下的Ubantu操作系统。
Ubantu是一个以桌面应用为主的Linux操作系统，并且Ubantu是一个开源、免费的系统版本之一。服务器之间的Linux使用率是非常高的，全球大多数的web服务器就是基于Linux系统运行的。尽管Windows和mac之类的操作系统比Linux更为流行，但是Linux依然普及率很高。

Linux系统有如下的优势：
- 跨平台的硬件支持。
- 丰富的软件支
- 多用户多任务
- 可靠的安全性
- 良好的稳定性
- 完善的网络功能
### 1.2.2 Qt软件
本次实训客户端需要以图形界面的形式来操作，所以选择通过Qt来实现客户端界面和相关逻辑。Qt是由跨平台C++ 图形用户界面应用程序开发框架，它既可以开发GUI程序，也可用于开发非GUI程序，比如控制台工具和服务器。Qt是面向对象的框架，使用特殊的代码生成扩展以及一些宏，Qt很容易扩展，并且允许真正地组件编程。

# 2 实训原理
## 2.1整体框架分析
### 2.1.1整体框架图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221616468.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

### 2.1.2项目流程图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221544598.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

# 3 实训目的
在本次实训中需要设计并实现一个智能家居控制系统，主要包括服务端设计和客户端的设计。用户将客户端和服务端连接之后，用户可以在客户端界面收到通过M0板上传感器所传来的实时数据，有温度、湿度、和光照；用户还可以在客户端界面通过点击对应的家居控制按钮来控制对应的家居设备，当然在实训中的“家居设备”是M0板上的一些灯、蜂鸣器、风扇等电子元器件。
# 4 实训方案
对于整个实训，服务端采用Linux下的C语言编写，客户端采用Qt实现图形界面。智能家居通过STM32f051arm处理器（arm处理器）的M0板进行实时采集环境参数，例如温度、湿度、光感等数据；再通过ZigBee无线通信把采集到的环境参数或物品信息发送给ZigBee协调器，然后通过串口将数据传到linux服务端，由M0线程负责接收环境参数或物品信息，激活数据库线程对数据库进行相应的处理，通过socket通信将数据进一步传送到客户端，在客户端以图形化界面显示采集到的实时数据。M0板上的风扇、LED等“家居设备”可以通过客户端发送控制命令，对命令进行封装，然后将封装好的命令通过socket传输到服务端，在服务端通过ZigBee无线通信传输到M0板，进而对M0板上的风扇、LED等“家居设备”进行远程智能控制。
# 5实训内容
## 5.1基础学习
老师先带领我们学习了一些完成项目所必须的基础知识。
### 5.1.1系统调用和库函数
1、系统调用是通向操作系统本身的接口，是面向底层硬件的。通过系统调用，可以使得用户态运行的进程与硬件设备(如CPU、磁盘、打印机等)进行交互，是操作系统留给应用程序的一个接口。用户进程需要发生系统调用时，内核将调用内核相关函数来实现。用户程序不能直接调用这些函数，这些函数运行在内核态，CPU通过软中断切换到内核态开始执行内核系统调用函数。
2、库函数可以理解为是对系统调用的一层封装，是为了实现某种功能封装起来的API集合，提供统一的编程接口，便于应用程序移植。系统调用作为内核提供给用户程序的接口，它的执行效率是比较高效而精简的，但有时我们需要对获取的信息进行更复杂的处理，或更人性化的需要，我们把这些处理过程封装成一个函数再提供给程序员，更方便于程序员编码。
库函数和系统调用的关系如下图5.1所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221428655.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

### 5.1.2文件I/O
文件I/O以系统调用为基础，由posix(可移植操作系统接口)提供的一组用来输入输出的接口，操作核心是文件描述符。其中文每个打开的文件都有一个对应的文件描述符，文件描述符是非负整数，文件描述符从0开始分配，依次递增，默认打开三个描述符，分别是0、1、2，它们对应标准输入、标准输出和标准错误。
对应有函数有open()、close()、read()、write()等。
### 5.1.3标准IO
标准IO是由C库中提供的一组专门用来输入输出的函数。操作核心是FILE(文件流指针)，每个被使用的文件都在内存中开辟一个区域，用来存放文件的相关信息。
相关的函数有fopen()、flose()、fgetc()、fputc()、fgets()、fputs()、fread（）、fwrite()、fseek()、fftell()等。
标准IO缓存方式有全缓冲、行缓冲和无缓冲这三种方式。刷新条件有三种，分别是程序正常退出，缓存区刷满，遇到换行符‘\n’。
练习1，计算行缓存区大小，代码截图如下图5.2所示：
通过运行代码观察输出可以得出缓存区的大小为1024字节。
练习2，用fgetc()和fputc()实现linux中cat命令的功能，代码如下图5.3所示：
练习3，用fgets()实现wc -l的功能，代码如下图5.4所示：
练习4：用fgets和fputs实现cp的功能，代码如下图5.5所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221403424.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

### 5.1.4 TCP建立过程
首先 Client 端发送连接请求报文，Server 段接受连接后回复 ACK 报文，并为这次连接分配资源。Client 端接收到 ACK 报文后也向 Server 段发生 ACK 报文，并分配资源，这样 TCP 连接就建立了。
TCP三次握手，如图5.6所示：
- client-->server：第一次握手，建立连接时，客户端发送syn包（seq=j）到服务器，并进入SYN_SENT状态，等待服务器确认；SYN：同步序列编号。
- server-->client：第二次握手，服务器收到syn包，必须确认客户端的SYN（ack=j+1）同时自己也发送一个SYN包（seq=k），即SYN+ACK包，此时服务器进入SYN_RECV状态。
- client-->server：第三次握手，客户端收到服务器的SYN+ACK包，向服务器发送确认包ACK (ack=k+1)，此包发送完毕，客户端和服务器进入ESTABLISHED（TCP连接成功）状态，完成三次握手。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221334854.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)

### 5.1.5 TCP的C/S架构
**1、Server端配置：**
socket()产生用于建立连接的套接字-->bind()：绑定IP和端口-->listen（）监听，化主动为被动-->accept()：接受客户端连接请求，产生用于通信的套接字-->recv()/send()：数据收发-->close()：关闭套接字。
**2、client端配置：**
socket()：产生一个套接字用于建立连接和通信-->connect()：向服务器发送连接请求，建立连接-->recv()/send()：数据收发-->close()：关闭文件描述符。
### 5.1.6服务器模型
服务器模型可以分为循环服务器和并发服务器。循环服务器：当一个客户端退出后服务器可以继续接收下一个客户端的连接；并发服务器：一个服务器可以同时和多个客户端进行数据收发。
其中并发服务器又可以分为多进程并发、多线程并发和IO多路复用。
## 5.2 项目实现过程
在这次实训中我主要负责的是整个项目完成的最后一步——调试测试工作。由于实训时间限制，Qt客户端来不及完成，使用的是老师提供的一个Qt实现的客户端，我们完成的部分就是除了客户端之外的服务端。首先看一下整个项目的服务端代码结构，如下图5.7所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719220914669.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)
其中的Makefile文件是整个项目文件的编译链接规则，编写好这个文件并添加到工程文件夹中后只需在终端输入一个make命令就可以对整个项目文件进行编译并生成一个可执行文件。Makefile文件里面的内容如下图5.8所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221015824.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)
编译main.c，如图5.9所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221038756.png)
运行main.c，如图5.10所示，显示没有客户端的连接，接下来等待客户端的链接：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221101642.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)
打开客户端，如图5.11和5.12所示设置好IP和端口后，回到登录界面设置账号和密码，如图5.14点击“登录”：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021071922112878.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)
点击登录按钮后，如图5.13所示，可以立即在终端看到连接成功的提示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021071922115331.png)
在“主页”可看到M0板返回的实时数据，数据以折线图实时展示，返回的数据有温度、湿度和光照，如图5.15、5.16、5.17所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221223832.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)
接下来进入控制台界面，测试对应的按钮是否有效。这里展示了两个按钮的测试情况，如图5.18点击“卧室灯开”按钮，图5.20显示了终端所受到的控制命令；如图5.19点击“卧室灯开”按钮，图5.21显示了终端所受到的控制命令。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221244392.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYyNDYyNg==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210719221258452.png)
