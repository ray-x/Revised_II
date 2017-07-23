#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "ui_videomanager.h"
#include <QWidget>

namespace Ui {
class VideoManager;
}

class VideoManager : public QWidget
{
    Q_OBJECT
signals :
    void sigInsertVideoStep(QStringList step);

    public slots:
    //void showSetAudio();
    void addVideoStep();
    void addMoreVideo();
    void removeVideo();

public:
    QString projectDir;

    void loadVideoFromDir(QString myprojectDir);

public:
    explicit VideoManager(QWidget *parent = 0);
    ~VideoManager();

private:
    Ui::VideoManager *ui;
};

#endif // VIDEOMANAGER_H
