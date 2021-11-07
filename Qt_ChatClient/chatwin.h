#ifndef CHATWIN_H
#define CHATWIN_H

#include <QMainWindow>
#include <QString>
#include "datastruct.h"
#include <WS2tcpip.h>

namespace Ui {
class chatwin;
}

class chatwin : public QMainWindow
{
    Q_OBJECT

public:
    explicit chatwin(QWidget *parent = nullptr);
    ~chatwin();
    void fetch_er(std::string er);
    void fetch_msg(std::string msg);
    void fetch_data(SOCKET sock, transtruct login_token);

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::chatwin *ui;
    SOCKET s;
    transtruct to_send;
    std::string target, msg, from;

    void send_msg();
    void fill_msg();



};

#endif // CHATWIN_H
