#include"chess_engine.cpp"
ifstream fin("board.txt");
ofstream fout("move.txt");
int main(){
    string a,b;
    int c,d;
    board ex;
    while (fin>>a>>b>>c>>d){
        ex.insert(a,b,c,d);
    }
    int move[4];
    dfs(ex,move);
    fout<<move[0]<<' '<<move[1]<<' '<<move[2]<<' '<<move[3]<<endl;
    return 0;
}