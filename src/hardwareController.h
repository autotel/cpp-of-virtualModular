#pragma once

#include "ofMain.h"

class HardwareController {//: public ofBaseApp

	public:
		HardwareController();
		void setup();
		void addMatrixButttonPressedCallback(std::function<void(unsigned char button, unsigned int map)> onMatrixButton);
		std::function<void(unsigned char button, unsigned int map)>matrixButtonCallback;
		void sendString(unsigned char header, char str[]);
		//void receiveByte(unsigned char byte);
		void checkMessages();
		void messageReceived(unsigned char datarray[], int len);
		void setLed(int r, int g, int b);
		void sendScreenA(char str[]);
		void sendScreenB(char str[]);
		ofSerial	serial;
};

