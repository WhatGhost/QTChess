#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include "Board.h"
#include "CtrlPanel.h"
#include "ChooseDlg.h"


class MainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MainWnd(int gameType, QWidget *parent = 0);
    ~MainWnd();


    ChooseDlg dlg;
    int _gameType;
public slots:
    void slotreturn();
    void slotExit();
   // void slotMusic();
signals:
     void sendsignal();


public slots:
};

#endif // MAINWND_H
