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

#ifndef CHAPTERLIST_H
#define CHAPTERLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStringList>
#include <QList>
#include <QPushButton>
#include <QAction>

#include <QDebug>

#include "chapter.h"

class ChapterList : public QWidget
{
    Q_OBJECT

public:
    explicit ChapterList(CharacterManager *mwCharacterManager,
                         QWidget *parent = 0);
    ~ChapterList();

    void clearContents();
    
signals:
    void chapterChanged(Chapter *chapter);
    void stepRenderRequest(Step *step);

    
public slots:
    void setContents(QString path,
                     QStringList fileList);
    void saveContentsToRpyFile();

    void loadChapter(QTreeWidgetItem *item, int column);


    void addChapter();
    void removeChapter();


private:
    QVBoxLayout *mainLayout;
    QTreeWidget *treeWidget;

    QPushButton *addChapterButton;
    QPushButton *removeChapterButton;

    QPushButton *removeStepButton;


    CharacterManager *characterManager;
    QString projectPath;
    QList<Chapter *> chapters;
    int currentChapter;
};

#endif // CHAPTERLIST_H
