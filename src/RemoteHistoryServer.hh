#ifndef ___REMOTE_HISTORY_SERVER__
#define ___REMOTE_HISTORY_SERVER__

///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <exception>

///////////////////////////////////////////////////////////////////////////////
//chockets
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
///////////////////////////////////////////////////////////////////////////////
//hiloxh

#include <pthread.h>

///////////////////////////////////////////////////////////////////////////////

#include "LocalHistory.hh"

///////////////////////////////////////////////////////////////////////////////

using namespace std;


namespace exoo {

    class remote_history_server_exception : public exception {};    

    class RemoteHistoryServer {
    
    private:

        int port; 
        vector<pthread_t*> threads;
        bool stop;
        int socket_server;
        History *history;
        static const int MAX_CONNECTION_COUNT = 100;
        
    public:

        RemoteHistoryServer(int port) {
            this->port = port();
            this->stop = false;
            socket_server = -1;
            history = new LocalHistory();
        }

        virtual ~RemoteHistoryServer() {
            stop();
        }

        void start() {
            struct sockaddr *address;
            socket_server = socket(AF_INET, SOCK_STREAM, 0);

            if (socket_server < 0) throw remote_history_server_exception();

            address = (struct sockaddr*)new sockaddr_in;
            ((struct sockaddr_in*)address)->sin_family = AF_INET;
            ((struct sockaddr_in*)address)->sin_addr.s_addr = INADDR_ANY;
            ((struct sockaddr_in*)address)->sin_port = htons(port);

            if (bind(socket_server, address, sizeof(*address)))
                throw remote_history_server_exception();
           
            if (listen(socket_server, MAX_CONNECTION_COUNT) != 0)
                throw remote_history_server_exception();

            fd_set file_descriptors;
            struct timeval time;
            
            
            while (!stop) {
                FD_ZERO(&file_descriptors);
                FD_SET(socket_server, &file_descriptors);

                time.tv_sec = 1;
                time.tv_usec = 0;

                retval = select(socket_server + 1, &file_descriptors, NULL, NULL, &time);
                if (FD_ISSET(socketServer, &fileDescriptorSet)){
                    int client_socket = accept(socket_server, NULL, NULL);
                }
            } 
        }
        
        void stop() {
            for (int i = 0; i < (int)threads.size(); i++) {
                pthread_cancel(*threads[i]); 
                pthread_join(*threads[i], NULL);
            }
        }
    private: 


    }
}

#endif
