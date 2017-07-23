#ifndef AUIDOMANAGERFORM_H
#define AUIDOMANAGERFORM_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>

#include "ui_audiomanagerform.h"
namespace Ui {
class AudioManagerForm;
}

class AudioManagerForm : public QWidget
{
    Q_OBJECT

signals :
    void sigInsertAudioStep(QString step);

public slots:
    void showSetAudio();
    void addAudioStep();
    void addMoreAudio();

public:
    QString projectDir;
    explicit AudioManagerForm(QWidget *parent = 0);
    ~AudioManagerForm();
    void loadAudioFromDir(QString myprojectDir);
private:
    Ui::AudioManagerForm *ui;
};

#endif // AUIDOMANAGERFORM_H
