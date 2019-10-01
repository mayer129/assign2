#include "processBoard.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <thread>
#include <chrono>

using namespace std;

processBoard::processBoard(int height, int width, double density, string gameMode, string outputType) //constructor probability
{
  row = height; //set values from constructor
  column = width;
  this->gameMode = gameMode;
  this->outputType = outputType;
  generation = 0;

  if (outputType == "f")
    myFile.open("travis.out");

  boardArray = new char *[row]; //create first set pointers of array
  shadowArray = new char *[row];
  previousArray = new char *[row];

  for (int i = 0; i < row; i++)
  {
    boardArray[i] = new char[column]; //create second set pointers of array, so array is now matrix
    shadowArray[i] = new char[column];
    previousArray[i] = new char[column];
  }

  srand(time(NULL)); //seed rand()
  for (int i = 0; i < row; ++i) //assign row values
  {
    for (int j = 0; j < column; ++j) //assign column values
    {
      if ((rand() / double(RAND_MAX)) <= density) //assign according to provided density
      {
        boardArray[i][j] = 'X'; //assign 'X' values
        shadowArray[i][j] = 'X';
        previousArray[i][j] = 'X';
      }
      else
      {
        boardArray[i][j] = '-'; //assign '-' values
        shadowArray[i][j] = '-';
        previousArray[i][j] = '-';
      }
    }
  }
  printArray();
}

processBoard::processBoard(string file, string gameMode, string outputType) //constructor file map
{
  ifstream textFile(file); //reads file
  string line = "";

  getline(textFile, line); //gets row line from file
  row = stoi(line); //coverts string to int and sets equal to row
  getline(textFile, line); //gets column line from file
  column = stoi(line); //coverts string to int and sets equal to column

  this->gameMode = gameMode;
  this->outputType = outputType;
  generation = 0;

  if (outputType == "f")
    myFile.open("travis.out");

  boardArray = new char *[row]; //create first set pointers of array
  shadowArray = new char *[row];
  previousArray = new char *[row];

  for (int i = 0; i < row; i++)
  {
    boardArray[i] = new char[column]; //create second set pointers of array, so array is now matrix
    shadowArray[i] = new char[column];
    previousArray[i] = new char[column];
  }

  for (int i = 0; i < row; ++i) //read in number of rows of probability map
  {
    getline(textFile, line); //read in lines of probability map
    for (int j = 0; j < column; ++j) //read in number of columns of probability map
    {
      char lineChar = line[j];
      if (lineChar == 'X') //assign 'X' values based on probability map
      {
        boardArray[i][j] = 'X';
        shadowArray[i][j] = 'X';
        previousArray[i][j] = 'X';
      }

      else if (lineChar == '-') //assign '-' values based on probability map
      {
        boardArray[i][j] = '-';
        shadowArray[i][j] = '-';
        previousArray[i][j] = '-';
      }
    }
  }
  printArray();
}

processBoard::~processBoard() //destructor
{
  for (int i = 0; i < row; i++) //delete the dynamic array
  {
    delete[] boardArray[i];
    delete[] shadowArray[i];
    delete[] previousArray[i];
  }
  delete[] boardArray;
  delete[] shadowArray;
  delete[] previousArray;

  if (outputType == "f")
    myFile.close();
}

bool processBoard::gameLogic()
{
  bool changes = false, alive = false, previousDifference = false;

  for (int i = 0; i < row; ++i) //iterate row
  {
    for (int j = 0; j < column; ++j) //iterate column
    {
      if (checkNeighbors(i, j) <= 1) //check neighbor loneliness
        boardArray[i][j] = '-';
      else if (checkNeighbors(i, j) == 3) //check for cell creation
        boardArray[i][j] = 'X';
      else if (checkNeighbors(i, j) >= 4) //check for overcrowding
        boardArray[i][j] = '-';
      if (boardArray[i][j] == 'X') //if any char is X, board is alive
        alive = true;
      if (boardArray[i][j] != shadowArray[i][j]) //if any char changes, board is alive
        changes = true;
      if (previousArray[i][j] != boardArray[i][j])
        previousDifference = true;
    }
  }

    for (int i = 0; i < row; ++i) //iterate row
    {
      for (int j = 0; j < column; ++j) //iterate column
      {
        previousArray[i][j] = shadowArray[i][j]; //makes previous array = to shadow array. therefore the new previous
        shadowArray[i][j] = boardArray[i][j]; //makes shadow array = to board array again
      }
    }

  if (!alive || !previousDifference)
    printArray();
  if (!changes || !alive || !previousDifference) //if board isn't changing or is dead, return false, else return true
    return false;
  return true;
}

int processBoard::checkNeighbors(int r, int c)
{
  int neighbors = 0;
  for (int i = r - 1; i < r + 2; ++i) //count neighbors
  {
    for (int j = c - 1; j < c + 2; ++j)
    {
      if (i == -1 || i == row || j == -1 || j == column) //ignore edge cases
      {
        int tempI = i, tempJ = j;
        if (gameMode == "m") //mirror mode bonus gamerules
        {
          if (i == -1)
            tempI++;
          if (j == -1)
            tempJ++;
          if (i == row)
            tempI--;
          if (j == column)
            tempJ--;
          if (shadowArray[tempI][tempJ] == 'X')
            neighbors++;
        }
        else if (gameMode == "d") //donut mode bonus gamerules
        {
          if (i == -1)
            tempI = row - 1;
          if (j == -1)
            tempJ = column - 1;
          if (i == row)
            tempI = 0;
          if (j == column)
            tempJ = 0;
          if (shadowArray[tempI][tempJ] == 'X')
            neighbors++;
        }
        continue;
      }
      else if (shadowArray[i][j] == 'X')
       neighbors++;
    }
  }
  if (shadowArray[r][c] == 'X')
    neighbors--; //subtract if the location is X
  return neighbors;
}


void processBoard::printArray()
{
  if (outputType == "f") //outputs generation number
  {
    myFile << generation << endl;
    generation++;
    for (int i = 0; i < row; ++i) //assign width values
    {
      for (int j = 0; j < column; ++j) //assign height values
      {
        myFile << boardArray[i][j];
      }
      myFile << '\n';
    }
    myFile << '\n';
  }
  else
  {
    cout << generation << endl;
    generation++;
    for (int i = 0; i < row; ++i) //assign width values
    {
      for (int j = 0; j < column; ++j) //assign height values
      {
        cout << boardArray[i][j];
      }
      cout << '\n';
    }
    if (outputType == "p")
    {
      this_thread::sleep_for(chrono::milliseconds(500));
      cout << '\n'; //put \n in this loop cuz it already has one when doing "Enter" input
    }
    else
      system("read -p 'Please press Enter to continue...' var"); //alternative to pause for unix based systems. Will not work on windows.
        //system("pause"); // SYSTEM PAUSE does not work. pause not found because its unix, not windows. doesnt work between different OS
        //tried alternatives like getchar, but they still register any input, not just enter
  }
}
