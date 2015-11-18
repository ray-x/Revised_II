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

#ifndef SCENEDESIGNER_H
#define SCENEDESIGNER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include <QDebug>

#include "charactermanager.h"
#include "imagemanager.h"
#include "videomanager.h"
#include "timerform.h"
#include "scenepreviewer.h"
#include "charactercombobox.h"

#include "chapter.h"
#include "step.h"

#include "choicemenueditor.h"
#include "choicemenueditorform.h"
#include "audiomanagerform.h"
#include "chapterlist.h"

class SceneDesigner : public QWidget
{
    Q_OBJECT

public:
    explicit SceneDesigner(
        ChapterList *mwChapterList,
        CharacterManager *mwCharacterManager,
        ImageManager *mwImageManager,
        AudioManagerForm *mwAudioManager,
        VideoManager *mwVideoManager,
        TimerForm *mwTimerForm,
        QWidget *parent = nullptr) ;

    ~SceneDesigner();

    void clear();
    ChapterList *chapList;

signals:
    void characterManagerRequested();
    
public slots:
    void loadChapter(Chapter *chapter);

    void addBackgroundStep(QString imageRef, QString filename);
    void addImageStep(QString imageRef,
                      QString cmd,
                      QString alignment,
                      QString filename);
    void addImageStep(QString command);
    void addImageStep(QStringList commands);
    void addAudioStep(QString audiostep);

    void addVideoStep(QStringList videostep);
    void addTimerStep(QStringList videostep);
    void addMenuStep(QStringList commands);
    void addDialogStep();

    void renderStep(Step *step);

    void deleteCurrentStep();
	void showNextStep();
	void showPrevStep();
protected:




private:
    QVBoxLayout *mainLayout;
    QGridLayout *controlsLayout;

    ScenePreviewer *scenePreviewer;

    CharacterManager *characterManager;
    ImageManager *imageManager;
    AudioManagerForm *audioManager;
    VideoManager *videoManager;
    TimerForm *timerForm;
    ChoiceMenuEditorForm *choiceMenuEditor;

    QPushButton *previousStepButton;
    QPushButton *nextStepButton;
    QPushButton *deleteStepButton;

    QPushButton *insertMenuButton;

    QPushButton *setBackgroundButton;
    QPushButton *insertImageButton;

    CharacterComboBox *characterComboBox;
    QLineEdit *textLine;
    QPushButton *acceptTextButton;


    Chapter *currentChapter;

};

#endif // SCENEDESIGNER_H
