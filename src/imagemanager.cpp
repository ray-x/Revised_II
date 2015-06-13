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

#include "imagemanager.h"

ImageManager::ImageManager(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Revised - " + tr("Image Manager"));
    this->setWindowIcon(QIcon::fromTheme("folder-image"));
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    this->setMinimumSize(640, 440);

    QSettings settings;
    this->resize(settings.value("imageManagerSize", QSize(720, 480)).toSize());


    // Left side
    imageList = new QListWidget();
    imageList->setMinimumWidth(256);
    imageList->setViewMode(QListView::ListMode);
    imageList->setMovement(QListView::Static);
    imageList->setSortingEnabled(true);
    //imageList->setAlternatingRowColors(true);
    imageList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    imageList->setIconSize(QSize(128, 128));  // 128x128 thumbnails

    addAnotherImageButton = new QPushButton(QIcon::fromTheme("list-add"),
                                tr("Add &More Images"));
    connect(addAnotherImageButton, SIGNAL(clicked()),
            this, SLOT(addAnotherImage()));



    // Right side
    imageRefLabel = new QLabel(tr("&ID:"));
    imageRefLabel->setAlignment(Qt::AlignLeft);

    imageRefLineEdit = new QLineEdit();
    imageRefLineEdit->setPlaceholderText(tr("Example: character happy smile"));
    imageRefLineEdit->setMinimumWidth(128); // tmp?
    imageRefLabel->setBuddy(imageRefLineEdit);

    connect(imageList, SIGNAL(currentTextChanged(QString)),
            imageRefLineEdit, SLOT(setText(QString)));

    connect(imageRefLineEdit, SIGNAL(returnPressed()),
            this, SLOT(updateImageRefInList()));


    changeImageRefButton = new QPushButton(QIcon::fromTheme("edit-rename"),
                                           tr("Re&name"));
    connect(changeImageRefButton, SIGNAL(clicked()),
            this, SLOT(updateImageRefInList()));

    removeSelectedImageButton = new QPushButton(QIcon::fromTheme("list-remove"),
                                                tr("&Remove from List"));
    connect(removeSelectedImageButton, SIGNAL(clicked()),
            this, SLOT(removeImageFromList()));



    setBackgroundButton = new QPushButton(QIcon::fromTheme("insert-image"),
                                          tr("Set as &Background"));
    connect(setBackgroundButton, SIGNAL(clicked()),
            this, SLOT(setBackground()));


    insertImageButtonLeft = new QPushButton(QIcon::fromTheme("align-horizontal-left"),
                                            tr("&Left"));
    connect(insertImageButtonLeft, SIGNAL(clicked()),
            this, SLOT(insertImageLeft()));

    insertImageButtonCenter = new QPushButton(QIcon::fromTheme("align-horizontal-center"),
                                              tr("&Center"));
    connect(insertImageButtonCenter, SIGNAL(clicked()),
            this, SLOT(insertImageCenter()));

    insertImageButtonRight = new QPushButton(QIcon::fromTheme("align-horizontal-right"),
                                             tr("&Right"));
    connect(insertImageButtonRight, SIGNAL(clicked()),
            this, SLOT(insertImageRight()));



    closeAction = new QAction(this);
    closeAction->setShortcut(Qt::Key_Escape);
    connect(closeAction, SIGNAL(triggered()),
            this, SLOT(close()));
    this->addAction(closeAction);



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
    currentImageLayout->addWidget(imageRefLineEdit,          0, 1,  1, 2);
    currentImageLayout->addWidget(changeImageRefButton,      0, 3,  1, 1);
    currentImageLayout->addWidget(removeSelectedImageButton, 1, 3,  1, 1, Qt::AlignTop);

    currentImageLayout->addWidget(setBackgroundButton,       2, 0,  1, 4, Qt::AlignBottom);
    currentImageLayout->addWidget(alignButtonsGroupbox,      2, 0,  1, 4, Qt::AlignBottom);
    currentImageGroupbox->setLayout(currentImageLayout);


    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(imageListGroupbox,    1);  // stretch 1/2
    mainLayout->addSpacing(16);
    mainLayout->addWidget(currentImageGroupbox, 1);
    this->setLayout(mainLayout);



    // Ensure disabled buttons if img list is empty
    enableOrDisableButtons();


#if 0  // TMP, for tests
    this->show();
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
        rpyFileData.append("\"" + item->data(Qt::UserRole).toString() + "\"");
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

    this->alignButtonsGroupbox->hide(); // hides the 3 buttons inside

    this->show();
}



void ImageManager::showSetBackground()
{
    this->setBackgroundButton->show();
    this->setBackgroundButton->setDefault(true);

    this->alignButtonsGroupbox->hide();

    this->show();
}



void ImageManager::showInsertImage()
{
    this->setBackgroundButton->hide();

    this->alignButtonsGroupbox->show(); // shows the 3 buttons inside
    this->insertImageButtonCenter->setDefault(true);

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



/////////////////////////////// PROTECTED //////////////////////////////////



void ImageManager::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("imageManagerSize", this->size());

    this->saveImagesToRpyFile();

    event->accept();
}
