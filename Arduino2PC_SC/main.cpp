/* Zain Ul Mustafa */

//Rules:
/*
1. Check if connection with Arduino is made
2. If Arduino is connected then take input from user in a String
3. Make a char array of the size of string + 1
4. Copy the whole string into the char array
5. Add escape sequence \n because this represents the end of a line in Serial Comm port
6. Write the whole char array into the buffer (a buffer takes the info forward to the Serial Comm Port)
7. Read from the Arduino if data is received successfully or if the action is taken as per needed
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include "SerialPort.h"

using namespace std;

// String for getting the output from arduino
char output[MAX_DATA_LENGTH];

/* You must add these backslashes before writing your COM Portname */
// I have COM3 on my PC
char *port_name = "\\\\.\\COM3";

// String for incoming data
char incomingData[MAX_DATA_LENGTH];

int main(){
	SerialPort arduino(port_name);
	if (arduino.isConnected()){
		cout << "Connection Established" << endl;
	}
	else{
		cout << "ERROR, check port name";
	}

	while (arduino.isConnected()){
		cout << "Write something: \n";
		string input_string;
		// Getting input
		getline(cin, input_string);

		// Creating a charArray
		char *charArray = new char[input_string.size() + 1];

		// copying the input_string to charArray
		copy(input_string.begin(), input_string.end(), charArray);

		// Adding the delimiter -> \n states end of line in Serial Comm Port
		charArray[input_string.size()] = '\n';

		// Writing string to arduino
		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		// Getting reply/response from arduino
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		// printing the output
		puts(output);

		// freeing charArray memory
		delete[] charArray;
	}
}
