#pragma once

#include "./interactions/eventSelector.h"
#include "./interactions/patchMenu.h"

class interactorFactory
{
public:
	/*
	static interactor *eventSelector() {
		return new eventSelector;
	}*/
	static interactor *newModule(int  choice)
	{
		if (choice == 1)
			return new eventSelector;
		if (choice == 2)
			return new patchMenu;
		return 0;
	}
};