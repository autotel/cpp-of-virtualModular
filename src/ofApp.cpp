#include "ofApp.h"
#include "HardwareController.h"
#include "EventMessage.h"
#include "interactorFactory.h"
#include "moduleFactory.h"
#include "PatchMenu.h"
#include "HardwareView.h"
#include "timer.h"

vector <HardwareController> uiHardwares;

PatchMenu patchMenu;
vector <Module *> modules;
Scheduler *ttimer;



void onMatrixButton(unsigned char button, unsigned int map) {
	ofLog(OF_LOG_NOTICE, "callback received %d %d",button,map);
	patchMenu.onMatrixButtonPressed(button, map);
};

void ofApp::setup() {




	modules.push_back(moduleFactory::make(MODULE_SEQUENCER));
	modules.push_back(moduleFactory::make(MODULE_MIDI));
	modules[0]->setOutput(modules[1]);
	ttimer = new Scheduler(modules[0]);



	//TODO: must be more elegant ways for this:
	uiHardwares.push_back(HardwareController());
	uiHardwares[0].setup();
	uiHardwares[0].addMatrixButttonPressedCallback(onMatrixButton);
	uiHardwares[0].sendScreenA("test");
	
	patchMenu.init(uiHardwares[0], modules);

	if (!modules[0])
		ofLog(OF_LOG_NOTICE, "mm evals false");
	modules[0]->init(uiHardwares[0]);
	modules[1]->init(uiHardwares[0]);

	bSendSerialMessage = false;
#if GUI
	ofSetVerticalSync(true);
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	font.load("DIN.otf", 64);
#endif
	

	patchMenu.engage();
	/*
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);*/
}


void ofApp::update(){
	uiHardwares[0].checkMessages();
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

