#ifndef TIMERFORM_H
#define TIMERFORM_H


#include <QWidget>
#include<QTimer>
namespace Ui {
    class TimerForm;
}

class TimerForm : public QWidget
{
    Q_OBJECT

public:
    explicit TimerForm(QWidget *parent = 0);
    ~TimerForm();

    void StartStopwatch();  //启动秒表
    void ResetStopwatch();  //复位秒表
    void StopStopwatch();   //暂停秒表

private:
    Ui::TimerForm *ui;

     int hourTemp;           //Hour
     int minuteTemp;         //Minute
     int secondTemp;         //Second
     int countTemp;

   QTimer *msTimer;   //定义一个定时器
   void Display(QString,QString,QString);
   void SetStrLength(QString *str, int length);
private slots:
    void TimeSlot();
};




#endif // TIMERFORM_H
