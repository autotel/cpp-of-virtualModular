#ifndef Module
#include "./modules/Module.h"
#endif // !module
#include "ofxMidi.h"
//https://github.com/danomatika/ofxMidi

class MidiDummy : public Module
{
public:
	ofxMidiOut midiOut;
	Module *moutput;
	class headers {
		public:
			int noteOn = 0;
			int noteOff = 1;
			int noteWithLength = 2;
	};
	void init(HardwareController & HWCont) override {
		ofLog(OF_LOG_NOTICE,"created midi dummy");
		mOn = true;

		midiOut.listPorts(); // via instance
							 //ofxMidiOut::listPorts(); // via static too
		midiOut.openPort(0); // by number
							 //midiOut.openPort("IAC Driver Pure Data In"); // by name
							 //midiOut.openVirtualPort("ofxMidiOut"); // open a virtual port
		midiOut.sendNoteOn(10, 45, 100);
	};
	void setUiHardware(HardwareController & HWCont) override {
	};
	void setOutput(Module *m) override {
		moutput = m;
	};
	void engage() override {};
	void disengage() override {};
	void receive(EventMessage m) override {
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
	bool onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		mOn = false;
		midiOut.sendNoteOn(10, 36+button, 100);
		return false;
	};
	virtual ~MidiDummy() {};
private:
	bool mOn;
};