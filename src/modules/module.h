#pragma once
class Module
{
public:

	bool engaged = false;

	virtual void init(HardwareController & HWCont) = 0;
	virtual void setUiHardware(HardwareController & HWCont) = 0;

	virtual bool onMatrixButtonPressed(unsigned char button, unsigned int map) = 0;
	virtual void engage() = 0;
	virtual void disengage() = 0;
	virtual void receive(EventMessage evm) = 0;
	virtual void setOutput(Module *m) = 0;

	virtual ~Module() {};
};