#include "ofMain.h"
#include "ofxGoXtreme.h"

class ofApp : public ofBaseApp {
	public:
		ofVideoPlayer p;
		RTSPinterfaces rtsp;
		int w,h;

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
};
