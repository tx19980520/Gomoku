#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include "chessdialog.h"
#include <QDialog>
#include "logdialog.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include "editdialog.h"
#include "createdialog.h"
#include "rankdialog.h"
namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    bool a;
    RankDialog *ranks;
    ChessDialog *chessboard;
    logDialog *logsys;
    EditDialog *my_info;
    QMediaPlayer *player;
    people *present;
    people AI;
    QMediaPlaylist *playerlist;
    int Userlist_pos;
    explicit mainDialog(QWidget *parent = 0);
    void change(people s,int a);
    ~mainDialog();
private slots:
    void on_add_clicked();

    void on_itemloop_clicked();

    void on_itemonce_clicked();

    void on_listloop_clicked();

    void on_sequential_clicked();

    void on_random_clicked();

    void on_playing_clicked();

    void on_stop_clicked();

    void on_next_clicked();

    void on_pre_clicked();

    void on_Edit_clicked();

    void on_RankList_2_clicked();

    void MusicInfo(bool gets);
    void on_RankList_clicked();
    void fresh_info(people tmp);
    void on_PvP_clicked();

    void on_PvE_clicked();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
