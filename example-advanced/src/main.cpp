#include "ofMain.h"
#include "ofxGoXtreme.h"

class xApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		ofVideoPlayer p;
		RTSPinterfaces rtsp;
		PTPinterfaces ptp;
		FTPinterfaces ftp; 
		int w,h;

		void setup(){
			ofSetFrameRate(25);

			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

			string path = rtsp.getCameraMediaPath(640, 360, 100, 3000000);
			p.loadMovie(path);
			p.play();

			ptp.init();
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			p.update();
		}

		void draw(){
			ofBackgroundGradient(255,0);
			p.draw(0,0);
		}

		string img;
		void keyPressed(int key){
			/* refresh rtsp */
			if(key == 'r') {
				p.close();
				string path = rtsp.getCameraMediaPath(640, 360, 100, 6000000);
				p.loadMovie(path);
				p.play();
			}
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
};

int main( ){
        ofGLWindowSettings settings;
	settings.width=640;
	settings.height=360;
        ofCreateWindow(settings);
        ofRunApp(new xApp());
}
