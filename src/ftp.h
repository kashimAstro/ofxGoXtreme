#include "ofMain.h"
#include "Poco/Net/FTPClientSession.h"
#include "Poco/StreamCopier.h"

class FTP {
	public:
	Poco::Net::FTPClientSession* ftpClient;
	string user, host, pass;
	int port;
	bool bSetup;
	bool bVerbose;

	void startFtp() {
	       endFtp();
	       ftpClient = new Poco::Net::FTPClientSession(host, port);
	}

	void endFtp() {
	       if( ftpClient != NULL ){
		       ftpClient->close();
		       delete ftpClient;
	               ftpClient = NULL;
	       }
	}

	FTP() {
	    ftpClient   = NULL;
	    bVerbose    = false;
	    host        = "";
	    user        = "";
	    pass        = "";
	    port        = 0;
	    bSetup      = false;
	}

    void setup(string _host, string username, string password, int _port=21) {
        host    = _host;
        user    = username;
        pass    = password;
        port    = _port;
        bSetup  = true;
    }

    int send(string fileName, string localFolder, string remoteFolder) {
        if( bSetup == false ){
            if( bVerbose ) printf("error - you need to call setup first\n");
            return -1;
        }

        int numBytes = 0;

        try{
            startFtp();

            if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());
            localFolder = ofToDataPath( localFolder );
            if(localFolder.length() > 0){
                if( localFolder[localFolder.length()-1] != '/' ){
                    localFolder += "/";
                }
            }

            if(remoteFolder.length() > 0){
                if( remoteFolder[remoteFolder.length()-1] != '/' ){
                    remoteFolder += "/";
                }
            }

            string localPath    = localFolder  + fileName;
            string remotePath   = remoteFolder + fileName;

            ostringstream remoteOSS;
            remoteOSS << remoteFolder << fileName;

            if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());

            ftpClient->login(user, pass);
            ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);

            ostream& ftpOStream = ftpClient->beginUpload(remoteOSS.str().c_str());  //how to make it overwrite?

            ifstream localIFStream(localPath.c_str(), ifstream::in | ifstream::binary);
            numBytes = Poco::StreamCopier::copyStream(localIFStream, ftpOStream);
            ftpClient->endUpload();

            endFtp();

            if(bVerbose)printf("uploaded %i bytes\n\n", numBytes);

        }
        catch (Poco::Exception& exc)
        {
            cout << exc.displayText() << endl;
            return -1;
        }
        return numBytes;

    }

    int get(string fileName, string localFolder, string remoteFolder) {
        if( bSetup == false ){
            if( bVerbose )printf("error - you need to call setup first\n");
            return -1;
        }
        int numBytes = 0;

        try{
            startFtp();
            if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());
            localFolder = ofToDataPath( localFolder );
            if(localFolder.length() > 0){
                if( localFolder[localFolder.length()-1] != '/' ){
                    localFolder += "/";
                }
            }

            if(remoteFolder.length() > 0){
                if( remoteFolder[remoteFolder.length()-1] != '/' ){
                    remoteFolder += "/";
                }
            }

            string localPath    = localFolder  + fileName;
            string remotePath   = remoteFolder + fileName;

            ostringstream remoteOSS;
            remoteOSS << remoteFolder << fileName;

            if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());

            ftpClient->login(user, pass);
            ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
            istream& ftpOStream = ftpClient->beginDownload(remoteOSS.str().c_str());

            ofstream localIFStream(localPath.c_str(), ifstream::out | ifstream::binary);
            numBytes = Poco::StreamCopier::copyStream(ftpOStream, localIFStream);
            ftpClient->endDownload();
            endFtp();

            if(bVerbose)printf("downloaded %i bytes\n\n", numBytes);

        }
        catch (Poco::Exception& exc)
        {
            cout << exc.displayText() << endl;
            return -1;
        }
    }

    vector<string> list(string path) {
        try{
            startFtp();
            string res;
            ftpClient->login(user, pass);
            istream &ist = ftpClient->beginList(path, true);
            Poco::StreamCopier::copyToString(ist, res);
            ftpClient->endList();

            return ofSplitString(res, "\n", true, true);
            endFtp();
        }
        catch (Poco::Exception& exc)
        {
            cout << exc.displayText() << endl;
        }

    }
    void setVerbose(bool verbose) {
        bVerbose = verbose;
    }
};

class FTPinterfaces {
    public:
        vector<string> remote_path;
        string host,user,pass;
        FTP client;

        void init(){
            client.setup(host,user,pass);
            client.setVerbose(true);
            remote_path.push_back("/");              //0
            remote_path.push_back("/DCIM/");	     //1
            remote_path.push_back("/DCIM/100CARDV/");//2
            remote_path.push_back("/DCIM/100EVENT/");//3
            remote_path.push_back("/DCIM/100IMAGE/");//4
            remote_path.push_back("/DCIM/100VIDEO/");//5
        }

        string getPath(int path){
            return remote_path[path];
        }

        vector<string> list(int path){
            cout<<"path:"<<remote_path[path]<<endl;
            return client.list(remote_path[path]);
        }

        bool sendFile(string _path, string remotepath) {
            ofFile file(_path);
            string path = file.path().substr(0,file.path().length()-file.getFileName().length());
            if(client.send(file.getFileName(),path,"/")>0){
                return true;
            }
            return false;
        }

        bool getFile(string name, string path, string  remotepath){
            if(client.get(name,path,remotepath)>0){
                   return true;
            }
            return false;
        }
};
