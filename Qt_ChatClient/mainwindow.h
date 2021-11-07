#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QSocketNotifier>

#include <string>
#include "login_info.h"
#include <thread>
#include <vector>
#include <WS2tcpip.h>
#include "register_info.h"
#include "refrec.h"

#include "request.h"
#include "chatwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_Login_clicked();

    void on_Register_clicked();

    void on_Refresh_clicked();

    void on_Sendreq_clicked();

private:
    Ui::MainWindow *ui;
    QSocketNotifier *notifier;

public:
    void do_login(std::string username, std::string pass);
    void do_register (std::string username, std::string pass);
    void refresh();
    void send_request(std::string targetuser);
    void reqresponse(char c, transtruct login_token,std::string targetuser);


    std::string rec_status = "";
    transtruct login_token;
    transtruct recstc;

private slots:
    void rec();

    void on_Showchats_clicked();

private:
    SOCKET sock;

    login_info *linfo;
    register_info *rinfo;
    refrec *ref_obj;

    request *  popdialog;
    chatwin * msgdialog;
    char c = ' ';
    std::string targetuser, target;
    std::string popup = "";
    char ch = ' ';
    void connect_to_server();
    std::string msg,er = "";

  //  transtruct register_info;

    void login_sucess();

};
#endif // MAINWINDOW_H
