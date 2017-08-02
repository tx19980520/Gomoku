#include "chessdialog.h"
#include "ui_chessdialog.h"
#include <QPainter>
#include <QCursor>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
ChessDialog::ChessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChessDialog)
{
    for(int i =0; i <= 16; ++i)
    {

        for(int j=0; j <= 16; ++j)
        {
            board[i][j] = 0;
        }
     }
    ui->setupUi(this);
    lastPs.setX(-1);
    lastPs.setY(-1);

}

ChessDialog::~ChessDialog()
{
    delete ui;
}
void ChessDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//先横后竖
    for(int i=350;i<=950; i += 40)
    {
        painter.drawLine(QPoint(i,100),QPoint(i,700));
    }
    for(int j= 100;j<=700;j += 40)
    {
        painter.drawLine(QPoint(350,j),QPoint(950,j));
    }

        for (int x = 1; x <= 16;++x)
        {
            for (int y = 1; y <= 16; ++y)
            {
                if (board[x][y] == 1) //黑棋子
                {
                    QBrush brush(QColor(0,0,0),Qt::SolidPattern);
                    painter.setBrush(brush);
                    int p=x * 40-20+origin.x();
                    int q= y * 40-20+origin.y();
                    painter.drawEllipse(p,q, 40, 40);
                }
                else if (board[x][y] == 2) //白棋子
                {
                    QBrush brush(QColor(255,255,255),Qt::SolidPattern);
                    painter.setBrush(brush);
                    painter.drawEllipse(x*40-20+origin.x(),
                                             y*40-20+origin.y(), 40, 40);
                }
            }
            QDialog::paintEvent(event);
            update();
        }
        //将最后一步画的白棋子变绿，这样人能看清
        if (lastPs.x() >=1 && lastPs.y() >= 1)
        {
            QBrush brush(QColor(0,170,0),Qt::SolidPattern);
            painter.setBrush(brush);
            painter.drawEllipse(40 * lastPs.x()-20+origin.x(),
                                          40 * lastPs.y()-20+origin.y(), 40, 40);
        }
        QDialog::paintEvent(event);
        update();

}

bool ChessDialog::balance()
{
    for(int i=1; i<=16;++i)
        for(int j=1 ; j <= 16; ++j)
            if(board[i][j] != 1 ||board[i][j] != 2)
                return true;
    return false;
}

