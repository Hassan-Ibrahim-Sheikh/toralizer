#include "toralize.h"

int connect(int s2, const struct sockaddr *sock2, socklen_t addrlen){
    printf("[TORALIZE] Intercepted connect() call\n");
   
    int s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1){
        perror("socket");
        fprintf(stderr, "Failed to initialize socket.\n");
        return -1;
    }


    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXYHOST);

    int (*p) (int, const struct sockaddr*, socklen_t);
    p = dlsym(RTLD_NEXT, "connect");

    if (p(s, (struct sockaddr *)&sock, sizeof(sock)) == -1){
        perror("connect");
        fprintf(stderr, "Failed to Connect to proxy.\n");
        close(s);
        return -1;
    }

    
    Req *req;  
    if(request(&req,(struct sockaddr_in *)sock2) == -1){
        fprintf(stderr, "Failed to populate the request.\n");
        free(req);
        close(s);
        return -1;
    }  



    if (write(s, req, sizeof(Req)) == -1){
        perror("write");
        free(req);
        close(s);
        return -1;
    }

    printf("Sent the request successfully\n");

    Res *res;
    char buffer[512];
        
    if (read(s, buffer, sizeof(Res)) == -1){
        perror("read");
        close(s);
        return -1;
    }    
    res = (Res *)buffer;


    bool success = (res->cd == 90);
    if (!success){
        fprintf(stderr, "The request was rejected.\nCommand Code: %d\n", res->cd);
        close(s);
        return -1;
    }

    dup2(s, s2);

    free(req);
    
    return 0;

}


int request(Req **req, struct sockaddr_in *sock2){
    Req *tmp = calloc(1, sizeof(Req));

    if (tmp == NULL){
        perror("calloc");
        return -1;
    }

    tmp->vn = VERSION;
    tmp->cd = CONNECT;
    tmp->dstport = sock2->sin_port;
    tmp->dstip = sock2->sin_addr.s_addr;
    strncpy(tmp->userid, USERNAME, sizeof(tmp->userid) - 1);
    tmp->userid[sizeof(tmp->userid) - 1] = '\0';

    *req = tmp;

    return 0;
}
