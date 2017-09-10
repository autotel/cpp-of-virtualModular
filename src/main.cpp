#include "ofMain.h"
#include "ofApp.h"
#define GUI false
//========================================================================
int main( ){
#if GUI
		ofSetupOpenGL(1024, 768, OF_WINDOW);
#else
		ofAppNoWindow window;
		ofSetupOpenGL(&window, 0, 0, OF_WINDOW);
		ofRunApp(new ofApp());
#endif

	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
