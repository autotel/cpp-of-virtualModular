#pragma once
class ModuleView
{
public:
	ModuleView() {}
	int addModule(Module *m) {
		int reference = 0;
		//add the module to the list of module pointers (modules[]),
		//and return a reference where the pointer is stored in modules[]
		return reference;
	}
	void switchToModule(int modRef) {
		//run disengage in the currently viewed module
		//run engage in the newly viewed module
		//store the reference to the current module
	}
	//for every user input event,
	void onMatrixButton() {
		//forward the event to the currently selected module
	}
private:
	//TODO: of course, this should be  a vector and not an array
	Module *modules[16];
};