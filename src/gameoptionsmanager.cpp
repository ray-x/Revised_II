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

#include "gameoptionsmanager.h"

GameOptionsManager::GameOptionsManager(QWidget *parent) :  QWidget(parent)
{
    this->setWindowTitle("Revised - " + tr("Game Options Manager"));
    this->setWindowIcon(QIcon::fromTheme("games-config-options"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    this->setMinimumSize(380, 180);



    //// Form at the top
    configWindowTitle = new QLineEdit();
    configWindowTitle->setPlaceholderText(tr("Title of the game's window"));
    configScreenWidth = new QLineEdit();
    configScreenWidth->setPlaceholderText(tr("Width of the game's window. 800, 1024, etc."));
    configScreenHeight = new QLineEdit();
    configScreenHeight->setPlaceholderText(tr("Hight of the game's window. 600, 768, etc."));


    // Default values
    this->configWindowTitle->setText("-");
    this->configScreenWidth->setText("800");
    this->configScreenHeight->setText("600");


    formLayout = new QFormLayout();
    formLayout->addRow(tr("Window &title"), configWindowTitle);
    formLayout->addRow(tr("Screen &width"), configScreenWidth);
    formLayout->addRow(tr("Screen &height"), configScreenHeight);


    //// Buttons at the bottom
    okButton = new QPushButton(QIcon::fromTheme("dialog-ok"),
                               tr("&OK"));
    connect(okButton, SIGNAL(clicked()),
            this, SLOT(close()));
    cancelButton = new QPushButton(QIcon::fromTheme("dialog-cancel"),
                                   tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));

    closeAction = new QAction(this);
    closeAction->setShortcut(Qt::Key_Escape);
    connect(closeAction, SIGNAL(triggered()),
            this, SLOT(close()));
    this->addAction(closeAction);


    bottomLayout = new QHBoxLayout();
    bottomLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(cancelButton);


    //// General layout
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);



    qDebug() << "GameOptionsManager created";
}


GameOptionsManager::~GameOptionsManager()
{
    qDebug() << "GameOptionsManager destroyed";
}



/*
 * Load and parse all game options information from options.rpy
 *
 */
void GameOptionsManager::loadOptionsFromRpyFile(QString path)
{
    // options.rpy file format:

    // init -1:
    //    python hide:
    //        config.window_title = u"Some Title"
    //        config.screen_width = 800
    //        config.screen_height = 600


    this->projectPath = path;


    QFile rpyFile(projectPath + "/options.rpy");
    rpyFile.open(QIODevice::ReadOnly);
    QString rpyFileLine;

    while (!rpyFile.atEnd())
    {
        rpyFileLine = QString::fromLocal8Bit(rpyFile.readLine()).trimmed();

        if (rpyFileLine.startsWith("config.window_title"))
        {
            qDebug() << "config.window_title found:" << rpyFileLine;

            QRegExp regExp("config\\.window_title\\s+=\\s+u\\\"(.*)\\\"");
            regExp.exactMatch(rpyFileLine);

            this->configWindowTitle->setText(regExp.cap(1));
        }

        if (rpyFileLine.startsWith("config.screen_width"))
        {
            qDebug() << "config.screen_width found:" << rpyFileLine;

            QRegExp regExp("config\\.screen_width\\s+=\\s+(.*)");
            regExp.exactMatch(rpyFileLine);

            this->configScreenWidth->setText(regExp.cap(1));
        }

        if (rpyFileLine.startsWith("config.screen_height"))
        {
            qDebug() << "config.screen_height found:" << rpyFileLine;

            QRegExp regExp("config\\.screen_height\\s+=\\s+(.*)");
            regExp.exactMatch(rpyFileLine);

            this->configScreenHeight->setText(regExp.cap(1));
        }

    }

    rpyFile.close();


    qDebug() << projectPath + "/options.rpy loaded and parsed";


}


/*
 * Save all game options information in the options.rpy file
 *
 */
void GameOptionsManager::saveOptionsToRpyFile()
{
    // options.rpy file format:

    // init -1:
    //    python hide:
    //        config.window_title = u"Some Title"
    //        config.screen_width = 800
    //        config.screen_height = 600


    QString rpyFileData = "## Game Options\n\n";
    rpyFileData.append("init -1:\n");
    rpyFileData.append("    python hide:\n");


    rpyFileData.append(QString("        config.window_title = u\"%1\"\n").arg(this->configWindowTitle->text()));
    rpyFileData.append(QString("        config.screen_width = %1\n").arg(this->configScreenWidth->text()));
    rpyFileData.append(QString("        config.screen_height = %1\n").arg(this->configScreenHeight->text()));


    rpyFileData.append("\n## End of image definitions\n\n");


    QFile rpyFile(projectPath + "/options.rpy");
    rpyFile.open(QIODevice::WriteOnly);
    rpyFile.write(rpyFileData.toLocal8Bit());
    rpyFile.close();


    qDebug() << projectPath + "/options.rpy saved";
}



//////////////////////////// SLOTS /////////////////////////////////////






/////////////////////////// PROTECTED ///////////////////////////////////



/*
 * On close, save all game options
 *
 */
void GameOptionsManager::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("gameOptionsManagerSize", this->size());


    this->saveOptionsToRpyFile();


    event->accept();
}
