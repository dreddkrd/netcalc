#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QCloseEvent;

namespace Ui {
class MainWindow;
}

class QSystemTrayIcon;

class ip_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit ip_window(QWidget *parent = 0);
    ~ip_window();
    void move_to_corner();

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
