/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2012-2015  JanKusanagi JRR <jancoding@gmx.com>
 *             2014-2015  Ray             <ray.cn@gmail.com> 
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
#include <QTreeWidget>
#include <QDebug>



enum StepType { comments,
                labelStep,
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
		QTreeWidgetItem *treeParItem,
        QTreeWidgetItem *treeSceneItem,
		QStringList characterAliases,
		QObject *parent) ;

    explicit Step(QString line, QTreeWidgetItem *currSceneItem, Step *step, QStringList characterAliases, QObject *parent);
    ~Step();

	//void init_step(){ sceneItem = nullptr; };
    QString getScriptLine();
    StepType getStepType();
    QStringList getStepParameters();
	QTreeWidgetItem *sceneItem; //father
    QTreeWidgetItem *selfTreeItem;
signals:
    
public slots:



private:
    QString scriptLine;

    StepType type;
    QStringList parameters;
	//QTreeWidgetItem * sceneItem = nullptr;
};

class treenode{
public:
	QTreeWidgetItem *parent;
    QTreeWidgetItem *currentItem;
	int nthInParent;
	Step *step;
	int stepNum;
    int stepNumInScene;
    treenode(QTreeWidgetItem *p, int th, Step* s, int sp, int sp2 = 0) :parent(p), nthInParent(th), step(s), stepNum(sp), stepNumInScene(sp2){};
	treenode():parent(nullptr),nthInParent(0),step(0){};
};


//QTreeWidgetItem *Step::sceneItem;
//
//Student* Student::m_head = NULL;
Q_DECLARE_METATYPE(treenode);
Q_DECLARE_METATYPE(treenode*);
#endif // STEP_H
