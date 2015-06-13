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

#ifndef CHARACTERCOMBOBOX_H
#define CHARACTERCOMBOBOX_H

#include <QComboBox>
#include <QStringList>

#include <QDebug>


class CharacterComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit CharacterComboBox(QWidget *parent = 0);
    ~CharacterComboBox();


signals:
    void characterManagerRequested();


public slots:
    void populate(QStringList namesList = QStringList(),
                  QStringList aliasList = QStringList(),
                  QStringList colorsList = QStringList());
    void checkSelectedOption(int option);


private:
    bool populating;
};

#endif // CHARACTERCOMBOBOX_H
