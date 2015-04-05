#include "ofMain.h"
#include "ofApp.h"
#define OF_9

int main(){
        #ifdef OF_9
        ofGLWindowSettings settings;
        settings.width=1280;
        settings.height=360;
        ofCreateWindow(settings);
        #else
        ofSetupOpenGL(1280,360, OF_FULLSCREEN);
        #endif
        ofRunApp(new ofApp());
}
