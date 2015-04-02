#include "ofThread.h"

class command : public ofThread {
        public:
                ofEvent<string> commandComplete;
                void callCommand( string command ){
                        cmd = command;
                        stopThread();
                        startThread( );
                }

                std::string exec(char* cmd) {
                        FILE* pipe = popen(cmd, "r");
                        if (!pipe) return "ERROR";
                        char buffer[128];
                        std::string result = "";
                        while(!feof(pipe)) {
                                if(fgets(buffer, 128, pipe) != NULL)
                                result += buffer;
                        }
                        pclose(pipe);
                        return result;
                }

                void stop(){
                        stopThread();
                }
        private:
                void threadedFunction(){
                        ofLog( OF_LOG_VERBOSE, "call "+cmd );
                        string result = exec( (char *) cmd.c_str() );
                        ofLog( OF_LOG_VERBOSE, "RESULT "+result );
                        stopThread();
                        ofNotifyEvent( commandComplete, result, this );
                }

                string cmd;
};
