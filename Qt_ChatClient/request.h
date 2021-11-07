#ifndef REQUEST_H
#define REQUEST_H

#include <QDialog>
#include <QString>
#include "datastruct.h"
#include <WS2tcpip.h>

namespace Ui {
class request;
}

class request : public QDialog
{
    Q_OBJECT

public:
    explicit request(QWidget *parent = nullptr);
    void fetch_req(std::string popup);
    void get_rec_ans (SOCKET sock, transtruct login_token);
    ~request();


private slots:
    void on_yes_clicked();

    void on_no_clicked();

private:
    Ui::request *ui;
    std::string target = "";
    SOCKET  s;
    transtruct to_send;
    char ch = ' ';
    void send_ans();
};

#endif // REQUEST_H
