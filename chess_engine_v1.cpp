//Coded by DonaLdZY
#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
using namespace std;
const int MaxDepth=5;
const int INF=32767;

//红方 王2 士4 相6 马8 车10 炮12 兵14
//黑方 将3 仕5 象7 马9 车11 炮13 卒15
//type=t/2  player=t&1

//棋子评分权重
const int score[16]={0,0,1000,-1000,3,-3,3,-3,9,-9,20,-20,14,-14,2,-2};
//额外评分
//[棋子编号,x左范围,x右范围,y下范围,y上范围,额外分]
const int exscoresize=6;
const int exscore[exscoresize][6]={
    {14,0,8,5,9,1}, //过河兵
    {15,0,8,0,4,-1}, 
    {14,4,4,3,3,3}, //中兵
    {15,4,4,6,6,-3},
    {12,4,4,2,9,1}, //中炮
    {13,4,4,0,7,-1}
};
//方向标
const int f1[4][2]={{0,-1},{-1,0},{1,0},{0,1}};//上下左右
const int f2[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};//斜方向
const int f3[8][2]={{1,-2},{-1,-2},{-2,1},{-2,-1},{2,1},{2,-1},{-1,2},{1,2}};//马、马脚=f1[x/2]

inline bool inrange(int x,int z,int y){
    return z<=x&&x<=y;
}
//尝试更新最优走法
inline void updates(int score,int &ans,int (&bm)[4],int x,int y,int xi,int yi){
    if (score>ans){
        ans=score;
        bm[0]=x;
        bm[1]=y;
        bm[2]=xi;
        bm[3]=yi;
    }
}
class board{
  private:
    //棋盘本体
    int g[9][10];
  public:
    //构造函数
    board(){memset(g,0,sizeof(g));}
    //输出棋盘，用于调试
    void print();
    //插入数据
    void insert(string rb,string ctype,int x,int y);
    //行动之后的新棋盘
    board move(int x1,int y1,int x2,int y2);
    //换回合,棋盘反转
    board rotate();
    //当前局面其实已输
    bool lose(){
        for (int i=3;i<=5;i++)
        for (int j=0;j<=2;j++){
            if (g[i][j]==2) return 0;
        }
        return 1;
    }
    //当前局面其实已赢
    bool win(){
        for (int i=3;i<=5;i++)
        for (int j=7;j<=9;j++){
            if (g[i][j]==3) return 0;
        }
        return 1;
    }
    //对当前局面评分
    int judge();
    //位置x,y的必要条件:为空或对方棋子
    bool can_move(int x,int y){
        return g[x][y]==0||(g[x][y]&1==1);
    }
    //返回对于当前局面最优走法bm,迭代层数，αβ剪枝参数
    int solve(int (&bm)[4],int c,int worst);
};
//输出棋盘，用于调试
void board::print(){
    puts("------------------------");
    for (int i=9;i>=0;i--){
        for (int j=0;j<=8;j++)
            printf("%3d",g[j][i]);
        putchar('\n');
    }
    puts("------------------------");
}
//插入数据
void board::insert(string rb,string ctype,int x,int y){
    int &t=g[x][y];
    if (rb[0]=='R'){
        if (ctype=="King") t=2;
        else if (ctype=="Guard") t=4;
        else if (ctype=="Bishop") t=6;
        else if (ctype=="Knight") t=8;
        else if (ctype=="Rock") t=10;
        else if (ctype=="Cannon") t=12;
        else if (ctype=="Pawn") t=14;
    }
    else{
        if (ctype=="King") t=3;
        else if (ctype=="Guard") t=5;
        else if (ctype=="Bishop") t=7;
        else if (ctype=="Knight") t=9;
        else if (ctype=="Rock") t=11;
        else if (ctype=="Cannon") t=13;
        else if (ctype=="Pawn") t=15;
    }
}
//对当前局面评分
int board::judge(){ 
    int ans=0;
    for (int i=0;i<9;i++)
    for (int j=0;j<10;j++){
        ans+=score[g[i][j]]; 
        for (int k=0;k<exscoresize;k++)
            if (inrange(i,exscore[k][1],exscore[k][2])&&inrange(j,exscore[k][3],exscore[k][4])&&g[i][j]==exscore[k][0])
                ans+=exscore[k][5];
    }
    return ans;
}
//行动之后的新棋盘
board board::move(int x1,int y1,int x2,int y2){
    board x=*this;
    x.g[x2][y2]=x.g[x1][y1];
    x.g[x1][y1]=0;
    return x;
}
 //换回合,棋盘反转
