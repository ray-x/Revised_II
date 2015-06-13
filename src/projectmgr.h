#ifndef ProjectMgr_H
#define ProjectMgr_H

#include <QObject>
#include "mainwindow.h"
#include<vector>
using namespace std;
class MainWindow;
class ProjectMgr : public QObject
{
    Q_OBJECT
public:
    explicit ProjectMgr(QObject *parent = 0);
	ProjectMgr(MainWindow *win , QString path = "");
	//explicit ProjectMgr(MainWindow *win);
	bool ImportSaveProj(QString *projectname);
	bool CreateNewProj(MainWindow *win);
	bool CreateNewProj(QString *loadProjectFiles);
	bool CopyProj(MainWindow *win, QString NewProjFolder);
	bool loadProjectFiles(MainWindow *win);

	bool loadSettings(MainWindow *win);
	bool saveSettings(MainWindow *win);

signals:

public slots:


private:
	QString mProjectDir;
	QString projectfile;
	vector<QString> mRenPyFiles;
	vector<QString> mResourceFiles;
	vector<QString> mRenPySdkDir;
};

#endif // LOADSAVEPROJ_H
