#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QCloseEvent;

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

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
