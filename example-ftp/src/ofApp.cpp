#include "ofMain.h"
#include "ofApp.h"

void ofApp::setup(){
	ofSetFrameRate(25);

	w=ofGetScreenWidth();
	h=ofGetScreenHeight();
	ftp.init();
}

void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofApp::draw(){
	ofBackgroundGradient(255,0);
	ofDrawBitmapStringHighlight("press: l - select file",       ofPoint(10,20,0));
	ofDrawBitmapStringHighlight("press: d - download file file",ofPoint(10,50,0));
}

void ofApp::keyPressed(int key){
	if(key == 'l'){
		vector<string> s = ftp.list(4);
		for(int i = 0; i < s.size(); i++) {
			cout << s[i] <<endl;
		}
		if(s.size()>0){
			imgTmp=s[3];
			cout<<"select img:"<<imgTmp<<endl;
		}
	}
	if(key == 'd'){
		vector<string> fileName = ofSplitString(imgTmp," ");
		string localFolder = "/var/tmp/";
		string remoteFolder= ftp.getPath(3);
		cout<<"file-name:"<<fileName[fileName.size()-1]<<",local-folder:"<<localFolder<<",remote-folder:"<<remoteFolder<<endl;
		if(ftp.getFile( fileName[fileName.size()-1], localFolder, remoteFolder )){
			cout<<"download: " <<fileName[fileName.size()-1]<<" > "<<localFolder<<endl;
		}
	}
}
