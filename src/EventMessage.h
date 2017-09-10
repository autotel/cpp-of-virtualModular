#pragma once
class eventMessage
{
public:
	eventMessage(/* array of vars */) {
		/*
		just keep the vars
		*/
	}
	eventMessage(eventMessage &from) {
		/*
		clone the from eventMessage
		*/
	}
	eventMessage(/*pointe to array or vector*/) {
		/*
		create from the data
		*/
	}
	void eventMessage::append() {}
	void eventMessage::change(unsigned int to, unsigned int index) {}
	bool eventMessage::equals(eventMessage &other) {}
	bool eventMessage::equals(eventMessage &other, unsigned int index) {}
	~eventMessage() {}
private:

};