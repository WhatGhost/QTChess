#include "timerform.h"
#include "ui_timerform.h"

TimerForm::TimerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerForm)
{
    ui->setupUi(this);
    countTemp=0;
    secondTemp=0;
    minuteTemp=0;
    hourTemp=0;
    msTimer= new QTimer(this);  //this说明是当前类对象的定时器
    //把信号与槽进行连接
    connect(msTimer,SIGNAL(timeout()),this,SLOT(TimeSlot()));
}
void TimerForm::Display(QString hour, QString minute, QString second)
{
    ui->lineEditH->setText(hour);
    ui->lineEditM->setText(minute);
    ui->lineEditS->setText(second);
}

void TimerForm::StartStopwatch(){
    msTimer->start(10); //10ms
}

TimerForm::~TimerForm()
{
    delete ui;
}

void TimerForm::TimeSlot(){
    countTemp+=1;
        if(countTemp==100)
        {
            countTemp=0;
            secondTemp+=1;
            if(secondTemp==60)
            {
                secondTemp=0;
                minuteTemp+=1;
                if(minuteTemp==60)
                {
                    minuteTemp=0;
                    hourTemp+=1;
                    if(hourTemp==24)
                    {
                        hourTemp=0;
                    }
                }
            }
        }
        //把整数转换成字符串
        QString hourstr = QString::number(hourTemp);
        QString minutestr = QString::number(minuteTemp);
        QString secondstr = QString::number(secondTemp);
        Display(hourstr,minutestr,secondstr);
}


