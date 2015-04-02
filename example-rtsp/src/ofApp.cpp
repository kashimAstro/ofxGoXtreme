#include "ofMain.h"
#include "ofApp.h"

ofVideoPlayer p;
RTSPinterfaces rtsp;
int w,h;

void ofApp::setup(){
	ofSetFrameRate(25);

	w=ofGetScreenWidth();
	h=ofGetScreenHeight();

	string path = rtsp.getCameraMediaPath();
	p.loadMovie(path);
	p.play();
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	p.update();
}

void ofApp::draw(){
	ofBackgroundGradient(255,0);
	p.draw(0,0);
}

void ofApp::keyPressed(int key){

}
