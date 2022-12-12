#include<fstream>
#include"chess_engine_v1.cpp"
ifstream fin("board.txt");
ofstream fout("move.txt");
int main(){
    string a,b;
    int c,d;
    board ex;
    while (fin>>a>>b>>c>>d){
        ex.insert(a,b,c,d);
    }
    //ex.print();
    int move[4];
    ex.solve(move);
    fout<<move[0]<<' '<<move[1]<<' '<<move[2]<<' '<<move[3]<<endl;
    return 0;
}
