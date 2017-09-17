#pragma once
#ifndef interactor
#include "./interactions/interactor.h"
#endif // !module

//https://github.com/danomatika/ofxMidi

class patchMenu : public interactor
{
public:
	void init(hardwareController & HWCont) override {
		ofLog(OF_LOG_NOTICE, "created patch menu");
	};
	void engage() override {};
	void disengage() override {};
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
	};
	virtual ~patchMenu() {};
private:
	bool mOn;
};