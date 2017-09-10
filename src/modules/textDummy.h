#ifndef module
#include "./modules/module.h"
#endif // !module

class textDummy : public module
{
public:
	void init() override { mOn = true; };
	void setOutput() override {};
	void onMatrixButtonPressed(unsigned char button, unsigned int map) override {
		mOn = false;
		ofLog(OF_LOG_NOTICE, "Pliiiing ");
	};
	void engage() override {};
	void disengage() override {};
	void receive() override {}
	virtual ~textDummy() {};
private:
	bool mOn;
};