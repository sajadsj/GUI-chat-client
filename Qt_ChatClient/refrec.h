#ifndef REFREC_H
#define REFREC_H
#include <string>
#include "datastruct.h"
#include <WS2tcpip.h>
#include <iostream>
class refrec
{
public:
    refrec(SOCKET sock);
    void refresh(transtruct login_token);
    void send_req(std::string targetuser, transtruct login_token);
private:
    SOCKET sock;
    void fill_refresh();
    void fill_sendrec(std::string targetuser);
    void send_refrec();
    transtruct to_send;
};

#endif // REFREC_H
