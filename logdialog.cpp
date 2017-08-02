#include "logdialog.h"
#include "createdialog.h"
#include "ui_logDialog.h"
#include <QList>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QMessageBox>
#include "chessdialog.h"
logDialog::logDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logDialog)
{

    ui->setupUi(this);
    creater = new CreateDialog(this);
    connect(creater, SIGNAL(give_new_people(people)),this,SLOT(add_new(people)));
}


logDialog::~logDialog()
{
    delete ui;
}
void logDialog::LoadUserInfo()
{
    QFile file("PeopleData.txt");//get in words.
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "File has wrong!";
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString str1 = in.readLine();//name
        QString str2 = in.readLine();//signature
        QString str3 = in.readLine();//password
        QString str4 = in.readLine();//Email
        QString str5 = in.readLine();//score
        QString str6 = in.readLine();//rank
        QString str7 = in.readLine();//photoname
        people tmp;
        qDebug() << str1 << str2 << str3 << str4 << str5 << str6 << str7;
        tmp.UserName = str1;
        tmp.Signature = str2;
        tmp.PassWord = str3;
        tmp.Email = str4;
        tmp.score = str5.toInt();
        tmp.rank = str6.toInt();
        tmp.portrait = str7;
        UserList.append(tmp);
        ++NumOfPeople;
        qDebug() << NumOfPeople << "sx";
    }
    for(int i=0; i < NumOfPeople; ++i)
    {
        for( int j=1; j<NumOfPeople-i; ++j)
        {
            if(UserList[j].score > UserList[j-1].score)
            {
                people tms;
                tms = UserList[j];
                UserList[j] =UserList[j-1];
                UserList[j-1] = tms;
            }
        }
    }

    for(int i=0; i<NumOfPeople; ++i)
    {
        UserList[i].rank = i+1;
    }
}

int logDialog::findname(QString a)
{
    for(int i=0; i<NumOfPeople; ++i)
    {
        if(UserList[i].UserName == a)
            return i;
    }
    return -1;
}

bool logDialog::CheckPassWord(int s,QString ss)
{
    if(UserList[s].PassWord == ss)
        return true;
    else return false;
}

void logDialog::on_log_clicked()
{
    QString tmp_name, tmp_password;
    tmp_name = ui->GetUserName->text();
    tmp_password = ui->PassWord->text();
    int s = findname(tmp_name);
    if(s != -1)
    {
        if(CheckPassWord(s,tmp_password))
        {
            accept();//check the loader and give the accept to open the MyWidget.
            master = UserList[s];
            num = s;
        }
        else
            QMessageBox::warning(this,QObject::tr("no find!"),QObject::tr("用户名或密码不正确！")
                                              ,QMessageBox::Abort);
    }
    else
        QMessageBox::warning(this,QObject::tr("no find!"),QObject::tr("用户名或密码不正确！")
                                          ,QMessageBox::Abort);
}

void logDialog::on_CreateUser_clicked()
{
    /**bool ok1=false;
    bool ok2 = false;
    QString password;//create a new admin;
    QString admin = QInputDialog::getText(this,tr("创建新用户"),tr("请输入用户名")
                                          ,QLineEdit::Normal,tr("ty0207"),&ok1);
    if(ok1)
    {
        password = QInputDialog::getText(this,tr("创建新用户"),tr("请输入密码"),
                                                QLineEdit::Normal,tr("12345"),&ok2);
    }

    //if(ok2)
    //{
        QFile file("PeopleData.txt");//append in the person.txt and now_admin and now_password;
        if(file.open(QIODevice::Append|QFile::Text))
        {
            QTextStream out(&file);
            people tmp;
            tmp.UserName = admin;
            tmp.PassWord = password;
            tmp.Email = "None";
            tmp.Signature = "None";
            tmp.rank = 0;
            tmp.score = 0;
            tmp.portrait = "None.jpg";
            UserList.append(tmp);
            ++NumOfPeople;
            out << '\n';
            out << tmp.UserName << '\n';
            out << tmp.Signature << '\n';
            out <<  tmp.PassWord << '\n';
            out << tmp.Email<<'\n';
            out << tmp.rank << '\n';
            out << tmp.score << '\n';
        }
        file.close();
    }**/
        creater->show();
}
void logDialog::add_new(people newman)
{
    newman.rank = 0;
    newman.score = 0;
    UserList.append(newman);
    ++NumOfPeople;
}
void logDialog::give_score(people df)
{
    qDebug() << "get score";
    int g = findname(df.UserName);
    UserList[g].score += 1;
    for(int i=0; i < NumOfPeople; ++i)
    {
        for( int j=1; j<NumOfPeople-i; ++j)
        {
            if(UserList[j].score > UserList[j-1].score)
            {
                people tms;
                tms = UserList[j];
                UserList[j] =UserList[j-1];
                UserList[j-1] = tms;
            }
        }
    }

    for(int i=0; i<NumOfPeople; ++i)
    {
        UserList[i].rank = i+1;
    }
}
