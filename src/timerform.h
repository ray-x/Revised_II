#ifndef TIMERFORM_H
#define TIMERFORM_H

#include <QWidget>
#include"ui_timerform.h"

namespace Ui {
class TimerForm;
}

class TimerForm : public QWidget
{
    Q_OBJECT
signals :
    void sigInsertTimerStep(QStringList steps);

public slots:
    //void showSetAudio();
    void addTimer();
    void newTimer();
    void showTimer();
    void hideTimer();
    void enableDisplay(int);
    void enableAction(int);
    void enablePosition(int);
public:
    explicit TimerForm(QWidget *parent = 0);
    ~TimerForm();



private:
    Ui::TimerForm *ui;
    QString timerName;
    QString timeCountdown;
    QString actString;
    QString displayStr;
    QStringList pyScript;
    QStringList screenScript;
    QString showTimerStr;
    QString hideTimerStr;
    QStringList effectsStrL;
};

#endif // TIMERFORM_H
