/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2012-2014  JanKusanagi JRR <jancoding@gmx.com>
 *             2014-2016  Ray             <ray.cn@gmail.com>
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

#include "choicemenueditor.h"

ChoiceMenuEditor::ChoiceMenuEditor(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Revised - " + tr("Add Choice Menu"));
    this->setWindowIcon(QIcon::fromTheme("view-choose"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    this->setMinimumWidth(450);


    choicesList = new QListWidget();

    choiceTextLineEdit = new QLineEdit();
    choiceTextLineEdit->setPlaceholderText(tr("Text shown for this option"));

    jumpToComboBox = new QComboBox();
    jumpToComboBox->addItems(QStringList() << "--" << "one_event" << "big_party" << "end_of_game");


    addChoiceButton = new QPushButton(QIcon::fromTheme("list-add"), tr("&Add this choice") + " >>");
    connect(addChoiceButton, SIGNAL(clicked()),
            this, SLOT(addChoiceToList()));

    removeChoiceButton = new QPushButton(QIcon::fromTheme("list-remove"), tr("&Remove selected"));
    connect(removeChoiceButton, SIGNAL(clicked()),
            this, SLOT(removeChoiceFromList()));


    finishButton = new QPushButton(QIcon::fromTheme("task-complete"),
                                   tr("&Finish"));
    connect(finishButton, SIGNAL(clicked()),
            this, SLOT(finishSettingUpMenu()));

    cancelButton = new QPushButton(QIcon::fromTheme("dialog-cancel"),
                                   tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));

    closeAction = new QAction(this);
    closeAction->setShortcut(Qt::Key_Escape);
    connect(closeAction, SIGNAL(triggered()),
            this, SLOT(close()));
    this->addAction(closeAction);


    leftFormLayout = new QFormLayout();
    leftFormLayout->addRow(tr("&Option"),  choiceTextLineEdit);
    leftFormLayout->addRow(tr("&Jump to"), jumpToComboBox);
    leftFormLayout->addWidget(addChoiceButton);

    rightFormLayout = new QFormLayout();
    rightFormLayout->addRow(tr("C&hoices"), choicesList);
    rightFormLayout->addWidget(removeChoiceButton);

    topLayout = new QHBoxLayout();
    topLayout->addLayout(leftFormLayout);
    topLayout->addSpacing(32);
    topLayout->addLayout(rightFormLayout);


    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(finishButton);
    buttonsLayout->addWidget(cancelButton);


    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(32);
    mainLayout->addLayout(buttonsLayout);

    this->setLayout(mainLayout);

    qDebug() << "ChoiceMenuEditor created";
}

ChoiceMenuEditor::~ChoiceMenuEditor() 
{
    delete(choicesList);
    delete(choiceTextLineEdit);
    delete(jumpToComboBox);
    delete(addChoiceButton);
    delete(removeChoiceButton);
    delete(finishButton);
    delete(cancelButton);
    delete(closeAction);
    delete(leftFormLayout);
    delete(rightFormLayout);
    delete(topLayout);
    delete(buttonsLayout);
    delete(mainLayout);


}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////// SLOTS //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



void ChoiceMenuEditor::showForNewMenu()
{
    this->choiceTextLineEdit->clear();
    this->jumpToComboBox->setCurrentIndex(0);
    this->choicesList->clear();

    this->show();

    qDebug() << "ChoiceMenuEditor shown empty for new menu";
}




void ChoiceMenuEditor::addChoiceToList()
{
    // Check option has text and a valid label for the jump is selected
    if (!choiceTextLineEdit->text().isEmpty() && jumpToComboBox->currentIndex() != 0)
    {
        choicesList->addItem(this->choiceTextLineEdit->text() + " ---> " + this->jumpToComboBox->currentText());


        jumpToComboBox->setCurrentIndex(0); // Back to "--"
        choiceTextLineEdit->clear();
        choiceTextLineEdit->setFocus();
    }
}



void ChoiceMenuEditor::removeChoiceFromList()
{
    qDebug() << "choicesList->currentRow() " << choicesList->currentRow();

    if (choicesList->currentRow() != -1)  // only if row is valid
    {
        choicesList->takeItem(choicesList->currentRow());
    }
}




void ChoiceMenuEditor::finishSettingUpMenu()
{
    if (choicesList->count() < 1)
    {
        // No options added, warn  -- TMP/FIXME, QMessageBox for now...
        QMessageBox::critical(this, tr("Error: No choices"),
                                    tr("There are no choices in the menu.\nYou need at least one."));
    }
    else
    {
        //emit something()...



        this->close();
    }

}
