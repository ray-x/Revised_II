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

#include "scenepreviewer.h"
#include <QFileInfo>

ScenePreviewer::ScenePreviewer(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(640, 480);


    // Set up font for dialog lines preview
    dialogTextFont.setBold(true);
    dialogTextFont.setPointSize(dialogTextFont.pointSize() + 6);


    // Initial background
    //this->backgroundImage = ":/images/library.png";
    mObject = new GameObject(nullptr,QString("newGO"));

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
#if 0
    QString singleImage("C:\\TEMP\\Robocop.jpg");
    QPixmap singleImagePixmap = QPixmap(singleImage);
    painter.drawPixmap(30, 80,
        singleImagePixmap.width(), singleImagePixmap.height(),
        singleImagePixmap);

#endif
#if 0
    QString singleImage("C:\\TEMP\\monsters.png");
    QPixmap singleImagePixmap = QPixmap(singleImage);
    GameObject *ob=new GameObject(0, "GameObject", &singleImagePixmap);
    //ob->paint(painter);
    mObject = ob;
    if (mObject)
        paintObject(painter);
#endif 
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


void ScenePreviewer::paintObject(QPainter & ppaint)
{
    if (!mObject)
        return;

    //ppaint.fillRect(0, 0, width(), height(), Qt::gray);
    mObject->paint(ppaint);
    //drawSelection(painter, mObject->selectedObject()); TODO:
    drawSelection(ppaint, mObject);
}
void ScenePreviewer::drawSelection(QPainter& painter, GameObject* object)
{
    if (!object)
        return;

    QRectF rectf = object->sceneRect();
    painter.drawRect(rectf);

    QBrush brush(QColor(255, 0, 0));
    QPen pen;
    pen.setWidth(1);
    painter.save();
    painter.setPen(pen);

    QList<QRect> rects = object->resizeRects();
    foreach(const QRect& rect, rects) {
        painter.fillRect(rect, brush);
        painter.drawRect(rect);
    }

    painter.restore();
}

void ScenePreviewer::mousePressEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    qreal x = event->x(), y = event->y();
    GameObject * object = 0;
    mMousePressed = true;

    if (mObject) {
        mObject->selectObjectAt(x, y);
        object = mObject->selectedObject();
    }
    /*
    else if (mSceneManager->currentScene()) {
        mSceneManager->currentScene()->selectObjectAt(x, y);
        object = mSceneManager->currentScene()->selectedObject();
    }
    */
    if (mCanResize)
        mResizing = true;
    else if (mCanMove) {
        setCursor(Qt::ClosedHandCursor);
        mMoving = true;
    }
    /*
    if (object)
        emit selectionChanged(object);
    else if (mObject)
        emit selectionChanged(mObject);
    else
        emit selectionChanged(0);
        */
    update();

    QWidget::mousePressEvent(event);
}

void ScenePreviewer::mouseReleaseEvent(QMouseEvent * event)
{
    bool resizing = mResizing;
    bool moving = mMoving;
    GameObject* object = selectedObject();

    mMousePressed = false;
    mResizing = false;
    mCanResize = false;
    mMoving = false;

    if (object) {
        if (resizing)
            object->stopResizing();
        if (moving)
            object->stopMove();
        if (object->contains(event->x(), event->y()))
            setCursor(Qt::OpenHandCursor);
        else
            setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseReleaseEvent(event);
}

void ScenePreviewer::mouseMoveEvent(QMouseEvent * event)
{
    GameObject* object = selectedObject();
    qreal x = event->x(), y = event->y();
    int i;

    object = mObject;
    //if moving or resizing an object
    if (object && (mResizing || mMoving)) {
        if (mResizing) {
            object->resize(x, y);
        }
        else if (mMoving)
            object->dragMove(x, y);
        update();
        return;
    }

    //get hovered object at x, y, if any
    //TODO¡¡FIXME¡¡object = objectAt(x, y);
    object = mObject;

    mCanMove = false;
    mCanResize = false;

    if (!object) {
        if (cursor().shape() != Qt::UpArrowCursor)
            setCursor(Qt::UpArrowCursor);
        return;
    }

    QList<QRect> rects = object->resizeRects();
    for (i = 0; i < rects.size(); i++) {
        if (rects.at(i).contains(x, y))
            break;
    }

    object->setHoveredResizeRect(i);

    //if cursor is not hovering one of the rectangles, move the object
    if (i == rects.size()) {
        mCanMove = object->contains(x, y);
        if (mCanMove)
            setCursor(Qt::OpenHandCursor);
        else
            setCursor(Qt::ArrowCursor);
    }
    else {

        if (i % 2 == 0) {
            if (i == 0 || i == 4)
                setCursor(Qt::SizeFDiagCursor);
            else
                setCursor(Qt::SizeBDiagCursor);
        }
        else {
            if (i == 1 || i == 5)
                setCursor(Qt::SizeVerCursor);
            else
                setCursor(Qt::SizeHorCursor);
        }

        mCanResize = true;
    }
}

GameObject *ScenePreviewer::selectedObject()
{
    if (mObject)
        return mObject->selectedObject();
 //   else if (mSceneManager && mSceneManager->currentScene())
 //       return mSceneManager->currentScene()->selectedObject();
    return 0;
}

GameObject* ScenePreviewer::objectAt(qreal x, qreal y)
{
    if (mObject)
        return mObject->objectAt(x, y);
 //   else if (mSceneManager && mSceneManager->currentScene())
 //       return mSceneManager->currentScene()->objectAt(x, y);
    return 0;
}
/*
void ScenePreviewer::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    setFixedSize(event->size());
    //mSceneManager->onResizeEvent(event);
    }*/

