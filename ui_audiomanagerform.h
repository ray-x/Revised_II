/********************************************************************************
** Form generated from reading UI file 'audiomanagerform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOMANAGERFORM_H
#define UI_AUDIOMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioManagerForm
{
public:
    QLabel *label;
    QListWidget *audioListWidget;
    QGroupBox *groupBox;
    QCheckBox *FadeInChkBox;
    QLineEdit *FadeInTimeLEdit;
    QCheckBox *FadeoutChkBox;
    QLineEdit *FadeOutTimeLEdit;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *LoopChkBox;
    QPushButton *AddMusicStepPBtn;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *QueueMusiccheckBox;
    QPushButton *pushButton;
    QPushButton *AddMusicPushButton;

    void setupUi(QWidget *AudioManagerForm)
    {
        if (AudioManagerForm->objectName().isEmpty())
            AudioManagerForm->setObjectName(QStringLiteral("AudioManagerForm"));
        AudioManagerForm->resize(377, 528);
        label = new QLabel(AudioManagerForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 141, 16));
        audioListWidget = new QListWidget(AudioManagerForm);
        audioListWidget->setObjectName(QStringLiteral("audioListWidget"));
        audioListWidget->setGeometry(QRect(30, 40, 321, 251));
        groupBox = new QGroupBox(AudioManagerForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 370, 291, 101));
        FadeInChkBox = new QCheckBox(groupBox);
        FadeInChkBox->setObjectName(QStringLiteral("FadeInChkBox"));
        FadeInChkBox->setGeometry(QRect(20, 20, 91, 19));
        FadeInTimeLEdit = new QLineEdit(groupBox);
        FadeInTimeLEdit->setObjectName(QStringLiteral("FadeInTimeLEdit"));
        FadeInTimeLEdit->setGeometry(QRect(130, 20, 113, 21));
        FadeoutChkBox = new QCheckBox(groupBox);
        FadeoutChkBox->setObjectName(QStringLiteral("FadeoutChkBox"));
        FadeoutChkBox->setGeometry(QRect(20, 50, 91, 19));
        FadeOutTimeLEdit = new QLineEdit(groupBox);
        FadeOutTimeLEdit->setObjectName(QStringLiteral("FadeOutTimeLEdit"));
        FadeOutTimeLEdit->setGeometry(QRect(130, 50, 113, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 20, 72, 15));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 50, 21, 16));
        LoopChkBox = new QCheckBox(groupBox);
        LoopChkBox->setObjectName(QStringLiteral("LoopChkBox"));
        LoopChkBox->setGeometry(QRect(20, 80, 101, 19));
        AddMusicStepPBtn = new QPushButton(AudioManagerForm);
        AddMusicStepPBtn->setObjectName(QStringLiteral("AddMusicStepPBtn"));
        AddMusicStepPBtn->setGeometry(QRect(130, 480, 121, 28));
        layoutWidget = new QWidget(AudioManagerForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 340, 261, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        QueueMusiccheckBox = new QCheckBox(layoutWidget);
        QueueMusiccheckBox->setObjectName(QStringLiteral("QueueMusiccheckBox"));

        horizontalLayout->addWidget(QueueMusiccheckBox);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        AddMusicPushButton = new QPushButton(AudioManagerForm);
        AddMusicPushButton->setObjectName(QStringLiteral("AddMusicPushButton"));
        AddMusicPushButton->setGeometry(QRect(130, 300, 121, 28));

        retranslateUi(AudioManagerForm);

        QMetaObject::connectSlotsByName(AudioManagerForm);
    } // setupUi

    void retranslateUi(QWidget *AudioManagerForm)
    {
        AudioManagerForm->setWindowTitle(QApplication::translate("AudioManagerForm", "Add Audio", Q_NULLPTR));
        label->setText(QApplication::translate("AudioManagerForm", "Musice/Audio", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("AudioManagerForm", "Effects", Q_NULLPTR));
        FadeInChkBox->setText(QApplication::translate("AudioManagerForm", "FadeIn", Q_NULLPTR));
        FadeoutChkBox->setText(QApplication::translate("AudioManagerForm", "FadeOut", Q_NULLPTR));
        label_2->setText(QApplication::translate("AudioManagerForm", "s", Q_NULLPTR));
        label_3->setText(QApplication::translate("AudioManagerForm", "s", Q_NULLPTR));
        LoopChkBox->setText(QApplication::translate("AudioManagerForm", "LoopMusic", Q_NULLPTR));
        AddMusicStepPBtn->setText(QApplication::translate("AudioManagerForm", "AddMusicStep", Q_NULLPTR));
        QueueMusiccheckBox->setText(QApplication::translate("AudioManagerForm", "AddToQueue", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AudioManagerForm", "QueMusic", Q_NULLPTR));
        AddMusicPushButton->setText(QApplication::translate("AudioManagerForm", "AddMoreMusic", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AudioManagerForm: public Ui_AudioManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOMANAGERFORM_H
