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

#include <QApplication>
#include <QTranslator>
#include <QString>
#include <iostream>


#include "mainwindow.h"



#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
void customMessageHandlerQt4(QtMsgType type, const char *msg)
{
    // do nothing
    Q_UNUSED(type)
    Q_UNUSED(msg)

    return;
}
#else
void customMessageHandlerQt5(QtMsgType type,
                             const QMessageLogContext &context,
                             const QString &msg)
{
    Q_UNUSED(type)
    Q_UNUSED(context)
    Q_UNUSED(msg)

    // Do nothing

    return;
}
#endif



int main(int argc, char *argv[])
{
    QApplication revisedApp(argc, argv);

    revisedApp.setApplicationName("Revised");
    revisedApp.setApplicationVersion("0.2");
    revisedApp.setOrganizationName("JanCoding");
    revisedApp.setOrganizationDomain("jancoding.wordpress.com");

    std::cout << QString("Revised v%1 - Copyright 2012-2015  JanKusanagi\n"
                         "http://jancoding.wordpress.com/revised\n\n")
                 .arg(revisedApp.applicationVersion()).toStdString();
    std::cout << QString("- Built with Qt v%1 on %2, %3\n")
                 .arg(QT_VERSION_STR)
                 .arg(__DATE__)
                 .arg(__TIME__).toStdString();
    std::cout << QString("- Running with Qt v%1\n\n").arg(qVersion()).toStdString();
    std::cout.flush();

    QStringList cmdLine = qApp->arguments();
    cmdLine.removeFirst();

    bool debugMode = false;

    QString pathToProject;

    // Register custom message handler, to hide debug messages unless specified
    if (!cmdLine.isEmpty())
    {
        foreach (QString argument, cmdLine)
        {
            // Help
            if (argument.startsWith("--help", Qt::CaseInsensitive))
            {
                std::cout << "Help:\n";
                std::cout << "    " << argv[0]
                          << " [options] [projectFolder]\n\n\n";
                std::cout << "Options:\n";
                std::cout << "    --debug    Show debug messages in terminal "
                             "while running\n\n";


                return 0; // Exit to shell
            }

            // Debug mode
            if (argument.startsWith("--debug", Qt::CaseInsensitive))
            {
                debugMode = true;
                cmdLine.removeAll(argument);

                std::cout << "Debug messages enabled\n";
            }
        }

        // If there are some unrecognized parameters. assume a path to project
        if (cmdLine.length() > 0)
        {
            pathToProject = cmdLine.at(0);

            std::cout << QString("Trying to load project from %1\n\n")
                         .arg(pathToProject).toStdString();
            std::cout.flush();
        }

    }


    if (!debugMode)
    {
        std::cout << "To see debug messages while running, use --debug\n";

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        qInstallMsgHandler(customMessageHandlerQt4);
#else
        qInstallMessageHandler(customMessageHandlerQt5);
#endif

    }




    // Enable localization
    QTranslator translator;
    QString languageFile;
    // get LANG environment variable, and generate the resource filename
    languageFile = QString(":/translations/revised_%1")
                   .arg(qgetenv("LANG").constData());
    std::cout << "Language file:" << languageFile.toStdString() << "\n";

    translator.load(languageFile);
    revisedApp.installTranslator(&translator);

    std::cout.flush();


    MainWindow revisedWindow;
	if (!pathToProject.isEmpty()) // If there's a path in the command line
	{
		revisedWindow.loadProjectFiles(pathToProject);
	}


	revisedWindow.setWindowFlags(revisedWindow.windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

	revisedWindow.showMaximized();
    revisedWindow.show();

    
    return revisedApp.exec();
}
