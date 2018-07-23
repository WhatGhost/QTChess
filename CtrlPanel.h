#ifndef CTRLPANEL_H
#define CTRLPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>

class CtrlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlPanel(QWidget *parent = 0);
    ~CtrlPanel();

    QPushButton* _back;
    bool ret;
    QPushButton* _return;
    QListWidget* listWidget;
    QComboBox* _cb;

signals:
    void sigBack();
    void sendsignal();
    void sigChangeIndex(int);
    //void sigReturn();


public slots:
    void sReturn();
};

#endif // CTRLPANEL_H
