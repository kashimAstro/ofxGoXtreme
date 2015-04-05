#include "ofApp.h"

void ofApp::setup(){
	ofSetFrameRate(25);
	w=ofGetScreenWidth();
	h=ofGetScreenHeight();

	rtsp.setup();
	ptp.init();
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	rtsp.update();
}

void ofApp::draw(){
	ofBackgroundGradient(255,0);
	rtsp.draw(0,0);
        ofDrawBitmapStringHighlight("press: l - select file ftp",  ofPoint(10,50,0));
        ofDrawBitmapStringHighlight("press: d - download file ftp",ofPoint(10,80,0));
        ofDrawBitmapStringHighlight("press: 1 - list file ptp",    ofPoint(10,110,0));
        ofDrawBitmapStringHighlight("press: 2 - capture photo ptp",ofPoint(10,140,0));
}

void ofApp::keyPressed(int key){
	/* ftp sample */
	if(key == 'l'){
		vector<string> s = ftp.list(4);
		for(int i = 0; i < s.size(); i++) {
			cout << s[i] <<endl;
		}
		if(s.size()>0){
			img=s[3];
			cout<<"select img:"<<img<<endl;
		}
	}
	if(key == 'd'){
		vector<string> fileName = ofSplitString(img," ");
		string localFolder = "/var/tmp/";
		string remoteFolder= ftp.getPath(4);
		cout<<"file-name:"<<fileName[fileName.size()-1]<<",local-folder:"<<localFolder<<",remote-folder:"<<remoteFolder<<endl;
		if(ftp.getFile( fileName[fileName.size()-1], localFolder, remoteFolder )){
			cout<<"download: " <<fileName[fileName.size()-1]<<" > "<<localFolder<<endl;
		}
	}
	/* ptp sample */
	if(key == '1'){
		ptp.listFile();
	}
	if(key == '2'){
		ptp.captureSingleImage();
	}
}
