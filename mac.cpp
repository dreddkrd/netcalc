#include "mac.h"
#include "ui_mac.h"
#include <QtGui/QCloseEvent>

mac::mac(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mac)
{
    ui->setupUi(this);
}

mac::~mac()
{
    delete ui;
}

void mac::closeEvent(QCloseEvent *e)
{
this->hide();
e->ignore();
}
