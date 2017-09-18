#pragma once
#ifndef Module
#include "./interactors/EventSelector.h"
#endif // !module
//#include "ofxMidi.h"
//https://github.com/danomatika/ofxMidi

class Sequencer : public Module
{
public:
	//ofxMidiOut midiOut;
	Module *moutput;
	int dummyPattern[16][3];
	int patternBitMap = 0x0000;
	int playHead = 0;

	Interactor *eventSelector;


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
		eventSelector = interactorFactory::make(INTERACTOR_EVENTSELECTOR);
	};
	void setUiHardware(hardwareController & HWCont) override {
		myX16pad = HWCont;
	};
	void setOutput(Module *m) override {
		moutput = m;
	};
	void engage() override {
		engaged = true;
	};
	void disengage() override {
		eventSelector->disengage();
		engaged = false;
	};
	void receive(EventMessage evm) override {
		playHead++;
		playHead %= 16;
		if (dummyPattern[playHead][0] != 0) {
			moutput->receive(EventMessage(dummyPattern[playHead][0], dummyPattern[playHead][1], dummyPattern[playHead][2]));
			//midiOut.sendNoteOn();
		}
		if (engaged) {
			updateLeds();
		}
	}
	bool onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		if (engaged) {
			dummyPattern[button][0] = 10 | (0 << 12);
			dummyPattern[button][1] = 40;
			dummyPattern[button][2] = 110;
			patternBitMap |= 0x1 << button;
			updateLeds();
			return true;
		}
		if ((*eventSelector).engaged) {

			return true;
		}
		return false;
	};

	virtual ~Sequencer() {};
private:
	bool engaged=false;
	void updateLeds() {
		myX16pad.setLed(patternBitMap, 1 << playHead, 0);
	}
};