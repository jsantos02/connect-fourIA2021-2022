#include "board.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

using namespace std;

char player1;
char player2;
char turn;
int action;
int aiInd;
int ganhou;

// Constructor to create de game
// Empty game
Board::Board()
{
  player1 = 'O';
  player2 = 'X';
  turn = 'X';
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      matrix[i][j] = '-';
    }
  }
}

// Creates one board with the same matrix
Board Board::clone()
{
  Board nw;
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      nw.matrix[i][j] = matrix[i][j];
    }
  }
  return nw;
}

// Read the initial configuration
void Board::read(char args[]) {
  ifstream f(args);
  for (int i = 0; i < 6 ; i++) {
    for (int j = 0; j < 7; j++) {
      f >> matrix[i][j];
    }
  }
  f.close();
}

// Prints the current state of the game
void Board::printgame()
{
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  // cout << "isto é o jogo lol" << endl;
  printf("\n");
}

// Returns the next player to play
char Board::player()
{
  int counterpl1 = 0;
  int counterpl2 = 0;
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (matrix[i][j] == player2)
      {
        counterpl2++;
      }
      else if (matrix[i][j] == player1)
      {
        counterpl1++;
      }
    }
  }
  if (counterpl1 >= counterpl2)
  {
    turn = 'X';
    return turn;
  }
  else if (counterpl2 > counterpl1)
  {
    turn = 'O';
    return turn;
  }
  /* else if (counterpl1 == counterpl2) {
    if(turn == 'X') turn = 'O';
    else if (turn == 'O') turn = 'X';
  } */

  return turn;
}

// Something ----------------------------------------
int Board::result(int y)
{
  int p;
  for (int i = 5; i >= 0; i--)
  {
    if (matrix[i][y] == '-')
    {
      matrix[i][y] = turn;
      p = i;

      if (turn == player1)
      {
        turn = player2;
      }
      else
      {
        turn = player1;
      }
      action = p;
      return action;
    }
  }
  return 404;
}

// Plays
int Board::move(int y)
{
  int p;
  for (int i = 5; i >= 0; i--)
  {
    if (matrix[i][y] == '-')
    {
      matrix[i][y] = turn;
      p = i;
      return p;
    }
  }
  return 404;
}

void Board::play(int y,char player)
{
  for (int i = 5; i >= 0; i--)
  {
    if (matrix[i][y] == '-')
    {
      matrix[i][y] = player;
      return;
    }
  }
}

void Board::IAplay(char player)
{
  for (int i = 5; i >= 0; i--)
  {
    if (matrix[i][aiInd] == '-')
    {
      matrix[i][aiInd] = player;
      return;
    }
  }
}

// Place a char
int Board::place(int y, char t) {
  turn = t;
  return move(y);
}

// Check horizontal locations
bool Board::checkHorizontal(char player)
{
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7 - 3; j++)
    {
      if (matrix[i][j] == player &&
          matrix[i][j + 1] == player &&
          matrix[i][j + 2] == player &&
          matrix[i][j + 3] == player)
        return true;
    }
  }
  return false;
}

// Check vertical locations
bool Board::checkVertical(char player)
{
  for (int i = 0; i < 6 - 3; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (matrix[i][j] == player &&
          matrix[i + 1][j] == player &&
          matrix[i + 2][j] == player &&
          matrix[i + 3][j] == player)
        return true;
    }
  }
  return false;
}

// Check positive diagonal locations
bool Board::checkPosDiagonal(char player)
{
  for (int i = 0; i < 6 - 3; i++)
  {
    for (int j = 0; j < 7 - 3; j++)
    {
      if (matrix[i][j] == player &&
          matrix[i + 1][j + 1] == player &&
          matrix[i + 2][j + 2] == player &&
          matrix[i + 3][j + 3] == player)
        return true;
    }
  }
  return false;
}

// Check negative diagonal locations
bool Board::checkNegDiagonal(char player)
{
  for (int i = 3; i < 6; i++)
  {
    for (int j = 0; j < 7 - 3; j++)
    {
      if (matrix[i][j] == player &&
          matrix[i - 1][j + 1] == player &&
          matrix[i - 2][j + 2] == player &&
          matrix[i - 3][j + 3] == player)
        return true;
    }
  }
  return false;
}

