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

#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QTreeWidgetItem>

#include <QDebug>

#include "step.h"
#include "charactermanager.h"

class Chapter : public QObject
{
    Q_OBJECT

public:
    explicit Chapter(QString scriptFilename,
                     QTreeWidgetItem *treeItem,
                     CharacterManager *mwCharacterManager,
                     QObject *parent = 0);
    ~Chapter();

    void addStep(Step *step);
    void removeCurrentStep();

    Step *getStep(int stepNumber);
	Step *getNextStep();
	Step *getPrevStep();
	//Step *currentStep();
	Step *setCurrentStep(int stepNumber);
    QList<Step *> getAllSteps();
    QString getStepLine(int stepNumber);
    int getNumberOfSteps();

    QString getScriptFilename();

    QTreeWidgetItem* getTreeItem();
	int currentStep;

signals:
    
public slots:


private:
    QString filename;
    QTreeWidgetItem *item;
    CharacterManager *characterManager;


    QList<Step *> steps;

};

#endif // CHAPTER_H
