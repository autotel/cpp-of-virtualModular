#ifndef module
#include "./modules/module.h"
#endif // !module
#include "ofxMidi.h"
//https://github.com/danomatika/ofxMidi

class midiDummy : public module
{
public:
	ofxMidiOut midiOut;
	module *moutput;
	class headers {
		public:
			int noteOn = 0;
			int noteOff = 1;
			int noteWithLength = 2;
	};
	void init(hardwareController & HWCont) override {
		ofLog(OF_LOG_NOTICE,"created midi dummy");
		mOn = true; 

		midiOut.listPorts(); // via instance
							 //ofxMidiOut::listPorts(); // via static too
		midiOut.openPort(6); // by number
							 //midiOut.openPort("IAC Driver Pure Data In"); // by name
							 //midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
		midiOut.sendNoteOn(10, 45, 100);
	};
	void setOutput(module *m) override {
		moutput = m;
	};
	void engage() override {};
	void disengage() override {};
	void receive(eventMessage m) override {
		m.midiFill();
		cout << "FnHead:" << (m.value[0] >> 12) << ", chan:" << (m.value[0] & 0xff) << ", val a:" << m.value[1] << ", val b:" << m.value[2] << "\n";
		switch (m.value[0]>>12) {
			//noteon until noteoff
			case 0:
				cout << "on";
				midiOut.sendNoteOn(( m.value[0] & 0x0f), m.value[1], m.value[2]);
				break;
				//noteoff
			case 1:
				cout << "off";
				midiOut.sendNoteOff((m.value[0] & 0x0f), m.value[1], m.value[2]);
				break;
				//noteon, sustained for  n clocks
			case 2: break;
			case 0x80: break;
			case 0x90: break;
		}
	}
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		mOn = false; 
		midiOut.sendNoteOn(10, 36+button, 100);
	};
	virtual ~midiDummy() {};
private:
	bool mOn;
};