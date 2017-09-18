#pragma once
class EventMessage
{
public:
	vector <int> value;
	EventMessage(vector <int> &from) {
		value = from;
	}
	EventMessage(EventMessage &from) {
		value = from.value;
	}
	EventMessage(int head) {
		value = { head };
	}
	EventMessage(int head, int a) {
		value = { head, a };
	}
	EventMessage(int head, int a, int b) {
		value = { head, a, b };
	}
	EventMessage(int head, int a, int b, int c) {
		value = { head, a, b, c};
	}
	void EventMessage::fillWith(EventMessage &other) {
		//TODO: i have not defined a value that will represent "transparent"
		if (value.size() > other.value.size()) {
			return;
		}
	}
	void EventMessage::midiFill() {
		while (value.size() <= 3) {
			value.push_back(90);
		}
	}
	void EventMessage::append(int w) {
		value.push_back(w);
	}
	void EventMessage::change(unsigned int to, unsigned int index) {
		value[index] = to;
	}
	bool EventMessage::equals(EventMessage &other) {
		return value == other.value;
	}
	bool EventMessage::equals(EventMessage &other, unsigned int index) {
		return value[index] == other.value[index];
	}
	~EventMessage() {}
private:

};