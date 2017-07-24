/********************************************************************************
** Form generated from reading UI file 'choicemenueditorform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEMENUEDITORFORM_H
#define UI_CHOICEMENUEDITORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChoiceMenuEditorForm
{
public:
    QLineEdit *lineEditMenuItem;
    QCheckBox *checkBoxJump;
    QCheckBox *checkBoxSetVar;
    QLabel *label;
    QLineEdit *lineEditJumpTo;
    QLineEdit *lineEditVarSet;
    QPushButton *pushButtonAddOption;
    QPushButton *pushButtonDelOption;
    QPushButton *pushButtonFinished;
    QPushButton *pushButtonCancel;
    QListWidget *listWidgetChoices;
    QLineEdit *lineEditDialog;
    QCheckBox *checkBoxDialog;

    void setupUi(QWidget *ChoiceMenuEditorForm)
    {
        if (ChoiceMenuEditorForm->objectName().isEmpty())
            ChoiceMenuEditorForm->setObjectName(QStringLiteral("ChoiceMenuEditorForm"));
        ChoiceMenuEditorForm->resize(645, 429);
        lineEditMenuItem = new QLineEdit(ChoiceMenuEditorForm);
        lineEditMenuItem->setObjectName(QStringLiteral("lineEditMenuItem"));
        lineEditMenuItem->setGeometry(QRect(150, 40, 181, 21));
        checkBoxJump = new QCheckBox(ChoiceMenuEditorForm);
        checkBoxJump->setObjectName(QStringLiteral("checkBoxJump"));
        checkBoxJump->setGeometry(QRect(20, 100, 91, 19));
        checkBoxSetVar = new QCheckBox(ChoiceMenuEditorForm);
        checkBoxSetVar->setObjectName(QStringLiteral("checkBoxSetVar"));
        checkBoxSetVar->setGeometry(QRect(20, 170, 131, 19));
        label = new QLabel(ChoiceMenuEditorForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 101, 16));
        lineEditJumpTo = new QLineEdit(ChoiceMenuEditorForm);
        lineEditJumpTo->setObjectName(QStringLiteral("lineEditJumpTo"));
        lineEditJumpTo->setGeometry(QRect(150, 100, 181, 21));
        lineEditVarSet = new QLineEdit(ChoiceMenuEditorForm);
        lineEditVarSet->setObjectName(QStringLiteral("lineEditVarSet"));
        lineEditVarSet->setGeometry(QRect(150, 170, 181, 21));
        pushButtonAddOption = new QPushButton(ChoiceMenuEditorForm);
        pushButtonAddOption->setObjectName(QStringLiteral("pushButtonAddOption"));
        pushButtonAddOption->setGeometry(QRect(60, 340, 271, 28));
        pushButtonDelOption = new QPushButton(ChoiceMenuEditorForm);
        pushButtonDelOption->setObjectName(QStringLiteral("pushButtonDelOption"));
        pushButtonDelOption->setGeometry(QRect(350, 340, 261, 28));
        pushButtonFinished = new QPushButton(ChoiceMenuEditorForm);
        pushButtonFinished->setObjectName(QStringLiteral("pushButtonFinished"));
        pushButtonFinished->setGeometry(QRect(60, 380, 271, 28));
        pushButtonCancel = new QPushButton(ChoiceMenuEditorForm);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(350, 380, 261, 28));
        listWidgetChoices = new QListWidget(ChoiceMenuEditorForm);
        listWidgetChoices->setObjectName(QStringLiteral("listWidgetChoices"));
        listWidgetChoices->setGeometry(QRect(370, 40, 256, 221));
        lineEditDialog = new QLineEdit(ChoiceMenuEditorForm);
        lineEditDialog->setObjectName(QStringLiteral("lineEditDialog"));
        lineEditDialog->setGeometry(QRect(150, 240, 181, 21));
        checkBoxDialog = new QCheckBox(ChoiceMenuEditorForm);
        checkBoxDialog->setObjectName(QStringLiteral("checkBoxDialog"));
        checkBoxDialog->setGeometry(QRect(20, 240, 131, 19));

        retranslateUi(ChoiceMenuEditorForm);

        QMetaObject::connectSlotsByName(ChoiceMenuEditorForm);
    } // setupUi

    void retranslateUi(QWidget *ChoiceMenuEditorForm)
    {
        ChoiceMenuEditorForm->setWindowTitle(QApplication::translate("ChoiceMenuEditorForm", "Form", Q_NULLPTR));
        lineEditMenuItem->setText(QString());
        checkBoxJump->setText(QApplication::translate("ChoiceMenuEditorForm", "JumpTo", Q_NULLPTR));
        checkBoxSetVar->setText(QApplication::translate("ChoiceMenuEditorForm", "Set Variable", Q_NULLPTR));
        label->setText(QApplication::translate("ChoiceMenuEditorForm", "Menu Item:", Q_NULLPTR));
        pushButtonAddOption->setText(QApplication::translate("ChoiceMenuEditorForm", "AddMenuItem>>", Q_NULLPTR));
        pushButtonDelOption->setText(QApplication::translate("ChoiceMenuEditorForm", "<<RemoveMenuItem", Q_NULLPTR));
        pushButtonFinished->setText(QApplication::translate("ChoiceMenuEditorForm", "Finished", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("ChoiceMenuEditorForm", "Cancel", Q_NULLPTR));
        lineEditDialog->setText(QString());
        checkBoxDialog->setText(QApplication::translate("ChoiceMenuEditorForm", "Add Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChoiceMenuEditorForm: public Ui_ChoiceMenuEditorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICEMENUEDITORFORM_H
