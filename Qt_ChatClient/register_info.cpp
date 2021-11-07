#include "register_info.h"

register_info::register_info(SOCKET socket)
{
sock = socket;
}


    void register_info::register_user(std::string username, std::string pass)
    {
        fill_register_info(username, pass);
        send_register_info();
    }


    void register_info::fill_register_info(std::string username, std::string pass)
    {
        strcpy_s(register_token.username, username.c_str());
        strcpy_s(register_token.pass, pass.c_str());
        register_token.com = 2;
        strcpy_s(register_token.targetuser, "");
        register_token.st = 0;
        register_token.acc = ' ';
    }

    void register_info::send_register_info()
    {
        int sendResult = send(sock, reinterpret_cast <char*> (&register_token), sizeof(register_token), 0);

        if (sendResult == SOCKET_ERROR)
        {
            std::cerr << "Send ERROR!" << std::endl;
        }
    }
