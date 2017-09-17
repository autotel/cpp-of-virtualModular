#pragma once
#ifndef module
#include "./modules/module.h"
#endif // !module
//#include "ofxMidi.h"
//https://github.com/danomatika/ofxMidi

class sequencer : public module
{
public:
	//ofxMidiOut midiOut;
	module *moutput;
	int dummyPattern [16][3];
	int patternBitMap = 0x0000;
	int playHead = 0;
	
	eventSelector eventSelector();

	hardwareController myX16pad;
	void init(hardwareController & HWCont) override {
		myX16pad = HWCont;
		ofLog(OF_LOG_NOTICE, "created midi dummy");
		for (int a = 0; a < 16; a++) {
			dummyPattern[a][0] = 0;
		}
		//midiOut.listPorts(); // via instance
							 //ofxMidiOut::listPorts(); // via static too
		//midiOut.openPort(0); // by number
							 //midiOut.openPort("IAC Driver Pure Data In"); // by name
							 //midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
		//midiOut.sendNoteOn(10, 45, 100);
	};
	void setOutput(module *m) override {
		moutput = m;
	};
	void engage() override {};
	void disengage() override {};
	void receive(eventMessage evm) override {
		playHead++;
		playHead %= 16;
		if (dummyPattern[playHead][0] != 0) {
			moutput->receive(eventMessage(dummyPattern[playHead][0], dummyPattern[playHead][1], dummyPattern[playHead][2]));
			//midiOut.sendNoteOn();
		}
		updateLeds();
	}
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		dummyPattern[button][0] = 10 | (0<<12);
		dummyPattern[button][1] = 40;
		dummyPattern[button][2] = 110;
		patternBitMap |= 0x1 << button;
		updateLeds();
	};
	virtual ~sequencer() {};
private:
	bool mOn;
	void updateLeds() {
		myX16pad.setLed(patternBitMap, 1 << playHead, 0);
	}
};