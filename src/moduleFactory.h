#pragma once


#include "./modules/MidiDummy.h"
#include "./modules/Sequencer.h"

#define MODULE_SEQUENCER 3
#define MODULE_MIDI 1

class moduleFactory
{
public:
	static Module *make(int  choice)
	{
		if (choice == 1)
			return new MidiDummy;
		if (choice == 3)
			return new Sequencer;
		return 0;
	}
};