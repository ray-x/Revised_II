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

#include "choicemenueditorform.h"
#include "ui_choicemenueditorform.h"
#include <algorithm>
ChoiceMenuEditorForm::ChoiceMenuEditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoiceMenuEditorForm)
{
    ui->setupUi(this);
    connect(ui->pushButtonAddOption, SIGNAL(clicked()), this, SLOT(AddMenuItem()));
    connect(ui->pushButtonDelOption, SIGNAL(clicked()), this, SLOT(RemoveMenuItem()));
    connect(ui->pushButtonFinished, SIGNAL(clicked()), this, SLOT(Finished()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(Cancel()));

    MenuItems.push_back("menu:");
    ui->listWidgetChoices->setWordWrap(true);
    items.clear();
}

ChoiceMenuEditorForm::~ChoiceMenuEditorForm()
{
    delete ui;
}
void ChoiceMenuEditorForm::AddMenuItem()
{
    QString locs;
    int i,j;
    if (!ui->lineEditMenuItem->text().isEmpty() )
    {   
        i = MenuItems.length()-1;
        MenuItems.push_back(QString("    \"%1\":").arg(ui->lineEditMenuItem->text()));
        if (ui->checkBoxJump->isChecked() && !ui->lineEditJumpTo->text().isEmpty())
        {
            MenuItems.push_back(QString("        jump %1").arg(ui->lineEditJumpTo->text()));
            locs.push_back(QString("[%1]->%2\n").arg(ui->lineEditMenuItem->text()).arg(ui->lineEditJumpTo->text()));
        }
        if (ui->checkBoxSetVar->isChecked() && !ui->lineEditVarSet->text().isEmpty())
        {
            MenuItems.push_back(QString("        %1").arg(ui->lineEditVarSet->text()));
            if (locs.isEmpty())
                locs.push_back(QString("[%1]->").arg(ui->lineEditMenuItem->text()));
            locs.push_back(QString("\t%1\n").arg(ui->lineEditVarSet->text()));
        }

        if (ui->checkBoxDialog->isChecked() && !ui->lineEditDialog->text().isEmpty())
        {
            if (locs.isEmpty())
                locs.push_back(QString("[%1]->").arg(ui->lineEditMenuItem->text()));
            MenuItems.push_back(QString("        %1").arg(ui->lineEditDialog->text()));
            locs.push_back(QString("\t%1\n").arg(ui->lineEditDialog->text()));
        }
            
      //      ui->listWidgetChoices->addItem(ui->lineEditMenuItem->text() + " ---> ");
        ui->listWidgetChoices->addItem(locs);
        j = MenuItems.length() - 1;
        items.push_back(std::make_pair(i, j));
       // jumpToComboBox->setCurrentIndex(0); // Back to "--"
      //  choiceTextLineEdit->clear();
       // choiceTextLineEdit->setFocus();
    }
    // jumpToComboBox->setCurrentIndex(0); // Back to "--"
    ui->lineEditJumpTo->clear();
    ui->lineEditVarSet->clear();
    ui->lineEditDialog->clear();
    ui->lineEditMenuItem->clear();
    ui->checkBoxJump->setCheckState(Qt::Unchecked);
    ui->checkBoxSetVar->setCheckState(Qt::Unchecked);
    ui->checkBoxDialog->setCheckState(Qt::Unchecked);
    // choiceTextLineEdit->setFocus();
}


void ChoiceMenuEditorForm::RemoveMenuItem()
{
    if (ui->listWidgetChoices->currentRow() != -1)  // only if row is valid
    {
        ui->listWidgetChoices->takeItem(ui->listWidgetChoices->currentRow());
    }
    
    std::pair<int, int> p = items[ui->listWidgetChoices->currentRow()];
    auto it = MenuItems.begin()+p.first;
    auto end = MenuItems.begin() + p.second;
    for (int i = p.first; i <= p.second; i++)
        MenuItems.removeAt(i);

}
void ChoiceMenuEditorForm::Finished()
{
    ui->listWidgetChoices->reset();
    items.clear();
    emit sigInsertMenuStep(MenuItems);
    MenuItems.clear();
    close();
}

void ChoiceMenuEditorForm::Cancel()
{
    ui->listWidgetChoices->reset();
    MenuItems.clear();
    close();
}