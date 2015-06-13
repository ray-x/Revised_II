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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTabWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDate>
#include <QToolBar>
#include <QDesktopServices>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QStandardPaths>
#endif

#include <QUrl>
#include <QProcess>

#include <QDebug>


#include "chapterlist.h"
#include "scenedesigner.h"
#include "codeeditor.h"

#include "configurationwindow.h"

#include "charactermanager.h"
#include "imagemanager.h"
#include "ProjectMgr.h"
#include "gameoptionsmanager.h"


class MainWindow : public QMainWindow
{
	friend class ProjectMgr;
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createMenus();
    void createOpenRecentMenu();

    void loadSettings();
    void saveSettings();

    void loadProjectFiles(QString path);
    void enableMenusAndWidgets(bool state);
    void createActions();

public slots:
    void createNewProject();
    void openProject(QString projFile="");
    void openRecentProject();
    void saveProject();
	void storySaveAs();
    void closeProject();
    void ImportProject();

    void runProject();

    void updateConfiguration(QString executable,
                             QString folder);

    void visitWebsite();
    void goToRenpyDoc();
    void aboutRevised();


protected:
    virtual void closeEvent(QCloseEvent *event);


private:
    QString programIdleTitle;

    // Splitter to act as main layout
    QSplitter *mainSplitter;

    // Menu structure
    QMenu *fileMenu;

    QAction *fileNew;
    QAction *fileOpen;
    QAction *fileSave;
    QAction *fileSaveAs;
    QAction *fileClose;
    QAction *fileQuit;

    QMenu *fileOpenRecentMenu;


    QMenu *projectMenu;

    QAction *projectRunGame;
    QAction *projectDefineCharacters;
    QAction *projectDefineImages;
    QAction *projectDefineOptions;


    QMenu *sceneMenu;

    QAction *sceneSetBackground;
    QAction *sceneAddCharacter;
    QAction *sceneAddDialogText;

    QMenu *settingsMenu;

    QAction *settingsConfiguration;


    QMenu *helpMenu;

    QAction *helpWebsite;
    QAction *helpRenpyDoc;
    QAction *helpAbout;


    // Chapter list
    ChapterList *chapterList;

    // Tabs
    QTabWidget *tabWidget;


    // Visual scene designer
    SceneDesigner *sceneDesigner;

    // Code editor
    CodeEditor *codeEditor;


    // Add begin
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *ctlToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *closeAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QAction *exeAct;
    QAction *rollbackAct;
    QAction *backAct;
    QAction *bgAct;
    // Add end

    // Configuration window
    ConfigurationWindow *configWindow;

    // Character manager
    CharacterManager *characterManager;

    // Image manager
    ImageManager *imageManager;

    // Game Options manager
    GameOptionsManager *gameOptionsManager;


    // Program variables
    QString renpyExecutable;
    QString projectsFolder;
    QStringList recentlyOpenedFiles;

    // Project stuff
    QString projectName;
    QString projectDirectory;
    QString projectPath;
	QString projectFile;


    QStringList fileList;

	ProjectMgr *projectmgr;

};


#endif // MAINWINDOW_H
