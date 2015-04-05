#include "ofMain.h"
#include "ofApp.h"

void ofApp::setup(){
	ofSetFrameRate(25);

	w=ofGetScreenWidth();
	h=ofGetScreenHeight();
	rtsp.setup();
	p.load(rtsp.getCameraMediaPath());
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	rtsp.update();
	p.update();
}

void ofApp::draw(){
	ofBackgroundGradient(255,0);
	rtsp.draw();
	p.draw(rtsp.tex.getWidth(),0);
        ofDrawBitmapStringHighlight("not latency ofGstVideoUtils", ofPoint(10,20,0));
        ofDrawBitmapStringHighlight("latency ofVideoPlayer",       ofPoint(rtsp.tex.getWidth()+20,20,0));
}

void ofApp::keyPressed(int key){

}
