#include <iostream>
#include <fstream>

using namespace std;

class processBoard
{
public:
  processBoard(int height, int width, double density, string gameMode, string outputType); //constructor based on randomm probability
  processBoard(string file, string gameMode, string outputType); //constructor based on file map
  ~processBoard(); //destructor

  int column; //height of the matrix
  int row; //width of the matrix

  string gameMode; //gamemode: n, d, m
  string outputType; //output type: p, e, f
  int generation; //current generation count

  ofstream myFile; //ofstream for output type f

  bool gameLogic();
  int checkNeighbors(int r, int c);

  void printArray(); //basic print function

  char** boardArray; //the printed matrix
  char** shadowArray; //matrix used to calculate generation changes
  char** previousArray; //matrix used to check if game stuck in infinite loop between generations
};
