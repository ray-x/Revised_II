#include "projectmgr.h"
#include <vector>
#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QDir>
using namespace std;



ProjectMgr::ProjectMgr(QObject *parent): QObject(parent)
{

}

ProjectMgr::ProjectMgr(MainWindow *win, QString path)
{
	if (!path.isEmpty()){
		projectfile = path;
		qDebug() << "projectfile:" << projectfile ;
		QFileInfo settinginfo(path);
		if (settinginfo.exists())
		{
			if (settinginfo.isFile()){
				this->mProjectDir = settinginfo.dir().path();
				QDir projectdir = settinginfo.dir();
				win->projectName = projectdir.dirName();

				QDir projectsdir = settinginfo.dir();
				projectsdir.cdUp();
				win->projectDirectory = projectsdir.path();
				if (!win->projectDirectory.endsWith("/"))
				{
					win->projectDirectory.append("/");
				}

				win->projectPath = win->projectDirectory + win->projectName;
				qDebug() << "project projectDirectory" << win->projectDirectory;
				qDebug() << "project projectPath" << win->projectPath;
				loadSettings(win);

			}
			else if (settinginfo.isDir()){
				//TODO
				qDebug() << "NOT finished" ;

			}
		}
	}
	else{ //create new prject entry here
		projectfile = win->projectPath + win->projectName + QString(".rproj");
		qDebug() << "projectfile: " << projectfile;
		QFileInfo settinginfo(projectfile);
		if (settinginfo.exists())
			loadSettings(win);
		else
			saveSettings(win);
	}
}




bool ProjectMgr::loadSettings(MainWindow *win)
{
	QSettings settings(projectfile, QSettings::IniFormat);
	qDebug() << "load file from : " << projectfile;
	if (settings.status() != QSettings::NoError) 
		qDebug() << "settings load  code" << settings.status() << endl;;
	//win->resize(settings.value("mainWindowSize", QSize(1024, 768)).toSize());
	win->mainSplitter->restoreState(settings.value("mainSplitterState").toByteArray());

	win->renpyExecutable = settings.value("renpyExecutable",
		"/usr/games/renpy").toString();

	QString defaultProjectsFolder;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	defaultProjectsFolder = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#else
	defaultProjectsFolder = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();
#endif

	defaultProjectsFolder.append("/Renpy-Games/");
	win->projectsFolder = settings.value("projectsFolder",
		defaultProjectsFolder).toString();
	qDebug() << "load file from : " << win->projectsFolder;
	//win->recentlyOpenedFiles = settings.value("recentlyOpenedFiles",
	//	QStringList()).toStringList();

	qDebug() << "Settings loaded";
	return false;
}



bool ProjectMgr::saveSettings(MainWindow *win)
{
	QSettings settings(projectfile, QSettings::IniFormat);
	qDebug() << "error code" << settings.status() << endl;
	if (1){
		settings.setValue("mainWindowSize", win->size());
		settings.setValue("mainSplitterState", win->mainSplitter->saveState());

		settings.setValue("renpyExecutable", win->renpyExecutable);
		settings.setValue("projectsFolder", win->projectsFolder);

		//settings.setValue("recentlyOpenedFiles", win->recentlyOpenedFiles);
		qDebug() << "Settings saved";
		return true;
	}

	return false;
}


bool ProjectMgr::CreateNewProj(MainWindow *win)
{
	QDir().mkdir(win->projectPath);

	QFile charactersFile(win->projectPath + "/" + "001-characters.rpy");
	charactersFile.open(QIODevice::WriteOnly);
	charactersFile.write(QString("## Ren'py project %1 created with Revised on %2\n"
		"## Character definitions\n\n")
		.arg(win->projectName)
		.arg(QDate::currentDate().toString("dd-MMM-yyyy")).toLocal8Bit());
	charactersFile.close();


	QFile imagesFile(win->projectPath + "/" + "002-images.rpy");
	imagesFile.open(QIODevice::WriteOnly);
	imagesFile.write(QString("## Ren'py project %1 created with Revised on %2\n"
		"## Image definitions\n\n")
		.arg(win->projectName)
		.arg(QDate::currentDate().toString("dd-MMM-yyyy")).toLocal8Bit());
	imagesFile.close();



	QFile scriptFile(win->projectPath + "/" + "100-script.rpy");
	scriptFile.open(QIODevice::WriteOnly);
	scriptFile.write(QString("## Ren'py project %1 created with Revised on %2\n"
		"## Script, first chapter\n\n")
		.arg(win->projectName)
		.arg(QDate::currentDate().toString("dd-MMM-yyyy")).toLocal8Bit());
	scriptFile.write("label start:\n"
		"    \"This is a test from Revised\"\n\n");
	scriptFile.close();



	QFile optionsFile(win->projectPath + "/" + "options.rpy");
	optionsFile.open(QIODevice::WriteOnly);
	optionsFile.write(QString("## Ren'py project %1 created with Revised on %2\n"
		"## Game options\n\n")
		.arg(win->projectName)
		.arg(QDate::currentDate().toString("dd-MMM-yyyy")).toLocal8Bit());
	optionsFile.write(QString("init -1:\n"
		"    python hide:\n"
		"        config.window_title = u\"%1\"\n\n")
		.arg(win->projectName).toLocal8Bit());
	optionsFile.close();


	qDebug() << "New project created at" << win->projectPath;
	loadProjectFiles(win);
	return true;

}

