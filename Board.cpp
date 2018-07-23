#include "Board.h"
#include <QPainter>
#include <math.h>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QPalette>
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col

Board::Board(QWidget *parent) : QWidget(parent)
{
    this->_r = 20;
    setMinimumSize(_r*18+1, _r*20+1);
    init(true);
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/image/images/large3/background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

}

Board::~Board()
{

}

void Board::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    qDebug()<<"finish Init1";
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
        }
    }

    _selectid = -1;
    _bRedTurn = true;
    _bSide = bRedSide;
    qDebug()<<"before update";
    update();
    qDebug()<<"finish update";
}

void Board::setCtrlPanel(CtrlPanel *cp){
    this->_cp=cp;
    this->_cp->listWidget->addItem("                    ");
}

void Board::paintEvent(QPaintEvent *)
{   qDebug()<<"before paintEvent";
    int r = height()/20;
    _r = r;
    _off = QPoint(r+1, r+1);
    qDebug()<<"before painter";
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    p.save();
    drawPlate(p);
    p.restore();

    p.save();
    drawPlace(p);
    p.restore();

    p.save();
    drawInitPosition(p);
    p.restore();
    qDebug()<<"before drawStones";
    p.save();
    drawStone(p);
    p.restore();
}

void Board::drawStone(QPainter &p)
{
    qDebug()<<"start drawStones";
    for(int i=0; i<32; i++)
    {
        drawStone(p, i);
    }
    qDebug()<<"finish drawStones";
}

bool Board::isDead(int id)
{
    if(id == -1)return true;
    return _s[id]._dead;
}

void Board::drawStone(QPainter &p, int id)
{
    if(isDead(id)) return;
/*
    QColor color;
    if(red(id)) color = Qt::red;
    else color = Qt::black;

    p.setPen(QPen(QBrush(color), 2));

    if(id == _selectid) p.setBrush(Qt::gray);
    else p.setBrush(Qt::yellow);

    p.drawEllipse(cell(id));

    p.setFont(QFont("system", _r*1.2, 700));
    p.drawText(cell(id), name(id), QTextOption(Qt::AlignCenter));
  */
    QPixmap pix;
    QString path = getIconPath(id);
    pix.load(path);

    p.drawPixmap(cell(id),pix);
}

QString Board::getIconPath(int id){
    QString prefix = ":/image/images/large3/";
    QString p;
    switch(_s[id]._type){
        case Stone::CHE:
            if(_s[id]._red)
                p=prefix+"RR";
            else
                p=prefix+"BR";
            break;
        case Stone::MA:
            if(_s[id]._red)
                p=prefix+"RN";
            else
                p=prefix+"BN";
            break;
        case Stone::XIANG:
            if(_s[id]._red)
                p=prefix+"RB";
            else
                p=prefix+"BB";
            break;
        case Stone::PAO:
            if(_s[id]._red)
                p=prefix+"RC";
            else
                p=prefix+"BC";
            break;
        case Stone::SHI:
            if(_s[id]._red)
                p=prefix+"RA";
            else
                p=prefix+"BA";
            break;
        case Stone::BING:
            if(_s[id]._red)
                p=prefix+"RP";
            else
                p=prefix+"BP";
            break;
        case Stone::JIANG:
            if(_s[id]._red)
                p=prefix+"RK";
            else
                p=prefix+"BK";
            break;

    }
    if(id == _selectid)
        p+="S";
    p+=".GIF";
    return p;
}

QString Board::name(int id)
{
    qDebug()<<"name"<<_s[id].name();
    return _s[id].name();
}

bool Board::red(int id)
{
    return _s[id]._red;
}

void Board::drawInitPosition(QPainter &p, int row, int col)
{
    QPoint pt = center(row, col);
    QPoint off = QPoint(_r/6, _r/6);
    int len = _r/3;

    QPoint ptStart;
    QPoint ptEnd;

    if(col != 0)
    {
        /* 左上角 */
        ptStart = QPoint(pt.x() - off.x(), pt.y() - off.y());
        ptEnd = ptStart + QPoint(-len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, -len);
        p.drawLine(ptStart, ptEnd);

        /* 左下角 */
        ptStart = QPoint(pt.x() - off.x(), pt.y() + off.y());
        ptEnd = ptStart + QPoint(-len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, +len);
        p.drawLine(ptStart, ptEnd);
    }

    if(col != 8)
    {
        /* 右下角 */
        ptStart = QPoint(pt.x() + off.x(), pt.y() + off.y());
        ptEnd = ptStart + QPoint(+len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, +len);
        p.drawLine(ptStart, ptEnd);

        /* 右上角 */
        ptStart = QPoint(pt.x() + off.x(), pt.y() - off.y());
        ptEnd = ptStart + QPoint(+len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, -len);
        p.drawLine(ptStart, ptEnd);
    }
}

