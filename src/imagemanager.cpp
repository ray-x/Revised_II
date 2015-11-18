/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2012-2015  JanKusanagi JRR <jancoding@gmx.com>
 *             2014-2015  Ray             <ray.cn@gmail.com>
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

#include "imagemanager.h"

ImageManager::ImageManager(QWidget *parent) : QWidget(parent)
{
	this->setWindowFlags(Qt::Dialog);
	this->setWindowModality(Qt::WindowModal);
	this->setupUi(this); 
    effects = { "None", "fade", "dissolve", "pixellate", "move", "moveinright", "moveoutright", "ease", \
        "zoomin", "zoomout", "zoominout", "vpunch", "hpunch", "blinds", "squares", "wipeleft", "slideleft", "slideawayleft", "irisin" };

    ATLs = { "None", "pause", "linear", "ease", "easein", "pos", "xpos", "ypos", "anchor", "xanchor", "yanchor", "align", "xalign", \
        "yalign", "xoffset", "yoffset", "xcenter", "ycenter", "rotate", "rotate_pad", "transform_anchor", "zoom", "xzoom", "yzoom", "nearest", "alpha", \
        "additive", "around", "alignaround", "angle", "radius", "crop", "crop_relative", "corner1", "corner2", "size", "subpixel", "delay", "events" };
    this->setWindowTitle("Revised - " + tr("Image Manager"));
    this->setWindowIcon(QIcon::fromTheme("folder-image"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    this->setMinimumSize(640, 440);

    QSettings settings;
    this->resize(settings.value("imageManagerSize", QSize(720, 520)).toSize());


    // Left side
    imageList->setViewMode(QListView::ListMode);
    imageList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    imageList->setIconSize(QSize(128, 128));  // 128x128 thumbnails

	connect(addAnotherImageButton, SIGNAL(clicked()),
		this, SLOT(addAnotherImage()));
    connect(addScaledImageButton, SIGNAL(clicked()),
        this, SLOT(addScaledImage()));

	connect(imageList, SIGNAL(currentTextChanged(QString)),
		imageRefLineEdit, SLOT(setText(QString)));

	connect(imageRefLineEdit, SIGNAL(returnPressed()),
		this, SLOT(updateImageRefInList()));
	connect(changeImageRefButton, SIGNAL(clicked()),
		this, SLOT(updateImageRefInList()));
	connect(removeSelectedImageButton, SIGNAL(clicked()),
		this, SLOT(removeImageFromList()));
	connect(setBackgroundButton, SIGNAL(clicked()),
		this, SLOT(setBackground()));

	connect(applyImageChange, SIGNAL(clicked()),
		this, SLOT(insertImage()));


	//connect(btnHide, SIGNAL(clicked()),	this, SLOT(hideImage()));


	/*
	connect(insertImageButtonLeft, SIGNAL(clicked()),
		this, SLOT(insertImageLeft()));
	connect(insertImageButtonCenter, SIGNAL(clicked()),
		this, SLOT(insertImageCenter()));
	connect(insertImageButtonRight, SIGNAL(clicked()),
		this, SLOT(insertImageRight()));
	*/

	closeAction = new QAction(this);
	closeAction->setShortcut(Qt::Key_Escape);
	connect(closeAction, SIGNAL(triggered()),
		this, SLOT(close()));
	this->addAction(closeAction);
    effectsComboBox->insertItems(0, effects);
    effectsComboBox->setMaxVisibleItems(10);

    ATLsComboBox1->insertItems(0, ATLs);
    ATLsComboBox1->setMaxVisibleItems(10);
    ATLsComboBox2->insertItems(0, ATLs);
    ATLsComboBox2->setMaxVisibleItems(10);
    ATLsComboBox3->insertItems(0, ATLs);
    ATLsComboBox3->setMaxVisibleItems(10);
    ATLsComboBox4->insertItems(0, ATLs);
    ATLsComboBox4->setMaxVisibleItems(10);
    ATLsComboBox5->insertItems(0, ATLs);
    ATLsComboBox5->setMaxVisibleItems(10);
    ATLsComboBox6->insertItems(0, ATLs);
    ATLsComboBox6->setMaxVisibleItems(10);
    enableOrDisableButtons();



#if 0
    addAnotherImageButton = new QPushButton(QIcon::fromTheme("list-add"),
                                tr("Add &More Images"));


    // Right side
    imageRefLabel = new QLabel(tr("&ID:"));
    imageRefLabel->setAlignment(Qt::AlignLeft);

    imageRefLineEdit = new QLineEdit();
    imageRefLineEdit->setPlaceholderText(tr("Example: character happy smile"));
    imageRefLineEdit->setMinimumWidth(128); // tmp?
    imageRefLabel->setBuddy(imageRefLineEdit);



    changeImageRefButton = new QPushButton(QIcon::fromTheme("edit-rename"),
                                           tr("Re&name"));
    removeSelectedImageButton = new QPushButton(QIcon::fromTheme("list-remove"),
                                                tr("&Remove"));



    setBackgroundButton = new QPushButton(QIcon::fromTheme("insert-image"),
                                          tr("Set as &Background"));


    insertImageButtonLeft = new QPushButton(QIcon::fromTheme("align-horizontal-left"),
                                            tr("&Left"));

    insertImageButtonCenter = new QPushButton(QIcon::fromTheme("align-horizontal-center"),
                                              tr("&Center"));

    insertImageButtonRight = new QPushButton(QIcon::fromTheme("align-horizontal-right"),
                                             tr("&Right"));





    // Layouts

    imageListGroupbox = new QGroupBox(tr("&Available images"));
    imageListLayout = new QVBoxLayout();
    imageListLayout->addWidget(imageList);
    imageListLayout->addWidget(addAnotherImageButton);
    imageListGroupbox->setLayout(imageListLayout);


    alignButtonsGroupbox = new QGroupBox(tr("Insert image at"));
    alignButtonsLayout = new QHBoxLayout();
    alignButtonsLayout->addWidget(insertImageButtonLeft);
    alignButtonsLayout->addWidget(insertImageButtonCenter);
    alignButtonsLayout->addWidget(insertImageButtonRight);
    alignButtonsGroupbox->setLayout(alignButtonsLayout);


    currentImageGroupbox = new QGroupBox(tr("&Selected image"));
    currentImageLayout = new QGridLayout();
    currentImageLayout->addWidget(imageRefLabel,             0, 0,  1, 1);
    currentImageLayout->addWidget(imageRefLineEdit,          0, 1,  2, 3);
    currentImageLayout->addWidget(changeImageRefButton,      0, 3,  1, 1);
	currentImageLayout->addWidget(removeSelectedImageButton, 0, 4, 1, 1);// , Qt::AlignTop);

    currentImageLayout->addWidget(setBackgroundButton,       2, 0,  1, 4, Qt::AlignBottom);
    currentImageLayout->addWidget(alignButtonsGroupbox,      3, 0,  1, 4, Qt::AlignBottom);
    currentImageGroupbox->setLayout(currentImageLayout);


    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(imageListGroupbox,    1);  // stretch 1/2
    mainLayout->addSpacing(16);
    mainLayout->addWidget(currentImageGroupbox, 1);
    this->setLayout(mainLayout);



    // Ensure disabled buttons if img list is empty
    


#if 0  // TMP, for tests
    this->show();
#endif
#endif

    qDebug() << "ImageManager created";
}


ImageManager::~ImageManager()
{
    qDebug() << "ImageManager destroyed";
}




void ImageManager::enableOrDisableButtons()
{
    bool enableButtons;

    if (imageList->count() <= 0)  // If list became empty, disable some widgets
    {
        enableButtons = false;
    }
    else
    {
        enableButtons = true;
    }

    currentImageGroupbox->setEnabled(enableButtons);
}



/*
 * Set the RPY filename of the image definitions
 * and parse it to populate the image list
 *
 */
void ImageManager::loadImagesFromRpyFile(QString filename)
{
    this->rpyFilename = filename;
    this->projectPath = QFileInfo(filename).absolutePath();


    QFile rpyFile(rpyFilename);
    rpyFile.open(QIODevice::ReadOnly);
    QString rpyFileLine;

    while (!rpyFile.atEnd())    // Parse RPY file, etc.
    {
        rpyFileLine = QString::fromLocal8Bit(rpyFile.readLine());
        if (rpyFileLine.startsWith("image"))
        {
            QString imageRef = rpyFileLine;

            imageRef.remove(QRegExp("\\s*image\\s+"));
            imageRef.remove(QRegExp("=.+"));
            imageRef = imageRef.trimmed();

            qDebug() << "loaded imageRef:" << imageRef;

            QString imageFilename = rpyFileLine;

            imageFilename.remove(QRegExp(".*=\\s+\\\""));
            imageFilename.remove(QRegExp("\\\""));

            QString fullImageFilename = projectPath + "/" + imageFilename.trimmed();
			qDebug() << "loaded filename:" << imageFilename;
			QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(fullImageFilename)),
                                                        imageRef);
			item->setData(Qt::UserRole, imageFilename);
			//item->setData(Qt::UserRole, imageFilename);
			/*
			imageFilename = projectPath + "/" + imageFilename.trimmed();
            qDebug() << "loaded filename:" << imageFilename;
            QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(imageFilename)),
                                                        imageRef);
            item->setData(Qt::UserRole, QFileInfo(imageFilename).fileName());
			*/
            imageList->addItem(item);
        }
    }
    rpyFile.close();

    enableOrDisableButtons();

    qDebug() << "ImageManager data loaded from" << rpyFilename << "on" << projectPath;
}



