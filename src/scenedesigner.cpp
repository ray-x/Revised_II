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

#include "scenedesigner.h"

SceneDesigner::SceneDesigner(
    ChapterList *mwChapterList,
    CharacterManager *mwCharacterManager,
    ImageManager *mwImageManager,
    AudioManagerForm *mwAudioManager,
    VideoManager *mwVideoManager,
    TimerForm *mwtimerForm,
    QWidget *parent) : QWidget(parent), chapList(mwChapterList)
{
    this->characterManager = mwCharacterManager;
    this->imageManager = mwImageManager;
    this->audioManager = mwAudioManager;
    this->videoManager = mwVideoManager;
    this->timerForm = mwtimerForm;
    //this->videoManager=mwVideoManger;

    scenePreviewer = new ScenePreviewer();

    choiceMenuEditor = new ChoiceMenuEditorForm();


    previousStepButton = new QPushButton(QIcon::fromTheme("go-previous"),
                                   tr("&Previous"));
	connect(previousStepButton, SIGNAL(clicked()),
		this, SLOT(showPrevStep()));
    //previousStepButton->setDisabled(true);// TMP!
    // Previous step is disabled on start, until you insert something

    nextStepButton = new QPushButton(QIcon::fromTheme("go-next"),
                               tr("&Next"));
	connect(nextStepButton, SIGNAL(clicked()),
		this, SLOT(showNextStep()));
    //nextStepButton->setDisabled(true);// TMP!
    // Next step will be available if you're not on the last one
    // If you're in the last step, insert an image, text or menu


    // Button to remove current step
    deleteStepButton = new QPushButton(QIcon::fromTheme("edit-delete"),
                                 tr("&Delete this step"));
    connect(deleteStepButton, SIGNAL(clicked()),
            this, SLOT(deleteCurrentStep()));



    insertMenuButton = new QPushButton(QIcon::fromTheme("view-choose"),
                                       tr("Insert Choice &Menu"));
    insertMenuButton->setStatusTip(tr("Insert a menu with several choices. "
                                      "Each choice will go to a different part of the game"));
    connect(insertMenuButton, SIGNAL(clicked()),
        choiceMenuEditor, SLOT(show()));


    setBackgroundButton = new QPushButton(QIcon::fromTheme("insert-image"),
                                        tr("Set &Background..."));
    connect(setBackgroundButton, SIGNAL(clicked()),
            imageManager, SLOT(showSetBackground()));

    connect(imageManager, SIGNAL(backgroundSelected(QString,QString)),
            this, SLOT(addBackgroundStep(QString,QString)));

    connect(imageManager, SIGNAL(imageInsert(QString, QString, QString, QString)),
        this, SLOT(addImageStep(QString, QString, QString, QString)));
    connect(imageManager, SIGNAL(imageInsert(QString)),
        this, SLOT(addImageStep(QString)));
    connect(imageManager, SIGNAL(imageInsert(QStringList)),
        this, SLOT(addImageStep(QStringList)));
    connect(audioManager, SIGNAL(sigInsertAudioStep(QString)),
        this, SLOT(addAudioStep(QString)));
    connect(choiceMenuEditor, SIGNAL(sigInsertMenuStep(QStringList)),
        this, SLOT(addMenuStep(QStringList)));

    connect(videoManager, SIGNAL(sigInsertVideoStep(QStringList)),
        this, SLOT(addVideoStep(QStringList)));

    connect(timerForm, SIGNAL(sigInsertTimerStep(QStringList)),
        this, SLOT(addTimerStep(QStringList)));

	insertImageButton = new QPushButton(QIcon::fromTheme("folder-image-people"),
                                      tr("Insert &Image..."));
    connect(insertImageButton, SIGNAL(clicked()),
            imageManager, SLOT(showInsertImage()));

    connect(imageManager, SIGNAL(imageSelected(QString,QString,QString)),
            this, SLOT(addImageStep(QString,QString,QString)));

    connect(audioManager, SIGNAL(addAudioStep(QString)),
        this, SLOT(addAudioStep(QString)));

    characterComboBox = new CharacterComboBox();
    characterComboBox->populate();
    connect(characterComboBox, SIGNAL(characterManagerRequested()),
            characterManager, SLOT(show()));

    connect(characterManager, SIGNAL(characterListUpdated(QStringList,QStringList,QStringList)),
            characterComboBox, SLOT(populate(QStringList,QStringList,QStringList)));



    textLine = new QLineEdit();
    textLine->setPlaceholderText(tr("Some dialog..."));
    connect(textLine, SIGNAL(returnPressed()),
            this, SLOT(addDialogStep()));

    acceptTextButton = new QPushButton(QIcon::fromTheme("insert-text"),
                                       tr("Insert &Text Step"));
    connect(acceptTextButton, SIGNAL(clicked()),
            this, SLOT(addDialogStep()));


    controlsLayout = new QGridLayout();
    controlsLayout->addWidget(previousStepButton,        0,  0,  1,  1, Qt::AlignLeft);
    controlsLayout->addWidget(nextStepButton,            0,  3,  1,  1, Qt::AlignRight);

    controlsLayout->addWidget(setBackgroundButton, 1,  0,  1,  1);
    controlsLayout->addWidget(insertImageButton,   1,  1,  1,  1);

    controlsLayout->addWidget(insertMenuButton,    1,  2,  1,  1);

    controlsLayout->addWidget(deleteStepButton,          1,  3,  1,  1); // kinda TMP


    controlsLayout->addWidget(characterComboBox,   2,  0,  1,  1);
    controlsLayout->addWidget(textLine,            2,  1,  1,  2);
    controlsLayout->addWidget(acceptTextButton,    2,  3,  1,  1);


    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scenePreviewer);
    mainLayout->addLayout(controlsLayout);

    this->setLayout(mainLayout);

    qDebug() << "SceneDesigner created";
}