// Check if someone won
int Board::checkWin(char player)
{
  if (checkHorizontal(player) || checkVertical(player) || checkPosDiagonal(player) || checkNegDiagonal(player))
  {
    //cout << "Player " << player << " won!" << endl;
    ganhou = 1;
  
  if (player == player1 && ganhou == 1)
  {
    return 1;
  }
  else if (player == player2 && ganhou == 1)
  {
    return 2;
  }
  else return 404;
  } else 
  return 404;
}

// Returns the player who won
void Board::winner()
{
  if (checkWin(player1) == 1)
  {
    return;
  }
  else if (checkWin(player2) == 2)
  {
    return;
  }
  else
    cout << "Draw" << endl;
}

// Checks if the board is full
bool Board::fullBoard()
{
  int count = 0;
  for (int i = 0; i < 7; i++)
  {
    if (matrix[0][i] != '-')
      count++;
  }
  if (count == 7)
    return true;
  else
    return false;
}

// Checks if game ended
bool Board::terminal()
{
  cout << "ganhou no inicio " << ganhou << endl;
  cout << checkWin(player1) << " boas " << checkWin(player2) << " " <<  endl;
  if (checkWin(player1) == 1)
  {
    ganhou = 1;
    cout << "Ganhou O!" << endl;
  }
  else if (checkWin(player2) == 2)
  {
    ganhou = 2;
    cout << "Ganhou X!" << endl;
  }
  else if (fullBoard())
  {
    cout << "Draw" << endl;
  }
  cout << "fullBoard" << fullBoard() << endl;
  cout << "ganhou " << ganhou << endl;
  if (fullBoard() == true || ganhou == 1 || ganhou == 2)
    return true;
  else
    return false;
}

// Pontuation of the state
int Board::pontua(int pointsp2, int pointsp1)
{ // pointsp2 = pontos player 2, pointsp1 = pontos player 1
  if (pointsp2 == 4)
    return 512;
  if (pointsp1 == 4)
    return -512;
  if (pointsp1 > 0 && pointsp2 > 0)
    return 0;
  if (pointsp2 == 1)
    return 1;
  if (pointsp2 == 2)
    return 10;
  if (pointsp2 == 3)
    return 50;
  if (pointsp1 == 1)
    return -1;
  if (pointsp1 == 2)
    return -10;
  if (pointsp1 == 3)
    return -50;
  return 0;
}

// Utility function
int Board::utility()
{
  int pointsp2 = 0;
  int pointsp1 = 0;
  int sum = 0;
  int p = 0;
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (matrix[i][j + k] == 'X')
        {
          pointsp2 = pointsp2 + 1;
        }
        if (matrix[i][j + k] == 'O')
        {
          pointsp1 = pointsp1 + 1;
        }
      }
      p = pontua(pointsp2, pointsp1);
      pointsp2 = 0;
      pointsp1 = 0;
      if (p == 512 || p == -512)
      {
        return p;
      }
      sum = sum + p;
    }
  }
  //cout << "Score for lines: " << sum << endl;
  // int lines = sum;

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      for (int k = 0; k < 4; k++)
      {

        if (matrix[i + k][j] == 'X')
        {
          pointsp2 = pointsp2 + 1;
        }
        if (matrix[i + k][j] == 'O')
        {
          pointsp1 = pointsp1 + 1;
        }
      }
      p = pontua(pointsp2, pointsp1);
      pointsp2 = 0;
      pointsp1 = 0;
      if (p == 512 || p == -512)
      {
        return p;
      }
      sum = sum + p;
    }
  }
  //cout << "Score for columns: " << sum - lines << endl;
  //cout << "Indice of diagonals" << endl;
  // diagonal
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (matrix[i + k][j + k] == 'X')
        {
          pointsp2 = pointsp2 + 1;
        }
        if (matrix[i + k][j + k] == 'O')
        {
          pointsp1 = pointsp1 + 1;
        }
        //cout << "(" << i + k << "," << j + k << ")" << endl;
      }
      //cout << "===========" << endl;
      p = pontua(pointsp2, pointsp1);
      pointsp2 = 0;
      pointsp1 = 0;
      if (p == 512 || p == -512)
      {
        return p;
      }
      sum = sum + p;
    }
  }
  // antidiagonal
  for (int i = 3; i < 6; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (matrix[i - k][j + k] == 'X')
        {
          pointsp2 = pointsp2 + 1;
        }
        if (matrix[i - k][j + k] == 'O')
        {
          pointsp1 = pointsp1 + 1;
        }
        //cout << "(" << i - k << "!" << j + k << ")" << endl;
      }
      //cout << "===========" << endl;
      p = pontua(pointsp2, pointsp1);
      pointsp2 = 0;
      pointsp1 = 0;
      if (p == 512 || p == -512)
      {
        return p;
      }
      sum = sum + p;
    }
  }
  return sum;
}

