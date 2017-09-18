#pragma once
class Module
{
public:
	virtual void init(hardwareController & HWCont) = 0;
	virtual void setUiHardware(hardwareController & HWCont) = 0;

	virtual void onMatrixButtonPressed(unsigned char button, unsigned int map) = 0;
	virtual void engage() = 0;
	virtual void disengage() = 0;
	virtual void receive(EventMessage evm) = 0;
	virtual void setOutput(Module *m) = 0;

	virtual ~Module() {};
};