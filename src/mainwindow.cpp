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


#include "mainwindow.h"
#include "projectmgr.h"
/*
 * Constructor
 *
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->programIdleTitle = "Revised - " + tr("Visual Editor for Ren'Py");

    this->setWindowTitle(programIdleTitle);
    this->setWindowIcon(QIcon(":/icon/64x64/revised.png"));


    characterManager = new CharacterManager(this);
    imageManager = new ImageManager(this);
    gameOptionsManager = new GameOptionsManager(this);


    // Visual scene designer: set background, characters, texts, menus...
    sceneDesigner = new SceneDesigner(characterManager, imageManager);

    // Code Editor with ren'py (and some python) syntax hightlighting
    codeEditor = new CodeEditor();


    chapterList = new ChapterList(characterManager);
    connect(chapterList, SIGNAL(chapterChanged(Chapter*)),
            sceneDesigner, SLOT(loadChapter(Chapter*)));
    connect(chapterList, SIGNAL(chapterChanged(Chapter*)),
            codeEditor, SLOT(loadChapter(Chapter*)));
    connect(chapterList, SIGNAL(stepRenderRequest(Step*)),
            sceneDesigner, SLOT(renderStep(Step*)));


    tabWidget = new QTabWidget(this);
    tabWidget->addTab(sceneDesigner, QIcon::fromTheme("view-preview"),
                      tr("&Visual"));
    tabWidget->addTab(codeEditor, QIcon::fromTheme("code-block"),
                      tr("&Code Editor"));
    tabWidget->setTabPosition(QTabWidget::West);

    createActions();
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
	fileToolBar->addAction(saveAsAct);

    editToolBar = addToolBar(tr("Edit"));
    //editToolBar->addAction(cutAct);
    //editToolBar->addAction(copyAct);
    //editToolBar->addAction(pasteAct);


    ctlToolBar= addToolBar(tr("Control"));
    ctlToolBar->addAction(exeAct);
    //ctlToolBar->addAction(rollbackAct);
    //ctlToolBar->addAction(backAct);
    ctlToolBar->addAction(bgAct);
	ctlToolBar->addAction(characterAct);

    mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->setChildrenCollapsible(false);
    mainSplitter->addWidget(chapterList);
    mainSplitter->addWidget(tabWidget);

    this->setCentralWidget(mainSplitter);


    loadSettings();

    configWindow = new ConfigurationWindow(this->renpyExecutable,
                                           this->projectsFolder);
    connect(configWindow, SIGNAL(configurationChanged(QString,QString)),
            this, SLOT(updateConfiguration(QString,QString)));



    // Populate the menu bar
    createMenus();

    // Ensure relevant menus are disabled, etc.
    closeProject();


    this->statusBar()->showMessage("Work in progress...");
	projectmgr = nullptr;
	this->showFullScreen();
    qDebug() << "Ren'Py executable:" << this->renpyExecutable;

    qDebug() << "MainWindow created\n=================================\n";
}



/*
 * Destructor
 *
 */
MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroyed";
}