SceneDesigner::~SceneDesigner()
{
    delete(scenePreviewer);
    delete(previousStepButton);
    delete(choiceMenuEditor);
    delete(nextStepButton);
    delete(deleteStepButton);
    delete(insertMenuButton);
    delete(setBackgroundButton);
    delete(insertMenuButton);
    delete(characterComboBox);
    delete(textLine);
    delete(acceptTextButton);
    delete(controlsLayout);
    delete(mainLayout);
    qDebug() << "SceneDesigner destroyed";
}




void SceneDesigner::clear()
{
    characterComboBox->populate();
    scenePreviewer->clear();

    qDebug() << "Cleared SceneDesigner";
}



//////////////////////////////////// SLOTS ///////////////////////////////////




void SceneDesigner::loadChapter(Chapter *chapter)
{
    this->currentChapter = chapter;
    this->imageManager->currentChapter = chapter;

    qDebug() << "SceneDesigner loading chapter" << chapter->getScriptFilename();
}




/*
 *
 * Format:
 *          scene background image reference
 */
void SceneDesigner::addBackgroundStep(QString imageRef, QString filename)
{
    QString line = "    "; // Always start with 4-char indentation
    line.append("scene  ");
    line.append(imageRef);
    line.append("\n");
    //Step(QString line, QTreeWidgetItem *currSceneItem, Step *step, QStringList characterAliases, QObject *parent);
    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    this->currentChapter->insertStep(new Step(line,
                                           currentChapter->getTreeItem(),
                                           curstep,
                                           QStringList(),
                                           currentChapter));


    this->scenePreviewer->setBackgroundImage(filename);
}



/*
 *
 * Format:
 *          show regular image reference
 */
void SceneDesigner::addImageStep(QString imageRef,
                                 QString cmd,
                                 QString alignment,
                                 QString filename)
{
    QString line = "    "; // Always start with 4-char indentation

    line = line.append(cmd +" "+ imageRef +" "+ alignment);
    qDebug() << line;



    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    this->currentChapter->insertStep(new Step(line,
                                           currentChapter->getTreeItem(), //scene
                                           curstep,                     //stepnum
                                           QStringList(),
                                           currentChapter));


    this->scenePreviewer->addOtherImage(filename, alignment);
    imageManager->close();
    
}



void SceneDesigner::addImageStep(QString command)
{
    QString line = "    "; // Always start with 4-char indentation

    line = line.append(command);
    qDebug() << line;
    
    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    this->currentChapter->insertStep(new Step(line,
        currentChapter->getTreeItem(), //scene
        curstep,                     //stepnum
        QStringList(),
        currentChapter));

    imageManager->close();

}
void SceneDesigner::addImageStep(QStringList commands)
{
    //QString line = "    "; // Always start with 4-char indentation

    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);

    for (auto step : commands)
    {
        this->currentChapter->insertStep(new Step(step,
            currentChapter->getTreeItem(), curstep,
            QStringList(), // not needed
            currentChapter));
        curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    }
    //videoManager->close();

    imageManager->close();

}


void SceneDesigner::addMenuStep(QStringList commands)
{
    //QString line = "    "; // Always start with 4-char indentation

    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);

    for (auto step : commands)
    {
        this->currentChapter->insertStep(new Step(step,
            currentChapter->getTreeItem(), curstep,
            QStringList(), // not needed
            currentChapter));
        curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    }
    //videoManager->close();

    imageManager->close();

}



//*begin with audio first

void SceneDesigner::addAudioStep(QString audiostep)
{

    qDebug() << audiostep;
    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);

    this->currentChapter->insertStep(new Step(audiostep, 
        currentChapter->getTreeItem(), curstep,
        QStringList(), // not needed
        currentChapter));
    //this->scenePreviewer->addOtherImage(filename, alignment);
    audioManager->close();

}

