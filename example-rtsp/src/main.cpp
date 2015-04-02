#include "ofMain.h"
#include "ofxGoXtreme.h"

class xApp : public ofBaseApp {
	public:
		ofVideoPlayer p;
		RTSPinterfaces rtsp;
		int w,h;

		void setup(){
			ofSetFrameRate(25);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

			string path = rtsp.getCameraMediaPath();
			p.loadMovie(path);
			p.play();
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			p.update();
		}

		void draw(){
			ofBackgroundGradient(255,0);
			p.draw(0,0);
		}

		void keyPressed(int key){

		}
};

int main( ){
	ofGLWindowSettings settings;
        settings.width=640;
        settings.height=360;
        ofCreateWindow(settings);
	ofRunApp(new xApp());
}
