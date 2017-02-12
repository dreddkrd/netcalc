#ifndef MAC_H
#define MAC_H

#include <QMainWindow>

namespace Ui {
class mac;
}

class mac : public QMainWindow
{
    Q_OBJECT

public:
    explicit mac(QWidget *parent = 0);
    ~mac();

private:
    Ui::mac *ui;

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MAC_H
