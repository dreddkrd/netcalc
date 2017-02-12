#ifndef MAC_H
#define MAC_H

#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class mac;
}

class mac_window : public QMainWindow
{
    Q_OBJECT
    QLineEdit *lines[3][2];
public:
    explicit mac_window(QWidget *parent = 0);
    ~mac_window();
    void move_to_corner();

private:
    Ui::mac *ui;

protected:
    void closeEvent(QCloseEvent *e);

public slots:
    void mac_change(QString str);
};

#endif // MAC_H
