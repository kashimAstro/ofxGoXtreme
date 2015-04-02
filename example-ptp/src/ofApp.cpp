#include "ofMain.h"
#include "ofApp.h"

PTPinterfaces ptp;
int w,h;

void ofApp::setup(){
	ofSetFrameRate(25);

	w=ofGetScreenWidth();
	h=ofGetScreenHeight();
	ptp.init();
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofApp::draw(){
	ofBackgroundGradient(255,0);
	ofDrawBitmapStringHighlight("press: 1 - list file",       ofPoint(10,20,0));
        ofDrawBitmapStringHighlight("press: 2 - capture photo" ,  ofPoint(10,50,0));
}

void ofApp::keyPressed(int key){
	if(key == '1'){
               ptp.listFile();
        }
        if(key == '2'){
               ptp.captureSingleImage();
        }
}
