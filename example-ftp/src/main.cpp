#include "ofMain.h"
#include "ofxGoXtreme.h"

class xApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		FTPinterfaces ftp;
		int w,h;
		string imgTmp;


		void setup(){
			ofSetFrameRate(25);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
			ftp.init();
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
		}

		void draw(){
			ofBackgroundGradient(255,0);
		}

		void keyPressed(int key){
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
				string remoteFolder= ftp.getPath(4);
				cout<<"file-name:"<<fileName[fileName.size()-1]<<",local-folder:"<<localFolder<<",remote-folder:"<<remoteFolder<<endl;
				if(ftp.getFile( fileName[fileName.size()-1], localFolder, remoteFolder )){
					cout<<"download: " <<fileName[fileName.size()-1]<<" > "<<localFolder<<endl;
				}
			}
			
		}
};

int main( ){
	ofGLWindowSettings settings;
        settings.width=640;
        settings.height=360;
        ofCreateWindow(settings);
	ofRunApp(new xApp());
}
