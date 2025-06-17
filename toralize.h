#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <stdbool.h>

#define PROXYHOST "127.0.0.1"
#define PROXYPORT 9050
#define VERSION 4
#define CONNECT 1
#define USERNAME "hsheikh"

typedef unsigned char int8;
typedef unsigned short int16;
typedef unsigned int int32;


struct proxy_request{
    int8 vn; //version = VERSION
    int8 cd; //command code = CONNECT
    int16 dstport; //destination port
    int32 dstip; //destination ip
    char userid[8]; //USERNAME
};

struct proxy_response{ 
    int8 vn;
    int8 cd;
    int16 dstport; //ignored
    int32 dstip; //ignored
};

typedef struct proxy_request Req;
typedef struct proxy_response Res;

#define reqsize sizeof(Req);
#define ressize sizeof(Res);

int request(Req**, struct sockaddr_in*);
int connect(int, const struct sockaddr*, socklen_t);