// All the sucessors
std::vector<Board> Board::actions()
{
  vector<Board> sucessors;
  for (int i = 0; i < 7; i++)
  {
    if (matrix[0][i] == '-')
    {
      Board nw;
      nw = clone();
      nw.play(i,'O');
      sucessors.push_back(nw);
    }
  }
  return sucessors;
}

Board Board::find(std::vector<Board> list, int util)
{
  Board fail;
  for(int i = 0; i < list.size();i++)
  {
    if(list.at(i).utility() == util) {
      return list.at(i);
    }
  }
  return fail;
}

int Board::diff(Board what) {
  for(int i = 0; i < 6; i++) {
    for(int j = 0 ; j < 7; j++) {
      if(matrix[i][j] != what.matrix[i][j])
        return j;
    }
  }
  return 404;
}


// MiniMax Algorithm
int Board::minimax(Board cur,int depth, bool maxplayer)
{
  cout << "oi" << endl;
  cout << boolalpha <<cur.terminal() << endl;
  int best = 0, bestB =0;
  int worst = 0, worstB = 0;
  if (!cur.terminal() || depth == 0)
  {
    return cur.utility();
  }
  vector<Board> act = cur.actions();
  if (maxplayer)
  {
    cout << "cheguei ao maxplayer" << endl;
    int v = INT_MIN;
    for (int i = 0; i < act.size(); i++)
    {
      v = max(v, minimax(act.at(i),depth-1, false));
      cout << "utilidade desta jogada: " << v << endl;
      act.at(i).printgame();
      if (v>best) {
        best = v;
        bestB = i;
      }
    }
    cout << "cheguei aqui e v é igual a: " << v << endl;
    aiInd = cur.diff(act.at(bestB));
    cout << "cheguei aqui e ind é igual a: " << aiInd << endl;

    return v;
  }
  else
  {
    cout << "Isto é o minplayer" <<endl;
    int v = INT_MAX;
    for (int i = 0; i < act.size(); i++)
    {
      v = min(v, minimax(act.at(i),depth-1, true));
      if (v<worst) {
        worst = v;
        worstB = i;
      }
    }
    aiInd = cur.diff(act.at(worstB));
    return v;
  }
}

// Alpha-Beta Pruning
int Board::alphabeta(Board cur, int depth, int alpha, int beta, bool maxplayer)
{
  vector<Board> act = cur.actions();
  if (cur.terminal() || depth == 0)
  {
    return cur.utility();
  }
  if (maxplayer)
  {
    int v = INT_MIN;
    for (int i = 0; i < act.size(); i++)
    {
      v = max(v, alphabeta(act.front(), depth - 1, alpha, beta, false));
      alpha = max(alpha, v);
      if (alpha >= beta)
        break;
    }
    return v;
  }
  else
  {
    int v = INT_MAX;
    for (int i = 0; i < act.size(); i++)
    {
      v = min(v, alphabeta(act.front(), depth - 1, alpha, beta, true));
      beta = min(beta, v);
      if (beta <= alpha)
        break;
    }
    return v;
  }
}

// Monte Carlo Tree Search (MCTS)
typedef struct {

} MCTSNode;