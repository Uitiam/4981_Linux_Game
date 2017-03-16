#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <string>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <limits.h>
#include <atomic>
#include <memory>
#include <map>
#include "../UDPHeaders.h"

#include "../player/Player.h"

#define STDIN           0
#define TCP_PORT 		35223
#define UDP_PORT 		35222
#define STD_BUFFSIZE    1024
#define MAX_EVENTS 		1
#define MAX_USERS		23
#define SYNC_PACKET_MAX USHRT_MAX


//moved enums to the bottom, and commented out

enum class NetworkState {
    NOT_RUNNING,
    GAME_STARTED
};

class NetworkManager {
public:
    static NetworkManager& instance();
    void run(const char *ip, const char *username);
    void closeConnection();
    int writeSocket(int, const char *, int);
    void writeUDPSocket(const char *buf, const int &len);

    int32_t getPlayerId() const {return _myid;};
    NetworkState getNetworkState() const {return state;};
private:
    NetworkState state = NetworkState::NOT_RUNNING;
    int32_t _myid;  // EY: March 14 - to be removed for game intergration
    bool connected, running; // EY: March 14 - to be removed for game intergration
    int sockTCP;
    int sockUDP;
    in_addr_t serverIP;
    NetworkManager() {};

    void runTCPClient();
    void runUDPClient();
    int readUDPSocket(char *buf, const int& len);
    int createSocket(int) const;
    int connectSocket(const char *) const;
    void connectSocket(int sock, const struct sockaddr_in& addr) const;
    void bindSocket(int sock, struct sockaddr_in addr);
    void handshake(const char * ip, const char * uname);
    void waitRecvId();

    struct sockaddr_in createAddress(const in_addr_t ip, const int port) const;
    int readSocket(int sock, char *buf, int len) const;

};

#endif

/*
//ENUMS
#ifndef PACKET_SPECIFIER_ENUMCL
#define PACKET_SPECIFIER_ENUMCL

enum class P_SPECIFIER{
	  EXIT,
		UNAME,
		CHAT
};

#endif

#ifndef GAMESTATE_ENUMCL
#define GAMESTATE_ENUMCL

enum class GAMESTATE{
		GAME_RECV,
		AI_RECV
};
#endif
*/
