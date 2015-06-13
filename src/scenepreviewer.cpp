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

#include "scenepreviewer.h"
#include <QFileInfo>
ScenePreviewer::ScenePreviewer(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(640, 480);


    // Set up font for dialog lines preview
    dialogTextFont.setBold(true);
    dialogTextFont.setPointSize(dialogTextFont.pointSize() + 6);


    // Initial background
    this->backgroundImage = ":/images/library.png";

    qDebug() << "ScenePreviewer created" << this->width() << this->height();
}


ScenePreviewer::~ScenePreviewer()
{
    qDebug() << "ScenePreviewer destroyed";
}






void ScenePreviewer::setBackgroundImage(QString filename)
{
    this->backgroundImage = filename;

    this->update();

    qDebug() << "ScenePreviewer() backgroundImage:" << filename;
}



void ScenePreviewer::addOtherImage(QString filename, QString alignment)
{
    // Add to list of single images (sprites, etc)

    this->otherImages.append(filename);
    this->otherImagesAlignments.append(alignment);


    this->update();
}



void ScenePreviewer::setDialogText(QString name, QString color, QString text)
{
    this->characterName = name;
    this->characterColor = color;

    this->dialogText = text;

    this->update();
}




void ScenePreviewer::clear()
{
    this->setBackgroundImage(":/images/tmp-scene.png");
    this->otherImages.clear();
    this->otherImagesAlignments.clear();
    this->setDialogText("", "", "");
}



////////////////////////////////// PROTECTED ///////////////////////////////////




void ScenePreviewer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int maxWidth = this->width();
    int maxHeight = this->height();


    // Draw background
	QPixmap backgroundImagePixmap;
	QString path = this->backgroundImage;
	backgroundImagePixmap = QPixmap(path.trimmed());

    // FIXME: if no BG selected, pixmap is null, and calculations
    // for single image Height fail
    // Also, floating point crashes occur (see divisions below)
    if (backgroundImagePixmap.isNull()) // temporary workaround
    {
		qDebug() << "failed to load image from " << this->backgroundImage;
        backgroundImagePixmap = QPixmap(":/images/tmp-scene.png");
    }

    painter.drawPixmap(0, 0,
                       maxWidth, maxHeight,
                       backgroundImagePixmap);



    // Draw characters, etc (single images)
    for (int counter = 0; counter != otherImages.length(); ++counter)
    {
        QString singleImage = otherImages.at(counter);
        QString alignment = otherImagesAlignments.at(counter);

        QPixmap singleImagePixmap = QPixmap(singleImage);

        // Prepare to resize the pixmap according to the
        // real size of the current previewer

        // Cross-multiplication
        int singleImageWidth = (maxWidth * singleImagePixmap.width()) / backgroundImagePixmap.width();
        int singleImageHeight = (maxHeight * singleImagePixmap.height()) / backgroundImagePixmap.height();


        int xPosition = 0;

        if (alignment == "left")
        {
            xPosition = 16;
        }
        else if (alignment == "center")
        {
            xPosition = (maxWidth / 2) - (singleImageWidth / 2);
        }
        else // "right"
        {
            xPosition = maxWidth - singleImageWidth - 16;
        }


        painter.drawPixmap(xPosition, maxHeight - singleImageHeight,
                           singleImageWidth, singleImageHeight,
                           singleImagePixmap);

    }



    QRect rectangle = QRect(64,                   // X
                            (maxHeight / 4) * 3,  // Y
                            maxWidth - 128,       // Width
                            maxHeight - ((maxHeight / 4) * 3) - 16); // Height

    // Draw rectangle for text
    painter.setPen(QColor(Qt::white));
    painter.setOpacity(0.8);
    painter.setBrush(QBrush(QColor(Qt::black), Qt::SolidPattern));
    painter.drawRoundedRect(rectangle, 10.0, 10.0);
    painter.setOpacity(1.0);


    // Make the rectangle 8 pixels smaller on each side before using it for texts
    rectangle.adjust(16, 8, -16, -8);


    // Draw character's name
    painter.setPen(QColor(this->characterColor));
    painter.setFont(this->dialogTextFont);
    painter.drawText(rectangle,
                     Qt::AlignLeft | Qt::AlignTop,
                     characterName);


    // Draw dialog text
    painter.setPen(QColor(Qt::white));
    painter.drawText(rectangle,
                     Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextWordWrap,
                     dialogText);




    painter.end();

    event->accept();
}