board board::rotate(){
    board x;
    for (int i=0;i<9;i++)
    for (int j=0;j<10;j++){
        x.g[i][j]=g[8-i][9-j];
        if (x.g[i][j]>0) x.g[i][j]^=1;
    }
    return x;
}
//返回对于当前局面最优走法bm,迭代层数，αβ剪枝参数
int board::solve(int (&bm)[4],int c=MaxDepth,int worst=3*INF){ 
    //胜利//败北//搜索到底
    if (win()) return INF;
    if (lose()) return -INF;
    if (c==0) return judge();
    int outsiders[4]; //占位置的
    int ans=-2*INF; //当前最优分数
    for (int x=0;x<=8;x++)
    for (int y=0;y<=9;y++)
    if (g[x][y]>=2&&g[x][y]%2==0){ 
        switch (g[x][y]){
            case 2: //王
                for (int i=0;i<=3;i++){
                    int xi=x+f1[i][0],yi=y+f1[i][1];
                    if (inrange(xi,3,5)&&inrange(yi,0,2)&&can_move(xi,yi)){
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans; 
                    }
                }
                //飞将
                { 
                    int xi=x,yi=y+1;
                    while (inrange(xi,0,8)&&inrange(yi,0,9)&&g[xi][yi]==0){
                        yi++;
                    }
                    if (inrange(xi,0,8)&&inrange(yi,0,9)&&g[xi][yi]==3){
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                }
                break;
            case 4: //士
                for (int i=0;i<=3;i++){
                    int xi=x+f2[i][0],yi=y+f2[i][1];
                    if (inrange(xi,3,5)&&inrange(yi,0,2)&&can_move(xi,yi)){
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                }
                break;
            case 6: //象
                for (int i=0;i<=3;i++){
                    int xi=x+2*f2[i][0],yi=y+2*f2[i][1];
                    if (inrange(xi,0,8)&&inrange(yi,0,4)&&can_move(xi,yi)&&g[x+f2[i][0]][y+f2[i][1]]==0){
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                }
                break;
            case 8: //马
                for (int i=0;i<8;i++)
                if (g[x+f1[i/2][0]][y+f1[i/2][1]]==0){
                    int xi=x+f3[i][0],yi=y+f3[i][1];
                    if (inrange(xi,0,8)&&inrange(yi,0,9)&&can_move(xi,yi)){
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                }
                break;
            case 10: //车
                for (int i=0;i<=3;i++){
                    int xi=x,yi=y;
                    while (inrange(xi+f1[i][0],0,8)&&inrange(yi+f1[i][1],0,9)&&g[xi+f1[i][0]][yi+f1[i][1]]==0){
                        xi+=f1[i][0];
                        yi+=f1[i][1];
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                    if (inrange(xi+f1[i][0],0,8)&&inrange(yi+f1[i][1],0,9)&&g[xi+f1[i][0]][yi+f1[i][1]]%2==1){
                        xi+=f1[i][0];
                        yi+=f1[i][1];
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                }
                break;
            case 12://炮
                for (int i=0;i<=3;i++){
                    int xi=x,yi=y;
                    while (inrange(xi+f1[i][0],0,8)&&inrange(yi+f1[i][1],0,9)&&g[xi+f1[i][0]][yi+f1[i][1]]==0){
                        xi+=f1[i][0];
                        yi+=f1[i][1];
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                    //炮击
                    xi+=f1[i][0],yi+=f1[i][1];
                    if (inrange(xi,0,8)&&inrange(yi,0,9)){ 
                        while (inrange(xi+f1[i][0],0,8)&&inrange(yi+f1[i][1],0,9)&&g[xi+f1[i][0]][yi+f1[i][1]]==0){
                            xi+=f1[i][0];
                            yi+=f1[i][1];
                        }
                        if (inrange(xi+f1[i][0],0,8)&&inrange(yi+f1[i][1],0,9)&&g[xi+f1[i][0]][yi+f1[i][1]]%2==1){
                            xi+=f1[i][0];
                            yi+=f1[i][1];
                            updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                            if (ans>=worst) return ans;
                        }
                    }  
                }
                break;
            case 14://兵
                for (int i=(y<=4)?3:1;i<=3;i++){
                    int xi=x+f1[i][0],yi=y+f1[i][1];
                    if (inrange(xi,0,8)&&inrange(yi,0,9)&&can_move(xi,yi)){
                        updates(-move(x,y,xi,yi).rotate().solve(outsiders,c-1,-ans),ans,bm,x,y,xi,yi);
                        if (ans>=worst) return ans;
                    }
                }
                break;
        }
    }
    return ans;
}
