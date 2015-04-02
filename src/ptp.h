#include "ofMain.h"
#include "command.h"

#define DEBUG

class PTPinterfaces{
	public:
	string IPptp;
	string MarkerImage;
	string MarkerVideo;
	string PATHVIDEO;
	string PATHPHOTO;
	string FORMATVIDEO;
	string FORMATPHOTO;

	void init(string _ip="192.168.1.1",string _BINARY="/usr/bin/gphoto2") {
		IPptp=_ip;
		BINARY = _BINARY;

		MarkerImage = "image/jpeg";
		MarkerVideo = "video/quicktime";
		PATHVIDEO   = "/DCIM/100VIDEO/";
		PATHPHOTO   = "/DCIM/100PHOTO/";
		FORMATVIDEO = "MOV";
		FORMATPHOTO = "JPG";

        ofAddListener(ptp.commandComplete, this, &PTPinterfaces::complete);
	}

	void listFile() {
		stringstream cmd;
		cmd << BINARY <<" --port ptpip:" << IPptp << " --camera \"PTP/IP Camera\" -L";
		#ifdef DEBUG
		ofLog()<<"command-list-file:"<<cmd.str()<<endl;
		#endif
                ptp.callCommand( cmd.str() );
	}

	void captureSingleImage( string name=ofGetTimestampString() ){
		stringstream cmd;
		cmd << BINARY <<" --port ptpip:" << IPptp << " --camera \"PTP/IP Camera\" --capture-image";
		#ifdef DEBUG
		ofLog()<<"command-single-image:"<<cmd.str()<<endl;
		#endif
                ptp.callCommand( cmd.str() );
	}

	void captureSingleMovie( string name=ofGetTimestampString() ) {
		stringstream cmd;
		cmd << BINARY <<" --port ptpip:" << IPptp << " --camera \"PTP/IP Camera\" --capture-movie";
		#ifdef DEBUG
		ofLog()<<"command-single-video:"<<cmd.str()<<endl;
		#endif
		ptp.callCommand( cmd.str() );
	}

	void stopCaptureMovie( ) {
		ofLog()<<"Stop process!"<<endl;
		ptp.stop();
	}

	private:
	string BINARY;
	command ptp;

	void complete(string & value) {
		vector<string> result = ofSplitString(value,"\n");
		for(int i = 0; i < result.size(); i++){
			if(result[i]!=""){
				/* photo */
				size_t foundPhoto = result[i].find(MarkerImage);
				if (foundPhoto!=string::npos) {
					vector<string> resphoto = ofSplitString(result[i]," ");
					string xpath;
					for(int x = 0; x < resphoto.size(); x++) {
						size_t formatPhoto = resphoto[x].find(FORMATPHOTO);
						if (formatPhoto!=string::npos) {
							xpath=resphoto[x];
						}
					}
					#ifdef DEBUG
					ofLog()<<"Found:"<<PATHPHOTO<<xpath<<endl;
					#endif
				}
				/* video */
				size_t foundVideo = result[i].find(MarkerVideo);
				if (foundVideo!=string::npos) {
					vector<string> resvideo = ofSplitString(result[i]," ");
					string vpath;
					for(int v = 0; v < resvideo.size(); v++) {
						size_t formatVideo = resvideo[v].find(FORMATVIDEO);
						if (formatVideo!=string::npos) {
							vpath=resvideo[v];
						}
					}
					#ifdef DEBUG
					ofLog()<<"Found:"<<PATHVIDEO<<vpath<<endl;
					#endif
				}
			}
		}
	}
	/**/
};
