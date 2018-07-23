#ifndef ChooseDlg_H
#define ChooseDlg_H

#include <QDialog>
#include <QPushButton>
#include <QMediaPlayer>

class ChooseDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseDlg(QWidget *parent = 0);
    ~ChooseDlg();

    QPushButton* _buttons[4];
    QPushButton* _music;
    QMediaPlayer  *player;
    int _selected;
    bool play;
signals:

public slots:
    void slotClicked();
    void onMusicClick();
};

#endif // ChooseDlg_H
