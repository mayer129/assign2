#include "processInput.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

processInput::processInput()
{

}

processInput::~processInput()
{

}

 vector<string> processInput::processVect()
{
  vector<string> inputVect;
  while (true)
  {
    string input = "";
    cout << "Do you wish to provide a map file (m), or would you like a random assignment (r)?" << endl;
    cin >> input;

    if (input == "map" || input == "m")
    {
      string fileLocation = "";
      while (true)
      {
        cout << "Please enter the file location." << endl;
        cin >> fileLocation;
        ifstream textFile(fileLocation);
        if (textFile.is_open() && textFile.good())
        {
          textFile.close();
          inputVect.push_back(fileLocation); //adds file location to vector
          break;
        }
        cout << "Error: File location invalid" << endl;
      }
      break; //break file location loop
    }

    else if (input == "random" || input == "r")
    {
      string height = "", width = "", density = "";
      while (true)
      {
        cout << "Please enter the height." << endl;
        cin >> height;
        cout << "Please enter the width." << endl;
        cin >> width;
        cout << "Please enter the density." << endl;
        cin >> density;
        if (stoi(height) < 1 || stoi(width) < 1 || stod(density) <= 0 || stod(density) > 1)
          cout << "Error: Input is outside parameters. Height and Width can't be < 1, and density must be > 0 and <= 1" << endl;
        else
        {
          inputVect.push_back(height);
          inputVect.push_back(width);
          inputVect.push_back(density);
          break; //break random loop
        }
      }
      break; //break input type loop
    }
    cout << "Error: Incorrect Input" << endl;
  }

  string mode = "";
  while (true)
  {
    cout << "What type of boundary mode would you like to run (normal, donut, mirror)?" << endl;
    cin >> mode;
    if (mode == "normal" || mode == "n")
    {
      mode = "n";
      inputVect.push_back(mode);
      break; //break boundary mode loop
    }
    else if (mode == "donut" || mode == "d")
    {
      mode = "d";
      inputVect.push_back(mode);
      break; //break boundary mode loop
    }
    else if (mode == "mirror" || mode == "m")
    {
      mode = "m";
      inputVect.push_back(mode);
      break; //break boundary mode loop
    }
    cout << "Error: That is not a valid boundary mode." << endl;
  }

  string outputType = "";
  while (true)
  {
    cout << "Would you like a pause between generations (p), to press 'Enter' to prompt generations (e), or to output to a file (f)?" << endl;
    cin >> outputType;
    if (outputType == "pause" || outputType == "p")
    {
      outputType = "p";
      inputVect.push_back(outputType);
      break; //break output type loop
    }
    else if (outputType == "enter" || outputType == "e")
    {
      outputType = "e";
      inputVect.push_back(outputType);
      break; //break output type loop
    }
    else if (outputType == "file" || outputType == "f")
    {
      outputType = "f";
      inputVect.push_back(outputType);
      break; //break output type loop
    }
    cout << "Error: Incorrect Input" << endl;
  }
  return inputVect;
}
