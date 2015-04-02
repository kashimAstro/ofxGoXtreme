#include "ofMain.h"
#include "ofxGoXtreme.h"

class xApp : public ofBaseApp {
	public:
		PTPinterfaces ptp;
		int w,h;

		void setup(){
			ofSetFrameRate(25);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
			ptp.init();
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
		}

		void draw(){
			ofBackgroundGradient(255,0);
		}

		void keyPressed(int key){
			if(key == '1'){
                                ptp.listFile();
                        }
                        if(key == '2'){
                                ptp.captureSingleImage();
                        }
		}
};

int main(){
        ofGLWindowSettings settings;
        settings.width=640;
        settings.height=360;
        ofCreateWindow(settings);
	ofRunApp(new xApp());
}