/*
 * On close, save all image information as ren'py image definitions
 * in the RPY file
 *
 */
void ImageManager::saveImagesToRpyFile()
{
    // Images.rpy file format:

    // image bg uni = "uni.jpg"
    // image sylvie smile = "sylvie_smile.png"


    QString rpyFileData = "## Image definitions\n\n";

    for (int imageListRow = 0; imageListRow != imageList->count(); ++imageListRow)
    {
        QListWidgetItem *item = imageList->item(imageListRow);

        rpyFileData.append("image ");
        rpyFileData.append(item->text());
        rpyFileData.append(" = ");
        rpyFileData.append("\"" + item->data(Qt::UserRole).toString().trimmed() + "\"");
        rpyFileData.append("\n");
    }

    rpyFileData.append("\n## End of image definitions\n\n");


    QFile rpyFile(rpyFilename);
    rpyFile.open(QIODevice::WriteOnly);
    rpyFile.write(rpyFileData.toLocal8Bit());
    rpyFile.close();


    qDebug() << rpyFilename << "saved";
}




QString ImageManager::getFilenameFromRef(QString ref)
{
    for (int counter = 0; counter < imageList->count(); ++counter)
    {
        if (imageList->item(counter)->text() == ref)
        {
            return this->projectPath + "/"
                    + imageList->item(counter)->data(Qt::UserRole).toString().trimmed();
        }
    }

    return QString();  // Shouldn't get here if reference is correct
}