void Board::drawInitPosition(QPainter &p)
{
    drawInitPosition(p, 3, 0);
    drawInitPosition(p, 3, 2);
    drawInitPosition(p, 3, 4);
    drawInitPosition(p, 3, 6);
    drawInitPosition(p, 3, 8);

    drawInitPosition(p, 6, 0);
    drawInitPosition(p, 6, 2);
    drawInitPosition(p, 6, 4);
    drawInitPosition(p, 6, 6);
    drawInitPosition(p, 6, 8);

    drawInitPosition(p, 2, 1);
    drawInitPosition(p, 2, 7);

    drawInitPosition(p, 7, 1);
    drawInitPosition(p, 7, 7);
}

void Board::drawPlace(QPainter &p)
{
    p.drawLine(center(0, 3), center(2, 5));
    p.drawLine(center(2, 3), center(0, 5));

    p.drawLine(center(9, 3), center(7, 5));
    p.drawLine(center(7, 3), center(9, 5));
}

void Board::drawPlate(QPainter &p)
{
    for(int i=0; i<10; ++i)
    {
        if(i==0 || i==9)
        {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        p.drawLine(center(i, 0), center(i, 8));
    }

    for(int i=0; i<9; ++i)
    {
        if(i==0 || i==8)
        {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
            p.drawLine(center(0, i), center(9, i));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
            p.drawLine(center(0, i), center(4, i));
            p.drawLine(center(5, i), center(9, i));
        }
    }
}

QPoint Board::center(int row, int col)
{
    QPoint pt(_r*col*2, _r*row*2);
    return pt + _off;
}

QPoint Board::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}

QPoint Board::topLeft(int row, int col)
{
    return center(row, col) - QPoint(_r, _r);
}

QPoint Board::topLeft(int id)
{
    return center(id) - QPoint(_r, _r);
}

QRect Board::cell(int row, int col)
{
    return QRect(topLeft(row, col), QSize(_r*2-1, _r*2-1));
}

QRect Board::cell(int id)
{
    return QRect(topLeft(id), QSize(_r*2-1, _r*2-1));
}

bool Board::getClickRowCol(QPoint pt, int &row, int &col)
{
    for(row=0; row<=9; ++row)
    {
        for(col=0; col<=8; ++col)
        {
            QPoint distance = center(row, col) - pt;
            if(distance.x() * distance.x() + distance.y() * distance.y() < _r* _r)
                return true;
        }
    }
    return false;
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }

    click(ev->pos());
}

bool Board::canSelect(int id)
{
    return _bRedTurn == _s[id]._red;
}

void Board::trySelectStone(int id)
{
    if(id == -1)
        return;

    if(!canSelect(id)) return;

    _selectid = id;
    update();
}

bool Board::sameColor(int id1, int id2)
{
    if(id1 == -1 || id2 == -1) return false;

    return red(id1) == red(id2);
}

void Board::tryMoveStone(int killid, int row, int col)
{
    if(killid != -1 && sameColor(killid, _selectid))
    {
        trySelectStone(killid);
        return;
    }

    bool ret = canMove(_selectid, killid, row, col);
    if(ret)
    {
        moveStone(_selectid, killid, row, col);
        _selectid = -1;
        update();
    }
}

int Board::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1) ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1) ++ret;
        }
    }

    return ret;
}

int Board::relation(int row1, int col1, int row, int col)
{
    return qAbs(row1-row)*10+qAbs(col1-col);
}

bool Board::canMoveChe(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row1, col1, row, col);
    if(ret == 0)
        return true;
    return false;
}

bool Board::canMoveMa(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 12 && r != 21)
        return false;

    if(r == 12)
    {
        if(getStoneId(row1, (col+col1)/2) != -1)
            return false;
    }
    else
    {
        if(getStoneId((row+row1)/2, col1) != -1)
            return false;
    }

    return true;
}

bool Board::canMovePao(int moveid, int killid, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row, col, row1, col1);
    if(killid != -1)
    {
        if(ret == 1) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return false;
}

bool Board::canMoveBing(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(isBottomSide(moveid))
    {
        if(row > row1) return false;
        if(row1 >= 5 && row == row1) return false;
    }
    else
    {
        if(row < row1) return false;
        if(row1 <= 4 && row == row1) return false;
    }

    return true;
}

bool Board::canMoveJiang(int moveid, int killid, int row, int col)
{
    if(killid != -1 && _s[killid]._type == Stone::JIANG)
        return canMoveChe(moveid, killid, row, col);

    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}

bool Board::canMoveShi(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 11) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))
    {
        if(row < 7) return false;
    }
    else
    {
        if(row > 2) return false;
    }
    return true;
}

bool Board::canMoveXiang(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 22) return false;

    int rEye = (row+row1)/2;
    int cEye = (col+col1)/2;
    if(getStoneId(rEye, cEye) != -1)
        return false;

    if(isBottomSide(moveid))
    {
        if(row < 4) return false;
    }
    else
    {
        if(row > 5) return false;
    }
    return true;
}

