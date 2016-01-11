/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2012-2015  JanKusanagi JRR <jancoding@gmx.com>
 *             2015-2015  Ray <RayX.cn@gmail.com>
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
#include <QTextCodec>
#include "chapterlist.h"
#include "step.h"
ChapterList::ChapterList(CharacterManager *mwCharacterManager,
    QWidget *parent) : QWidget(parent), currentItem(nullptr)
{
    this->characterManager = mwCharacterManager;

    // The list itself

    treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabels(QStringList(tr("Chapter List")));
    treeWidget->setColumnCount(1);
    treeWidget->setAnimated(true);
    treeWidget->setIndentation(8);
    treeWidget->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    //treeWidget->setRootIsDecorated(false);  // Nice, possible usability issues

    connect(treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
            this, SLOT(loadChapter(QTreeWidgetItem*,int)));
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem * , int )),
        this, SLOT(loadChapter(QTreeWidgetItem*, int)));

    treeWidget->setStatusTip(tr("List of chapters in your game, with their steps"));



    // The control buttons

    addChapterButton = new QPushButton(QIcon::fromTheme("list-add"),
                                       "&Add Chapter");
    connect(addChapterButton, SIGNAL(clicked()),
            this, SLOT(addChapter()));
    removeChapterButton = new QPushButton(QIcon::fromTheme("list-remove"),
                                       "&Remove Chapter");
    removeChapterButton->setDisabled(true); // Initially disabled,
                                            // until a chapter is selected
    connect(removeChapterButton, SIGNAL(clicked()),
            this, SLOT(removeChapter()));


    // TMP, some tests
    treeWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    pAddChapter = new QAction(QIcon::fromTheme("list-remove"),
        "Remove Chapter", treeWidget);
    treeWidget->addAction(pAddChapter);
    pRemoveChapter = new QAction("Remove Chapter", treeWidget);
    treeWidget->addAction(pRemoveChapter);
    
    
    pRemoveStep = new QAction(QIcon::fromTheme("list-remove"),
        "Remove Step", treeWidget);
    treeWidget->addAction(pRemoveStep);
    pCopyStep = new QAction(QIcon::fromTheme("list-remove"),
        "Copy Step", treeWidget);
    treeWidget->addAction(pCopyStep);
    pInsertCopiedStep = new QAction(QIcon::fromTheme("list-remove"),
        "Insert Copied Step", treeWidget);
    treeWidget->addAction(pInsertCopiedStep);

    connect(pAddChapter, SIGNAL(triggered()),
        this, SLOT(addChapter()));
    connect(pRemoveChapter, SIGNAL(triggered()),
        this, SLOT(removeChapter()));
    
    connect(pRemoveStep, SIGNAL(triggered()),
        this, SLOT(RemoveStep()));
    connect(pCopyStep, SIGNAL(triggered()),
        this, SLOT(CopyStep()));
    connect(pInsertCopiedStep, SIGNAL(triggered()),
        this, SLOT(InsertCopiedStep()));


    // Layout
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(treeWidget);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(addChapterButton);
    mainLayout->addWidget(removeChapterButton);
    this->setLayout(mainLayout);
    stepCopied = false;

    qDebug() << "ChapterList created";
}

void ChapterList::InsertCopiedStep()
{
    Chapter * Chapter = chapters.at(currentChapter - 1);
    Step *curstep = Chapter->getAllSteps().at(Chapter->currentStep);

    //Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    
    Chapter->insertStep(new Step(*copiedStepLine,
        Chapter->getTreeItem(), 
        curstep->selfTreeItem, 
        characterManager->getAllAliases(),
        Chapter));


    stepCopied = false;
    qDebug() << "insert step copied";
}
void ChapterList::CopyStep()
{
    Chapter * Chapter = chapters.at(currentChapter - 1);
    Step *curstep = Chapter->getAllSteps().at(Chapter->currentStep);
    copiedStepLine = new QString(curstep->getScriptLine());
    stepCopied = true;
    qDebug() << "step copied" << copiedStepLine;
}
void ChapterList::RemoveStep()
{
    Chapter * Chapter = chapters.at(currentChapter - 1);

    if (nullptr == stepsel)
        return;
    treeWidget->removeItemWidget(stepsel->selfTreeItem, 0);
    delete(stepsel->selfTreeItem);
    Chapter->removeStepAt(stepsel);
    Chapter->currentStep--;
    //int index= treeWidget->indexOfTopLevelItem(curstep->selfTreeItem);
    //treeWidget->takeTopLevelItem(index);
    qDebug() << "step removed";
}