void ImageManager::insertImage(QString alignment)
{
    if (this->imageList->currentItem())  // if valid item selected
    {
        emit imageSelected(imageList->currentItem()->text(),
                           alignment,
                           projectPath + "/" + imageList->currentItem()->data(Qt::UserRole).toString());

        this->close();
    }
}




///////////////////////////////// SLOTS //////////////////////////////////





void ImageManager::updateImageRefInList()
{
    if (imageList->count() == 0)
    {
        return;  // Don't do anything if list is empty (shouldn't be possible)
    }

    if (!imageList->currentItem())
    {
        return; // If there is no current item, don't do anything
        // TMP FIXME nicer
    }


    QString newImageRef = this->imageRefLineEdit->text().replace("-","_").trimmed();

    if (newImageRef.isEmpty())
    {
        qDebug() << "Trying to set an empty image reference. Ignoring...";
    }
    else
    {
        this->imageList->currentItem()->setText(newImageRef);
    }
}




/*
 * Remove currently selected image from the list
 *
 */
void ImageManager::removeImageFromList()
{
    delete imageList->currentItem();

    enableOrDisableButtons(); // Check if list becomes empty, and disable stuff

    qDebug() << "Removed image from list";
}




/*
 * Find another image on disk, and add it to the list
 *
 */
void ImageManager::addAnotherImage()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                         tr("Select one or more images"),
                                                         this->projectPath,
                                                         tr("Images")
                                                         + " (*.png *.gif *.jpg)");


    if (fileList.isEmpty())  // if FileDialog was cancelled, don't do anything
    {
        return;
    }


    foreach (QString filename, fileList)
    {
        // If selected image isn't in project directory, copy it
        if (QFileInfo(filename).path() != this->projectPath)
        {
            // Copy to project path
            qDebug() << QFileInfo(filename).path() << "vs" << projectPath;

            QString newFilename = projectPath + "/" + QFileInfo(filename).fileName();

            QFile::copy(filename, newFilename);
            qDebug() << "Copying image to project directory:" << newFilename;

            filename = newFilename;

        }

        QListWidgetItem *imageItem = new QListWidgetItem();

        // FIXME: aspect ratio, etc.
        imageItem->setIcon(QIcon(QPixmap(filename).scaled(128, 128)));

        // Set bare filename, without extension, as Image Ref initially
        // replacing "-" with "_", as it's not supported in image refs
        QString imageRef = QFileInfo(filename).baseName();
        imageRef.replace("-", " ");
        imageRef.replace("_", " ");
        imageItem->setText(imageRef);

        // Store full filename with extension, without path, in the item
        imageItem->setData(Qt::UserRole, QFileInfo(filename).fileName());

        imageList->addItem(imageItem);
    }


    enableOrDisableButtons();
}

