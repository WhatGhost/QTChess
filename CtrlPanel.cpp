#include "CtrlPanel.h"
#include "ChooseDlg.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDebug>
#include <QProcess>
#include <QComboBox>

CtrlPanel::CtrlPanel(QWidget *parent) : QWidget(parent)
{
    listWidget = new QListWidget(this);
    listWidget->setMinimumHeight(100);
    listWidget->setMaximumWidth(200);
    listWidget->setStyleSheet("QListWidget{border-image:url(:/img/images/ctrl.jpg)}");

    QGridLayout* grid = new QGridLayout(this);
    QVBoxLayout* vLay = new QVBoxLayout;
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(2, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(2, 1);
    grid->addLayout(vLay, 1, 1);
    vLay->addWidget(this->_back = new QPushButton(QString("悔棋")),0,Qt::AlignCenter);
    this->_back->setFixedSize(90,30);
    this->_back->setStyleSheet("QPushButton{border-image:url(:/img/images/buttonb.png);\
                               color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
"QPushButton:hover{border-image:url(:/img/images/buttonb.png); color: black;}"  // 鼠标停放时的色彩
"QPushButton:pressed{border-image:url(:/img/images/buttonb.png); border-style: inset; }");

    vLay->addWidget(listWidget,0,Qt::AlignCenter);
    vLay->addWidget(this->_return = new QPushButton(QString("返回")),0,Qt::AlignCenter);
    _cb = new QComboBox(this);
    _cb->addItem(QString("超超超菜"));
    _cb->addItem(QString("超超菜"));
    _cb->addItem(QString("超菜"));
    _cb->addItem(QString("菜"));
    _cb->addItem(QString("还行"));
    _cb->setCurrentIndex(3);
    vLay->addWidget(_cb);
    this->_return->setFixedSize(90,30);
    this->_return->setStyleSheet("QPushButton{border-image:url(:/img/images/buttonb.png);\
                               color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
"QPushButton:hover{border-image:url(:/img/images/buttonb.png); color: black;}"  // 鼠标停放时的色彩
"QPushButton:pressed{border-image:url(:/img/images/buttonb.png); border-style: inset; }");


    connect(this->_return, SIGNAL(clicked()), this, SLOT(sReturn()));
    connect(this->_back, SIGNAL(clicked()), this, SIGNAL(sigBack()));
    connect(_cb, SIGNAL(currentIndexChanged(int)), this, SIGNAL(sigChangeIndex(int)));
    ret=false;

}
void CtrlPanel:: sReturn(){

    //ChooseDlg dlg;
    //dlg.exec();
    ret=true;
    emit sendsignal();
    this->close();
}

CtrlPanel::~CtrlPanel()
{

}


