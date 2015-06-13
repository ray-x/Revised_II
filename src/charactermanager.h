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

#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QIcon>
#include <QFile>
#include <QFileInfo>
#include <QColor>
#include <QColorDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QAction>
#include <QFont>

#include <QSettings>
#include <QCloseEvent>

#include <QDebug>

class CharacterManager : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterManager(QWidget *parent = 0);
    ~CharacterManager();

    void loadCharactersFromRpyFile(QString filename);
    void saveCharactersToRpyFile();

    QStringList getAllAliases();
    QString getCharacterName(QString alias);
    QString getCharacterColor(QString alias);


signals:
    void characterListUpdated(QStringList charactersNames,
                              QStringList charactersAliases,
                              QStringList charactersColors);


public slots:
    void fillFields(int row);

    void getColor();

    void updateCharacterInList();
    void removeCharacterFromList();

    void addMoreCharacters();

    void clear();

protected:
    virtual void closeEvent(QCloseEvent *event);


private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;

    QListWidget *characterList;

    QGroupBox *rightGroupBox;

    QLabel *characterAliasLabel;
    QLineEdit *characterAlias;

    QLabel *characterNameLabel;
    QLineEdit *characterName;

    QLabel *colorCodeLabel;
    QLineEdit *colorCode;
    QPushButton *chooseColorButton;

    QPushButton *updateCharacterButton;

    QPushButton *addMoreCharactersButton;
    QPushButton *removeCharacterButton;

    QAction *closeAction;

    QString rpyFilename;
    QString projectPath;

};

#endif // CHARACTERMANAGER_H
