#include "ofMain.h"
#include "ofxGoXtreme.h"

class ofApp : public ofBaseApp {
	public:
		PTPinterfaces ptp;
		int w,h;

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
};
