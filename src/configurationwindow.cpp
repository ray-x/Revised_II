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

#include "configurationwindow.h"

ConfigurationWindow::ConfigurationWindow(QString renpyExecutable,
                                         QString projectsFolder,
                                         QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Revised - " + tr("Configuration"));
    this->setWindowIcon(QIcon::fromTheme("configure"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    this->setMinimumSize(480, 140);



    renpyExecutableLineEdit = new QLineEdit(renpyExecutable);
    renpyExecutableLineEdit->setPlaceholderText(tr("Executable with path, "
                                                   "like /usr/games/renpy"));

    projectsFolderLineEdit = new QLineEdit(projectsFolder);
    projectsFolderLineEdit->setPlaceholderText(tr("Default folder for "
                                                  "new projects"));

    okButton = new QPushButton(QIcon::fromTheme("dialog-ok"),
                               tr("&OK"));
    okButton->setDefault(true);
    connect(okButton, SIGNAL(clicked()),
            this, SLOT(saveConfiguration()));

    cancelButton = new QPushButton(QIcon::fromTheme("dialog-cancel"),
                                   tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));

    closeAction = new QAction(this);
    closeAction->setShortcut(Qt::Key_Escape);
    connect(closeAction, SIGNAL(triggered()),
            this, SLOT(close()));
    this->addAction(closeAction);


    upperLayout = new QFormLayout();
    upperLayout->addRow(tr("Ren'Py executable"),
                        renpyExecutableLineEdit);
    upperLayout->addRow(tr("Default project folder"),
                        projectsFolderLineEdit);

    lowerLayout = new QHBoxLayout();
    lowerLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    lowerLayout->addWidget(okButton);
    lowerLayout->addWidget(cancelButton);


    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);
    this->setLayout(mainLayout);

    qDebug() << "ConfigurationWindow created";
}


ConfigurationWindow::~ConfigurationWindow()
{
    delete(lowerLayout);
    delete(upperLayout);
    delete(renpyExecutableLineEdit);
    delete(projectsFolderLineEdit);
    delete(okButton);
    delete(cancelButton);
    delete(mainLayout);
    delete(closeAction);
    qDebug() << "ConfigurationWindow destroyed";
}




///////////////////////////////// SLOTS //////////////////////////////////////



void ConfigurationWindow::saveConfiguration()
{
    if (renpyExecutableLineEdit->text().isEmpty()
     || projectsFolderLineEdit->text().isEmpty())
    {
        qDebug() << "ConfigurationWindow: One or more fields are invalid";
        return;
    }


    emit configurationChanged(this->renpyExecutableLineEdit->text(),
                              this->projectsFolderLineEdit->text());

    this->close();

    qDebug() << "Configuration updated";
}
