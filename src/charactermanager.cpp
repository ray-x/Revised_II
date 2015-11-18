/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2012-2015  JanKusanagi JRR <jancoding@gmx.com>
 *             2014-2015  Ray             <ray.cn@gmail.com>
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

#include "charactermanager.h"


CharacterManager::CharacterManager(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Revised - " + tr("Character Manager"));
    this->setWindowIcon(QIcon::fromTheme("user-identity"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    this->setMinimumSize(420, 420);


    QSettings settings;
    this->resize(settings.value("characterManagerSize", QSize(480, 480)).toSize());



    QFont listFont;  // Set up the font for the list
    listFont.setBold(true);
    listFont.setPointSize(listFont.pointSize() + 1);

    characterList = new QListWidget();
    characterList->setFont(listFont);
    characterList->setStyleSheet("background: black");
    connect(characterList, SIGNAL(currentRowChanged(int)),
            this, SLOT(fillFields(int)));


    rightGroupBox = new QGroupBox(tr("Character Details"));

    characterAliasLabel = new QLabel(tr("&Alias"));
    characterAlias = new QLineEdit();
    connect(characterAlias, SIGNAL(returnPressed()),
            this, SLOT(updateCharacterInList()));
    characterAliasLabel->setBuddy(characterAlias);

    characterNameLabel = new QLabel(tr("&Name"));
    characterName = new QLineEdit();
    connect(characterName, SIGNAL(returnPressed()),
            this, SLOT(updateCharacterInList()));
    characterNameLabel->setBuddy(characterName);

    colorCodeLabel = new QLabel(tr("&Color"));
    colorCode = new QLineEdit();
    connect(colorCode, SIGNAL(returnPressed()),
            this, SLOT(updateCharacterInList()));
    colorCodeLabel->setBuddy(colorCode);

    chooseColorButton = new QPushButton(QIcon::fromTheme("color-picker"),
                                        tr("&Pick a Color"));
    connect(chooseColorButton, SIGNAL(clicked()),
            this, SLOT(getColor()));


    updateCharacterButton = new QPushButton(QIcon::fromTheme("document-save"),
                                            tr("&Update Character"));
    connect(updateCharacterButton, SIGNAL(clicked()),
            this, SLOT(updateCharacterInList()));


    addMoreCharactersButton = new QPushButton(QIcon::fromTheme("list-add"),
                                              tr("Add &More Characters"));
    connect(addMoreCharactersButton, SIGNAL(clicked()),
            this, SLOT(addMoreCharacters()));

    removeCharacterButton = new QPushButton(QIcon::fromTheme("list-remove"),
                                            tr("&Remove Selected Character"));
    connect(removeCharacterButton, SIGNAL(clicked()),
            this, SLOT(removeCharacterFromList()));



    closeAction = new QAction(this);
    closeAction->setShortcut(Qt::Key_Escape);
    connect(closeAction, SIGNAL(triggered()),
            this, SLOT(close()));
    this->addAction(closeAction);

    leftLayout = new QVBoxLayout();
    leftLayout->addWidget(characterList);
    leftLayout->addWidget(addMoreCharactersButton);
    leftLayout->addWidget(removeCharacterButton);


    rightLayout = new QVBoxLayout();
    rightLayout->addWidget(characterAliasLabel);
    rightLayout->addWidget(characterAlias);
    rightLayout->addWidget(characterNameLabel);
    rightLayout->addWidget(characterName);
    rightLayout->addWidget(colorCodeLabel);
    rightLayout->addWidget(colorCode);
    rightLayout->addWidget(chooseColorButton);
    rightLayout->addStretch(1);
    rightLayout->addWidget(updateCharacterButton);

    rightGroupBox->setLayout(rightLayout);
    rightGroupBox->setDisabled(true); // Initially disabled
                                      // Re-enabled if items are loaded

    mainLayout = new QHBoxLayout();    
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(rightGroupBox);
    this->setLayout(mainLayout);


#if 0 // TMP, for quick testing
    this->show();
    this->setFocus();
#endif

    qDebug() << "CharacterManager created";
}



CharacterManager::~CharacterManager()
{
    qDebug() << "CharacterManager destroyed";
}



void CharacterManager::loadCharactersFromRpyFile(QString filename)
{
    this->rpyFilename = filename;
    this->projectPath = QFileInfo(filename).absolutePath();

    QFile rpyFile(rpyFilename);
    rpyFile.open(QIODevice::ReadOnly);
    QString rpyFileLine;

    /*
     * File format:
     * define s = Character('Sylvie', color="#c8ffc8")
     *
     */

    QRegExp regExp = QRegExp("\\s*define\\s+(.*)\\s+=\\s+Character\\(\\s*\\'(.*)\\'\\s*,\\s*color\\s*=\\s*\\\"(.*)\\\"\\)");


    QStringList charactersNames;
    QStringList charactersAliases;
    QStringList charactersColors;


    while (!rpyFile.atEnd())    // Parse RPY file, etc.
    {
        rpyFileLine = QString::fromLocal8Bit(rpyFile.readLine());
        if (rpyFileLine.startsWith("define"))
        {            
            regExp.exactMatch(rpyFileLine);

            QStringList capturedTexts;
                                            // cap(0) is the full string
            capturedTexts << regExp.cap(1).trimmed();
            capturedTexts << regExp.cap(2).trimmed();
            capturedTexts << regExp.cap(3).trimmed();


            qDebug() << "CharacterManager::loadRPY matches" << capturedTexts;

            QListWidgetItem *item = new QListWidgetItem(capturedTexts.at(1));
            item->setData(Qt::UserRole, capturedTexts);

            item->setTextColor(QColor(capturedTexts.at(2)));

            characterList->addItem(item);


            // append character Name also to charactersNames list, for SIGNAL
            charactersNames.append(capturedTexts.at(1));
            charactersAliases.append(capturedTexts.at(0));
            charactersColors.append(capturedTexts.at(2));
        }
    }
    rpyFile.close();


    if (characterList->count() > 0) // if there are items, enable right side
    {
        rightGroupBox->setEnabled(true);

        // Send signal to update character names combobox
        emit characterListUpdated(charactersNames,
                                  charactersAliases,
                                  charactersColors);
    }


    qDebug() << "CharacterManager data loaded from" << rpyFilename << "on" << projectPath;
}






/*
 * Save all character information as ren'py character definitions
 * in the RPY file
 *
 */
void CharacterManager::saveCharactersToRpyFile()
{
    QStringList charactersNames;
    QStringList charactersAliases;
    QStringList charactersColors;

    /*
     * File format:
     * define s = Character('Sylvie', color="#c8ffc8")
     *
     */

    QString rpyFileData = "## Character definitions\n\n";

    for (int charListRow = 0; charListRow != characterList->count(); ++charListRow)
    {
        QListWidgetItem *item = characterList->item(charListRow);

        QStringList characterData = item->data(Qt::UserRole).toStringList();

        rpyFileData.append("define ");
        rpyFileData.append(characterData.at(0));
        rpyFileData.append(" = Character('" + characterData.at(1) +  "', ");
        rpyFileData.append("color=\"" + characterData.at(2) + "\")");
        rpyFileData.append("\n");


        // append character Name also to charactersNames list, for SIGNAL
        charactersNames.append(characterData.at(1));
        charactersAliases.append(characterData.at(0));
        charactersColors.append(characterData.at(2));
    }

    rpyFileData.append("\n## End of character definitions\n\n");


    QFile rpyFile(rpyFilename);
    rpyFile.open(QIODevice::WriteOnly);
    rpyFile.write(rpyFileData.toLocal8Bit());
    rpyFile.close();


    qDebug() << rpyFilename << "saved";


    emit characterListUpdated(charactersNames,
                              charactersAliases,
                              charactersColors);


    QSettings settings;
    settings.setValue("characterManagerSize", this->size());


}




QStringList CharacterManager::getAllAliases()
{
    QStringList aliasesList;
    QStringList characterData;

    for (int counter = 0; counter < this->characterList->count(); ++counter)
    {
        // Alias stored in itemData
        characterData = characterList->item(counter)->data(Qt::UserRole).toStringList();
        if (!characterData.isEmpty())
        {
            aliasesList.append(characterData.at(0));
        }
    }

    qDebug() << "CharacterManager: All aliases:" << aliasesList;

    return aliasesList;
}



/*
 * Get the character's name from the alias
 *
 */
QString CharacterManager::getCharacterName(QString alias)
{
    if (alias.isEmpty())  //
    {
        return QString();
    }


    QString name = "(null)";
    QStringList characterData;

    for (int counter = 0; counter < this->characterList->count(); ++counter)
    {
        // Name stored in itemData
        characterData = characterList->item(counter)->data(Qt::UserRole).toStringList();
        if (characterData.length() >= 3)
        {
            if (characterData.at(0) == alias)
            {
                name = characterData.at(1);
                break;
            }
        }
    }


    return name;
}


/*
 * Get the character's color from the alias
 *
 */
QString CharacterManager::getCharacterColor(QString alias)
{
    QString color = "#FFFFFF";  // default, in case it's not set
    QStringList characterData;

    for (int counter = 0; counter < this->characterList->count(); ++counter)
    {
        // Color stored in itemData
        characterData = characterList->item(counter)->data(Qt::UserRole).toStringList();
        if (characterData.length() >= 3)
        {
            if (characterData.at(0) == alias)
            {
                color = characterData.at(2);
                break;
            }
        }
    }


    return color;
}


//////////////////////////// PROTECTED ////////////////////////////////



/*
 * On close, save all character information
 *
 */
void CharacterManager::closeEvent(QCloseEvent *event)
{
    this->saveCharactersToRpyFile();

    event->accept();
}



//////////////////////////////// SLOTS /////////////////////////////////




void CharacterManager::fillFields(int row)
{
    qDebug() << "fillFields() from row:" << row << " / " << characterList->count();


    if (row < 0)
    {
        // Avoid crash
        return;
    }


    if (characterList->count() < 1)  // List just became empty
    {
        // Gets here after removing last item, just clear the fields and disable
        qDebug() << "List is empty, aborting fillFields()";

        return;
    }


    QStringList characterData = characterList->item(row)->data(Qt::UserRole).toStringList();

    this->characterAlias->setText(characterData.at(0));
    this->characterName->setText(characterData.at(1));
    this->colorCode->setText(characterData.at(2));
}





void CharacterManager::getColor()
{
    QColor characterColor = QColorDialog::getColor(QColor(colorCode->text()),
                                                this,
                                                tr("Choose the color for this player's name"));

    if (characterColor.isValid())
    {
        this->colorCode->setText(characterColor.name());
    }
    else
    {
        qDebug() << "Invalid color:" << characterColor;
    }
}





void CharacterManager::updateCharacterInList()
{
    if (!characterList->currentItem())
    {
        qDebug() << "updateCharacter(), no currentItem()";
        return;
    }


    QStringList characterData;
    characterData.append(this->characterAlias->text());
    characterData.append(this->characterName->text());
    characterData.append(this->colorCode->text());

    // Set visible name
    characterList->currentItem()->setText(characterData.at(1));

    // Set color of text in list to character's color
    characterList->currentItem()->setTextColor(QColor(characterData.at(2)));

    // and set internal data (3 fields)
    characterList->currentItem()->setData(Qt::UserRole,
                                          characterData);


    qDebug() << "Character data updated in list with:" << characterData;

}




void CharacterManager::removeCharacterFromList()
{
    if (!characterList->currentItem())
    {
        // if currentItem is NULL
        qDebug() << "Character list is empty or nothing is selected";
        return;
    }

    delete characterList->currentItem();
    qDebug() << "Removed character;" << characterList->count() << "left";

    if (characterList->count() <= 0)
     {
         qDebug() << "Character list just got empty";

         this->characterAlias->clear();
         this->characterName->clear();
         this->colorCode->clear();

         this->rightGroupBox->setDisabled(true);
     }

}




void CharacterManager::addMoreCharacters()
{
    QListWidgetItem *item = new QListWidgetItem(tr("New Character"));
    item->setData(Qt::UserRole, QStringList() << "nc" << tr("New Character") << "#FFFFFF");
    item->setTextColor(QColor("#FFFFFF"));
    characterList->addItem(item);
    characterList->setCurrentRow(characterList->count() - 1);

    rightGroupBox->setEnabled(true);  // Re-enable controls, just in case

    characterAlias->setFocus();  // Give focus to the first field
    characterAlias->selectAll(); // and select contents, for convenience
}



/*
 * Clear all the fields, leave CM ready for next loaded project
 *
 */
void CharacterManager::clear()
{
    this->characterList->clear();


    this->characterAlias->clear();
    this->characterName->clear();
    this->colorCode->clear();

    rightGroupBox->setDisabled(true);

    this->hide(); // hide, to avoid possible closeEvent() afterwards
}