int ChessDialog::check_the_battle()
{
    int re = 0;
    if(row_check(1))
     {
        re=1;
        return re;
     }
    if(row_check(2))
     {
        re=2;
       return re;
     }
    if(line_check(1))
    {
        re=1;
        return re;
    }
    if(line_check(2))
    {
         re=2;
         return re;
    }
    if(LU_check(1))
    {
        re=1;
        return re;
    }

    if(LU_check(2))
    {
        re=2;
        return re;
    }
    if(RU_check(1))
    {
        re=1;
        return re;
    }
    if(RU_check(2))
    {
        re=2;
    return re;
    }
    if(balance())
    {
        re = 3;
        return re;
    }
    return re;
}
bool ChessDialog::row_check(int a)
{
    for(int i=1; i <= 16; ++i)
    {
        for(int j=1; j <= 16; ++j)
        {
            if(board[i][j] == a)
            {
                int m,n;
                m = i;
                n = j;
                int count = 1;
                while(board[m+1][n] == a)
                {
                    ++count;
                    ++m;
                    if(count == 5)
                    {
                        qDebug() << "row_check";
                        return true;
                        break;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessDialog::line_check(int a){
    for(int i=1; i <= 16; ++i)
    {
        for(int j=1; j <= 16; ++j)
        {
            if(board[i][j] == a)
            {
                int m,n;
                m = i;
                n = j;
                int count = 1;
                while(board[m][n+1] == a)
                {
                    ++count;
                    ++n;
                    if(count == 5)
                    {
                        qDebug() << "line_check";
                        return true;
                        break;
                    }
                 }
             }
         }
      }
    return false;
    }
bool ChessDialog::LU_check(int a)
{
    for(int i=1; i <= 16; ++i)
    {
        for(int j=1; j <= 16; ++j)
        {
            if(board[i][j] == a)
            {
                int m,n;
                m = i;
                n = j;
                int count = 1;
                while(board[m-1][n+1] == a)
                {
                    ++count;
                    ++n;
                    --m;
                    if(count == 5)
                    {
                        qDebug() << "LU_check";
                        return true;
                        break;
                    }
                 }
            }
        }
     }
     return false;
}

bool ChessDialog::RU_check(int a)
{
    for(int i=1; i <= 16; ++i)
    {
        for(int j=1; j <= 16; ++j)
        {
            if(board[i][j] == a)
            {
                int m,n;
                m = i;
                n = j;
                int count = 1;
                while(board[m][n+1] == a)
                {
                    ++count;
                    ++n;
                    if(count == 5)
                    {
                        qDebug() << "RU_check";
                        return true;
                        break;
                    }
                }
            }
        }
    }
return false;
}
void ChessDialog::mousePressEvent(QMouseEvent *event)
{
    origin.setX(350);
    origin.setY(100);
    if(event->button() == Qt::LeftButton)
    { 
        QPoint offset = event->pos()-origin;
        //qDebug() << offset.x() << offset.y();//获取坐标没有问题了
        if(offset.x()/40 <= 16 && offset.x()/40 >= 1 && offset.y()/40 <= 16 && offset.y()/40 >= 1)
        {
            int rx = offset.x()/40;
            int ry = offset.y()/40;
            if(board[rx][ry] == 0)
            {
            if(playflag)
            {
                 board[rx][ry] = 1;
                 qDebug() << rx << ry << 1;
                 lastPs.setX(rx);
                 lastPs.setY(ry);
                 playflag = !playflag;
                 ui->show_turn->setText(tr("白"));
            }
            else
            {
                board[rx][ry] = 2;
                lastPs.setX(rx);
                lastPs.setY(ry);
                playflag = !playflag;
                ui->show_turn->setText(tr("黑"));
                if(PvE)
                {
                    AIvalue();
                    ui->show_turn->setText(tr("白"));
                }

            }

            int finish = check_the_battle();
            if(finish == 1)
            {
                 emit getscore(black);
                QMessageBox::information(this,tr("Game Over"),tr("Black Win!"),QMessageBox::Ok);
                return;
            }
            else if(finish == 2)
            {
                emit getscore(white);
               QMessageBox::information(this,tr("Game Over"),tr("White Win!"),QMessageBox::Ok);
                return ;
            }
        }
    }
        }
    update();
}

void ChessDialog::ready()
{
    ui->black_name->setText(black.UserName);
    QPixmap wpro,bpro;
    wpro.load(white.portrait);
    bpro.load(black.portrait);
    ui->white_name->setText(white.UserName);
    ui->black_po->setPixmap(bpro);
    ui->white_po->setPixmap(wpro);
}

void ChessDialog::on_pushButton_clicked()
{
    playflag = true;
    ui->show_turn->setText(tr("黑"));
    if(PvE)
    {
        AIvalue();
    }
    for(int i =0; i <= 16; ++i)
    {

        for(int j=0; j <= 16; ++j)
        {
            board[i][j] = 0;
        }
     }
    lastPs.setX(-1);
    lastPs.setY(-1);
}

void ChessDialog::on_pushButton_3_clicked()
{
    if(playflag)
    {
        if(black.UserName != "AI")
            emit getscore(black);
       QMessageBox::information(this,tr("Game Over"),tr("Black Win!"),QMessageBox::Ok);
       return;
    }
    else
    {
        emit getscore(white);
       QMessageBox::information(this,tr("Game Over"),tr("White Win!"),QMessageBox::Ok);
        return ;
    }
}

void ChessDialog::value_search(int x, int y ,int m, int n,int a )
{
    int link = 1;
    int space = 0;
    int p,q;
    p = x;
    q = y;
    while(p+m != 17 &&q+n != 17)
    {
        if(AIboard[p+m][q+n] == a)
        {
            ++link;
            p = p+m;
            q = q+n;
        }
        else break;
    }
    while(p+m != 17 &&q+n != 17)
    {
        if(AIboard[p+m][q+n] == 0||AIboard[p-m][q-n] == a)
        {
            ++space;
            p = p+m;
            q = q+n;
        }
        else break;
    }
    p = x;
    q = y;
    while(p-m != 0 &&q-n != 0)
    {
        if(AIboard[p-m][q-n] == a)
        {
            ++link;
            p = p-m;
            q = q-n;
        }
        else break;
    }
    while(p-m != 0 &&q-n != 0)
    {
        if(AIboard[p-m][q-n] == 0 ||AIboard[p-m][q-n] == a)
        {
            ++space;
            p = p-m;
            q = q-n;
        }
        else break;
    }
    if(link >= 5)
        AIvalueboard[x][y] =10000;
    else {
        AIvalueboard[x][y] += link*200;
        if((link+space) >= 5 )
            AIvalueboard[x][y] += 400;
    }

}

void ChessDialog::AIvalue()//AI always is 1.
{
    for(int i=0; i<17; ++i)
    {
        for(int j=0; j<17; ++j)
        {
           AIvalueboard[i][j] = 0;
           AIboard[i][j] = 0;
        }
    }
    for(int i=0; i<17; ++i)
    {
        for(int j=0; j<17; ++j)
        {
            AIboard[i][j] = board[i][j];
        }
    }
    for(int i=0; i<17;++i)
    {
        for(int j=0; j<17; ++j)
        {
              if(AIboard[i][j] == 0)
              {
                  AIboard[i][j] = 1;
                  value_search(i,j,1,0,1);
                  value_search(i,j,0,1,1);
                  value_search(i,j,1,1,1);
                  value_search(i,j,1,-1,1);

                  AIboard[i][j] = 2;
                  value_search(i,j,1,0,2);
                  value_search(i,j,0,1,2);
                  value_search(i,j,1,1,2);
                  value_search(i,j,1,-1,2);

                  AIboard[i][j] = 0;
              }
        }
    }
    int max = 0;
    int maxx = 0;int maxy = 0;
    for(int i=0; i<17; ++i)
    {
        for(int j=0; j<17; ++j)
        {
            if(AIvalueboard[i][j] >= max)
            {
                max = AIvalueboard[i][j];
                maxx = i;
                maxy = j;
            }
        }
    }
    board[maxx][maxy] = 1;
    lastPs.setX(maxx);
    lastPs.setY(maxy);
    playflag = !playflag;
}
