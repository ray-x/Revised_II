/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2014-2015  Ray             <ray.cn@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .
 */
#include <QDebug>

#include "timerform.h"
#include "ui_timerform.h"



TimerForm::TimerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerForm)
{

    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    //ui->videoListWidget->setViewMode(QListView::ListMode);
    //ui->videoListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //ui->videoListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //listWidget->selectedItems()
    connect(ui->addTimerPushButton, SIGNAL(clicked()), this, SLOT(addTimer()));
    //connect(ui->newTimerPushButton, SIGNAL(clicked()), this, SLOT(addMoreVideo()));
    connect(ui->showTimerPushButton, SIGNAL(clicked()), this, SLOT(showTimer()));
    connect(ui->hideTimerPushBtn, SIGNAL(clicked()), this, SLOT(hideTimer()));
	effectsStrL = QStringList({ "None", "fade", "dissolve", "pixellate", "move", "moveinright", "moveoutright", "ease", \
		"zoomin", "zoomout", "zoominout", "vpunch", "hpunch", "blinds", "squares", "wipeleft", "slideleft", "slideawayleft", "irisin" });
    ui->effectComboBox->insertItems(0, effectsStrL);
    ui->effectComboBox->setMaxVisibleItems(10);

    connect(ui->displayCheckBox, SIGNAL(stateChanged(int)), this, SLOT(enableDisplay(int)));
    connect(ui->timerActionCheckBox, SIGNAL(stateChanged(int)), this, SLOT(enableAction(int)));
    connect(ui->timerPositionChkBox, SIGNAL(stateChanged(int)), this, SLOT(enablePosition(int)));
}

TimerForm::~TimerForm()
{
    delete ui;
}

#if 0
screen timer : 
    default time = 30
    timer time action[Hide("timer"), Jump("gameover")]
    add DynamicDisplayable(countdown, sec = time) align(0.5, 0.3)

init python :
    def countdown(show_time, same_tag_show_time, sec) :
        remain_sec = sec - show_time
        remain_text = Text('remain {:.1f} s'.format(remain_sec), size = 40)
        return (remain_text, 0.1)
#endif



//void showSetAudio();
void TimerForm::addTimer()
{
    QStringList cmds = {};
    if (ui->timerNamelineEdit->text().isEmpty())
        return;
    timerName = ui->timerNamelineEdit->text();
    if (!ui->timerCountDownlineEdit->text().isEmpty())
        timeCountdown = ui->timerCountDownlineEdit->text();
    if (ui->timerActionCheckBox->isChecked())
        actString = ui->timerActionlineEdit->text();
    if (ui->displayCheckBox->isChecked())
    {
        displayStr = ui->timerDisplayableLineEdit->toPlainText();
        pyScript = ui->timerPyPlainTextEdit->toPlainText().split("\n");
        for (auto m : pyScript)
            qDebug() << m;
    }
    QString line1, line2, line3, line4;
    line1=QString("    screen %1 :").arg(timerName);
    line2=QString("    default time = %1").arg(timeCountdown);
    cmds.push_back(line1);
    cmds.push_back(line2);
    if (ui->timerActionCheckBox->isChecked())
    {
        line3 = QString("    %1 time action %2").arg(timerName).arg(actString);
        cmds.push_back(line3);
    }
    
    if (ui->displayCheckBox->isChecked())
    {
        cmds.push_back(displayStr);
        cmds = cmds + pyScript;
    }
    emit(sigInsertTimerStep(cmds));

#if 0
    screen timer :
    default time = 30
        timer time action[Hide("timer"), Jump("gameover")]
        add DynamicDisplayable(countdown, sec = time) align(0.5, 0.3)
#endif

    
    qDebug() << "addTimer";
}

void TimerForm::newTimer()
{

    qDebug() << "newTimer";
}
void TimerForm::showTimer()
{
    QStringList cmds = {};
    if (ui->timerNamelineEdit->text().isEmpty())
        return;
    timerName = ui->timerNamelineEdit->text();
    //show screen timer(time = 10)     
    timeCountdown = ui->timerCountDownlineEdit->text().trimmed();

    QString delay = timeCountdown.isEmpty() ? QString("") : QString("(time = % 2)").arg(timeCountdown);
    QString positon = ui->timerPositionChkBox->isChecked() ? ui->timerPosionlineEdit->text() : QString("");
    cmds.push_back(QString("show screen %1 %2 %3").arg(timerName).arg(delay).arg(positon));
    emit(sigInsertTimerStep(cmds));
    qDebug() << "showTimer";
}
void TimerForm::hideTimer()
{
    //hide screen timer 
    QStringList cmds = {};
    if (ui->timerNamelineEdit->text().isEmpty())
        return;
    int idx = ui->effectComboBox->currentIndex();
    QString effect = idx>0 ? effect.at(idx) : QString("");
    cmds.push_back(QString("hide screen %1 %2").arg(timerName).arg(effect));
    qDebug() << "hideTimer";
}

void TimerForm::enableAction(int flag)
{
    if (flag == Qt::Checked)
        ui->timerActionlineEdit->setEnabled(true);
    else
        ui->timerActionlineEdit->setEnabled(false);
};
void TimerForm::enableDisplay(int flag)
{
    if (flag == Qt::Checked)
    {
        ui->timerDisplayableLineEdit->setEnabled(true);
        ui->timerPyPlainTextEdit->setEnabled(true);
    }
    else{
        ui->timerActionlineEdit->setEnabled(false);
        ui->timerPyPlainTextEdit->setEnabled(false);
    }
        
}
void TimerForm::enablePosition(int flag)
{
    if (flag == Qt::Checked)
        ui->timerPosionlineEdit->setEnabled(true);
    else
        ui->timerPosionlineEdit->setEnabled(false);
}
