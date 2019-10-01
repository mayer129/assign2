#include "processBoard.h"
#include "processInput.h"
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char** argv)
{
  processInput myInput;
  vector<string> myVec = myInput.processVect();

  processBoard* myBoard; //have to declare outside of if statement, or else it won't be declared in scope
  cout << '\n';

  if (myVec.size() == 3)
    myBoard = new processBoard(myVec[0], myVec[1], myVec[2]);
  else
    myBoard = new processBoard(stoi(myVec[0]), stoi(myVec[1]), stod(myVec[2]), myVec[3], myVec[4]);

  while (myBoard->gameLogic()) //keeps running until either dead or stable
    myBoard->printArray(); //prints matrix after every run

  system("read -p 'Simulation Finished. Please press Enter to end program' var");
  /*for (std::vector<string>::const_iterator i = myVec.begin(); i != myVec.end(); ++i)
    std::cout << *i << '\n';
  cout << myVec.size() << endl;*/ //TESTING

  delete myBoard;
  return 0;
}
