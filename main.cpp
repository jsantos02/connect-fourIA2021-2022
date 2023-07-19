#include <iostream>
#include "board.h"
using namespace std;

int main(int argc, char** argv)
{
  Board game;
  Board nw;
  int move;
  int flag;
  char x;
  cout << "Initial configuration:" << endl;
  if(argc==1) {
    game.printgame();
    while(game.terminal()) {
      if(game.player() == 'X') {
        cout << "What's your move?" << endl;
        int i = 0;
        cin >> i;
        game.play(i,'X');
        game.printgame();
      } else if(game.player() == 'O') {
        cout << "AI playing" << endl;
        game.minimax(game,2,true);
       // cout << "util value: " << util << endl;
        game.IAplay('O');
        game.printgame();
      }
    }
    //game.terminal();
  } else if(argc==2) {
    game.read(argv[1]);
    game.printgame();
    cout << boolalpha << game.terminal() << endl;
    while(game.terminal()) {
    cout << boolalpha << game.terminal() << endl;
      cout << game.player() << endl;
      if(game.player() == 'X') {
        cout << "What's your move?" << endl;
        int i = 0;
        cin >> i;
        game.place(i,'X');
        game.printgame();
      } else if(game.player() == 'O') {
        cout << "AI playing" << endl;
        //mudar para algoritmo 
        game.minimax(game,2,true);
        game.IAplay('O');
        game.printgame();
      }
      cout << boolalpha << "já deu? " << game.terminal() << endl;
    }
    //game.terminal();
  }
  return 0;
  /*game.read();
  game.printgame();

  if (game.terminal()) {
    throw string("Game Over!");
  }
  else
  {
    if(argc == 2) {

    }
    cout << "Who is starting? X or O?" << endl;
    cin >> x;
   // cout << "Your turn player, " << x << "!" << endl;

    (x == 'X') ? flag = 1 : flag = 0;

    while (!game.terminal())
    {
      cout << "Your turn player, " << x << "!" << endl;
      printf("\nChoose a column (0-6) to place: \n");
      cin >> move;
      cout << endl;
      if (flag == 1)
      {
        game.place(move, 'X');
        if (game.checkWin('X'))
        {
          cout << "Player X wins!!!" << endl;
          game.printgame();
          return 0;
        }
        x = 'O';
        flag = 0;
      }
      else
      {
        game.place(move, 'O');
        if (game.checkWin('O'))
        {
          cout << "Player O wins!!!" << endl;
          game.printgame();
          return 0;
        }
        x = 'X';
        flag = 1;
      }
      game.printgame();
    }
  }
  cout << "Draw!!!" << endl;
  return 0;*/
}