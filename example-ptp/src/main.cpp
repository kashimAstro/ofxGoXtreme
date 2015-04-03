#include "ofMain.h"
#include "ofApp.h"
#define OF_9

int main(){
        #ifdef OF_9
        ofGLWindowSettings settings;
        settings.width=640;
        settings.height=360;
        ofCreateWindow(settings);
        #else
        ofSetupOpenGL(630,360, OF_FULLSCREEN);
        #endif
        ofRunApp(new ofApp());
}
