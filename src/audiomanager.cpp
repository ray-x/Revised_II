/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2014-2015  Ray             <ray.cn@gmail.com>
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

#include "audiomanager.h"

AudioManager::AudioManager(QWidget *parent) : QWidget(parent)
{
    // Left side

    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    this->setupUi(this);


    //this->setWindowTitle("Revised - " + tr("Audio Manager"));
    //this->setWindowIcon(QIcon::fromTheme("folder-image"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    //this->setMinimumSize(320, 320);

    //AudioListWidget->setViewMode(QListView::ListMode);
    //AudioListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //AudioListWidget->setIconSize(QSize(128, 128));  // 128x128 thumbnails

//    connect(addAnotherImageButton, SIGNAL(clicked()),
//        this, SLOT(addAnotherImage()));

}

void AudioManager::showSetAudio()
{
    
    //    this->alignButtonsGroupbox->hide();

    this->show();
}

AudioManager::~AudioManager()
{
    qDebug() << "ImageManager destroyed";
}


void AudioManager::loadAudiosFromDir(QString myprojectDir)
{
    //this->rpyFilename = filename;

   QString projectDir = QFileInfo(myprojectDir).absolutePath();


    //QDir projectDir(projectDir);
    QStringList nameFilter("*.png");
    QDir directory(projectDir);
    QStringList txtFilesAndDirectories = directory.entryList(nameFilter);
    qDebug() << txtFilesAndDirectories;

    while (!rpyFile.atEnd())    // Parse RPY file, etc.
    {
        rpyFileLine = QString::fromLocal8Bit(rpyFile.readLine());
        if (rpyFileLine.startsWith("image"))
        {
            QString imageRef = rpyFileLine;

            imageRef.remove(QRegExp("\\s*image\\s+"));
            imageRef.remove(QRegExp("=.+"));
            imageRef = imageRef.trimmed();

            qDebug() << "loaded imageRef:" << imageRef;

            QString imageFilename = rpyFileLine;

            imageFilename.remove(QRegExp(".*=\\s+\\\""));
            imageFilename.remove(QRegExp("\\\""));

            QString fullImageFilename = projectPath + "/" + imageFilename.trimmed();
            qDebug() << "loaded filename:" << imageFilename;
            QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(fullImageFilename)),
                imageRef);
            item->setData(Qt::UserRole, imageFilename);
            //item->setData(Qt::UserRole, imageFilename);

            imageFilename = projectPath + "/" + imageFilename.trimmed();
            qDebug() << "loaded filename:" << imageFilename;
            QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(imageFilename)),
            imageRef);
            item->setData(Qt::UserRole, QFileInfo(imageFilename).fileName());

            imageList->addItem(item);
        }
    }
    rpyFile.close();

    enableOrDisableButtons();
    //qDebug() << "ImageManager data loaded from" << rpyFilename << "on" << projectPath;
}

