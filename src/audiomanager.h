#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QWidget>
#include <QDebug>
#include <QAction>
#include "projectmgr.h"
#include <QFileDialog>

#include "ui_audiomanager.h"

class AudioManager : public QWidget, public Ui::AudioManagerForm
{
    Q_OBJECT
public:
    explicit AudioManager(QWidget *parent = 0);
    ~AudioManager();
    
    void loadAudioFromDsk(QString filename);

    //QString getFilenameFromRef(QString ref);

    void loadAudiosFromDir(QString filename);

signals:

public slots :
    void showSetAudio();

};

#endif // AUDIOMANAGER_H
