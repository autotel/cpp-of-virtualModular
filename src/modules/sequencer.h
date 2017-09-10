#pragma once
#ifndef module
#include "./modules/module.h"
#endif // !module
#include "ofxMidi.h"
//https://github.com/danomatika/ofxMidi

class sequencer : public module
{
public:
	ofxMidiOut midiOut;
	int dummyPattern [16][3];
	int patternBitMap = 0x0000;
	int playHead = 0;
	void init() override {
		ofLog(OF_LOG_NOTICE, "created midi dummy");
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
	void receive() override {
		playHead++;
		if (dummyPattern[playHead]) {
			midiOut.sendNoteOn(dummyPattern[playHead][0], dummyPattern[playHead][1] , dummyPattern[playHead][2]);
		}
	}
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		dummyPattern[button][0] = 10;
		dummyPattern[button][1] = 40;
		dummyPattern[button][2] = 110;
		patternBitMap |= 0x1 << button;
	};
	virtual ~sequencer() {};
private:
	bool mOn;
};