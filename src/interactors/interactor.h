#pragma once
class Interactor
{
public:
	bool engaged;
	virtual void init(hardwareController & HWCont) = 0;
	virtual void onMatrixButtonPressed(unsigned char button, unsigned int map) = 0;
	virtual void engage() = 0;
	virtual void disengage() = 0;
	virtual ~Interactor() {};
};