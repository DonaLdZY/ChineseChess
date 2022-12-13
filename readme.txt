ChineseChess Coded By DonaLdZY
简介：
是个配有GUI的中国象棋人机对战的项目
python web GUI由 刘聪老师 提供
象棋AI基于min-max搜索算法，v1引入αβ剪枝，v2引入记忆化搜索

依赖环境：
Python3
exe可能依赖某些动态连接库，要适配当前电脑可能需要重新编译

启动方法：
- 在终端中cd到项目目录 例如项目在/Documents/Code/chess，则cd /Documents/Code/chess
- 输入 python -m serv move.exe
- 打开浏览器在地址栏输入 http://localhost

一些注释：
迭代层数设为5层可以在2秒内算出结果
若迭代层数设为6层则需要10~20秒才算出结果
要修改迭代层数，打开chess_engine_v2.cpp,修改MaxDepth常量，然后重新编译move.cpp即可

have fun ! :)







--------------------一下是原本python GUI与参考代码的REDAME----------------
在这个项目里面，你将用c++写一个象棋对弈程序。它配合其余的python界面程序一起运行。
如果你写的程序编译后叫做 move.exe, 那么你需要
- 运行 python3 -m serv move.exe
- 打开浏览器在地址栏输入 http://localhost

当你拖动棋子后，move.exe 将会被调用来帮助python界面程序产生下一步棋。
move.exe 将读入一个描述当前棋盘的文件board.txt, 然后把计算出的下一步棋写到move.txt中。

board.txt的格式如下：每行描述一个棋子，每个棋子由两个字符串和两个整数描述
每行的数据分别是棋子的颜色，种类，和当前的位置 (x,y). 其中 0<=x<9, 0<=y<10

对于初始棋盘，board.txt如下:
Black Bishop 2 9
Black Bishop 6 9
Black Cannon 1 7
Black Cannon 4 7
Black Guard 3 9
Black Guard 5 9
Black King 4 9
Black Knight 1 9
Black Knight 7 9
Black Pawn 0 6
Black Pawn 2 6
Black Pawn 4 6
Black Pawn 6 6
Black Pawn 8 6
Black Rock 0 9
Black Rock 8 9
Red Bishop 2 0
Red Bishop 6 0
Red Cannon 1 2
Red Cannon 7 2
Red Guard 3 0
Red Guard 5 0
Red King 4 0
Red Knight 1 0
Red Knight 7 0
Red Pawn 0 3
Red Pawn 2 3
Red Pawn 4 3
Red Pawn 6 3
Red Pawn 8 3
Red Rock 0 0
Red Rock 8 0

而move.txt里面只有一行。它包括4个整数，由单个空格隔开
如果下一步棋是把在位置(1,0)中的马移动到位置(2,2), 那么move.txt的内容是
1 0 2 2

在项目中已用python3将简单实现了min-max搜索(min_max.py)和alpha-beta搜索(alpha_beta.py),供参考和对比。
项目中文件夹web/py_lib/*.py中的文件你可以阅读并参考(如果你觉得阅读python暂时对你比较困难，也可以不管这些代码)。
文件夹web/py_lib/中，以'_'结尾的文件(如ui_.py)是与界面和其它功能有关的程序，不必阅读。
要尝试运行这些参考的程序，可以使用下面的命令：
python3 -m serv min_max
python3 -m serv alpha_beta
python3 -m serv 'python3 -m web.py_lib.move'
最后一个命令中，web/py_lib/move.py展示了你将写的move.exe中读board.txt和写move.txt的一个示例。

如果你要更改项目中的python代码实现更多功能(一般不建议修改，这个项目的考察的对象是C++编写的算法实现)
- 这个项目里面的python程序是被两个python编译器共享的，它们是你电脑中使用的和一个在览器中使用的简化的python编译器。
- 后者不是标准的python编译器(web/lib/jswrt/readme.txt)，它的报错信息显示在浏览器控制台中。
- 如果两个编译器的其中一个报错，则程序不能运行。
