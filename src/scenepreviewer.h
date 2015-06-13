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

#ifndef SCENEPREVIEWER_H
#define SCENEPREVIEWER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QDebug>


class ScenePreviewer : public QWidget
{
    Q_OBJECT

public:
    explicit ScenePreviewer(QWidget *parent = 0);
    ~ScenePreviewer();

    void setBackgroundImage(QString filename);
    void addOtherImage(QString filename, QString alignment = "center");
    void setDialogText(QString name, QString color, QString text);


    void clear();

signals:

protected:
    virtual void paintEvent(QPaintEvent *event);
    
public slots:


private:
    QString backgroundImage;
    QStringList otherImages;
    QStringList otherImagesAlignments;

    QString characterName;
    QString characterColor;
    QString dialogText;

    QFont dialogTextFont;

};

#endif // SCENEPREVIEWER_H
