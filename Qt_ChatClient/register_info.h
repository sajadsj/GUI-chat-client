#ifndef REGISTER_INFO_H
#define REGISTER_INFO_H
#include <string>
#include "datastruct.h"
#include <WS2tcpip.h>
#include <iostream>

class register_info
{
public:
    register_info(SOCKET sock);
    void register_user (std::string username, std::string pass);

private:
    void fill_register_info(std::string username, std::string pass);
    void send_register_info();
    transtruct register_token;
    SOCKET sock;
};

#endif // REGISTER_INFO_H
