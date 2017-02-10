#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class QSystemTrayIcon;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSystemTrayIcon *mSystemTrayIcon;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
