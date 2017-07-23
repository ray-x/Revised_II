#ifndef CHOICEMENUEDITORFORM_H
#define CHOICEMENUEDITORFORM_H
#include <vector>
#include <utility> 
#include <QWidget>
//#include "ui_choicemenueditorform.h"
namespace Ui {
class ChoiceMenuEditorForm;
}

class ChoiceMenuEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChoiceMenuEditorForm(QWidget *parent = 0);
    ~ChoiceMenuEditorForm();
signals:
    void sigInsertMenuStep(QStringList cmd);
public slots:
    void AddMenuItem();
    void RemoveMenuItem();
    void Finished();
    void Cancel();

private:
    QStringList MenuItems;
    Ui::ChoiceMenuEditorForm *ui;
    std::vector < std::pair<int, int> > items;

};

#endif // CHOICEMENUEDITORFORM_H
