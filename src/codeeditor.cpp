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

#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) :  QTextEdit(parent)
{
    this->setTabChangesFocus(true);  // Disable tabulations


    // TMP, read-only until code editor becomes useful (if ever! xD)
    //this->setReadOnly(true);


    qDebug() << "CodeEditor created";
}


CodeEditor::~CodeEditor()
{
    qDebug() << "CodeEditor destroyed";
}



/////////////////////////////// SLOTS ////////////////////////////////////


void CodeEditor::loadChapter(Chapter *chapter)
{        
    QFile scriptFile(chapter->getScriptFilename());
    scriptFile.open(QIODevice::ReadOnly);
    this->setText(QString::fromLocal8Bit(scriptFile.readAll()));
    scriptFile.close();

    qDebug() << "CodeEditor loaded chapter" << chapter->getScriptFilename();
}
