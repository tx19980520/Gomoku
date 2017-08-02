#include "createdialog.h"
#include "ui_createdialog.h"
#include <QFileDialog>
#include <QString>
#include <QPixmap>
CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog)
{
    ui->setupUi(this);
}

CreateDialog::~CreateDialog()
{
    delete ui;
}

void CreateDialog::on_pushButton_clicked()
{
    int ret = QMessageBox::information(this,tr("sure?"),tr("确认上述信息吗？"),QMessageBox::Ok);
    if(ret == QMessageBox::Ok)
    {
        newman.UserName = ui->gname->text();
        QString t1,t2;
        t1 = ui->gpassword->text();
        t2 = ui->gpassword2->text();
        if(t1 != t2)
        {
            QErrorMessage *err;
            err = new QErrorMessage;
            err->setModal(true);
            err->setWindowTitle(tr("你大概是手贱"));
            err->showMessage(tr("两次密码不一致!"));

        }
        else{
            newman.PassWord = t1;
            newman.rank = 0;
            newman.score = 0;
            newman.Email = ui->gmail->text();
            newman.Signature = ui->gsignature->text();
            emit give_new_people(newman);
        }
    }
}

void CreateDialog::on_pushButton_4_clicked()
{
    QString jpgname = QFileDialog::getOpenFileName(this, tr("文件对话框"),"D:",tr("图片文件(*png *jpg)"));
    QPixmap j;
    j.load(jpgname);
    ui->jpg->clear();
    ui->jpg->setPixmap(j);
    newman.portrait = jpgname;
    ui->jpg->show();
}

void CreateDialog::on_pushButton_3_clicked()
{
    ui->gname->setText("");
    ui->gmail->setText("");
    ui->gpassword->setText("");
    ui->gpassword2->setText("");
    ui->gsignature->setText("");
    ui->jpg->clear();
}
