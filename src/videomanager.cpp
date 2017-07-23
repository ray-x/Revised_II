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
#include "videomanager.h"
#include "ui_videomanager.h"
#include <QDebug>
#include <QFileDialog>

VideoManager::VideoManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoManager)
{
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->videoListWidget->setViewMode(QListView::ListMode);
    //ui->videoListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->videoListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //listWidget->selectedItems()
    connect(ui->addVideoStepBtn, SIGNAL(clicked()), this, SLOT(addVideoStep()));
    connect(ui->addVideoBtn, SIGNAL(clicked()), this, SLOT(addMoreVideo()));
    connect(ui->removeVideoBtn, SIGNAL(clicked()), this, SLOT(removeVideo()));
}

VideoManager::~VideoManager()
{
    //remove all items
    ui->videoListWidget->clear();
    delete ui;
}


void VideoManager::addMoreVideo()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,
        tr("Select one or more images"),
        this->projectDir,
        tr("Images")
        + " (*.mp4 *.mkv *.mpg *.ogv)");


    if (fileList.isEmpty())  // if FileDialog was cancelled, don't do anything
    {
        return;
    }


    foreach(QString filename, fileList)
    {
        // If selected image isn't in project directory, copy it
        if (QFileInfo(filename).path() != this->projectDir)
        {
            // Copy to project path
            qDebug() << QFileInfo(filename).path() << "vs" << projectDir;

            QString newFilename = projectDir + "/" + QFileInfo(filename).fileName();

            QFile::copy(filename, newFilename);
            qDebug() << "Copying image to project directory:" << newFilename;

            filename = newFilename;

        }

        QListWidgetItem *videoItem = new QListWidgetItem();

        // FIXME: aspect ratio, etc.
        videoItem->setIcon(QIcon(QPixmap(filename).scaled(32, 32)));

        // Set bare filename, without extension, as Image Ref initially
        // replacing "-" with "_", as it's not supported in image refs
        QString imageRef = QFileInfo(filename).baseName();
        imageRef.replace("-", " ");
        imageRef.replace("_", " ");
        videoItem->setText(imageRef);

        // Store full filename with extension, without path, in the item
        videoItem->setData(Qt::UserRole, QFileInfo(filename).fileName());

        ui->videoListWidget->addItem(videoItem);
    }
}

void VideoManager::removeVideo()
{

    QList<QListWidgetItem *> items = ui->videoListWidget->selectedItems();
    QString music;
    for (auto item : items)
    {
        QString music_pathname = item->data(Qt::UserRole).toString();
        QFile removeFile(music_pathname);
        removeFile.remove();
    }

    qDeleteAll(items);

 }



void VideoManager::loadVideoFromDir(QString myprojectDir)
{
    //this->rpyFilename = filename;

    projectDir = myprojectDir;


    //QDir projectDir(projectDir);
    QStringList nameFilter = { "*.mpg", "*.mkv", "*.mp4" };
    QDir directory(projectDir);
    QStringList videoFileList = directory.entryList(nameFilter);

    qDebug() << videoFileList;

    for (QString filename : videoFileList) {
        QString videoRef = QFileInfo(filename).fileName();
        qDebug() << videoFileList;
        QString VideoFilename = projectDir + "/" + filename.trimmed();
        QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(VideoFilename)), videoRef);

        item->setData(Qt::UserRole, VideoFilename);
        ui->videoListWidget->addItem(item);
    }
    //qDebug() << "ImageManager data loaded from" << rpyFilename << "on" << projectPath;
}

void VideoManager::addVideoStep()
{

    /*
    image movie = Movie(size=(400, 300), xalign=0.5, yalign=0.5)
    show movie
    play movie "incubus.mkv"
    */
    QStringList videoStep;
    QListWidgetItem *  item = ui->videoListWidget->currentItem();
    if (ui->videoListWidget->selectedItems().count() < 1)
        return;
    QString movie;
    QString movie_pathname = item->data(Qt::UserRole).toString();
    QString movie_name = QFileInfo(movie_pathname).fileName();
    movie.append(movie_name + " ");

    if (ui->ImageRdBox->isChecked())
    {
        videoStep.append("image movie = Movie(size=(640, 480), xalign=0.5, yalign=0.5)");
        videoStep.append("show movie");
        videoStep.append(QString("play movie \"%1\"").arg(movie_name));
        videoStep.append("stop movie");
        videoStep.append("hide movie");
    }       
    else
        videoStep.append(QString("renpy.movie_cutscene(\"%1\")").arg(movie_name));
       

    qDebug() << videoStep;


    emit sigInsertVideoStep(videoStep);

}
