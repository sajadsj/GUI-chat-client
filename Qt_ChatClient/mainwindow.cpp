/*
 * Title: GUI chat client 
 * Project aim: Learning Qt/C++
 * by: SajadSojoudi@gmail.com
 * Client Code
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string.h>
#include <qstring.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <thread>
#include <vector>
#include <cstring>


#pragma comment(lib, "ws2_32.lib")
using namespace std;





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pass->setEchoMode(QLineEdit::Password);
    ui->pass_conf->setEchoMode(QLineEdit::Password);

    ui->onlineswidget->setVisible(false);

    connect_to_server();

    linfo = new login_info(sock);
    rinfo = new register_info(sock);
    ref_obj = new refrec(sock);

    notifier = new QSocketNotifier(sock, QSocketNotifier::Read);
    connect(notifier, SIGNAL(activated(int)), this, SLOT(rec()));

    popdialog = new request(this);
    msgdialog = new chatwin(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::rec()
{
    //get user and password from login info
   recstc = linfo->get_login_token();

   char buf[4096];
   ZeroMemory(buf, 4096);



       int bytesReceived = recv(sock, reinterpret_cast <char*> (& recstc), sizeof(recstc), 0);


       Sleep(10);



       if (bytesReceived > 0)
       {

cout << "data recived.\n login token st: "<<recstc.st<<endl;

           // 1: this is a chat request, 2: this is a server respons, 3: this is a msg from other clients, 4: ERROR
           switch (recstc.st)
           {

           case 101://login succecful and no one is online
           {
            rec_status = "\nHellow " + string(recstc.username) +
                    ", welcome to chat server!\nSadly you are alone in server!\n";
            login_sucess();
           }
           break;

           case 102://102: login succecful and here is the onlines
            {
              rec_status = "Hellow " + string(recstc.username) +
                            ", welcome to chat server!\n" +
                            "Here is online users:\n" + string(recstc.onlines);         
              login_sucess();
            }
           break;

           //104: user pass not match, or already loged in
           case 104:
           {
               rec_status = "\nThere is something wrong with your username or password \nor you already loged in!";
           }
           break;

           //201: register succes
           case 201:
           {
              rec_status = "You are added to server.";
           }
           break;

           //204: username is repeated
           case 204:
           {
              rec_status = "Username is repeated";
           }
           break;


           //here is onlines and chat req result if there was any
           case 301:            
            rec_status ="Here is online users and chat request results if you had any:\n" +
                    string(recstc.onlines);
           break;

           //303: there are not online
           case 303:
           {
                rec_status = "There are not any online user.\n";
           }
           break;


           //302: there is chat req
           case 302:
           {
               //popup
                popup =  "You have chat request(s) notification, from: \t" + string(recstc.chat_req);
                popdialog->fetch_req(popup);
                popdialog->show();
                popdialog->get_rec_ans(sock, login_token);
           }
           break;


           case 401:
           {
                rec_status = "\nYour chat request submited.";
           }
           break;

           case 403:
           {
                rec_status = "Sorry, there is not " + string(recstc.targetuser) + " in the server.";
           }
           break;

           case 404:
           {
               rec_status = "\nYour target user is not online.";
           }
           break;

           //405: you can not req to yourself
           case 405:

               rec_status = "You can not req to yourself!";
               break;

               //501 this is msg from other client(s)
           case 501:
                msg = " ";
                msg = recstc.msg;
                msgdialog->fetch_msg(msg);
               break;

               // target user does not accepted you
           case 502:
               er = "You can not send msg to" + string(recstc.targetuser) +"\n because he/she does not accept your chat request.";
                msgdialog->fetch_er(er);
               break;
           }
       }   ui->status->setText(QString::fromStdString (rec_status));  //return status;

   //}
}



void MainWindow::do_login(std::string username, std::string pass)
{
    linfo->login(username, pass);
    login_token = linfo->get_login_token();

}

void MainWindow::do_register (std::string username, std::string pass)
{
     rinfo->register_user(username, pass);

}

void MainWindow::refresh()
{

    ref_obj->refresh(login_token);
}

void MainWindow::send_request(std::string targetuser)
{
    ref_obj->send_req(targetuser, login_token);
}

//connect to socket

void MainWindow::connect_to_server()
{
    string ipAddress = "127.0.0.1";			// IP Address of the server
    int port = 54000;						// Listening port # on the server

    // Initialize WinSock
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        cerr << "Can't start Winsock, Err #" << wsResult << endl;

    }

    // Create socket
     sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
        WSACleanup();

    }

    // Fill in a hint structure
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to server
    int connResult = ::connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
       // return SOCKET_ERROR;
    }
}


void MainWindow::on_Login_clicked()
{

   string username, pass = "";
   username = ui->username->text().toStdString();
   pass = ui->pass->text().toStdString();
   ui->name->setText(QString::fromStdString (username));

   do_login(username, pass);
   ui->username->clear();
   ui->pass->clear();
}

void MainWindow::login_sucess()
{

   if (recstc.st == 101 || recstc.st == 102) // login succescful
   {
       ui->loginwidget->setVisible(false);
       ui->onlineswidget->setVisible(true);
   }
}


void MainWindow::on_Register_clicked()
{
    string username, pass, con_pass = "";
    username = ui->username->text().toStdString();

    pass = ui->pass->text().toStdString();
    con_pass = ui->pass_conf->text().toStdString();

    if (pass.compare(con_pass) == 0)
    {
        do_register(username, pass);
        ui->status->setText(QString::fromStdString (rec_status));
        ui->username->clear();
        ui->pass->clear();
        ui->pass_conf->clear();
    }
    else
        ui->status->setText("Passwords are not match!");

}





void MainWindow::on_Refresh_clicked()
{        
        refresh();
        ui->status->setText(QString::fromStdString (rec_status));

}


void MainWindow::on_Sendreq_clicked()
{
    string target = "";
    target = ui->targetuser->text().toStdString();
    send_request(target);
    ui->targetuser->clear();
}



void MainWindow::on_Showchats_clicked()
{
    msgdialog->fetch_data(sock, login_token);
    msgdialog->show();
}

