#include "ofMain.h"
#include "ofApp.h"

int main(){
	ofGLWindowSettings settings;
        settings.width=640;
        settings.height=360;
        ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
