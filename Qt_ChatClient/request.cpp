#include "request.h"
#include "ui_request.h"

#include <iostream>
request::request(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request)
{
    ui->setupUi(this);
}

request::~request()
{
    delete ui;
}


void request::get_rec_ans(SOCKET sock, transtruct login_token)
{
    s = sock;
    to_send = login_token;
    to_send.com = 6;

}

void request::on_yes_clicked()
{
    target = ui->targetconfirm->text().toStdString();

    if (target == "")
    {
        ui->label->setText(QString::fromStdString("Please insert the target user confirmation."));
    }
    else
    {
        strcpy_s(to_send.targetuser, target.c_str());
        to_send.acc = 'y';
        send_ans();
        close();
    }

}


void request::on_no_clicked()
{
    to_send.acc = 'n';
    send_ans();
    close();
}



void request::fetch_req(std::string popup)
{
    ui->label->setText((QString::fromStdString (popup)));
}

void request::send_ans()
{
    int sendResult = send(s, reinterpret_cast <char*> (&to_send), sizeof(to_send), 0);

    if (sendResult == SOCKET_ERROR)
    {
        std::cerr << "Send ERROR!" << std::endl;
    }
}
