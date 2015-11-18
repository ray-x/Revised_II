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

#include "step.h"
#include"chapter.h"


Step::Step(QString line,
	QTreeWidgetItem *treeItem,
    QTreeWidgetItem *curSceneItem,
	QStringList characterAliases,
    QObject *parent) : QObject(parent)
{
    sceneItem = curSceneItem;
	this->scriptLine = line.trimmed();
	//QTreeWidgetItem *Step::sceneItem;
	QString treeItemText;
	QString copiedString;
	//static QTreeWidgetItem * sceneItem = nullptr;
	if (scriptLine.startsWith("#"))
	{
		type = comments;

		copiedString = scriptLine;
		parameters = QStringList() << copiedString.remove(0, 1);

        treeItemText = tr("# ") + parameters.join(" ");
	}else 	if (scriptLine.startsWith("label"))
	{
		type = labelStep;

		copiedString = scriptLine;
		parameters = QStringList() << copiedString.remove(0, 6);

		treeItemText = tr("Label: ") + parameters.join(" ");
	}
	else if (scriptLine.startsWith("scene"))
	{
		type = sceneStep;
		
		copiedString = scriptLine;
		parameters = QStringList() << copiedString.remove(0, 6);

		treeItemText = tr("Scene Change: ") + parameters.join(" ");
	}
	else if (scriptLine.startsWith("show"))
	{
		type = showStep;

		copiedString = scriptLine;
		parameters = copiedString.remove(0, 5).split(" at ");

		treeItemText = tr("Image: ") + parameters.join(" @");

		qDebug() << "PARAMETERS:" << parameters;
	}
	else if (scriptLine.startsWith("menu"))
	{
		type = menuStep;

		parameters = QStringList();
		treeItemText = tr("Menu: ");

		// Read more lines until the whole menu block is done

	}
	else if (scriptLine.startsWith("jump"))
	{
		type = jumpStep;

		parameters = QStringList();
		treeItemText = "Jump to " + parameters.join(" ");
	}
	else if (scriptLine.startsWith("return"))
	{
		type = returnStep;

		parameters = QStringList();
		treeItemText = tr("Return");

	}
	else if (scriptLine.startsWith("play music"))
	{
		type = playMusicStep;

		parameters = QStringList();
		treeItemText = tr("Play Music");
	}
	else if (scriptLine.startsWith("stop music"))
	{
		type = stopMusicStep;

		parameters = QStringList();
		treeItemText = tr("Stop Music");
	}
	else if (scriptLine.startsWith("play sound"))
	{
		type = playSoundStep;

		parameters = QStringList();
		treeItemText = tr("Play Sound");
	}
	else if (scriptLine.startsWith("stop sound"))
	{
		type = stopSoundStep;

		parameters = QStringList();
		treeItemText = tr("Stop Sound");
	}
	else if (scriptLine.startsWith("image"))
	{
		qDebug() << "Step() script line ends in quotes:" << scriptLine;
		type = imageDefine;
		treeItemText = tr("imageDefine");
	}else if (scriptLine.startsWith("define"))
	{
		qDebug() << "Step() script line ends in quotes:" << scriptLine;
		type = characterDefine;
		treeItemText = tr("characterDefine");
	}    else// Here go the commands that don't have a specific start, like dialog
    {        // If the line ends with ", it can be dialog
        // or a command like: play "song.ogg"
        if (scriptLine.endsWith("\""))
        {
            qDebug() << "Step() script line ends in quotes:" << scriptLine;

            bool aliasFound = false;
            QString alias = "";
            QString copiedString;

            foreach (QString possibleAlias, characterAliases)
            {
                if (scriptLine.startsWith(possibleAlias))
                {
                    aliasFound = true; // line starts with an alias
                    alias = possibleAlias;

                    // remove the found alias from the line
                    copiedString = scriptLine.trimmed();
                    copiedString.remove(0, alias.length());
                    qDebug() << copiedString;

                    break;
                }
            }


            if (aliasFound || scriptLine.startsWith("\""))
            {
                type = dialogStep;

                // If no alias found (narrator sentence), copiedString is empty
                if (copiedString.isEmpty())
                {
                    copiedString = scriptLine;
                }
                copiedString = copiedString.trimmed();
                copiedString.remove(0, 1);  // first "
                copiedString.remove(-1, 1); // last "
                parameters = QStringList() << alias << copiedString;

                if (alias.isEmpty()) // Narrator
                {
                    treeItemText = tr("Narration: ") + parameters.join("");
                }
                else  // Some character
                {
                    treeItemText = tr("Dialog: ") + "(" + parameters.join(") ");
                }


                qDebug() << "PARAMETERS:" << parameters;
            } else  // nothing known
            {
                treeItemText = tr("Unknown");

                type = unknownStep;
                parameters = QStringList();
            }
        }


        else   // definitely, nothing known
        {
            treeItemText = "Unknown";

            type = unknownStep;
            parameters = QStringList();
        }

    }

    qDebug() << "step creation..... ";
	QTreeWidgetItem *childItem;
	treenode *treeNode;
	QVariant data;
	Chapter *chp = dynamic_cast<Chapter*>(parent);

    if (treeItemText.startsWith("Scene") || sceneItem==nullptr)
	{
		sceneItem = new QTreeWidgetItem(treeItem, QStringList(treeItemText));
		treeNode = new treenode(treeItem, treeItem->childCount(), this,chp->getNumberOfSteps(), sceneItem->childCount());

		data.setValue(treeNode);
		sceneItem->setData(0, Qt::UserRole, data);
		//decode: treenode vnode = v.value<treenode>();
        
		treeItem->addChild(sceneItem);
        selfTreeItem = sceneItem;
		qDebug() << "append to top" << QString("Step created from script line:  %1\n").arg(scriptLine) << endl;;
	}
	else{
		childItem = new QTreeWidgetItem(QStringList(treeItemText));
		if (sceneItem != nullptr){
            treeNode = new treenode(sceneItem, sceneItem->childCount(), this, chp->getNumberOfSteps(), sceneItem->childCount());
			data.setValue(treeNode);
			childItem->setData(0, Qt::UserRole, data);
			sceneItem->addChild(childItem);
            //sceneItem->insertChild(curre  ,childItem);
			qDebug() << "append to sceneItem" << QString("Step created from script line:  %1\n").arg(scriptLine);
		}
        selfTreeItem = childItem;
        sceneItem = curSceneItem;
	}
}

