
//TODO: clean this up!!
class Scheduler : public ofThread {
public:
	
	Scheduler(Module *m) {
		timer.setPeriodicEvent(125000000); // this is .125 second in nanoseconds
		startThread();
		mm = m;
	}

private:
	Module *mm;
	ofTimer timer;
	void threadedFunction() {
		while (isThreadRunning()) {
			timer.waitNext();
			EventMessage clockEvent= EventMessage(0);
			mm->receive(clockEvent);
		}
	}
};