ChapterList::~ChapterList()
{
    delete(pRemoveStep);
    delete(pCopyStep);
    delete(pInsertCopiedStep);
    delete(removeChapterButton);
    delete(addChapterButton);
    delete(pAddChapter);
    delete(removeChapterButton);
    delete(treeWidget);

    qDebug() << "ChapterList destroyed";
}



void ChapterList::clearContents()
{
    qDebug() << "Clearing ChapterLIst contents...";

    foreach (Chapter *chapter, chapters)
    {
        delete chapter;   /// Delete all Chapter objects from chapters list
    }
    chapters.clear(); // Clear the chapters list itself


    treeWidget->clear(); // Delete the visible list contents, the tree items
}




//////////////////////////////// SLOTS ////////////////////////////////////




void ChapterList::setContents(QString path, QStringList fileList)
{
    qDebug() << "Setting ChapterList contents from" << projectPath;

    this->projectPath = path;

    int fileCounter = 0;
    foreach (QString fileName, fileList)
    {
         // Avoid loading chardefs, imagedefs and options.rpy
        if (fileName.contains("-script"))  // Kinda TMP
        {
            ++fileCounter;

            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(tr("Chapter %1").arg(fileCounter)));
            item->setIcon(0, QIcon::fromTheme("folder-bookmark"));
            item->setData(0, Qt::UserRole, fileCounter); // Store the chapter #

            // Kinda TMP / FIXME
            item->setForeground(0, QBrush(QColor("#000000")));
            item->setBackgroundColor(0, QColor("#CCCCDD"));

            treeWidget->addTopLevelItem(item);

            chapters.append(new Chapter(fileName,
                                        item,
                                        characterManager,
                                        treeWidget));
        }
    }

    treeWidget->expandAll();

    emit chapterChanged(chapters.at(0)); // Load first chapter automatically


    //tmp, move where appropiate // FIXME
    qDebug() << "Project's chapters:";
    foreach (Chapter *chapter, chapters)
    {
		int st = chapter->getNumberOfSteps();
        for (int counter = 0; counter < st; ++counter)
        {
            Step *step = chapter->getStep(counter);
            qDebug() << step->getScriptLine();

            emit stepRenderRequest(step);
        }
    }
}





void ChapterList::saveContentsToRpyFile()
{
    qDebug() << "Saving Chapters to RPY files";

    int chapterNumber = 1;

    foreach (Chapter *chapter, chapters)
    {
        QString rpyFileContents = QString("## Chapter %1\n\n").arg(chapterNumber);

        foreach (Step *step, chapter->getAllSteps())
        {
            qDebug() << step->getScriptLine();
            switch (step->getStepType())
            {
            case labelStep:
                break;

            // In all other cases, add the 4-space indentation
            default:
                rpyFileContents.append("    ");
            }


            rpyFileContents.append(step->getScriptLine());
            rpyFileContents.append("\n");

        }

        rpyFileContents.append(QString("\n## End of chapter %1\n").arg(chapterNumber));

        QTextCodec *code = QTextCodec::codecForName("utf8");
        QFile rpyFile(chapter->getScriptFilename());
        rpyFile.open(QIODevice::WriteOnly);
        rpyFile.write(rpyFileContents.toLocal8Bit());
        qDebug() << rpyFile.fileName() << "saved";
        rpyFile.close();

        ++chapterNumber;
    }
}




