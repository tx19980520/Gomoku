#ifndef EDITDIALOG_H
#define EDITDIALOG_H
#include "logdialog.h"
#include <QDialog>
#include "logdialog.h"
#include "createdialog.h"
namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = 0);
    void preset(people a);
    people tmp;
    ~EditDialog();
signals:
    void UserChange(people tmp);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
