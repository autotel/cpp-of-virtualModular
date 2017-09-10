#pragma once

#include "./modules/midiDummy.h"
#include "./modules/textDummy.h"
#include "./modules/sequencer.h"
class moduleFactory
{
public:
	static module *newModule(int  choice)
	{
		if (choice == 1)
			return new midiDummy;
		if (choice == 2)
			return new textDummy;
		if (choice == 3)
			return new sequencer;
		return 0;
	}
};