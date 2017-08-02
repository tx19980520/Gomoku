#include "rankdialog.h"
#include "ui_rankdialog.h"

RankDialog::RankDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankDialog)
{
    ui->setupUi(this);
}

RankDialog::~RankDialog()
{
    delete ui;
}
void RankDialog::putshow(QString str1, QString str2, QString str3, QString str4)
{
    ui->first->setText(str1);
    ui->second->setText(str2);
    ui->third->setText(str3);
    ui->forth->setText(str4);
}
