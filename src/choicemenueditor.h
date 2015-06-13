/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2012-2015  JanKusanagi JRR <jancoding@gmx.com>
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

#ifndef CHOICEMENUEDITOR_H
#define CHOICEMENUEDITOR_H


#include <QWidget>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QAction>
#include <QListWidget>

#include <QMessageBox>

#include <QDebug>

class ChoiceMenuEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ChoiceMenuEditor(QWidget *parent = 0);
    
signals:
    
public slots:
    void showForNewMenu();

    void addChoiceToList();
    void removeChoiceFromList();

    void finishSettingUpMenu();


private:
    QVBoxLayout *mainLayout;
    QFormLayout *leftFormLayout;
    QFormLayout *rightFormLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *buttonsLayout;


    QLineEdit *choiceTextLineEdit;
    QComboBox *jumpToComboBox;
    QPushButton *addChoiceButton;

    QListWidget *choicesList;
    QPushButton *removeChoiceButton;

    QPushButton *finishButton;
    QPushButton *cancelButton;

    QAction *closeAction;
};

#endif // CHOICEMENUEDITOR_H
