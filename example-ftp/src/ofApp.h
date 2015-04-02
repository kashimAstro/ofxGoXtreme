#include "ofMain.h"
#include "ofxGoXtreme.h"

class ofApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		FTPinterfaces ftp;
		int w,h;
		string imgTmp;

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
};
