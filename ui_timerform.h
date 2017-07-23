/********************************************************************************
** Form generated from reading UI file 'timerform.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMERFORM_H
#define UI_TIMERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimerForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QCheckBox *displayCheckBox;
    QLineEdit *timerNamelineEdit;
    QLineEdit *timerCountDownlineEdit;
    QLineEdit *timerActionlineEdit;
    QPlainTextEdit *timerDisplayableLineEdit;
    QPlainTextEdit *timerPyPlainTextEdit;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *showTimerPushButton;
    QLineEdit *timerPosionlineEdit;
    QPushButton *hideTimerPushBtn;
    QComboBox *effectComboBox;
    QLabel *label_6;
    QCheckBox *timerPositionChkBox;
    QCheckBox *timerActionCheckBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addTimerPushButton;

    void setupUi(QWidget *TimerForm)
    {
        if (TimerForm->objectName().isEmpty())
            TimerForm->setObjectName(QStringLiteral("TimerForm"));
        TimerForm->setEnabled(true);
        TimerForm->resize(514, 595);
        label = new QLabel(TimerForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 21));
        label_2 = new QLabel(TimerForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(270, 20, 121, 21));
        displayCheckBox = new QCheckBox(TimerForm);
        displayCheckBox->setObjectName(QStringLiteral("displayCheckBox"));
        displayCheckBox->setGeometry(QRect(20, 100, 131, 19));
        timerNamelineEdit = new QLineEdit(TimerForm);
        timerNamelineEdit->setObjectName(QStringLiteral("timerNamelineEdit"));
        timerNamelineEdit->setGeometry(QRect(120, 20, 113, 21));
        timerCountDownlineEdit = new QLineEdit(TimerForm);
        timerCountDownlineEdit->setObjectName(QStringLiteral("timerCountDownlineEdit"));
        timerCountDownlineEdit->setGeometry(QRect(400, 20, 61, 21));
        timerActionlineEdit = new QLineEdit(TimerForm);
        timerActionlineEdit->setObjectName(QStringLiteral("timerActionlineEdit"));
        timerActionlineEdit->setEnabled(false);
        timerActionlineEdit->setGeometry(QRect(150, 50, 321, 21));
        timerDisplayableLineEdit = new QPlainTextEdit(TimerForm);
        timerDisplayableLineEdit->setObjectName(QStringLiteral("timerDisplayableLineEdit"));
        timerDisplayableLineEdit->setEnabled(false);
        timerDisplayableLineEdit->setGeometry(QRect(150, 90, 321, 51));
        timerPyPlainTextEdit = new QPlainTextEdit(TimerForm);
        timerPyPlainTextEdit->setObjectName(QStringLiteral("timerPyPlainTextEdit"));
        timerPyPlainTextEdit->setEnabled(false);
        timerPyPlainTextEdit->setGeometry(QRect(150, 160, 321, 191));
        label_4 = new QLabel(TimerForm);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 160, 61, 21));
        label_5 = new QLabel(TimerForm);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 180, 91, 16));
        showTimerPushButton = new QPushButton(TimerForm);
        showTimerPushButton->setObjectName(QStringLiteral("showTimerPushButton"));
        showTimerPushButton->setGeometry(QRect(20, 420, 171, 31));
        timerPosionlineEdit = new QLineEdit(TimerForm);
        timerPosionlineEdit->setObjectName(QStringLiteral("timerPosionlineEdit"));
        timerPosionlineEdit->setEnabled(false);
        timerPosionlineEdit->setGeometry(QRect(230, 420, 271, 31));
        timerPosionlineEdit->setReadOnly(true);
        hideTimerPushBtn = new QPushButton(TimerForm);
        hideTimerPushBtn->setObjectName(QStringLiteral("hideTimerPushBtn"));
        hideTimerPushBtn->setGeometry(QRect(20, 470, 171, 31));
        effectComboBox = new QComboBox(TimerForm);
        effectComboBox->setObjectName(QStringLiteral("effectComboBox"));
        effectComboBox->setGeometry(QRect(290, 470, 151, 31));
        label_6 = new QLabel(TimerForm);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(210, 464, 72, 31));
        QFont font;
        font.setFamily(QStringLiteral("Century"));
        font.setPointSize(10);
        label_6->setFont(font);
        timerPositionChkBox = new QCheckBox(TimerForm);
        timerPositionChkBox->setObjectName(QStringLiteral("timerPositionChkBox"));
        timerPositionChkBox->setGeometry(QRect(200, 428, 91, 21));
        timerActionCheckBox = new QCheckBox(TimerForm);
        timerActionCheckBox->setObjectName(QStringLiteral("timerActionCheckBox"));
        timerActionCheckBox->setGeometry(QRect(20, 50, 121, 19));
        layoutWidget = new QWidget(TimerForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 370, 281, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        addTimerPushButton = new QPushButton(layoutWidget);
        addTimerPushButton->setObjectName(QStringLiteral("addTimerPushButton"));

        horizontalLayout->addWidget(addTimerPushButton);


        retranslateUi(TimerForm);

        QMetaObject::connectSlotsByName(TimerForm);
    } // setupUi

    void retranslateUi(QWidget *TimerForm)
    {
        TimerForm->setWindowTitle(QApplication::translate("TimerForm", "Form", 0));
        label->setText(QApplication::translate("TimerForm", "TimerName:", 0));
        label_2->setText(QApplication::translate("TimerForm", "TimerCountDown:", 0));
        displayCheckBox->setText(QApplication::translate("TimerForm", "Displayable", 0));
        timerNamelineEdit->setText(QApplication::translate("TimerForm", "Timer", 0));
        timerCountDownlineEdit->setText(QApplication::translate("TimerForm", "30", 0));
        timerActionlineEdit->setText(QApplication::translate("TimerForm", "[Hide(\"timer\"), Jump(\"gameover\")]", 0));
        timerDisplayableLineEdit->setPlainText(QApplication::translate("TimerForm", "add DynamicDisplayable(countdown, sec = time) align (0.5, 0.3)", 0));
        timerPyPlainTextEdit->setPlainText(QApplication::translate("TimerForm", "init python:                  \n"
"    def countdown(st, at, sec):\n"
"        rs = sec - st\n"
"        rt = Text('Remain {:.1f} Sec'.format(rs), size = 40)\n"
"        return (rt, 0.1)", 0));
        label_4->setText(QApplication::translate("TimerForm", "Dynamic", 0));
        label_5->setText(QApplication::translate("TimerForm", "Displayable", 0));
        showTimerPushButton->setText(QApplication::translate("TimerForm", "Show Timer Screen", 0));
        timerPosionlineEdit->setText(QApplication::translate("TimerForm", "at Position(xalign=.1, yalign=.1)", 0));
        hideTimerPushBtn->setText(QApplication::translate("TimerForm", "Hide Timer", 0));
        label_6->setText(QApplication::translate("TimerForm", "effect:", 0));
        timerPositionChkBox->setText(QString());
        timerActionCheckBox->setText(QApplication::translate("TimerForm", "TimerAction:", 0));
        addTimerPushButton->setText(QApplication::translate("TimerForm", "Add Timer", 0));
    } // retranslateUi

};

namespace Ui {
    class TimerForm: public Ui_TimerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMERFORM_H
