/********************************************************************************
** Form generated from reading UI file 'videomanager.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOMANAGER_H
#define UI_VIDEOMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoManager
{
public:
    QListWidget *videoListWidget;
    QPushButton *addVideoStepBtn;
    QGroupBox *groupBox;
    QRadioButton *ImageRdBox;
    QRadioButton *FullScreenRdBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addVideoBtn;
    QPushButton *removeVideoBtn;

    void setupUi(QWidget *VideoManager)
    {
        if (VideoManager->objectName().isEmpty())
            VideoManager->setObjectName(QStringLiteral("VideoManager"));
        VideoManager->resize(361, 479);
        VideoManager->setToolTipDuration(1);
        videoListWidget = new QListWidget(VideoManager);
        videoListWidget->setObjectName(QStringLiteral("videoListWidget"));
        videoListWidget->setGeometry(QRect(18, 20, 321, 291));
        addVideoStepBtn = new QPushButton(VideoManager);
        addVideoStepBtn->setObjectName(QStringLiteral("addVideoStepBtn"));
        addVideoStepBtn->setGeometry(QRect(120, 440, 111, 28));
        groupBox = new QGroupBox(VideoManager);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 380, 301, 61));
        ImageRdBox = new QRadioButton(groupBox);
        ImageRdBox->setObjectName(QStringLiteral("ImageRdBox"));
        ImageRdBox->setGeometry(QRect(20, 30, 115, 19));
        ImageRdBox->setChecked(true);
        FullScreenRdBox = new QRadioButton(groupBox);
        FullScreenRdBox->setObjectName(QStringLiteral("FullScreenRdBox"));
        FullScreenRdBox->setGeometry(QRect(170, 30, 115, 19));
        widget = new QWidget(VideoManager);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(28, 340, 301, 30));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        addVideoBtn = new QPushButton(widget);
        addVideoBtn->setObjectName(QStringLiteral("addVideoBtn"));

        horizontalLayout->addWidget(addVideoBtn);

        removeVideoBtn = new QPushButton(widget);
        removeVideoBtn->setObjectName(QStringLiteral("removeVideoBtn"));

        horizontalLayout->addWidget(removeVideoBtn);


        retranslateUi(VideoManager);

        QMetaObject::connectSlotsByName(VideoManager);
    } // setupUi

    void retranslateUi(QWidget *VideoManager)
    {
        VideoManager->setWindowTitle(QApplication::translate("VideoManager", "Add Video", Q_NULLPTR));
        addVideoStepBtn->setText(QApplication::translate("VideoManager", "AddVideoStep", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("VideoManager", "GroupBox", Q_NULLPTR));
        ImageRdBox->setText(QApplication::translate("VideoManager", "AsImage", Q_NULLPTR));
        FullScreenRdBox->setText(QApplication::translate("VideoManager", "FullScreen", Q_NULLPTR));
        addVideoBtn->setText(QApplication::translate("VideoManager", "AddVideo", Q_NULLPTR));
        removeVideoBtn->setText(QApplication::translate("VideoManager", "RemoveVideo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VideoManager: public Ui_VideoManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOMANAGER_H
