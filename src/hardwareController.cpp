#include "hardwareController.h"
#define SOFT_BAUDRATE 19200

//recieve headers
#define RH_null 0x0
#define RH_null_len 0x0
#define RH_hello 0x1
#define RH_hello_len 0x0
#define RH_buttonMatrixPressed 0x2
#define RH_buttonMatrixPressed_len 0x4
#define RH_buttonMatrixReleased 0x3
#define RH_buttonMatrixReleased_len 0x4
#define RH_buttonMatrixHold 0x4
#define RH_buttonMatrixHold_len 0x4
#define RH_buttonMatrixVelocity 0x5
#define RH_buttonMatrixVelocity_len 0x4
#define RH_selectorButtonPressed 0x6
#define RH_selectorButtonPressed_len 0x2
#define RH_selectorButtonReleased 0x7
#define RH_selectorButtonReleased_len 0x2
#define RH_encoderScroll 0x8
#define RH_encoderScroll_len 0x2
#define RH_encoderPressed 0x09
#define RH_encoderPressed_len 0x1
#define RH_encoderReleased 0x0A
#define RH_encoderReleased_len 0x1
#define RH_comTester 0x0B
#define RH_comTester_len 0x1

#define TH_null 0x0
#define TH_null_len 0x0
#define TH_hello 0x1
#define TH_hello_len 0x0
#define TH_ledMatrix 0x2
#define TH_ledMatrix_len 0x6
#define TH_screenA 0x3
#define TH_screenA_len -1
#define TH_screenB 0x4
#define TH_screenB_len -1
#define TH_setInteractionMode 0x5
#define TH_setInteractionMode_len 0x4
#define TH_currentStep 0x6
#define TH_currentStep_len 0x2
#define TH_comTester 0x7
#define TH_comTester_len 0x1

#define serialInLength 32
unsigned char inBuff[serialInLength];

bool recordingBuffer = false;
int expectedLength = 0;
unsigned char currentHeader = 0;
int byteNumber = 0;

#define EOMessage 3
#define unknown -1

void hardwareController::setup(){
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = SOFT_BAUDRATE;
	serial.setup(0, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
}

void hardwareController::addMatrixButttonPressedCallback(std::function<void(unsigned char, unsigned int)> onMatrixButton) {
	//or maybe I should do this? http://openframeworks.cc/documentation/events/ofEvent/
	//only that current method is compatible with arduino, better for learning...
	matrixButtonCallback = onMatrixButton;
}

//send a string which has dynamic length

void hardwareController::sendString(unsigned char header, char str[] ) {
	//from https://github.com/openframeworks/openFrameworks/issues/279
#define HEADSIZE 2
	string msg(str);
	char heads[HEADSIZE] = { header,strlen(str)+1 };
	unsigned char* msguc = new unsigned char[18];
	memcpy(&msguc[0], heads, HEADSIZE);
	memcpy(&msguc[HEADSIZE], msg.c_str(), msg.size()+(HEADSIZE+1));
	serial.writeBytes(msguc, msg.size() + HEADSIZE+1);
	delete[] msguc;
}


// to be ran in a loop

void hardwareController::checkMessages() {
	while (serial.available() && (byteNumber < serialInLength)) {
		//delayMicroseconds(100);
		unsigned char data_a = serial.readByte();
		//ofLog(OF_LOG_NOTICE, ">>data %d", data_a);
		if (!recordingBuffer) {
			//we are expecting a message header, so we check what header current byte is
			//if is successfull, we start gathering or recording a new data packet.
			//TODO: there should be a more maintainable way of doing this
			//byte  is in our header list?
			switch (data_a) {
			case RH_null:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_null_len;
				break;
			case RH_hello:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_hello_len;
				//ofLog(OF_LOG_NOTICE, "hello received %d", data_a);
				break;
			case RH_buttonMatrixPressed:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_buttonMatrixPressed_len;
				break;
			case RH_buttonMatrixReleased:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_buttonMatrixReleased_len;
				break;
			case RH_buttonMatrixHold:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_buttonMatrixHold_len;
				break;
			case RH_buttonMatrixVelocity:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_buttonMatrixVelocity_len;
				break;
			case RH_selectorButtonPressed:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_selectorButtonPressed_len;
				break;
			case RH_selectorButtonReleased:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_selectorButtonReleased_len;
				break;
			case RH_encoderScroll:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_encoderScroll_len;
				break;
			case RH_encoderPressed:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_encoderPressed_len;
				break;
			case RH_encoderReleased:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_encoderReleased_len;
				break;
			case RH_comTester:
				// lcdPrintA("H_null");
				recordingBuffer = true;
				expectedLength = RH_comTester_len;
				break;
			}
		}

		if (recordingBuffer) {
			if (expectedLength == unknown) {
				//ofLog(OF_LOG_NOTICE, "continue unknown length");
				if (byteNumber == 0) {
					//get header and +1
					inBuff[byteNumber] = data_a;
					byteNumber++;
				}
				else if (byteNumber == 1) {
					//undetermined length so byte 2 must be length
					inBuff[byteNumber] = data_a;
					expectedLength = data_a + 1;
					byteNumber++;
				}
			}
			else if (byteNumber < expectedLength) {
				//a new byte arrived and is added to the current packet
				//ofLog(OF_LOG_NOTICE, "continue msg expected len %d", expectedLength);
				inBuff[byteNumber] = data_a;
				byteNumber++;
			}
			else {
				//a whole expected packet arrived
				//ofLog(OF_LOG_NOTICE, "end of msg len %d", byteNumber);
				inBuff[byteNumber] = data_a;
				recordingBuffer = false;
				messageReceived(inBuff, byteNumber);
				byteNumber = 0;
			}
		}
		
	}
}

//react and split messages
void hardwareController::messageReceived(unsigned char datarray [], int len) {
	//ofLog(OF_LOG_NOTICE, "message received %d", datarray[0]);
	int a = 0;
	unsigned char header = datarray[a];
	a++;
	switch (header) {
		while (a < len) {
			case RH_hello: {
				break;
			}
			case RH_buttonMatrixPressed: {
				ofLog(OF_LOG_NOTICE, "button %d", datarray[1]);
				ofLog(OF_LOG_NOTICE, "btnMx received %d, %d, %d, %d", datarray[1], datarray[2], datarray[3], datarray[4]);
				matrixButtonCallback((unsigned char) datarray[1], datarray[3] | ( datarray[4]<<8 ) );
				break;
			}
			default:
				a++;
		}
	}
}
//TODO This is working strange, I can't figure out why yet.
void hardwareController::setLed(int r, int g, int b) {
	unsigned char msg[] = {
		TH_ledMatrix,
		g & 0xff,(g >> 8) & 0xff,
		b & 0xff,(b >> 8) & 0xff,
		r & 0xff,(r >> 8) & 0xff
	};
	serial.writeBytes(msg, TH_ledMatrix_len + 1);
}

void hardwareController::sendScreenA(char str[]) {
	sendString(3, str);
}
void hardwareController::sendScreenB(char str[]) {
	sendString(4, str);
}