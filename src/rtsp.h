#include "ofMain.h"

class RTSPinterfaces {
    public:
        string host;
        string user;
        string pass;

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
