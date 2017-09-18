#pragma once

class PatchMenu{
	public:
		bool engaged = false;
		HardwareController* myX16pad;
		
		PatchMenu() {
		};

		void init(HardwareController& HWCont, vector <Module *> &mods) {
			myX16pad = &HWCont;
			modules = mods;
		};
		~PatchMenu() {};
		void engage()  {
			updateLeds();
			myX16pad->sendScreenA("select mod");
			engaged = true;
		};
		void disengage()  {
			engaged = false;
		};
		bool onMatrixButtonPressed(unsigned char button, unsigned int map) {
			//myX16pad.sendScreenB("lalal");
			cout << "lala";
			bool taken = false;
			//warning: modules is a global. is that good or bad?
			for (int a = 0; a < modules.size(); a++) {
				//make sure no two modules are engaged at the same time.
				if (taken & modules[a]->engaged) {
					modules[a]->disengage();
				}
				taken |= modules[a]->onMatrixButtonPressed(button, map);
			}
			if (!taken & !engaged) {
				engage();
				taken = true;
			}
			return taken;
		};
		int selectedModuleIndex;
		void updateLeds() {
			int availableModulesMap = ~(0xffff << modules.size());
			int a = 1 << selectedModuleIndex;
			int b = (1 << selectedModuleIndex ) | availableModulesMap;
			myX16pad->setLed(a, b, b);
		}
	private:
		vector <Module *> modules;
};

