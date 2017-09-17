#pragma once
class eventMessage
{
public:
	vector <int> value;
	eventMessage(vector <int> &from) {
		value = from;
	}
	eventMessage(eventMessage &from) {
		value = from.value;
	}
	eventMessage(int head) {
		value = { head };
	}
	eventMessage(int head, int a) {
		value = { head, a };
	}
	eventMessage(int head, int a, int b) {
		value = { head, a, b };
	}
	eventMessage(int head, int a, int b, int c) {
		value = { head, a, b, c};
	}
	void eventMessage::fillWith(eventMessage &other) {
		//TODO: i have not defined a value that will represent "transparent"
		if (value.size() > other.value.size()) {
			return;
		}
	}
	void eventMessage::midiFill() {
		while (value.size() <= 3) {
			value.push_back(90);
		}
	}
	void eventMessage::append(int w) {
		value.push_back(w);
	}
	void eventMessage::change(unsigned int to, unsigned int index) {
		value[index] = to;
	}
	bool eventMessage::equals(eventMessage &other) {
		return value == other.value;
	}
	bool eventMessage::equals(eventMessage &other, unsigned int index) {
		return value[index] == other.value[index];
	}
	~eventMessage() {}
private:

};