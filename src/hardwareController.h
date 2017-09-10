#pragma once

#include "ofMain.h"

class hardwareController {//: public ofBaseApp
	
	public:
		void setup();
		void addMatrixButttonPressedCallback(std::function<void(unsigned char button, unsigned int map)> onMatrixButton);
		std::function<void(unsigned char button, unsigned int map)>matrixButtonCallback;
		void sendString(unsigned char header, char str[]);
		//void receiveByte(unsigned char byte);
		void checkMessages();
		void messageReceived(unsigned char datarray[], int len);
		void sendScreenA(char str[]);
		void sendScreenB(char str[]);
		ofSerial	serial;
};