bool ProjectMgr::loadProjectFiles(MainWindow *win)
{


	QDirIterator dirList(QDir(win->projectPath, "*.rpy", QDir::Name, QDir::Files));

	win->fileList.clear();
	while (dirList.hasNext())
	{
		win->fileList.append(dirList.next());
	}

	win->fileList.sort();  // fileList should be sorted, but sort to make sure
	qDebug() << "File list:" << win->fileList;


	// remove any matches of this file in the "open recent" list, first, to avoid duplicates
	//win->recentlyOpenedFiles.removeAll(win->projectPath);


	// No files = no project to load, so abort
	if (win->fileList.isEmpty())
	{
		qDebug() << "There is no renpy project in this directory";

		QMessageBox::warning(NULL, tr("Not a Ren'Py project"),
			tr("The folder %1 does not seem to contain "
			"a Ren'Py project.")
			.arg(win->projectPath));
	}
	else
	{
		////// very TMP; FIXME    //////////////////////////

		// Load game options from options.rpy
		win->gameOptionsManager->loadOptionsFromRpyFile(win->projectPath);


		// Load the character definitions file (first script) in the CharacterManager
		win->characterManager->loadCharactersFromRpyFile(win->fileList.at(0));

		// Load the image definitions file (second script) in the ImageManager
		win->imageManager->loadImagesFromRpyFile(win->fileList.at(1));  // FIXME, ensure correct file, etc


		// Load the chapter list, and the third script (first chapter) file
		win->chapterList->setContents(win->projectPath, win->fileList);


		win->projectName = win->projectPath;
		win->projectName.remove(QRegExp(".*/"));
		qDebug() << "Loaded project:" << win->projectName << "from" << win->projectPath;


		win->setWindowTitle("Revised - " + win->projectName);

		// Re-enable some menus and widgets that were disabled initially or after project closed
		win->enableMenusAndWidgets(true);

		win->setStatusTip(tr("Project %1 loaded").arg(win->projectName));


		// On successful load, add this project at the top of the Recent list
		//win->recentlyOpenedFiles.prepend(win->projectPath);
	}
	return true;
}


static bool copyRecursively(const QString &srcFilePath,
	const QString &tgtFilePath)
{
	QFileInfo srcFileInfo(srcFilePath);
	if (srcFileInfo.isDir()) {
		QDir targetDir(tgtFilePath);
		targetDir.cdUp();
		qDebug() <<"MakeDIR: " <<QFileInfo(tgtFilePath).fileName();
		if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
			return false;
		QDir sourceDir(srcFilePath);
		QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
		foreach(const QString &fileName, fileNames) {
			const QString newSrcFilePath
				= srcFilePath + QLatin1Char('/') + fileName;
			const QString newTgtFilePath
				= tgtFilePath + QLatin1Char('/') + fileName;
			if (!copyRecursively(newSrcFilePath, newTgtFilePath))
				return false;
		}
	}
	else {
		if (!QFile::copy(srcFilePath, tgtFilePath))
			return false;
	}
	return true;
}



bool ProjectMgr::CopyProj(MainWindow *win, QString NewProjFolder)
{
	QString sourcedir = win->projectPath;
	QFileInfo srcFileInfo(sourcedir);
	if (!srcFileInfo.exists())
		return false;
	QString destDir = NewProjFolder;
	if (sourcedir.endsWith('/'))	
		sourcedir.remove(sourcedir.length()-1, 1);
	if (destDir.endsWith('/'))
		destDir.remove(destDir.length() - 1, 1);

	copyRecursively(sourcedir, destDir);
	QString destdir = NewProjFolder;

}