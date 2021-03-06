#pragma once
#ifndef interactor
#include "./interactors/Interactor.h"
#endif // !module
class EventSelector : public Interactor
{
public:
	HardwareController myHWCont;
	void init(HardwareController & HWCont) override {

	};
	void engage() override {
		engaged = true;
	};

	void disengage() override {
		engaged = false;
	};
	bool onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		return engaged;
	};
	virtual ~EventSelector() {};
private:

};