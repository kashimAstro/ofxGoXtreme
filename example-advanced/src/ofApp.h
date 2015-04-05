#include "ofMain.h"
#include "ofxGoXtreme.h"

class ofApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		RTSPinterfaces rtsp;
		PTPinterfaces ptp;
		FTPinterfaces ftp; 
		int w,h;
		string img;

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
};
