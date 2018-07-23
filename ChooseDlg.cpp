#include "ChooseDlg.h"
#include <QVBoxLayout>
#include <QString>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPixmap>
#include <QIcon>

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{


    player = new QMediaPlayer(this);
    player->setMedia(QMediaContent(QUrl::fromLocalFile("E:\\code_for_nothing\\QTchess\\Chess\\Chess\\MUSICS\\hillwater.mp3")));
    play=true;
    player->play();
    _selected=-1;

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    this->setWindowTitle(QString("模式选择"));
    this->setWindowIcon(QIcon(":/img/images/logo.png"));
    this->setStyleSheet("QDialog{border-image:url(:/img/images/123.png);}");
    int _r=20;
    this->setMinimumSize(_r*18+20,_r*20+1);

    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(_music= new QPushButton(""),0,Qt::AlignLeft);
    lay->addWidget(_buttons[0] = new QPushButton("人机对战"),0,Qt::AlignCenter);
    lay->addWidget(_buttons[1] = new QPushButton("人人对战"),0,Qt::AlignCenter);
    lay->addWidget(_buttons[2] = new QPushButton("网络对战(服务端)"),0,Qt::AlignCenter);
    lay->addWidget(_buttons[3] = new QPushButton("网络对战(客户端)"),0,Qt::AlignCenter);
    _music->setFixedSize(30,30);
    _buttons[0]->setFixedSize(120,30);
    _buttons[1]->setFixedSize(120,30);
    _buttons[2]->setFixedSize(120,30);
    _buttons[3]->setFixedSize(120,30);

   // QIcon button_ico(":/img/images/musicopen1.jpg");
    _music->setStyleSheet("QPushButton{border-image: url(:/img/images/musicopen.png);}");
    _buttons[0]->setStyleSheet("QPushButton{border-image:url(:/img/images/buttona.png);\
                               color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
"QPushButton:hover{background-color:#CCFFFF; color: black;}"  // 鼠标停放时的色彩
"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");

    _buttons[1]->setStyleSheet("QPushButton{border-image:url(:/img/images/buttona.png);\
                               color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
"QPushButton:hover{background-color:#CCFFFF; color: black;}"  // 鼠标停放时的色彩
"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    _buttons[2]->setStyleSheet("QPushButton{border-image:url(:/img/images/buttona.png);\
                               color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
"QPushButton:hover{background-color:#CCFFFF; color: black;}"  // 鼠标停放时的色彩
"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    _buttons[3]->setStyleSheet("QPushButton{border-image:url(:/img/images/buttona.png);\
                               color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
"QPushButton:hover{background-color:#CCFFFF; color: black;}"  // 鼠标停放时的色彩
"QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");


    connect(_music, SIGNAL(clicked()), this, SLOT(onMusicClick()));
    for(int i=0; i<4; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<4; ++i)
    {
        if(_buttons[i] == s)
        {
            this->_selected = i;
            break;
        }
    }
    accept();
}

void ChooseDlg::onMusicClick()
{
   // QObject* s = sender();
    //播放
    if(play)
    {
        player->pause();
        play=!play;
        _music->setStyleSheet("QPushButton{border-image: url(:/img/images/musicclose.png);}");
    }else{
        play=!play;
        player->play();
        _music->setStyleSheet("QPushButton{border-image: url(:/img/images/musicopen.png);}");

    }

    //accept();
}

ChooseDlg::~ChooseDlg()
{

}