bool Board::canMove(int moveid, int killid, int row, int col)
{
    if(sameColor(moveid, killid)) return false;

    switch (_s[moveid]._type)
    {
    case Stone::CHE:
        return canMoveChe(moveid, killid, row, col);

    case Stone::MA:
        return canMoveMa(moveid, killid, row, col);

    case Stone::PAO:
        return canMovePao(moveid, killid, row, col);

    case Stone::BING:
        return canMoveBing(moveid, killid, row, col);

    case Stone::JIANG:
        return canMoveJiang(moveid, killid, row, col);

    case Stone::SHI:
        return canMoveShi(moveid, killid, row, col);

    case Stone::XIANG:
        return canMoveXiang(moveid, killid, row, col);

    }
    return false;
}

void Board::reliveStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = false;
}

void Board::killStone(int id,int isFake)
{
    if(id==-1) return;
    _s[id]._dead = true;

    if(isFake==0&&_s[id]._type==Stone::JIANG){
        if(_s[id]._red){
            qDebug()<<"BLACK";
            QMessageBox::StandardButton rb=QMessageBox::information(NULL, QString("胜利"), QString("黑方胜利"), QMessageBox::Ok);
            if(rb==QMessageBox::Ok){
                qApp->quit();
            }
        }
        else{
            QMessageBox::StandardButton rb=QMessageBox::information(NULL, QString("胜利"), QString("红方胜利"), QMessageBox::Ok);
            qDebug()<<"RED";
            qApp->quit();
        }
    }

}

bool Board::isBottomSide(int id)
{
    return _bSide == _s[id]._red;
}

void Board::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;

    _bRedTurn = !_bRedTurn;
}

void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps,int Fake)
{
    GetRowCol(row1, col1, moveid);
    Step* step = new Step;
    step->_colFrom = col1;
    step->_colTo = col;
    step->_rowFrom = row1;
    step->_rowTo = row;
    step->_moveid = moveid;
    step->_killid = killid;

    steps.append(step);
    if(Fake==0){
        if(!_bSide){
            col=8-col;
            col1=8-col1;
            row=8-row;
            row1=8-row1;
        }
        QString s=name(moveid);
        qDebug()<<"col1:"<<col1<<endl;
        if(_s[moveid]._type==Stone::MA||_s[moveid]._type==Stone::XIANG||_s[moveid]._type==Stone::SHI)
        {
            if(_s[moveid]._red){
                s+=QString::number(col1+1,10);
                if(row>row1){
                    s+=QString("退");
                }else{
                    s+=QString("进");
                }
                s+=QString::number(abs(col+1),10);
            }else{
                s+=QString::number(9-col1,10);
                if(row>row1){
                    s+=QString("进");
                }else{
                    s+=QString("退");
                }
                s+=QString::number(abs(9-col),10);
            }

        }else{
            if(_s[moveid]._red){
                if(row==row1){
                    s+=QString::number(col1+1,10);
                    s+=QString("平");
                    s+=QString::number(col+1,10);
                }else{
                    s+=QString::number(col1+1,10);
                    if(row>row1){
                        s+=QString("退");
                    }else{
                        s+=QString("进");
                    }
                    s+=QString::number(abs(row1-row),10);
                }
            }else{
                if(row==row1){
                    s+=QString::number(9-col1,10);
                    s+=QString("平");
                    s+=QString::number(9-col,10);
                }else{
                    s+=QString::number(9-col1,10);
                    if(row>row1){
                        s+=QString("进");
                    }else{
                        s+=QString("推");
                    }
                    s+=QString::number(abs(row-row1),10);
                }
            }
        }

        this->_cp->listWidget->addItem("                    "+s);
    }

}

void Board::moveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid, killid, row, col, _steps);
    moveStone(moveid, row, col);
    killStone(killid);

}

void Board::click(int id, int row, int col)
{
    if(this->_selectid == -1)
    {
        trySelectStone(id);
    }
    else
    {
        tryMoveStone(id, row, col);
    }
}

void Board::click(QPoint pt)
{
    int row, col;
    bool bClicked = getClickRowCol(pt, row, col);
    if(!bClicked) return;

    int id = getStoneId(row, col);
    click(id, row, col);
}

int Board::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(_s[i]._row == row && _s[i]._col == col && !isDead(i))
            return i;
    }
    return -1;
}

void Board::back(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void Board::backOne()
{
    if(this->_steps.size() == 0) return;

    Step* step = this->_steps.last();
    _steps.removeLast();
    back(step);

    update();
    delete step;
    this->_cp->listWidget->takeItem(this->_cp->listWidget->count()-1);
}

void Board::back()
{
    backOne();
}

void Board::slotBack()
{
    back();
}

void Board::slotChangeIndex(int i){
    qDebug()<<"index:"<<i+1;
}


