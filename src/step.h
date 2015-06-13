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

#ifndef STEP_H
#define STEP_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTreeWidgetItem>

#include <QDebug>



enum StepType { labelStep,
                menuStep,
                jumpStep,
                returnStep,

                dialogStep,

                sceneStep,
                showStep,

                playMusicStep,
                stopMusicStep,

                playSoundStep,
                stopSoundStep,

                playVoiceStep,
                stopVoiceStep,
				
				imageDefine,
				characterDefine,

                unknownStep
              };


class Step : public QObject
{
    Q_OBJECT

public:
	explicit Step(QString line,
		QTreeWidgetItem *treeItem,
		QStringList characterAliases,
		QObject *parent = 0) ;
    ~Step();


    QString getScriptLine();
    StepType getStepType();
    QStringList getStepParameters();
	//QTreeWidgetItem *sceneItem;

signals:
    
public slots:



private:
    QString scriptLine;

    StepType type;
    QStringList parameters;
    
};

class treenode{
public:
	QTreeWidgetItem *parent;
	int nthInParent;
	Step *step;
	//int stepNum;
	treenode(QTreeWidgetItem *p, int th, Step *st) :parent(p), nthInParent(th), step(st){};
	treenode():parent(nullptr),nthInParent(0),step(0){};
};
Q_DECLARE_METATYPE(treenode);
Q_DECLARE_METATYPE(treenode*);
#endif // STEP_H
