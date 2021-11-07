#include "chatwin.h"
#include "ui_chatwin.h"
#include <iostream>
chatwin::chatwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatwin)
{
    ui->setupUi(this);
}

chatwin::~chatwin()
{
    delete ui;
}
void chatwin::fetch_data (SOCKET sock, transtruct login_token)
{
        s = sock;
        to_send = login_token;
}

void chatwin::fetch_er(std::string er)
{
    ui->status->setText(QString::fromStdString (er));
}


void chatwin::fetch_msg(std::string msg)
{
    ui->plainTextEdit->insertPlainText(QString::fromStdString (msg+ "\n"));
}

void chatwin::on_pushButton_2_clicked()
{
    close();
}




void chatwin::on_pushButton_clicked()
{

    msg =  ui->msg->text().toStdString();
    target = ui->target->text().toStdString();
    from = to_send.username;
    ui->plainTextEdit->insertPlainText(QString::fromStdString (from + " : " + msg + "\n"));

    fill_msg();
    send_msg();

    ui->msg->clear();
    ui->target->clear();

}

void chatwin::fill_msg()
{
    to_send.com = 5;
    strcpy_s(to_send.msg, msg.c_str());
    strcpy_s(to_send.targetuser, target.c_str());
}

void chatwin::send_msg()
{
    int sendResult = send(s, reinterpret_cast <char*> (&to_send), sizeof(to_send), 0);


    if (sendResult == SOCKET_ERROR)
     {
        std::cerr << "Send ERROR!" << std::endl;
     }

}