#if 1

//TODO merge some of the code with step::step
Step::Step(QString line, QTreeWidgetItem *treeItemScene, Step *selStep, QStringList characterAliases, QObject *parent) : QObject(parent)
{
    QString linesave = line;
    scriptLine = line.trimmed();
    //QTreeWidgetItem *Step::sceneItem;
    QString treeItemText;
    QString copiedString;
    //static QTreeWidgetItem * sceneItem = nullptr;
    if (scriptLine.startsWith("#"))
    {
        type = comments;

        copiedString = scriptLine;
        parameters = QStringList() << copiedString.remove(0, 1);

        treeItemText = tr("# ") + parameters.join(" ");
    }
    else 	if (scriptLine.startsWith("label"))
    {
        type = labelStep;

        copiedString = scriptLine;
        parameters = QStringList() << copiedString.remove(0, 6);

        treeItemText = tr("Label: ") + parameters.join(" ");
    }
    else if (scriptLine.startsWith("scene"))
    {
        type = sceneStep;

        copiedString = scriptLine;
        parameters = QStringList() << copiedString.remove(0, 6);

        treeItemText = tr("Scene Change: ") + parameters.join(" ");
    }
    else if (scriptLine.startsWith("show"))
    {
        type = showStep;

        copiedString = scriptLine;
        parameters = copiedString.remove(0, 5).split(" at ");

        treeItemText = tr("Image: ") + parameters.join(" @");

        qDebug() << "PARAMETERS:" << parameters;
    }
    else if (scriptLine.startsWith("menu"))
    {
        type = menuStep;

        parameters = QStringList();
        treeItemText = tr("Menu: ");

        // Read more lines until the whole menu block is done

    }
    else if (scriptLine.startsWith("jump"))
    {
        type = jumpStep;

        parameters = QStringList();
        treeItemText = "Jump to " + parameters.join(" ");
    }
    else if (scriptLine.startsWith("return"))
    {
        type = returnStep;

        parameters = QStringList();
        treeItemText = tr("Return");

    }
    else if (scriptLine.startsWith("play music"))
    {
        type = playMusicStep;

        parameters = QStringList();
        treeItemText = tr("Play Music");
    }
    else if (scriptLine.startsWith("stop music"))
    {
        type = stopMusicStep;

        parameters = QStringList();
        treeItemText = tr("Stop Music");
    }
    else if (scriptLine.startsWith("play sound"))
    {
        type = playSoundStep;

        parameters = QStringList();
        treeItemText = tr("Play Sound");
    }
    else if (scriptLine.startsWith("stop sound"))
    {
        type = stopSoundStep;

        parameters = QStringList();
        treeItemText = tr("Stop Sound");
    }
    else if (scriptLine.startsWith("image"))
    {
        qDebug() << "Step() script line ends in quotes:" << scriptLine;
        type = imageDefine;
        treeItemText = tr("imageDefine");
    }
    else if (scriptLine.startsWith("define"))
    {
        qDebug() << "Step() script line ends in quotes:" << scriptLine;
        type = characterDefine;
        treeItemText = tr("characterDefine");
    }
    else// Here go the commands that don't have a specific start, like dialog
    {
        // If the line ends with ", it can be dialog
        // or a command like: play "song.ogg"
        if (scriptLine.endsWith("\""))
        {
            qDebug() << "Step() script line ends in quotes:" << scriptLine;

            bool aliasFound = false;
            QString alias = "";
            QString copiedString;

            foreach(QString possibleAlias, characterAliases)
            {
                if (scriptLine.startsWith(possibleAlias))
                {
                    aliasFound = true; // line starts with an alias
                    alias = possibleAlias;

                    // remove the found alias from the line
                    copiedString = scriptLine.trimmed();
                    copiedString.remove(0, alias.length());
                    qDebug() << copiedString;

                    break;
                }
            }


            if (aliasFound || scriptLine.startsWith("\""))
            {
                type = dialogStep;

                // If no alias found (narrator sentence), copiedString is empty
                if (copiedString.isEmpty())
                {
                    copiedString = scriptLine;
                }
                copiedString = copiedString.trimmed();
                copiedString.remove(0, 1);  // first "
                copiedString.remove(-1, 1); // last "
                parameters = QStringList() << alias << copiedString;

                if (alias.isEmpty()) // Narrator
                {
                    treeItemText = tr("Narration: ") + parameters.join("");
                }
                else  // Some character
                {
                    treeItemText = tr("Dialog: ") + "(" + parameters.join(") ");
                }


                qDebug() << "PARAMETERS:" << parameters;
            }
            else  // nothing known
            {
                treeItemText = tr("Unknown");

                type = unknownStep;
                parameters = QStringList();
            }
        }
        else   // definitely, nothing known
        {
            treeItemText = "Unknown";

            type = unknownStep;
            parameters = QStringList();
        }

    }
    qDebug() << "step creation..... ";


    QTreeWidgetItem *childItem;
    treenode *treeNode;
    QVariant data;
    Chapter *chp = dynamic_cast<Chapter*>(parent);
    QString q = selStep->getScriptLine();
    QTreeWidgetItem * node = selStep->selfTreeItem;


    QVariant  v = node->data(0, Qt::UserRole);
    treenode *vnode = v.value<treenode*>();
    int currentStep = vnode->stepNum;
    int iSceneStep = vnode->stepNumInScene;
    sceneItem = node->parent();

    if (treeItemText.startsWith("Scene"))
    {
        // treenode(QTreeWidgetItem *p, int th, Step* s, int sp, int sp2 = 0) 
        sceneItem = new QTreeWidgetItem(treeItemScene, QStringList(treeItemText));
        treeNode = new treenode(sceneItem, sceneItem->childCount(), this, chp->getNumberOfSteps());

        data.setValue(treeNode);
        sceneItem->setData(0, Qt::UserRole, data);
        //decode: treenode vnode = v.value<treenode>();

        treeItemScene->addChild(sceneItem);
        selfTreeItem = sceneItem;
        qDebug() << "append to top" << QString("Step created from script line:  %1\n").arg(scriptLine) << endl;;
    }
    else{ 
        //treenode(QTreeWidgetItem *p, int th, Step* s, int sp, int sp2 = 0)
        childItem = new QTreeWidgetItem(QStringList(treeItemText));
        if (sceneItem != nullptr){
            treeNode = new treenode(sceneItem, sceneItem->childCount(), this, chp->getNumberOfSteps(), iSceneStep);
            data.setValue(treeNode);
            childItem->setData(0, Qt::UserRole, data);
            //sceneItem->addChild(childItem);
            sceneItem->insertChild(iSceneStep, childItem);
            qDebug() << "append to sceneItem" << QString("Step created from script line:  %1\n").arg(scriptLine);
        }
        //TODO add more steps and need to update all the stepnumbers
        selfTreeItem = childItem;
    }    
    scriptLine = linesave;

}


#endif




Step::~Step()
{
    qDebug() << "Step destroyed";
}





QString Step::getScriptLine()
{
    return this->scriptLine;
}



StepType Step::getStepType()
{
    return this->type;
}


QStringList Step::getStepParameters()
{
    return this->parameters;
}
//QTreeWidgetItem *Step::sceneItem = nullptr;