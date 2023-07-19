#include <vector>
class Board {
  public:
    // Variables
    char matrix[6][7]; //defined as x->lines and y->columns
    char player1,player2;
    FILE *f;
    int action;
    int ganhou;

    // Constructor and Board clone
    Board();
    Board clone();

    // Board State
    void read(char arr[]);
    void printgame();
    bool fullBoard();
    bool terminal(); //checks if game ended
    Board find(std::vector<Board> list, int utility);

    // Playing
    char player();
    void IAplay(char player);
    int result(int y);
    int move(int y);
    void play(int y,char t);
    int place(int y, char t);
    int diff(Board what);
    std::vector<Board> actions();

    // Win conditions
    bool checkVertical(char player);
    bool checkHorizontal(char player);
    bool checkPosDiagonal(char player);
    bool checkNegDiagonal(char player);
    int checkWin(char player);
    void winner(); //returns player who won

    // Algortihms
    int pontua(int pointsp2, int pointsp1);
    int utility();
    int minimax(Board cur,int depth,bool maxplayer);
    int alphabeta(Board cur, int depth, int alpha, int beta, bool maxplayer);
};