#ifndef LOGDIALOG_H
#define LOGDIALOG_H
#include <QPixmap>
#include <QDialog>
#include <QString>
#include <QList>
#include "editdialog.h"
#include "createdialog.h"
namespace Ui {
class logDialog;
}


class logDialog : public QDialog
{
    Q_OBJECT

public:
    bool enter;
    people master;
    int NumOfPeople = 0;
    int num = 0;
    QList<people> UserList;
    void LoadUserInfo();
    explicit logDialog(QWidget *parent = 0);
    ~logDialog();
    int findname(QString a);
    bool CheckPassWord(int s ,QString ss);
    CreateDialog *creater;
public slots:
    void give_score(people);
    void add_new(people newman);
private slots:
    void on_log_clicked();
    void on_CreateUser_clicked();

private:
    Ui::logDialog *ui;
};

#endif // LOGDIALOG_H