void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, SIGNAL(triggered()), this, SLOT(createNewProject()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openProject()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveProject()));

    //saveAsAct = new QAction(tr("Save &As..."), this);


	saveAsAct = new QAction(QIcon(":/images/saveas.png"), tr("Save &As..."), this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(storySaveAs()));

    closeAct = new QAction(tr("&Close"), this);
    closeAct->setShortcut(tr("Ctrl+W"));
    closeAct->setStatusTip(tr("Close this window"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
	
    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

	aboutAct = new QAction(QIcon("About"),tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	
    exeAct = new QAction(QIcon(":/images/media-play-32.png"), tr("Run"), this);
    exeAct->setStatusTip(tr("Run Renpy with give settings"));
	connect(exeAct, SIGNAL(triggered()), this, SLOT(runProject()));
	
    rollbackAct = new QAction(QIcon(":/images/editundo.png"), tr("rollback"), this);
    rollbackAct->setStatusTip(tr("Going forward"));
    connect(rollbackAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    backAct = new QAction(QIcon(":/images/arrow.png"), tr("back"), this);
    backAct->setStatusTip(tr("Going back"));
    connect(backAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    bgAct = new QAction(QIcon(":/images/icon.png"), tr("background"), this);
    bgAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(bgAct, SIGNAL(triggered()), imageManager, SLOT(showSetBackground()));
	//connect(projectDefineImages, SIGNAL(triggered()),imageManager, SLOT(showForEditing()));


	characterAct = new QAction(QIcon(":/images/UserIcon.png"), tr("&Character"), this);
	characterAct->setStatusTip(tr("Show the application's About box"));
	connect(characterAct, SIGNAL(triggered()),	characterManager, SLOT(show()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    /*connect(textEdit, SIGNAL(copyAvailable(bool)),
            this, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));*/
}


void MainWindow::createMenus()
{
    // File

    fileNew = new QAction(QIcon::fromTheme("document-new"),
                           tr("&New Game"), this);
    fileNew->setShortcut(QKeySequence::New);
    connect(fileNew, SIGNAL(triggered()),
            this, SLOT(createNewProject()));

    fileOpen = new QAction(QIcon::fromTheme("document-open"),
                           tr("&Open"), this);
    fileOpen->setShortcut(QKeySequence::Open);
    connect(fileOpen, SIGNAL(triggered()),
            this, SLOT(openProject()));

    fileSave = new QAction(QIcon::fromTheme("document-save"),
                           tr("&Save"), this);
    fileSave->setShortcut(QKeySequence::Save);
    connect(fileSave, SIGNAL(triggered()),
            this, SLOT(saveProject()));


    fileSaveAs = new QAction(QIcon::fromTheme("document-save-as"),
                           tr("Save &As..."), this);
    fileSaveAs->setShortcut(QKeySequence::SaveAs);

    fileClose = new QAction(QIcon::fromTheme("document-close"),
                            tr("&Close"), this);
    fileClose->setShortcut(QKeySequence::Close);
    connect(fileClose, SIGNAL(triggered()),
            this, SLOT(closeProject()));


    fileQuit = new QAction(QIcon::fromTheme("application-exit"),
                           tr("&Quit"), this);
    fileQuit->setShortcut(QKeySequence::Quit);
    fileQuit->setStatusTip(tr("Exit Revised"));
    connect(fileQuit, SIGNAL(triggered()),
            qApp, SLOT(closeAllWindows()));


    // "Open Recent" sub-menu, for recently opened files list
    fileOpenRecentMenu = new QMenu(tr("Open &Recent"));
    fileOpenRecentMenu->setIcon(QIcon::fromTheme("document-open-recent"));
    fileOpenRecentMenu->setDisabled(true); // Disable it until it gets populated


    fileMenu = new QMenu(tr("&File"));
    fileMenu->addAction(fileNew);
    fileMenu->addAction(fileOpen);
    fileMenu->addMenu(fileOpenRecentMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(fileClose);
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuit);

    this->menuBar()->addMenu(fileMenu);


    // Project
    projectRunGame = new QAction(QIcon::fromTheme("system-run"),
                                 tr("&Run Game"),
                                 this);
    projectRunGame->setShortcut(QKeySequence("Ctrl+R"));
    projectRunGame->setStatusTip(tr("Run the game in Ren'Py"));
    connect(projectRunGame, SIGNAL(triggered()),
            this, SLOT(runProject()));

    projectDefineCharacters = new QAction(QIcon::fromTheme("user-identity"),
                                          tr("Define &Characters"),
                                          this);
    projectDefineCharacters->setStatusTip(tr("Define alias for characters in "
                                             "the game, with their name color"));
    connect(projectDefineCharacters, SIGNAL(triggered()),
            characterManager, SLOT(show()));

    projectDefineImages = new QAction(QIcon::fromTheme("folder-image"),
                                          tr("Define &Images"),
                                          this);
    projectDefineImages->setShortcut(QKeySequence("Ctrl+I"));
    projectDefineImages->setStatusTip(tr("Define the images used in the game"));
    connect(projectDefineImages, SIGNAL(triggered()),
            imageManager, SLOT(showForEditing()));

    projectDefineOptions = new QAction(QIcon::fromTheme("games-config-options"),
                                          tr("Define Game &Options"),
                                          this);
    projectDefineOptions->setStatusTip(tr("Define general game parameters like "
                                          "resolution or window title"));
    connect(projectDefineOptions, SIGNAL(triggered()),
            gameOptionsManager, SLOT(show()));


    projectMenu = new QMenu(tr("&Project"));
    projectMenu->addAction(projectRunGame);
    projectMenu->addSeparator();
    projectMenu->addAction(projectDefineCharacters);
    projectMenu->addAction(projectDefineImages);
    projectMenu->addAction(projectDefineOptions);


    this->menuBar()->addMenu(projectMenu);


    // Scene
    sceneSetBackground = new QAction(QIcon::fromTheme("insert-image"),
                                     tr("Set &Background Image"),
                                     this);
    sceneAddCharacter = new QAction(QIcon::fromTheme("list-add-user"),
                                     tr("Add &Character"),
                                     this);
    sceneAddDialogText = new QAction(QIcon::fromTheme("insert-text"),
                                     tr("Add &Dialog Text"),
                                     this);

    sceneMenu = new QMenu(tr("&Scene"));
    sceneMenu->addAction(sceneSetBackground);
    sceneMenu->addSeparator();
    sceneMenu->addAction(sceneAddCharacter);
    sceneMenu->addAction(sceneAddDialogText);

    this->menuBar()->addMenu(sceneMenu);


    settingsConfiguration = new QAction(QIcon::fromTheme("configure"),
                                        tr("&Configure Revised"),
                                        this);
    settingsConfiguration->setStatusTip(tr("General program configuration"));
    connect(settingsConfiguration, SIGNAL(triggered()),
            configWindow, SLOT(show()));

    settingsMenu = new QMenu(tr("S&ettings"));
    settingsMenu->addAction(settingsConfiguration);

    this->menuBar()->addMenu(settingsMenu);


    // Help

    helpWebsite = new QAction(QIcon::fromTheme("internet-web-browser"),
                            tr("Visit &Website"),
                              this);
    connect(helpWebsite, SIGNAL(triggered()),
            this, SLOT(visitWebsite()));

    helpRenpyDoc = new QAction(QIcon::fromTheme("documentation"),
                            tr("&Ren'Py Documentation") + " [renpy.org]",
                               this);
    helpRenpyDoc->setStatusTip(tr("Go to Ren'Py's Documentation on the web"));
    connect(helpRenpyDoc, SIGNAL(triggered()),
            this, SLOT(goToRenpyDoc()));


    helpAbout = new QAction(QIcon::fromTheme("help-about"),
                            tr("&About Revised..."),
                            this);
    connect(helpAbout, SIGNAL(triggered()),
            this, SLOT(aboutRevised()));

    helpMenu = new QMenu(tr("&Help"));
    helpMenu->addAction(helpWebsite);
    helpMenu->addAction(helpRenpyDoc);
    helpMenu->addSeparator();
    helpMenu->addAction(helpAbout);

    this->menuBar()->addMenu(helpMenu);


    this->createOpenRecentMenu();
}



/*
 * Populate Open Recent menu from the saved list
 *
 */
void MainWindow::createOpenRecentMenu()
{
    fileOpenRecentMenu->clear();

    foreach (QString recentProjectPath, this->recentlyOpenedFiles)
    {
        QAction *openRecentAction;
        openRecentAction = new QAction(recentProjectPath, this);
        connect(openRecentAction, SIGNAL(triggered()),
                this, SLOT(openRecentProject()));

        fileOpenRecentMenu->addAction(openRecentAction);
    }

    fileOpenRecentMenu->setEnabled(true);
}




void MainWindow::loadSettings()
{
    QSettings settings;

    //this->resize(settings.value("mainWindowSize", QSize(1024, 768)).toSize());
    this->mainSplitter->restoreState(settings.value("mainSplitterState").toByteArray());
	
    renpyExecutable = settings.value("renpyExecutable",
                                     "/usr/games/renpy").toString();

    QString defaultProjectsFolder;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    defaultProjectsFolder = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#else
    defaultProjectsFolder = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
#endif

    defaultProjectsFolder.append("/Renpy-Games/");
    projectsFolder = settings.value("projectsFolder",
                                    defaultProjectsFolder).toString();

	
	recentlyOpenedFiles = settings.value("recentlyOpenedFiles",
		QStringList()).toStringList();
    qDebug() << "Settings loaded";
}



void MainWindow::saveSettings()
{
    QSettings settings;

    settings.setValue("mainWindowSize", this->size());
    settings.setValue("mainSplitterState", this->mainSplitter->saveState());

    settings.setValue("renpyExecutable", this->renpyExecutable);
    settings.setValue("projectsFolder", this->projectsFolder);

    settings.setValue("recentlyOpenedFiles", this->recentlyOpenedFiles);

    qDebug() << "Settings saved";
}



/*
 * Load all RPY files from a directory
 *
 */
void MainWindow::loadProjectFiles(QString path)
{
    this->closeProject();  // Close open project, if any


    this->projectPath = path;
    if (projectPath.endsWith("/"))
    {
        projectPath.remove(projectPath.length()-1, 1);
    }
    qDebug() << "Loading project from:" << projectPath;
	recentlyOpenedFiles.removeAll(projectPath);
	projectmgr->loadProjectFiles(this);
	recentlyOpenedFiles.prepend(projectPath);
    // update "open recent" menu with/without out this last project
    createOpenRecentMenu();
}



void MainWindow::enableMenusAndWidgets(bool state)
{
    this->mainSplitter->setEnabled(state);
    this->projectMenu->setEnabled(state);
    //this->sceneMenu->setEnabled(state);
    this->sceneMenu->setEnabled(false);  // FIXME: This menu will probably disappear

    this->fileSave->setEnabled(state);
    //this->fileSaveAs->setEnabled(state);
    this->fileSaveAs->setEnabled(false);  // FIXME: temporarily, always disabled
    this->fileClose->setEnabled(state);

    if (state)
    {
        qDebug() << "Enabling menus and widgets";
    }
    else
    {
        qDebug() << "Disabling menus and widgets";
    }
}




void MainWindow::closeEvent(QCloseEvent *event)
{
    //this->projectmgr->saveSettings(this);
	saveSettings();
    event->accept();

    qDebug() << "Window closed";

    qApp->quit(); // Exit program completely (close other windows, etc.)
}




////////////////////////////////// SLOTS //////////////////////////////////




void MainWindow::createNewProject()
{
    projectDirectory = QFileDialog::getExistingDirectory(this,
                                                         tr("Select the folder "
                                                            "where the project "
                                                            "will be created"),
                                                         this->projectsFolder);
    qDebug() << projectDirectory;
    if (projectDirectory.isEmpty())
    {
        return;
    }

    if (!projectDirectory.endsWith("/"))
    {
        projectDirectory.append("/");
    }


    projectName = QInputDialog::getText(this, tr("Project name"),
                                        tr("Type a name for your project"));
    if (projectName.isEmpty())
    {
		QMessageBox::warning(this, tr("Warning"), tr("Need to input a project name"));
        return;  // TODO: ask again?
    }

	projectPath = projectDirectory + projectName;
	projectPath.append('/');
    if (QDir(projectPath).exists())
    {
        qDebug() << "Project exists!";
        QMessageBox::warning(this, tr("Project already exists"),
                             tr("There is a project named %1 at %2 already.")
                             .arg(projectName).arg(projectDirectory));

        // TODO: ask to load it, or for another name
    }
    else
    {
		if (projectmgr!=nullptr)
			delete(projectmgr);

		projectmgr = new ProjectMgr(this);
		projectmgr->CreateNewProj(this);
		recentlyOpenedFiles.prepend(projectPath);
        //loadProjectFiles(projectPath);
    }

}


void MainWindow::openProject(QString projFile)
{
	if (projFile.length() == 0)
		projectFile = QFileDialog::getOpenFileName(this,
		tr("Select Revised Project File "),
		QDir::homePath(),
		"Revised Game Projects (*.rproj)");
	else
		projectFile = projFile;

	
	if (!projectFile.isEmpty())
    {
		if (projectmgr != nullptr) delete projectmgr;
		try { projectmgr=new ProjectMgr(this, projectFile); }
		catch (QString errcode){
            QMessageBox::warning(this, tr("My Application"),
				tr("Project File incorrect:\n"),errcode);
		}
		projectmgr->loadProjectFiles(this);
		recentlyOpenedFiles.prepend(projectPath);
		//loadProjectFiles(projectPath);
    }

}


void MainWindow::storySaveAs()
{
	QString newProjectDirectory = QFileDialog::getExistingDirectory(this,
		tr("Select the folder "
		"where the project "
		"will be saved as"),
		this->projectsFolder);
	qDebug() << projectDirectory;
	if (newProjectDirectory.isEmpty()) return;

	if (!newProjectDirectory.endsWith("/")) newProjectDirectory.append("/");

	QString newProjectName = QInputDialog::getText(this, tr("Project name"),
		tr("Type a name for your project"));

	if (newProjectName.isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Need to input a project name"));
		return;  // TODO: ask again?
	}

	QString  newProjectPath = newProjectDirectory + newProjectName;
	newProjectPath.append('/');
	if (QDir(newProjectPath).exists())
	{
		qDebug() << "Project exists!";
		QMessageBox::warning(this, tr("Project already exists"),
			tr("There is a project named %1 at %2 already.")
			.arg(newProjectPath).arg(newProjectDirectory));
		return;
		// TODO: ask to load it, or for another name
	}
	else
	{
		QMessageBox::information(this, tr("Project Renamed"),
			tr("New project will be in %1  %2 .")
			.arg(newProjectPath).arg(newProjectDirectory));

		//projectmgr = new ProjectMgr(this);


		projectmgr->CopyProj(this, newProjectPath);

		QString oldprojectfile = newProjectPath + projectName + QString(".rproj");
		qDebug() << "project name: " << oldprojectfile;
		QString newprojectfile = newProjectPath + newProjectName + QString(".rproj");
		qDebug() << "new project name: " << newprojectfile;
		QFile::rename(oldprojectfile, newprojectfile);
		recentlyOpenedFiles.prepend(newProjectPath);		
		openProject(newprojectfile);
	}

}


void MainWindow::ImportProject()
{
	projectPath = QFileDialog::getExistingDirectory(this,
		tr("Select the project folder"),
		this->projectsFolder);
	if (!projectPath.isEmpty())
	{
		loadProjectFiles(projectPath);
	}
}


void MainWindow::openRecentProject()
{
    qDebug() << "Opening recent project";


    // Get the action object which triggered this action, get the path from it
    QAction *action = qobject_cast<QAction *>(this->sender());

    if (action) // if created action is valid
    {
        if (!action->text().isEmpty())
        {
            projectPath = action->text();
            loadProjectFiles(projectPath);
        }
    }
}


void MainWindow::saveProject()
{
    qDebug() << "Saving project...";

    // Display message at status bar for one second
    this->statusBar()->showMessage(tr("Saving project..."), 1000);
    chapterList->saveContentsToRpyFile();
}


/*
 * Close all files, clear code editor, etc.
 *
 */
void MainWindow::closeProject()
{
    this->setWindowTitle(programIdleTitle);

    projectDirectory.clear();
    projectName.clear();
    projectPath.clear();

    this->chapterList->clearContents();

    this->sceneDesigner->clear();
    this->codeEditor->clear();


    this->characterManager->clear();
    this->imageManager->clear();



    this->enableMenusAndWidgets(false);

    this->setStatusTip(tr("No project loaded"));

    qDebug() << "Project closed";
}


/*
 * Run the game on Ren'Py
 *
 */
void MainWindow::runProject()
{
    qDebug() << "Running the game on Ren'Py with parameters:" << this->projectPath;

    if (this->projectPath.isEmpty())
    {
        QMessageBox::warning(this,
                             tr("No project loaded"),
                             tr("There is no project currently loaded."));
        return;
    }

    QStringList renpyParameters;
    renpyParameters.append( this->projectPath);
	qDebug() << "running" << renpyExecutable << " " << renpyParameters;
    int errorCode;
    errorCode = QProcess::execute(renpyExecutable, renpyParameters);


    if (errorCode == -2)  // Can't execute ren'py
    {
        QMessageBox::critical(this,
                              tr("Cannot execute Ren'Py"),
                              tr("Ren'Py can't be run.\n"
                                 "Make sure you have it correctly installed, "
                                 "and the correct path is set in the configuration.\n\n"
                                 "Currently set to %1").arg(this->renpyExecutable));

        // FIXME: configurable path to renpy executable, etc.
    }


    qDebug() << "Ren'Py error code:" << errorCode;
}




void MainWindow::updateConfiguration(QString executable, QString folder)
{
    this->renpyExecutable = executable;
    this->projectsFolder = folder;
}





void MainWindow::visitWebsite()
{
    QDesktopServices::openUrl(QUrl("http://jancoding.wordpress.com/revised/"));
}


void MainWindow::goToRenpyDoc()
{
    QDesktopServices::openUrl(QUrl("http://www.renpy.org/doc/html/"));
}



void MainWindow::aboutRevised()
{
    QMessageBox::about(this,
                       tr("About Revised"),
                       "<b>Revised v0.2-dev</b><br />"
                       "Copyright 2012-2015  JanKusanagi<br />"
                       "<a href=\"http://jancoding.wordpress.com/revised\">"
                       "http://jancoding.wordpress.com/revised</a><br />"
                       "<br /><br />"

                       + tr("Revised is a visual editor, or wizard, for Ren'Py, "
                            "the visual-novel game engine.")
                       + " <a href=\"http://www.renpy.org\">"
                         "renpy.org</a>"
                       + "<br />"
                         "<hr>"    // ---
                         "<br />"

                       + tr("Ren'Py has a lot of capabilities, and Revised's "
                            "purpose is not to allow everything that Ren'Py "
                            "can do, just some of the basics.<br />"
                            "At least for now.")
                       + "<br /><br />"
                       + tr("You can think of it as a step-by-step wizard to "
                            "create the skeleton of a Ren'Py game.")

                       + "<br />"
                         "<hr>"    // ---
                         "<br />"

                       + tr("English translation by JanKusanagi.",
                            "TRANSLATORS: Change this with your corresponding "
                            "language and name ;)")

                       + "<br />"
                         "<hr>"    // ---
                         "<br />"

                       + tr("Revised is Free Software under a <b>GNU GPL</b> "
                            "license.")
                       + "<br />"
                         "<br />"
                         "<a href=\"http://www.gnu.org/licenses/gpl-2.0.html\">"
                         "GNU GPL v2</a>"
                       );
}
