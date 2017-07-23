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
#include <QIcon>
#include "audiomanagerform.h"
#include "ui_audiomanagerform.h"

AudioManagerForm::AudioManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioManagerForm)
{
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->audioListWidget->setViewMode(QListView::ListMode);
    ui->audioListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->audioListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //listWidget->selectedItems()
    connect(ui->AddMusicStepPBtn, SIGNAL(clicked()), this, SLOT(addAudioStep()));
    connect(ui->AddMusicPushButton, SIGNAL(clicked()), this, SLOT(addMoreAudio()));
}

AudioManagerForm::~AudioManagerForm()
{
    //delete all items
    ui->audioListWidget->clear();
    delete ui;
}

void AudioManagerForm::showSetAudio()
{
    show();
}

void AudioManagerForm::addMoreAudio()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,
        tr("Select one or more images"),
        this->projectDir,
        tr("Images")
        + " (*.wav *.mp3 *.ogg)");


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

        QListWidgetItem *audioItem = new QListWidgetItem();

        // FIXME: aspect ratio, etc.
        audioItem->setIcon(QIcon(QPixmap(filename).scaled(32, 32)));

        // Set bare filename, without extension, as Image Ref initially
        // replacing "-" with "_", as it's not supported in image refs
        QString imageRef = QFileInfo(filename).baseName();
        imageRef.replace("-", " ");
        imageRef.replace("_", " ");
        audioItem->setText(imageRef);

        // Store full filename with extension, without path, in the item
        audioItem->setData(Qt::UserRole, QFileInfo(filename).fileName());

        ui->audioListWidget->addItem(audioItem);
    }
}


void AudioManagerForm::loadAudioFromDir(QString myprojectDir)
{
    //this->rpyFilename = filename;

    projectDir = myprojectDir;


    //QDir projectDir(projectDir);
    QStringList nameFilter = { "*.wav", "*.mp3" ,"*.ogg"};
    QDir directory(projectDir);
    QStringList audioFileList = directory.entryList(nameFilter);

    qDebug() << audioFileList;

    for (QString filename:audioFileList) {
        QString audioRef = QFileInfo(filename).fileName();
        qDebug() << audioFileList;
        QString AudioFilename = projectDir + "/" + filename.trimmed();
        QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(AudioFilename)), audioRef);

        item->setData(Qt::UserRole, AudioFilename);
        ui->audioListWidget->addItem(item);
    }
    


#if 0
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
            /*
            imageFilename = projectPath + "/" + imageFilename.trimmed();
            qDebug() << "loaded filename:" << imageFilename;
            QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(imageFilename)),
            imageRef);
            item->setData(Qt::UserRole, QFileInfo(imageFilename).fileName());
            */
            imageList->addItem(item);
        }
    }
    rpyFile.close();

    enableOrDisableButtons();
#endif
    //qDebug() << "ImageManager data loaded from" << rpyFilename << "on" << projectPath;
}

void AudioManagerForm::addAudioStep()
{
    QString audioStep;
    QList<QListWidgetItem *> items = ui->audioListWidget->selectedItems();
    QString music="";
    for (auto item : items)
    {
        QString music_pathname= item->data(Qt::UserRole).toString();
        QString music_name = QFileInfo(music_pathname).fileName();
        qDebug() << music_name;
        if (music.isEmpty())
            music.append(music_name);
        else
            music.append(QString(" ")+music_name);
    }
    music.trimmed();
    QString audio_command="play ";
    QString fadeIn = "";
    QString fadeOut = "";
    QString audio_type = "";
    if (ui->LoopChkBox->isChecked())
        audio_type = "music";
    else
        audio_type = "sound";
    audio_command += audio_type;
    audio_command.append(" ");
    if (ui->FadeInChkBox->isChecked() && !ui->FadeInTimeLEdit->text().isEmpty())
        fadeIn.append("fadein ").append(ui->FadeInTimeLEdit->text().trimmed());
    if (ui->FadeoutChkBox->isChecked() && !ui->FadeOutTimeLEdit->text().isEmpty())
        fadeIn.append("fadeout ").append(ui->FadeOutTimeLEdit->text().trimmed());

    audioStep = audio_command.append(" \"") + music + fadeIn.append("\"") + fadeOut;
    emit sigInsertAudioStep(audioStep);
    audio_command = "stop ";
    audio_command.append(audio_type);


}