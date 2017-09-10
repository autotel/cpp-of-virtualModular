#pragma once
#ifndef module
#include "./modules/module.h"
#endif // !module

//https://github.com/danomatika/ofxMidi

class patchMenu : public module
{
public:
	void init() override {
		ofLog(OF_LOG_NOTICE, "created patch menu");
	};
	void setOutput() override {};
	void engage() override {};
	void disengage() override {};
	void receive() override {}
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
	};
	virtual ~patchMenu() {};
private:
	bool mOn;
};