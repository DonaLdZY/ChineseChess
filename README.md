ChineseChess Coded By DonaLdZY<br>
简介：<br>
是个配有GUI的中国象棋人机对战的项目<br>
python web GUI由 刘聪老师 提供<br>
象棋AI基于min-max搜索算法，v1引入αβ剪枝，v2引入记忆化搜索<br>
<br>
依赖环境：<br>
Python3<br>
exe可能依赖某些动态连接库，要适配当前电脑可能需要重新编译<br>
<br>
启动方法：<br>
- 在终端中cd到项目目录 例如项目在/Documents/Code/chess，则cd /Documents/Code/chess<br>
- 输入 python -m serv move.exe<br>
- 打开浏览器在地址栏输入 http://localhost<br>
<br>
一些注释：<br>
迭代层数设为5层可以在2秒内算出结果<br>
若迭代层数设为6层则需要10~20秒才算出结果<br>
要修改迭代层数，打开chess_engine_vX.cpp,修改MaxDepth常量即可<br>
<br>
have fun ! :)<br>