void ImageManager::addScaledImage()
{
    float scale;
    bool ok = false;
    QString cmd="";
    QString options = "";
    QString commandline = "";
    if (!imageList->currentItem())
    {
        return; // If there is no current item, don't do anything
        // TMP FIXME nicer
    }


    QString ImageRef = this->imageRefLineEdit->text().replace("-", "_").trimmed();

    if (!xScaleLineEdit->text().isEmpty()){
        qDebug() << xScaleLineEdit->text().trimmed();
        scale = xScaleLineEdit->text().toFloat(&ok);
    }

    QString filename = imageList->currentItem()->data(Qt::UserRole).toString().trimmed();

    if (ok)
        commandline = QString("image %1 scaled = im.FactorScale(\" %2 \", %3)").arg(ImageRef).arg(QFileInfo(filename).fileName()).arg(xScaleLineEdit->text().trimmed());

    QListWidgetItem *imageItem = new QListWidgetItem();

    // FIXME: aspect ratio, etc.
    imageItem->setIcon(QIcon(QPixmap(filename).scaled(128, 128)));

    // Set bare filename, without extension, as Image Ref initially
    // replacing "-" with "_", as it's not supported in image refs
    QString newimageRef = ImageRef+" scaled";
    newimageRef.replace("-", " ");
    newimageRef.replace("_", " ");
    imageItem->setText(newimageRef);

    // Store full filename with extension, without path, in the item


   // Store full filename with extension, without path, in the item
    imageItem->setData(Qt::UserRole, commandline);
    imageList->addItem(imageItem);
}




/*
 * Clear all the fields, leave IM ready for next loaded project
 *
 */
void ImageManager::clear()
{
    this->imageList->clear();

    enableOrDisableButtons();

    this->hide();
}



void ImageManager::showForEditing()
{
    // Hide unrequired buttons
    this->setBackgroundButton->hide();

//    this->alignButtonsGroupbox->hide(); // hides the 3 buttons inside

    this->show();
}



void ImageManager::showSetBackground()
{
    this->setBackgroundButton->show();
    this->setBackgroundButton->setDefault(true);

//    this->alignButtonsGroupbox->hide();

     this->show();
}



void ImageManager::showInsertImage()
{
    //TODO: delete this
//    this->setBackgroundButton->hide();
//    this->alignButtonsGroupbox->show(); // shows the 3 buttons inside
//    this->insertImageButtonCenter->setDefault(true);
    this->setBackgroundButton->show();
    this->setBackgroundButton->setDefault(true);
    this->show(); // tmp
}




void ImageManager::setBackground()
{
    if (this->imageList->currentItem())
    {
        emit backgroundSelected(imageList->currentItem()->text(),
                                projectPath + "/" + imageList->currentItem()->data(Qt::UserRole).toString());

        this->close();
    }

}




void ImageManager::insertImageLeft()
{
    this->insertImage("left");
}

void ImageManager::insertImageCenter()
{
    this->insertImage("center");
}

void ImageManager::insertImageRight()
{
    this->insertImage("right");
}

