#ifndef LOGIN_INFO_H
#define LOGIN_INFO_H
#include <string>
#include "datastruct.h"
#include <WS2tcpip.h>
class login_info
{
public:
    login_info(SOCKET socket);
    void login (std::string username, std::string pass);
    transtruct  get_login_token ();

private:
    void fill_login_info (std::string username, std::string pass);
    void  send_login_info();
    transtruct login_token;
    SOCKET sock;

};

#endif // LOGIN_INFO_H
