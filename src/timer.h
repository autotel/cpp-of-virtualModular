
//TODO: clean this up!!
class Scheduler : public ofThread {
public:
	Scheduler(module *m) {
		timer.setPeriodicEvent(125000000); // this is .125 second in nanoseconds
		startThread();
		mm = m;
	}

private:
	module *mm;
	ofTimer timer;
	void threadedFunction() {
		while (isThreadRunning()) {
			timer.waitNext();
			mm->receive();
		}
	}
};