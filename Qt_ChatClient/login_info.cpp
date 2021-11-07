#include "login_info.h"
#include "datastruct.h"
#include <iostream>
#include <WS2tcpip.h>

login_info::login_info(SOCKET socket)
{
sock = socket;
}

   void login_info::login (std::string username, std::string pass)
   {
   fill_login_info(username, pass);
   send_login_info();
   }

    transtruct  login_info::get_login_token()
    {
        return login_token;
    }

   void login_info::fill_login_info (std::string username, std::string pass)
   {

        login_token.com = 1;
        strcpy_s(login_token.username, username.c_str());
        strcpy_s(login_token.pass, pass.c_str());
        strcpy_s(login_token.targetuser, "");
        login_token.st = 0;
        login_token.acc = ' ';
        std::cout << "loging in to server..." << std::endl;
   }

    void  login_info::send_login_info()
    {

           int sendResult = send(sock, reinterpret_cast <char*> (&login_token), sizeof(login_token), 0);

           if (sendResult == SOCKET_ERROR)
           {
               std::cerr << "Send ERROR!" << std::endl;
           }
           else
           std::cout<<"user:  "<< login_token.username << "  pass:  " << login_token.pass<< " com: "<<login_token.com << std::endl;

    }
