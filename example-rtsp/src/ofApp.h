#include "ofMain.h"
#include "ofxGoXtreme.h"
#define OF_9

class ofApp : public ofBaseApp {
	public:
		ofVideoPlayer p;
		RTSPinterfaces rtsp;
		int w,h;
		ofGstVideoUtils gst;
		ofTexture tex;



		void setup();
		void update();
		void draw();
		void keyPressed(int key);
};
