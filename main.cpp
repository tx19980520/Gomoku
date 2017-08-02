#include "logdialog.h"
#include <QApplication>
#include "maindialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainDialog mainsys;
    mainsys.logsys->LoadUserInfo();
    if(mainsys.logsys->exec() == QDialog::Accepted)
    {
        mainsys.change(mainsys.logsys->master,mainsys.logsys->num);
        mainsys.show();
        return a.exec();
    }
    return a.exec();
}
