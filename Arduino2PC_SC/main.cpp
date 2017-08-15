#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<string>
#include "SerialPort.h"

using namespace std;

//String for getting the output from arduino
char output[MAX_DATA_LENGTH];

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char *port_name = "\\\\.\\COM3";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];

int main()
{
  SerialPort arduino(port_name);
  if (arduino.isConnected()) cout << "Connection Established" << endl;
  else cout << "ERROR, check port name";

  while (arduino.isConnected()){
    cout << "Write something: \n";
    std::string input_string;
    //Getting input
	getline(cin, input_string);
    //Creating a c string
    char *c_string = new char[input_string.size() + 1];
    //copying the std::string to c string
    std::copy(input_string.begin(), input_string.end(), c_string);
    //Adding the delimiter
    c_string[input_string.size()] = '\n';
    //Writing string to arduino
    arduino.writeSerialPort(c_string, MAX_DATA_LENGTH);
    //Getting reply from arduino
    arduino.readSerialPort(output, MAX_DATA_LENGTH);
    //printing the output
    puts(output);
    //freeing c_string memory
    delete[] c_string;
  }
}