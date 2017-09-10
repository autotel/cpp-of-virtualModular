#ifndef module
#include "./modules/module.h"
#endif // !module
#include "ofxMidi.h"
//https://github.com/danomatika/ofxMidi

class midiDummy : public module
{
public:
	ofxMidiOut midiOut;
	void init() override {
		ofLog(OF_LOG_NOTICE,"created midi dummy");
		mOn = true; 

		midiOut.listPorts(); // via instance
							 //ofxMidiOut::listPorts(); // via static too
		midiOut.openPort(1); // by number
							 //midiOut.openPort("IAC Driver Pure Data In"); // by name
							 //midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
		midiOut.sendNoteOn(10, 45, 100);
	};
	void setOutput() override {};
	void engage() override {};
	void disengage() override {};
	void receive() override {}
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		mOn = false; 
		midiOut.sendNoteOn(10, 36+button, 100);
	};
	virtual ~midiDummy() {};
private:
	bool mOn;
};