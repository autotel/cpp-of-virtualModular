#include "ofApp.h"
#include "hardwareController.h"
#include "moduleFactory.h"
#include "hardwareView.h"
#include "timer.h"

hardwareController x16pad;
//use factory pattern
//https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Programming_Patterns

//testing:
module *mm [16];
Scheduler *ttimer;

int test = 0;

void onMatrixButton(unsigned char button, unsigned int map) {
	
	test++;

	ofLog(OF_LOG_NOTICE, "callback received %d %d",button,map);
	mm[0]->onMatrixButtonPressed(button, map);
	
};

void ofApp::setup(){

	mm[0] = moduleFactory::newModule(3);

	ttimer = new Scheduler(mm[0]);
	x16pad.setup();
	x16pad.addMatrixButttonPressedCallback(onMatrixButton);

	if (!mm[0])
		ofLog(OF_LOG_NOTICE, "mm evals false");
	mm[0]->init(x16pad);


	bSendSerialMessage = false;
#if GUI 
	ofSetVerticalSync(true);
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	font.load("DIN.otf", 64);
#endif
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);

	
}


void ofApp::update(){
	x16pad.checkMessages();
}

void ofApp::draw(){
#if GUI 
	if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		ofSetColor(0);
	} else {
		ofSetColor(220);
	}
	string msg;
	msg += "click to test serial:\n";
	msg += "nBytes read " + ofToString(nBytesRead) + "\n";
	msg += "nTimes read " + ofToString(nTimesRead) + "\n";
	msg += "read: " + ofToString(bytesReadString) + "\n";
	msg += "(at time " + ofToString(readTime, 3) + ")";
	font.drawString(msg, 50, 100);
#endif
}


void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}

