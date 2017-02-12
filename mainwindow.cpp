#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QCloseEvent>
#include <QDesktopWidget>

ip_window::ip_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

ip_window::~ip_window()
{
    delete ui;
}

void ip_window::closeEvent(QCloseEvent *e)
{
this->hide();
e->ignore();
}

void ip_window::move_to_corner() {
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
    QPoint pos = rect.bottomRight(); //координаты центра экрана
    pos.setX(pos.x() - (this->width()));  // учитываем половину ширины окна
    pos.setY(pos.y() - (this->height()));  // .. половину высоты
    move(pos);
}
