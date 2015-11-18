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

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QAction>

#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>

#include <QDebug>
#include "CharacterManager.h"
#include "chapter.h"
#include "ui_ImageManager.h"

class ImageManager : public QWidget, public Ui::ImageManagerForm
{
    friend class SceneDesigner;
    Q_OBJECT

public:
    explicit ImageManager(QWidget *parent = 0);
    ~ImageManager();

    void enableOrDisableButtons();

    void loadImagesFromRpyFile(QString filename);
    void saveImagesToRpyFile();

    QString getFilenameFromRef(QString ref);

    void insertImage(QString options);
    QStringList effects; 
    QStringList ATLs;


signals:
    void backgroundSelected(QString imageRef,
                            QString filename);
    void imageSelected(QString imageRef,
                       QString alignment,
                       QString filename);
    void imageInsert(QString imageRef,
        QString filename,
        QString cmd,
        QString option);
    void imageInsert(QString imageRef);
    void imageInsert(QStringList cmds);
    //call addImage(QString imageref, QString filename, QString cmd, QString option)
    void imageInsertWithOptions(QString imageref, QString filename, QString cmd, QString option);

    
public slots:
    void updateImageRefInList();
    void removeImageFromList();

    void addAnotherImage();
    void addScaledImage();

    void clear();

    void showForEditing();
    void showSetBackground();
    void showInsertImage();

    void setBackground();
    void insertImageLeft();
    void insertImageCenter();
    void insertImageRight();
	void insertImage();
	void generateScript();
	void hideImage();
    //void addImage(QString imageref, QString dir, QString cmd, QString option);
protected:
    virtual void closeEvent(QCloseEvent *event);


private:
#if 0
    QHBoxLayout *mainLayout;

    QGroupBox * imageListGroupbox;
    QVBoxLayout *imageListLayout;
    QListWidget *imageList;
    QPushButton *addAnotherImageButton;


    QGroupBox *currentImageGroupbox;
    QGridLayout *currentImageLayout;
    QLabel *imageRefLabel;
    QLineEdit *imageRefLineEdit;
    QPushButton *changeImageRefButton;
    QPushButton *removeSelectedImageButton;


    QPushButton *setBackgroundButton;

    QGroupBox *alignButtonsGroupbox;
    QHBoxLayout *alignButtonsLayout;
    QPushButton *insertImageButtonLeft;
    QPushButton *insertImageButtonCenter;
    QPushButton *insertImageButtonRight;
#endif

    QAction *closeAction;

    QString rpyFilename;
    QString projectPath;
    CharacterManager *characterManager;
    Chapter *currentChapter;
};

#endif // IMAGEMANAGER_H
