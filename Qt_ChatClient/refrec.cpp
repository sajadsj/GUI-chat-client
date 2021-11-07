#include "refrec.h"

refrec::refrec(SOCKET socket)
{
    sock = socket;
}


void refrec::refresh(transtruct login_token)
{
    to_send = login_token;
    fill_refresh();
    send_refrec();
}

void refrec::send_req(std::string targetuser, transtruct login_token)
{
    to_send = login_token;
    fill_sendrec(targetuser);
    send_refrec();
}

void refrec::fill_refresh()
{
    to_send.com = 3;
}

void refrec::fill_sendrec(std::string targetuser)
{
    to_send.com = 4;
    strcpy_s(to_send.targetuser, targetuser.c_str());
}

void refrec::send_refrec()
{
    int sendResult = send(sock, reinterpret_cast <char*> (&to_send), sizeof(to_send), 0);
    if (sendResult == SOCKET_ERROR)
    {
        std::cerr << "Send ERROR!" << std::endl;
    }
}