void ChapterList::loadChapter(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)

        ////////// TODO: Clean up this mess of tests!


        // If a chapter (not a step) was selected
    currentItem = item;
    if (item->parent() == NULL)
    {
        int selectedChapter = item->data(0, Qt::UserRole).toInt();
        if (selectedChapter > 1) // If not Chapter 1, which cannot be removed
        {
            // FIXME: Removing chapters crashes a lot at this point

            this->removeChapterButton->setEnabled(true); // enable button to remove
        }

        if (selectedChapter == currentChapter)
        {
            return;
        }
        currentChapter = selectedChapter;
        qDebug() << "selected chapter" << currentChapter << "of" << chapters.length();

        emit chapterChanged(chapters.at(currentChapter - 1)); // -1, since they're stored from 1
    }
    else  // Selected a step, not a chapter
    {
        this->removeChapterButton->setDisabled(true); // disable button to remove
        //////////////////////
        // quite TMP, for tests
		QVariant  v = item->data(0, Qt::UserRole);
		treenode *vnode = v.value<treenode*>();
        stepsel = vnode->step;
		currentStep = vnode->stepNum;
        //currentItem = stepSel->selfTreeItem;
        qDebug() << "ChapterList::loadChapter() stepscript" << stepsel->getScriptLine() << "at step" << currentStep;
		int selectedChapter;
		if(item->parent()->text(0).startsWith("Scene"))
			selectedChapter = item->parent()->parent()->data(0, Qt::UserRole).toInt();
		else
			selectedChapter = item->parent()->data(0, Qt::UserRole).toInt();
        if (selectedChapter < 1)
            return;
        if (selectedChapter != currentChapter)
        {
            currentChapter = selectedChapter;
            emit chapterChanged(chapters.at(currentChapter - 1)); // -1, since they're stored from 1
        }
		chapters.at(currentChapter - 1)->currentStep = currentStep;

		//Step *selectStep = chapters.at(currentChapter - 1)->getStep(stepNum);
        emit stepRenderRequest(stepsel);
		qDebug() << "currentChapter:" << currentChapter << "current step" << currentStep;
        //qDebug() << this->chapters.at(currentChapter - 1)->getStepLine(stepNum);
		
    }
}





void ChapterList::addChapter()
{
    int chapterNumber = this->chapters.length() + 1;

    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(tr("Chapter %1").arg(chapterNumber)));
    item->setIcon(0, QIcon::fromTheme("folder-bookmark"));
    item->setData(0, Qt::UserRole, chapterNumber); // Store the chapter #

    // Kinda TMP / FIXME
    item->setForeground(0, QBrush(QColor("#000000")));
    item->setBackgroundColor(0, QColor("#CCCCDD"));

    treeWidget->addTopLevelItem(item);

    // Filename like 105-script.rpy
    QString filename = QString("1%1-script.rpy").arg(chapterNumber,
                                                    2,
                                                    10,
                                                    QChar('0'));
    chapters.append(new Chapter(projectPath + "/" + filename,
                                item,
                                characterManager,
                                treeWidget));

    treeWidget->expandAll(); // Expand all, including the new chapter

    qDebug() << "Added chapter";
}



void ChapterList::removeChapter()
{
    int selectedChapter = treeWidget->currentItem()->data(0, Qt::UserRole).toInt() - 1;

    // FIXME, plenty of error control missing here
    // The other chapters should be reorganized when deleting one in the middle


    qDebug() << "############################";
    qDebug() << "############################";
    qDebug() << "Selected chapter to remove:" << selectedChapter;
    qDebug() << "############################";
    qDebug() << "############################";

    Chapter *chapter = chapters.at(selectedChapter);
    qDebug() << "Chapter filename:" << chapter->getScriptFilename();
    QFile::remove(chapter->getScriptFilename());

    delete chapter;
    chapters.removeAt(selectedChapter);
    qDebug() << "chapters len()" << chapters.length();

    qDebug() << "############################";
    delete this->treeWidget->currentItem();
    qDebug() << "############################";


    qDebug() << "Removed chapter" << selectedChapter;
}
