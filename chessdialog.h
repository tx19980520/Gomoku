#ifndef CHESSDIALOG_H
#define CHESSDIALOG_H
#include <QPainter>
#include <QDialog>
#include <QMouseEvent>
#include "createdialog.h"
namespace Ui {
class ChessDialog;
}

class ChessDialog : public QDialog
{
    Q_OBJECT

public:
    //1//2
    bool PvE = false;
    void ready();
    people black;
    people white;
    int board[17][17];
    int AIboard[17][17];
    int AIvalueboard[17][17];
    explicit ChessDialog(QWidget *parent = 0);
    void value_search(int x,int y,int m,int n, int a);
    ~ChessDialog();
protected:
    QPoint origin;
    QPoint lastPs;
    void paintEvent(QPaintEvent *event);
    int check_the_battle();
    bool playflag =true;
    bool row_check(int a);
    bool line_check(int a);
    bool LU_check(int a);
    bool RU_check(int a);
    bool balance();
    void mousePressEvent(QMouseEvent *event);
private slots:
    void AIvalue();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();


signals:
    void getscore(people);
private:
    Ui::ChessDialog *ui;
};

#endif // CHESSDIALOG_H
