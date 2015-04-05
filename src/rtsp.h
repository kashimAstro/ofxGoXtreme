#include "ofMain.h"

class RTSPinterfaces {
    public:
        string host;
        string user;
        string pass;
	ofGstVideoUtils gst;
        ofTexture tex;

        RTSPinterfaces() {
            host="192.168.1.1";
            user="1234567890";
            pass="1234567890";
        }

        ~RTSPinterfaces(){

        }

        string getCameraTrack1() {
            string buffer = "rtsp://"+getHost()+"/MJPG/track1";//;seq=25838;rtptime=100001581
            return buffer;
        }

        string getCameraMediaPath( int width=320, int height=240, int quality=80, int bitrate=0x2dc6c0 ) {
                string buffer;
                buffer = "rtsp://"+getHost()+"/MJPG?W=";
                buffer += ofToString(width);
                buffer += ofToString("&H=");
                buffer += ofToString(height);
                buffer += ofToString("&Q=");
                buffer += ofToString(quality);
                buffer += ofToString("&BR=");
                buffer += ofToString(bitrate);
                return buffer;
        }

	void setup( int width=640, int height=360, int quality=100, int bitrate=0x2dc6c0 ) {
		string path = getCameraMediaPath(width,height,quality,bitrate);
        	gst.setPipeline("rtspsrc location=" + path + " latency=0 ! rtpjpegdepay ! decodebin ! videoconvert", OF_PIXELS_RGB, true, width, height);
	        gst.startPipeline();
	}

	void update() {
		gst.update();
	        if(gst.isFrameNew()) {
	            tex.loadData(gst.getPixels());
	        }
	}

	void draw(int x=0, int y=0, int w=640, int h=360) {
	        tex.draw(x,y,w,h);
	}

        string getHost(){
            return host;
        }

        string getUser(){
            return user;
        }

        string getPass(){
            return pass;
        }

};
