#pragma once

class PatchMenu{
	public:
		PatchMenu() {};
		PatchMenu(hardwareController & HWCont, vector <Module *> &mods) {
			myX16pad = HWCont;
			modules = mods;
			ofLog(OF_LOG_NOTICE, "created patch menu");
		};

		~PatchMenu() {};
		void engage()  {
			myX16pad.sendScreenA("select module");
		};
		void disengage()  {};
		void onMatrixButtonPressed(unsigned char button, unsigned int map) {
			//warning: modules is a global. is that good or bad?
			for (int a = 0; a < modules.size(); a++) {
				modules[a]->onMatrixButtonPressed(button, map);
			}
		};
		
	private:
		hardwareController myX16pad;
		vector <Module *> modules;
};

