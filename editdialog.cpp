#include "editdialog.h"
#include "ui_editdialog.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}
void EditDialog::preset(people a)
{
    ui->your_portrait->clear();
    QPixmap sx;
    sx.load(a.portrait);
    ui->your_portrait->setPixmap(sx);
    ui->your_portrait->show();
    ui->name->setText(a.UserName);
    ui->signature->setText(a.Signature);
    ui->password->setText(a.PassWord);
    ui->email->setText(a.Email);
    tmp = a;
}

void EditDialog::on_pushButton_clicked()
{
    tmp.UserName = ui->name->text();
    tmp.PassWord = ui->password->text();
    tmp.Email = ui->email->text();
    tmp.Signature = ui->signature->text();
    emit UserChange(tmp);
    qDebug() << tmp.Signature;
}

void EditDialog::on_pushButton_3_clicked()
{
    QString jpgname = QFileDialog::getOpenFileName(this, tr("文件对话框"),"D:",tr("图片文件(*png *jpg)"));
    QPixmap j;
    j.load(jpgname);
    ui->your_portrait->clear();
    ui->your_portrait->setPixmap(j);
    tmp.portrait = jpgname;
    ui->your_portrait->show();
}