void SceneDesigner::addVideoStep(QStringList videostep)
{
    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);

   for (auto step : videostep)
    {
        this->currentChapter->insertStep(new Step(step,
            currentChapter->getTreeItem(), curstep,
            QStringList(), // not needed
            currentChapter));
        curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);
    }
    videoManager->close();
}

void SceneDesigner::addTimerStep(QStringList steps)
{
    Step *curstep = currentChapter->getAllSteps().at(currentChapter->currentStep);

    for (auto step : steps)
    {
        this->currentChapter->insertStep(new Step(step,
            currentChapter->getTreeItem(), curstep,
            QStringList(), // not needed
            currentChapter));
        qDebug() << step;
        curstep = currentChapter->getAllSteps().at(currentChapter->currentStep++);
    }
    videoManager->close();
}

void SceneDesigner::addDialogStep()
{
    if (this->textLine->text().isEmpty())
    {
        qDebug() << "No dialog text!";
        return;
    }


    QString name; // if "Narrator" is selected, this will be kept empty
    QString color;

    QString line = "    "; // Always start with 4-char indentation


    int selectedCharacter = this->characterComboBox->currentIndex();
    QString strSelectedItem = this->characterComboBox->currentText();

    // if "Add New Character" is selected (shouldn't happen)
    if (selectedCharacter == this->characterComboBox->count())
    {
        this->characterComboBox->setCurrentIndex(0); // Select "Narrator"
        selectedCharacter = 0;
    }

    if (selectedCharacter != 0 && strSelectedItem!=" Add New Label: ") // If NOT narrator
    {
        // Get character's alias from combobox item data
        QStringList characterData = characterComboBox->itemData(selectedCharacter,
                                                                Qt::UserRole).toStringList();

        line.append(characterData.at(0));  // alias
        line.append("  ");  // Two spaces between character name and text

        name = characterComboBox->currentText();
        color = characterData.at(1);
    }
    if (strSelectedItem == " Add New Label: ")
    {
        line.append("Label:    ");  // alias

    }

    line.append(QString("\"%1\"\n").arg(this->textLine->text()));
 
    Step *curstep=currentChapter->getAllSteps().at(currentChapter->currentStep);
    this->currentChapter->insertStep(new Step(line,
                                           currentChapter->getTreeItem(),
                                           curstep,
                                           characterManager->getAllAliases(),
                                           this->currentChapter));

    this->scenePreviewer->setDialogText(name,
                                        color,
                                        textLine->text());

    this->textLine->clear();
}




void SceneDesigner::renderStep(Step *step)
{
    QString dialogCharacterAlias;
    QString dialogCharacterName;
    QString dialogCharacterColor;
    QString dialogText;
    QString imageRef;
    QString imageFilename;
    QString alignment;

    switch (step->getStepType())
    {
    case dialogStep:
        dialogCharacterAlias = step->getStepParameters().at(0);
        dialogCharacterName = characterManager->getCharacterName(dialogCharacterAlias);
        dialogCharacterColor = characterManager->getCharacterColor(dialogCharacterAlias);

        dialogText = step->getStepParameters().at(1);
        this->scenePreviewer->setDialogText(dialogCharacterName,
                                            dialogCharacterColor,
                                            dialogText);
        break;

    case sceneStep:
        this->scenePreviewer->clear();  // Clear first
		//QString imageRefStr = step->getStepParameters().at(0).trimmed(); // kinda TMP/FIXME
		imageRef = step->getStepParameters().at(0).trimmed().split("#", QString::SkipEmptyParts)[0].trimmed();
        imageFilename = imageManager->getFilenameFromRef(imageRef);
        this->scenePreviewer->setBackgroundImage(imageFilename);
		qDebug() << "setbackground to :" << imageFilename;
        break;

    case showStep:
        imageRef = step->getStepParameters().at(0).trimmed(); // kinda TMP/FIXME
        imageFilename = imageManager->getFilenameFromRef(imageRef);

        // If there is a second parameter (at position), else use default
        if (step->getStepParameters().size() > 1)
        {
            alignment = step->getStepParameters().at(1);
        }
        else
        {
            alignment = "center"; // default
        }

        this->scenePreviewer->addOtherImage(imageFilename, alignment);

        break;

    default:
        break;

    }
}



void SceneDesigner::deleteCurrentStep()
{
    this->currentChapter->removeCurrentStep();
}
void SceneDesigner::showNextStep()
{
	//this->currentChapter->
	this->currentChapter->currentStep += 1;
    if (this->currentChapter->currentStep >= this->currentChapter->getNumberOfSteps())
        this->currentChapter->currentStep = this->currentChapter->getNumberOfSteps() - 1;

	renderStep(this->currentChapter->getStep(this->currentChapter->currentStep));
}
	
void SceneDesigner::showPrevStep()
{
	this->currentChapter->currentStep -= 1;
    if (this->currentChapter->currentStep < 0)
        this->currentChapter->currentStep = 0;

	renderStep(this->currentChapter->getStep(this->currentChapter->currentStep));
}
