#ifndef RANKDIALOG_H
#define RANKDIALOG_H

#include <QDialog>
#include <QString>
#include <QQueue>
namespace Ui {
class RankDialog;
}

class RankDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RankDialog(QWidget *parent = 0);
    ~RankDialog();
    void putshow(QString str1, QString str2, QString str3, QString str4);
private:
    Ui::RankDialog *ui;
};

#endif // RANKDIALOG_H
