#pragma once


#include "./modules/midiDummy.h"
#include "./modules/textDummy.h"
#include "./modules/sequencer.h"
 
#define MODULE_SEQUENCER 3
#define MODULE_MIDI 1

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