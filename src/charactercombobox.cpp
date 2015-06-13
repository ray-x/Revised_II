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

#include "charactercombobox.h"

CharacterComboBox::CharacterComboBox(QWidget *parent) : QComboBox(parent)
{
    populating = false;

    connect(this, SIGNAL(currentIndexChanged(int)),
            this, SLOT(checkSelectedOption(int)));


    qDebug() << "CharacterComboBox created";
}


CharacterComboBox::~CharacterComboBox()
{
    qDebug() << "CharacterComboBox destroyed";
}




/////////////////////////////// SLOTS ////////////////////////////////




void CharacterComboBox::populate(QStringList namesList,
                                 QStringList aliasList,
                                 QStringList colorsList)
{
    populating = true;

    this->clear();


    this->addItem("-" + tr("Narrator") + "-");
    this->insertSeparator(1);

    for (int counter = 0; counter < namesList.size(); ++counter)
    {
        // Add an item with the nice name as text
        // and the alias as item's user data
        QStringList aliasAndColors;
        aliasAndColors.append(aliasList.at(counter));
        aliasAndColors.append(colorsList.at(counter));

        this->addItem(namesList.at(counter),  // visible text
                      aliasAndColors);        // invisible user data

        // FIXME: some error control missing
    }

    this->insertSeparator(this->count());
    this->addItem("-" + tr("Add New Character") + "-");



    populating = false;

    qDebug() << "CharacterComboBox populated with:" << namesList;
}





void CharacterComboBox::checkSelectedOption(int option)
{
    if (populating)
    {
        return;
    }

    qDebug() << "selected option" << option << "of" << this->count();


    // If the user selected the last option, "Add New Character"
    if (option+1 == this->count())
    {
        this->setCurrentIndex(0); // Take it back to "Narrator"

        emit characterManagerRequested();
    }
}
