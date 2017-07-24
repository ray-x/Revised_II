/*
*   This file is part of Revised, a visual editor for Ren'Py
*   Copy right: 2014-2015 Ray <ray.cn@gmail.com>
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
