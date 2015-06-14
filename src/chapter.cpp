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

#include "chapter.h"

Chapter::Chapter(QString scriptFilename,
                 QTreeWidgetItem *treeItem,
                 CharacterManager *mwCharacterManager,
                 QObject *parent) : QObject(parent)
{
    this->filename = scriptFilename;
    this->item = treeItem;
    this->characterManager = mwCharacterManager;

    QStringList characterAliases = characterManager->getAllAliases();

    QFile scriptFile(filename);
    scriptFile.open(QIODevice::ReadOnly);

    QString scriptLine;
	Step *pstep;
	pstep->init_step();
    while (!scriptFile.atEnd())
    {
        scriptLine = scriptFile.readLine();


        // If line is not empty, and not a comment
		if (!scriptLine.trimmed().startsWith("#") && !scriptLine.trimmed().isEmpty())
        {
            // TODO: if line starts with "menu" or "label", read the rest of the block
			pstep = new Step(scriptLine, this->item, characterAliases, this);
			addStep(pstep);
        }

    }
    scriptFile.close();


    qDebug() << "Chapter created from" << filename;
}


Chapter::~Chapter()
{
    qDebug() << "Chapter destroyed";
}





void Chapter::addStep(Step *step)
{
    this->steps.append(step);
    //qDebug() << "Chapter::addStep() steps =" << steps.length();
}


void Chapter::removeCurrentStep()
{
    qDebug() << "Removing current step";

    /// FIXME, last for now
    this->steps.removeLast();
    // remove also from Qtreewidget

    qDebug() << "steps left:" << this->steps.size();
}



Step* Chapter::getStep(int stepNumber)
{
    return this->steps[stepNumber];
}



QList<Step *> Chapter::getAllSteps()
{
    return this->steps;
}


QString Chapter::getStepLine(int stepNumber)
{
    qDebug() << "Chapter: Getting line for step " << stepNumber;
    return this->steps[stepNumber]->getScriptLine();
}


int Chapter::getNumberOfSteps()
{
    return this->steps.size();
}



QString Chapter::getScriptFilename()
{
    return this->filename;
}



QTreeWidgetItem* Chapter::getTreeItem()
{
    return this->item;
}
