#pragma once

class PatchMenu{
	public:
		PatchMenu() {};
		PatchMenu(hardwareController & HWCont) {
			myX16pad = HWCont;
			ofLog(OF_LOG_NOTICE, "created patch menu");
			modules;
		};

		~PatchMenu() {};
		void engage()  {
			myX16pad.sendScreenA("select module");
		};
		void disengage()  {};
		void onMatrixButtonPressed(unsigned char button, unsigned int map) {

		};
		
	private:
		hardwareController myX16pad;
};

