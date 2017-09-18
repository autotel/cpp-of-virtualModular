#pragma once

#include "./interactors/EventSelector.h"
#define INTERACTOR_EVENTSELECTOR 0
#define INTERACTOR_PATCHMENU 1
class interactorFactory
{
public:


	static Interactor *make(int  choice)
	{
		if (choice == 0)
			return new EventSelector;
		return 0;
	}

};