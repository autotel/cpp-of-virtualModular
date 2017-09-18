#pragma once
class Interactor
{
public:
	bool engaged;
	virtual void init(HardwareController & HWCont) = 0;
	virtual bool onMatrixButtonPressed(unsigned char button, unsigned int map) = 0;
	virtual void engage() = 0;
	virtual void disengage() = 0;
	virtual ~Interactor() {};
};