void ImageManager::insertImage()
{
	//this->insertImage("left");
    QString cmd="";
    QString options = "";
    QString image_string = "";
    if (ckbHide->isChecked())
        cmd = "hide ";
    else
        cmd = "show ";
    if (!xPosLineEdit->text().isNull() && yPosLineEdit->text().isNull())
    {
        options = QString("at Position(xpos = %1, xanchor = %1, ypos = %2, yanchor = %2)").arg(xPosLineEdit->text(), yPosLineEdit->text());
    }else
    {
        if (radioButtonL->isChecked())
            options = options + " at left";
        else if (radioButtonR->isChecked())
            options = options + " at Right";
        else
            options = options + " at Middle";
        options = options + " ";
    }

    //TODO: fix here
    if (!behindCharactersLineEdit->text().isEmpty())
        options = options + " behind " + behindCharactersLineEdit->text();//"behind mary, mary2"
        
    qDebug() << options;
    qDebug() << image_string;
    //call addImage(QString imageref, QString filename, QString cmd, QString option)
    emit imageInsert(imageList->currentItem()->text(), cmd, 
            options, projectPath + "/" + imageList->currentItem()->data(Qt::UserRole).toString());
    if (effectsComboBox->currentIndex() > 1)
    {
        int index = effectsComboBox->currentIndex();
        QString command2 = QString("with ").append(effects.at(index));
        emit imageInsert(command2);
    }


   /* this->close();    */
    QString cmdline0 = QString("show image ").append(imageList->currentItem()->text());
    QString cmdline1="    ";
    QString cmdline2 = "    ";
    QString cmdline3 = "    ";
    QString argATL("");
    QStringList ATLcmds{};
    ATLcmds.push_back(cmdline0);
    if (ATLsComboBox1->currentIndex() > 0){
        cmdline1.append(ATLs.at(ATLsComboBox1->currentIndex())).append(" ");
        if (!ATLEdit1->text().isEmpty())
        {
            argATL = QString("%1 ").arg(ATLEdit1->text()); 
            cmdline1.append(argATL);
        }
    }
    if (ATLsComboBox2->currentIndex() > 0){
        cmdline1.append(ATLs.at(ATLsComboBox2->currentIndex())).append(" ");
        if (!ATLEdit2->text().isEmpty())
        {
            argATL = QString("%1").arg(ATLEdit2->text());
            cmdline1.append(argATL);
        }
    }
    qDebug() << cmdline1;
    if (!cmdline1.trimmed().isEmpty())
        ATLcmds.push_back(cmdline1);

    if (ATLsComboBox3->currentIndex() > 0){
        cmdline2.append(ATLs.at(ATLsComboBox3->currentIndex())).append(" ");
        if (!ATLEdit3->text().isEmpty())
        {
            argATL = QString("%1 ").arg(ATLEdit3->text());
            cmdline2.append(argATL);
        }
    }

    if (ATLsComboBox4->currentIndex() > 0){
        cmdline2.append(ATLs.at(ATLsComboBox4->currentIndex()));
        if (!ATLEdit4->text().isEmpty())
        {
            argATL = QString(" %1 ").arg(ATLEdit4->text());
            cmdline2.append(argATL);
        }
    }
    qDebug() << cmdline2;
    if (!cmdline2.trimmed().isEmpty())
        ATLcmds.push_back(cmdline2);

    if (ATLsComboBox5->currentIndex() > 0){
        cmdline3.append(ATLs.at(ATLsComboBox5->currentIndex()));
        if (!ATLEdit5->text().isEmpty())
        {
            argATL = QString(" %1 ").arg(ATLEdit5->text());
            cmdline3.append(argATL);
        }
    }
    if (ATLsComboBox6->currentIndex() > 0){
        cmdline3.append(ATLs.at(ATLsComboBox6->currentIndex())).append(" ");
        if (!ATLEdit6->text().isEmpty())
        {
            argATL = QString(" %1").arg(ATLEdit6->text());
            cmdline3.append(argATL);
        }
    }
    qDebug() << cmdline3;
    if (!cmdline3.trimmed().isEmpty())
        ATLcmds.push_back(cmdline3);
    if (ALTLoopChkBox->isChecked())
        ATLcmds.push_back("    repeat");
    qDebug() << ATLcmds;
    emit imageInsert(ATLcmds);
}

void ImageManager::hideImage()
{
	//this->insertImage("left");

}


void ImageManager::generateScript()
{
	//this->insertImage("left");
	QString position;
	if (this->radioButtonL->isChecked())
		position = "at left";
	if (this->radioButtonR->isChecked())
		position = "at right";
	if (this->radioButtonL->isChecked())
		position = "";
	if (this->xPosLineEdit->text() != ""&&this->yPosLineEdit->text() != "")
		position = " at Position(xpos = " + this->xPosLineEdit->text() + \
		" xanchor = " + this->xPosLineEdit->text() + \
		", ypos = " + this->yPosLineEdit->text() + \
		", yanchor = " + this->yPosLineEdit->text() + ")";
	qDebug() << this->xPosLineEdit->text();
    qDebug() << position;
    //currentChapter->addStep(position);
}



/////////////////////////////// PROTECTED //////////////////////////////////



void ImageManager::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("imageManagerSize", this->size());

    this->saveImagesToRpyFile();

    event->accept();
}
