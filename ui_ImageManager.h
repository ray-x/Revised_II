/********************************************************************************
** Form generated from reading UI file 'ImageManager.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEMANAGER_H
#define UI_IMAGEMANAGER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageManagerForm
{
public:
    QGroupBox *imageListGroupbox;
    QListWidget *imageList;
    QPushButton *addAnotherImageButton;
    QPushButton *setBackgroundButton;
    QGroupBox *currentImageGroupbox;
    QLabel *imageRefLabel;
    QLineEdit *imageRefLineEdit;
    QGroupBox *groupBox_3;
    QRadioButton *radioButtonL;
    QRadioButton *radioButtonM;
    QRadioButton *radioButtonR;
    QGroupBox *groupBox_4;
    QLineEdit *xPosLineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *yPosLineEdit;
    QLabel *label_2;
    QLineEdit *behindCharactersLineEdit;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *applyImageChange;
    QTextEdit *textEdit;
    QSplitter *splitter;
    QPushButton *changeImageRefButton;
    QPushButton *removeSelectedImageButton;
    QCheckBox *ckbHide;
    QLineEdit *xScaleLineEdit;
    QLabel *label_5;
    QPushButton *addScaledImageButton;
    QLabel *label;
    QComboBox *effectsComboBox;
    QGroupBox *groupBox;
    QComboBox *ATLsComboBox5;
    QComboBox *ATLsComboBox1;
    QComboBox *ATLsComboBox3;
    QLineEdit *ATLEdit1;
    QLineEdit *ATLEdit3;
    QLineEdit *ATLEdit5;
    QLineEdit *ATLEdit6;
    QComboBox *ATLsComboBox6;
    QLineEdit *ATLEdit2;
    QComboBox *ATLsComboBox2;
    QComboBox *ATLsComboBox4;
    QLineEdit *ATLEdit4;
    QCheckBox *ALTLoopChkBox;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *ImageManagerForm)
    {
        if (ImageManagerForm->objectName().isEmpty())
            ImageManagerForm->setObjectName(QStringLiteral("ImageManagerForm"));
        ImageManagerForm->resize(747, 608);
        imageListGroupbox = new QGroupBox(ImageManagerForm);
        imageListGroupbox->setObjectName(QStringLiteral("imageListGroupbox"));
        imageListGroupbox->setGeometry(QRect(20, 20, 331, 571));
        imageList = new QListWidget(imageListGroupbox);
        imageList->setObjectName(QStringLiteral("imageList"));
        imageList->setGeometry(QRect(10, 20, 311, 471));
        addAnotherImageButton = new QPushButton(imageListGroupbox);
        addAnotherImageButton->setObjectName(QStringLiteral("addAnotherImageButton"));
        addAnotherImageButton->setGeometry(QRect(10, 500, 151, 31));
        addAnotherImageButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        setBackgroundButton = new QPushButton(imageListGroupbox);
        setBackgroundButton->setObjectName(QStringLiteral("setBackgroundButton"));
        setBackgroundButton->setGeometry(QRect(170, 500, 151, 31));
        setBackgroundButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        currentImageGroupbox = new QGroupBox(ImageManagerForm);
        currentImageGroupbox->setObjectName(QStringLiteral("currentImageGroupbox"));
        currentImageGroupbox->setGeometry(QRect(360, 20, 381, 571));
        imageRefLabel = new QLabel(currentImageGroupbox);
        imageRefLabel->setObjectName(QStringLiteral("imageRefLabel"));
        imageRefLabel->setGeometry(QRect(50, 30, 21, 21));
        imageRefLineEdit = new QLineEdit(currentImageGroupbox);
        imageRefLineEdit->setObjectName(QStringLiteral("imageRefLineEdit"));
        imageRefLineEdit->setGeometry(QRect(90, 20, 211, 31));
        groupBox_3 = new QGroupBox(currentImageGroupbox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 140, 321, 51));
        radioButtonL = new QRadioButton(groupBox_3);
        buttonGroup = new QButtonGroup(ImageManagerForm);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioButtonL);
        radioButtonL->setObjectName(QStringLiteral("radioButtonL"));
        radioButtonL->setGeometry(QRect(10, 20, 61, 19));
        radioButtonM = new QRadioButton(groupBox_3);
        buttonGroup->addButton(radioButtonM);
        radioButtonM->setObjectName(QStringLiteral("radioButtonM"));
        radioButtonM->setGeometry(QRect(110, 20, 81, 19));
        radioButtonM->setChecked(true);
        radioButtonR = new QRadioButton(groupBox_3);
        buttonGroup->addButton(radioButtonR);
        radioButtonR->setObjectName(QStringLiteral("radioButtonR"));
        radioButtonR->setGeometry(QRect(220, 20, 81, 19));
        groupBox_4 = new QGroupBox(currentImageGroupbox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(30, 210, 321, 51));
        xPosLineEdit = new QLineEdit(groupBox_4);
        xPosLineEdit->setObjectName(QStringLiteral("xPosLineEdit"));
        xPosLineEdit->setEnabled(true);
        xPosLineEdit->setGeometry(QRect(50, 20, 81, 21));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 31, 21));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 20, 31, 21));
        yPosLineEdit = new QLineEdit(groupBox_4);
        yPosLineEdit->setObjectName(QStringLiteral("yPosLineEdit"));
        yPosLineEdit->setEnabled(true);
        yPosLineEdit->setGeometry(QRect(210, 20, 81, 21));
        label_2 = new QLabel(currentImageGroupbox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 190, 221, 21));
        behindCharactersLineEdit = new QLineEdit(currentImageGroupbox);
        behindCharactersLineEdit->setObjectName(QStringLiteral("behindCharactersLineEdit"));
        behindCharactersLineEdit->setGeometry(QRect(100, 270, 221, 21));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        behindCharactersLineEdit->setFont(font);
        behindCharactersLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        label_7 = new QLabel(currentImageGroupbox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 270, 51, 21));
        label_8 = new QLabel(currentImageGroupbox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(60, 290, 241, 21));
        applyImageChange = new QPushButton(currentImageGroupbox);
        applyImageChange->setObjectName(QStringLiteral("applyImageChange"));
        applyImageChange->setGeometry(QRect(140, 540, 93, 28));
        applyImageChange->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        textEdit = new QTextEdit(currentImageGroupbox);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(30, 500, 321, 31));
        splitter = new QSplitter(currentImageGroupbox);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(50, 60, 279, 28));
        splitter->setOrientation(Qt::Horizontal);
        changeImageRefButton = new QPushButton(splitter);
        changeImageRefButton->setObjectName(QStringLiteral("changeImageRefButton"));
        splitter->addWidget(changeImageRefButton);
        removeSelectedImageButton = new QPushButton(splitter);
        removeSelectedImageButton->setObjectName(QStringLiteral("removeSelectedImageButton"));
        removeSelectedImageButton->setShortcut(QStringLiteral("Ctrl+D"));
        splitter->addWidget(removeSelectedImageButton);
        ckbHide = new QCheckBox(splitter);
        ckbHide->setObjectName(QStringLiteral("ckbHide"));
        splitter->addWidget(ckbHide);
        xScaleLineEdit = new QLineEdit(currentImageGroupbox);
        xScaleLineEdit->setObjectName(QStringLiteral("xScaleLineEdit"));
        xScaleLineEdit->setGeometry(QRect(130, 100, 61, 31));
        label_5 = new QLabel(currentImageGroupbox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 100, 61, 21));
        addScaledImageButton = new QPushButton(currentImageGroupbox);
        addScaledImageButton->setObjectName(QStringLiteral("addScaledImageButton"));
        addScaledImageButton->setGeometry(QRect(220, 100, 93, 31));
        label = new QLabel(currentImageGroupbox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 320, 91, 16));
        effectsComboBox = new QComboBox(currentImageGroupbox);
        effectsComboBox->setObjectName(QStringLiteral("effectsComboBox"));
        effectsComboBox->setGeometry(QRect(160, 320, 151, 22));
        effectsComboBox->setMaxCount(1024);
        groupBox = new QGroupBox(currentImageGroupbox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 350, 361, 131));
        ATLsComboBox5 = new QComboBox(groupBox);
        ATLsComboBox5->setObjectName(QStringLiteral("ATLsComboBox5"));
        ATLsComboBox5->setGeometry(QRect(10, 80, 101, 22));
        ATLsComboBox5->setMaxCount(1024);
        ATLsComboBox1 = new QComboBox(groupBox);
        ATLsComboBox1->setObjectName(QStringLiteral("ATLsComboBox1"));
        ATLsComboBox1->setGeometry(QRect(10, 20, 101, 22));
        ATLsComboBox1->setMaxCount(1024);
        ATLsComboBox3 = new QComboBox(groupBox);
        ATLsComboBox3->setObjectName(QStringLiteral("ATLsComboBox3"));
        ATLsComboBox3->setGeometry(QRect(10, 50, 101, 22));
        ATLsComboBox3->setMaxCount(1024);
        ATLEdit1 = new QLineEdit(groupBox);
        ATLEdit1->setObjectName(QStringLiteral("ATLEdit1"));
        ATLEdit1->setEnabled(true);
        ATLEdit1->setGeometry(QRect(120, 20, 51, 21));
        ATLEdit3 = new QLineEdit(groupBox);
        ATLEdit3->setObjectName(QStringLiteral("ATLEdit3"));
        ATLEdit3->setEnabled(true);
        ATLEdit3->setGeometry(QRect(120, 50, 51, 21));
        ATLEdit5 = new QLineEdit(groupBox);
        ATLEdit5->setObjectName(QStringLiteral("ATLEdit5"));
        ATLEdit5->setEnabled(true);
        ATLEdit5->setGeometry(QRect(120, 80, 51, 21));
        ATLEdit6 = new QLineEdit(groupBox);
        ATLEdit6->setObjectName(QStringLiteral("ATLEdit6"));
        ATLEdit6->setEnabled(true);
        ATLEdit6->setGeometry(QRect(300, 80, 51, 21));
        ATLsComboBox6 = new QComboBox(groupBox);
        ATLsComboBox6->setObjectName(QStringLiteral("ATLsComboBox6"));
        ATLsComboBox6->setGeometry(QRect(190, 80, 101, 22));
        ATLsComboBox6->setMaxCount(1024);
        ATLEdit2 = new QLineEdit(groupBox);
        ATLEdit2->setObjectName(QStringLiteral("ATLEdit2"));
        ATLEdit2->setEnabled(true);
        ATLEdit2->setGeometry(QRect(300, 20, 51, 21));
        ATLsComboBox2 = new QComboBox(groupBox);
        ATLsComboBox2->setObjectName(QStringLiteral("ATLsComboBox2"));
        ATLsComboBox2->setGeometry(QRect(190, 20, 101, 22));
        ATLsComboBox2->setMaxCount(1024);
        ATLsComboBox4 = new QComboBox(groupBox);
        ATLsComboBox4->setObjectName(QStringLiteral("ATLsComboBox4"));
        ATLsComboBox4->setGeometry(QRect(190, 50, 101, 22));
        ATLsComboBox4->setMaxCount(1024);
        ATLEdit4 = new QLineEdit(groupBox);
        ATLEdit4->setObjectName(QStringLiteral("ATLEdit4"));
        ATLEdit4->setEnabled(true);
        ATLEdit4->setGeometry(QRect(300, 50, 51, 21));
        ALTLoopChkBox = new QCheckBox(groupBox);
        ALTLoopChkBox->setObjectName(QStringLiteral("ALTLoopChkBox"));
        ALTLoopChkBox->setGeometry(QRect(140, 110, 91, 19));
        groupBox->raise();
        imageRefLabel->raise();
        imageRefLineEdit->raise();
        groupBox_3->raise();
        groupBox_4->raise();
        label_2->raise();
        behindCharactersLineEdit->raise();
        label_7->raise();
        label_8->raise();
        applyImageChange->raise();
        textEdit->raise();
        splitter->raise();
        xScaleLineEdit->raise();
        label_5->raise();
        addScaledImageButton->raise();
        label->raise();
        effectsComboBox->raise();
        currentImageGroupbox->raise();
        imageListGroupbox->raise();

        retranslateUi(ImageManagerForm);

        QMetaObject::connectSlotsByName(ImageManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ImageManagerForm)
    {
        ImageManagerForm->setWindowTitle(QApplication::translate("ImageManagerForm", "Form", 0));
        imageListGroupbox->setTitle(QApplication::translate("ImageManagerForm", "Avalible Images", 0));
        addAnotherImageButton->setText(QApplication::translate("ImageManagerForm", "Add More Images", 0));
        setBackgroundButton->setText(QApplication::translate("ImageManagerForm", "Set As Background", 0));
        currentImageGroupbox->setTitle(QApplication::translate("ImageManagerForm", "Show Image Settings", 0));
        imageRefLabel->setText(QApplication::translate("ImageManagerForm", "ID", 0));
        groupBox_3->setTitle(QApplication::translate("ImageManagerForm", "Image Position", 0));
        radioButtonL->setText(QApplication::translate("ImageManagerForm", "Left", 0));
        radioButtonM->setText(QApplication::translate("ImageManagerForm", "Middle", 0));
        radioButtonR->setText(QApplication::translate("ImageManagerForm", "Right", 0));
        groupBox_4->setTitle(QApplication::translate("ImageManagerForm", "Position", 0));
        label_3->setText(QApplication::translate("ImageManagerForm", "xPos", 0));
        label_4->setText(QApplication::translate("ImageManagerForm", "yPos", 0));
        label_2->setText(QApplication::translate("ImageManagerForm", "Or Specific your Position:", 0));
#ifndef QT_NO_WHATSTHIS
        behindCharactersLineEdit->setWhatsThis(QApplication::translate("ImageManagerForm", "name list sperate by ','", 0));
#endif // QT_NO_WHATSTHIS
        behindCharactersLineEdit->setText(QString());
        label_7->setText(QApplication::translate("ImageManagerForm", "Behind:", 0));
        label_8->setText(QApplication::translate("ImageManagerForm", "(Image behind this characters)", 0));
        applyImageChange->setText(QApplication::translate("ImageManagerForm", "&Add Step", 0));
        applyImageChange->setShortcut(QApplication::translate("ImageManagerForm", "Ctrl+A", 0));
        changeImageRefButton->setText(QApplication::translate("ImageManagerForm", "Rename", 0));
        removeSelectedImageButton->setText(QApplication::translate("ImageManagerForm", "&Delete", 0));
        ckbHide->setText(QApplication::translate("ImageManagerForm", "Hide", 0));
        xScaleLineEdit->setText(QApplication::translate("ImageManagerForm", "1", 0));
        label_5->setText(QApplication::translate("ImageManagerForm", "xScale:", 0));
        addScaledImageButton->setText(QApplication::translate("ImageManagerForm", "AddScaled", 0));
        label->setText(QApplication::translate("ImageManagerForm", "Transitions:", 0));
        effectsComboBox->setCurrentText(QString());
        groupBox->setTitle(QApplication::translate("ImageManagerForm", "ATL", 0));
        ATLsComboBox5->setCurrentText(QString());
        ATLsComboBox1->setCurrentText(QString());
        ATLsComboBox3->setCurrentText(QString());
        ATLsComboBox6->setCurrentText(QString());
        ATLsComboBox2->setCurrentText(QString());
        ATLsComboBox4->setCurrentText(QString());
        ALTLoopChkBox->setText(QApplication::translate("ImageManagerForm", "Repeat", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageManagerForm: public Ui_ImageManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEMANAGER_H
