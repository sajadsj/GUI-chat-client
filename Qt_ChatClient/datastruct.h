#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include <string>


struct transtruct      //transfer_strcut
{
	//control
	int com;  //1 for login, 2 for register, 3 chat request
    char username[33];
    char pass[33];
    char targetuser[33];
	char acc;
    char onlines[257];
    char chat_req[257];
    char msg[257];
    int st;

    transtruct& operator=(const transtruct& trans) {
        com = trans.com;
        strncpy_s(username, trans.username, 32);
        strncpy_s(pass,trans.pass, 32);
        strncpy_s(targetuser, trans.targetuser, 32);
        acc = trans.acc;
        st = trans.st;
        strncpy_s(onlines, trans.onlines, 256);
        strncpy_s(chat_req, trans.chat_req, 256);
        strncpy_s(msg, trans.msg, 256);
        return *this;
    }
    // 1: this is a chat request, 2: this is a server respons, 3: this is a msg from other clients, 4: ERROR
};


#endif
