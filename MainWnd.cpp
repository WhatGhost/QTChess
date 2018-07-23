#include "MainWnd.h"
#include <QHBoxLayout>
#include "ChooseDlg.h"
#include "SingleGame.h"
#include "MultiGame.h"
#include "NetGame.h"
#include "ChooseDlg.h"
#include <QCoreApplication>
#include <QString>
#include <QIcon>
#include <QProcess>

MainWnd::MainWnd(int gameType, QWidget *parent) : QWidget(parent)
{


    //dlg.exec();
    //_gameType = dlg._selected;
    _gameType=gameType;


    this->setWindowIcon(QIcon(":/img/images/logo.png"));
   // this->setStyleSheet("MainWnd{border-image:url(:/img/images/ChooseBgd.png);}");
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
    QBrush(QPixmap(":/img/images/ChooseBgd.png").scaled(// 缩放背景图.
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图



    CtrlPanel* panel = new CtrlPanel;
    if(_gameType == 0)
    {
        this->setWindowTitle(QString("人机对战"));
        SingleGame* game = new SingleGame;
        panel->_cb->setVisible(true);
        game->setCtrlPanel(panel);
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
        connect(panel, SIGNAL(sendsignal()), this, SLOT(slotreturn()));
        connect(panel, SIGNAL(sigChangeIndex(int)), game, SLOT(slotChangeIndex(int)));
        //connect(panel, SIGNAL(sigMusic()), this, SLOT(slotMusic()));
    }
    else if(_gameType == 1)
    {
        this->setWindowTitle(QString("双人对战"));
        MultiGame* game = new MultiGame;
        panel->_cb->setVisible(false);
       // CtrlPanel* panel = new CtrlPanel;
        game->setCtrlPanel(panel);
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sendsignal()), this, SLOT(slotreturn()));
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }
    else if(_gameType == 2)
    { this->setWindowTitle(QString("网络对战（服务端）"));
        NetGame* game = new NetGame(true);
        panel->_cb->setVisible(false);
        //CtrlPanel* panel = new CtrlPanel;
        game->setCtrlPanel(panel);
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sendsignal()), this, SLOT(slotreturn()));
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }
    else if(_gameType == 3)
    {
        this->setWindowTitle(QString("网络对战（客户端）"));
        NetGame* game = new NetGame(false);
        panel->_cb->setVisible(false);
       // CtrlPanel* panel = new CtrlPanel;
        game->setCtrlPanel(panel);
        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sendsignal()), this, SLOT(slotreturn()));
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }

}

MainWnd::~MainWnd()
{

}

void MainWnd::slotExit(){
    qApp->exit(0);
}

void MainWnd::slotreturn(){
    //this->re
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    qApp->exit(0);


}
