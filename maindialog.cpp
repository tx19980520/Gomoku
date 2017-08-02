#include "maindialog.h"
#include "ui_maindialog.h"
#include <QPixmap>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QApplication>
#include <QMediaPlaylist>
#include "editdialog.h"
#include <QFile>
#include <QInputDialog>
mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    playerlist = new QMediaPlaylist;
    player = new QMediaPlayer;
    player->setPlaylist(playerlist);
    logsys = new logDialog;
    my_info = new EditDialog;
    present = new people;
    chessboard = new ChessDialog;
    a = connect(my_info,EditDialog::UserChange,this,fresh_info);
    connect(player,&QMediaPlayer::metaDataAvailableChanged,this,MusicInfo);
    connect(chessboard,ChessDialog::getscore,logsys,logDialog::give_score);
    AI.UserName = "AI";
    AI.Signature = tr("都是来送死的！");
    AI.rank = 0;
    AI.score =0;
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::change(people s,int a)
{
    QString b = QString::number(s.rank);
    Userlist_pos = a;
    *present = s;
    ui->now_name->setText(s.UserName);
    ui->now_signature->setText(s.Signature);
    ui->now_rank->setText(b);
    ui->image->clear();
    ui->image->setPixmap(s.portrait);
    ui->image->show();

}

void mainDialog::on_add_clicked()
{
    QString musicName = QFileDialog::getOpenFileName(this,tr("选择音乐"),"D:",tr("音频文件(*mp3)"));
    playerlist->addMedia(QUrl::fromLocalFile(musicName));
}

void mainDialog::on_itemloop_clicked()
{
    playerlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}

void mainDialog::on_itemonce_clicked()
{
    playerlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void mainDialog::on_listloop_clicked()
{
    playerlist->setPlaybackMode(QMediaPlaylist::Loop);
}

void mainDialog::on_sequential_clicked()
{
    playerlist->setPlaybackMode(QMediaPlaylist::Sequential);
}

void mainDialog::on_random_clicked()
{
    playerlist->setPlaybackMode(QMediaPlaylist::Random);
}

void mainDialog::on_playing_clicked()
{
    player->play();
}

void mainDialog::on_stop_clicked()
{
    player->pause();
}

void mainDialog::on_next_clicked()
{
    int currentIndex=playerlist->currentIndex();
        if(++currentIndex==playerlist->mediaCount()) currentIndex=0;
        playerlist->setCurrentIndex(currentIndex);
        player->play();
}

void mainDialog::on_pre_clicked()
{
    int currentIndex=playerlist->currentIndex();
        if(--currentIndex<0) currentIndex=0;
        playerlist->setCurrentIndex(currentIndex);
        player->play();
}

void mainDialog::on_Edit_clicked()
{
    qDebug() << a;
    my_info->preset(*present);
    my_info->show();

}
void mainDialog::fresh_info(people tmp)
{
    qDebug() << tmp.Signature;
    *present = tmp;
    logsys->UserList[Userlist_pos] = tmp;//We change the info in UserList
    QPixmap f;
    f.load(tmp.portrait);
    QString b = QString::number(tmp.rank);
    ui->now_name->setText(tmp.UserName);
    ui->now_signature->setText(tmp.Signature);
    ui->now_rank->setText(b);
    ui->image->clear();
    ui->image->setPixmap(f);
    ui->image->show();
    qApp->processEvents();
}

void mainDialog::on_RankList_2_clicked()
{
    QFile file("PeopleData.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate|QIODevice::Text))
    {
        QTextStream out(&file);
        for(int i=0; i<logsys->NumOfPeople; ++i)
        {
            out << logsys->UserList[i].UserName << '\n';
            out << logsys->UserList[i].Signature << '\n';
            out << logsys->UserList[i].PassWord << '\n';
            out << logsys->UserList[i].Email<<'\n';
            out << logsys->UserList[i].rank << '\n';
            out << logsys->UserList[i].score << '\n';
            out << logsys->UserList[i].portrait << '\n';
        }
        file.close();
       }
}
void mainDialog::MusicInfo(bool gets)
{
    if(gets)
    {
        QString title = player->metaData("Title").toString();
        QString author = player->metaData("Author").toString();
        ui->music_name->setText(title);
        ui->music_author->setText(author);
    }
}

void mainDialog::on_RankList_clicked()
{
    ranks = new RankDialog;
    QString t1,t2,t3,t4;
    t1 = logsys->UserList[0].UserName;
    t2 = logsys->UserList[1].UserName;
    t3 = logsys->UserList[2].UserName;
    t4 = logsys->UserList[3].UserName;

    ranks->putshow(t1,t2,t3,t4);
    ranks->show();
}


void mainDialog::on_PvP_clicked()
{
    bool ok1;
    QString admin = QInputDialog::getText(this,tr("对手选择"),tr("请输入对手用户名")
                                          ,QLineEdit::Normal,tr("ty0207"),&ok1);
    if(ok1)
    {
        int dy = logsys->findname(admin);
        if(dy == -1)
        {
            QErrorMessage *tmd;
            tmd = new QErrorMessage;
            tmd->setModal(true);
            tmd->setWindowTitle(tr("不存在的"));
            tmd->showMessage(tr("没有这个人!"));
        }
        else{
            chessboard->black = *present;
            chessboard->white = logsys->UserList[dy];
            chessboard->ready();
            chessboard->PvE = false;
            chessboard->show();
        }
    }
}

void mainDialog::on_PvE_clicked()
{
    chessboard->white = *present;
    chessboard->black = AI;
    chessboard->ready();
    chessboard->show();
    chessboard->PvE = true;
}
