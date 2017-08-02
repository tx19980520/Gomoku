#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H
#include <QDialog>
#include <QMessageBox>
#include <QErrorMessage>
namespace Ui {
class CreateDialog;
}

class people{
public:
    QString portrait;
    QString UserName;
    QString PassWord;
    QString Signature;
    QString Email;
    int rank;
    int score;
};
class CreateDialog : public QDialog
{
    Q_OBJECT

public:
    people newman;
    explicit CreateDialog(QWidget *parent = 0);
    ~CreateDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();
signals:
    void give_new_people(people newman);
private:
    Ui::CreateDialog *ui;
};

#endif // CREATEDIALOG_H
