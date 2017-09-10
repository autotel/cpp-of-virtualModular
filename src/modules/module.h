#pragma once
class module
{
public:
	virtual void init(hardwareController & HWCont) = 0;
	virtual void onMatrixButtonPressed(unsigned char button, unsigned int map) = 0;
	virtual void engage() = 0;
	virtual void disengage() = 0;
	virtual void receive() = 0;
	virtual void setOutput() = 0;
	virtual ~module() {}; /* without this, you do not call Laptop or Desktop destructor in this example! */
};