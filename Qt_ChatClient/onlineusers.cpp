#include "onlineusers.h"
#include "ui_onlineusers.h"

onlineusers::onlineusers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::onlineusers)
{
    ui->setupUi(this);
}

onlineusers::~onlineusers()
{
    delete ui;
}
