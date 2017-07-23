/*
 *   This file is part of Revised, a visual editor for Ren'Py
 *   Copyright 2014-2015  Ray             <ray.cn@gmail.com>
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


#include "gameobject.h"
#include <QDebug>
#include <QFile>
#include <QColor>
#include <QFont>
#include <math.h>
#include <QPen>
#include <QPainter>
//static ObjectEditorWidget * mEditorWidget = 0;
static QFont mDefaultFont;

GameObject::GameObject(QObject* parent, const QString& name, QPixmap *img)
{
    init(name);
    updateResizeRects(); 
    mImage = img;
    //emit dataChanged();
}

GameObject::GameObject(const QVariantMap& data, QObject* parent)
{
    init("GameObject");
    _load(data);
    updateResizeRects();
    //emit dataChanged();
}

void GameObject::init(const QString& name)
{
    mOpacity = 255;
//    mBackground.setColor(QColor(255, 255, 255, 0));
    mCornerRadius = 0;
    mOriginalResizePointIndex = -1;
    mVisible = true;
    mPercentWidth = 0;
    mPercentHeight = 0;
    mBorderWidth = 0;
    mBorderColor = QColor();
    mSelectedObject = 0;
    mKeepAspectRatio = false;
    mAspectRatio = 1;
    //mScaledBackgroundImage = 0;
#if 0
    //mEventToActions.insert(Interaction::MouseMove, QList<Action*>());
   // mEventToActions.insert(Interaction::MousePress, QList<Action*>());
    //mEventToActions.insert(Interaction::MouseRelease, QList<Action*>());

    //check if name is valid
    if (objectName().isEmpty()) {
        if (parent() == ResourceManager::instance())
            setName(ResourceManager::instance()->newName(name));
        else {
            Scene* scene = qobject_cast<Scene*>(parent());
            if (scene)
                scene->newObjectName(name);
        }
    }
#endif
}

GameObject::~GameObject()
{
    emit destroyed(this);

//    if (mBackground.image())
//        AssetManager::instance()->releaseAsset(mBackground.image());
}

QVariantMap GameObject::fillWithResourceData(QVariantMap data)
{
    QString name = data.value("resource").toString();

//    GameObject* resource = ResourceManager::instance()->resource(name);
//    if (! resource)
//        return data;

//    QVariantMap resourceData = resource->toJsonObject();
//    QStringList keys = resourceData.keys();
//    foreach(const QString& key, keys)
//        if (! data.contains(key))
//            data.insert(key, resourceData.value(key));

    return data;
}

bool GameObject::isValidName(const QString& name)
{
#if 0
    if (name.isEmpty())
        return false;

    //check if parent is the scene
    Scene* scene = this->scene();
    if (scene)
        return scene->isValidObjectName(name);

    //check if parent is the resource manager
    ResourceManager* resourceManager = qobject_cast<ResourceManager*>(parent());
    if (resourceManager)
        return resourceManager->isValidName(name);
#endif 
    return true;
}

bool GameObject::contains(qreal x, qreal y)
{
    if (mSceneRect.contains(x, y) || containsResizeRectAt(x, y))
        return true;

    return false;
}

QRect GameObject::sceneRect() const
{
    return mSceneRect;
}

void GameObject::onResizeEvent(QResizeEvent* event)
{
    return;

    int width = 0;//Scene::width() - mSceneRect.width();
    int height = 0;//Scene::height() - mSceneRect.height();

    mSceneRect.setWidth(mSceneRect.width() + width);
    mSceneRect.setHeight(mSceneRect.height() + height);
}

void GameObject::move(int x, int y)
{
    mSceneRect.moveTo(x, y);
    updateResizeRects();
    QVariantMap data;
    data.insert("x", x);
    data.insert("y", y);
 //   emit dataChanged(data);
    //emit positionChanged(mSceneRect.x(), mSceneRect.y());
}

void GameObject::dragMove(int x, int y)
{
    if (mPreviousSceneRect.isEmpty() || mPreviousSceneRect.isNull()) {
        mPreviousSceneRect = mSceneRect;
        mXDif = x - mSceneRect.x();
        mYDif = y - mSceneRect.y();
    }

    //since x and y represent mouse coordinates and we move the rectangle by moving its top left corner,
    //we need to know the initial distance from the point where the mouse was clicked to the top left corner.
    move(x - mXDif, y - mYDif);
}

void GameObject::stopMove()
{
    mPreviousSceneRects.append(mPreviousSceneRect);
    mPreviousSceneRect = QRect();
}

QList<QRect> GameObject::previousSceneRects() const
{
    return mPreviousSceneRects;
}
/*
ObjectEditorWidget* GameObject::objectEditorWidget()
{
    return mEditorWidget;
}

void GameObject::setObjectEditorWidget(ObjectEditorWidget* widget)
{
    mEditorWidget = widget;
}

ObjectEditorWidget* GameObject::editorWidget()
{
    return mEditorWidget;
}
*/




int GameObject::opacity() const
{
    return mOpacity;
}

qreal GameObject::opacityF() const
{
    return (mOpacity * 1.0) / 255;
}

void GameObject::setOpacity(int opacity)
{
    if (opacity > 255)
        opacity = 255;
    else if (opacity < 0)
        opacity = 0;

    if (opacity != mOpacity){
        int prevOpacity = mOpacity;
        mOpacity = opacity;
        notify("opacity", mOpacity, prevOpacity);
    }
}


void GameObject::setWidth(int w, bool percent)
{
    int width = mSceneRect.width();

    if (percent) {
        mPercentWidth = w;
        GameObject * obj = qobject_cast<GameObject*>(parent());
        if (obj)
            width = obj->width() * w / 100;
//        else if (scene())
//            width = scene()->width() * w / 100;

        mSceneRect.setWidth(width);
    }
    else {
        mSceneRect.setWidth(w);
        mPercentWidth = 0;
    }

    updateResizeRects();

    notify("width", mSceneRect.width(), width);
}

void GameObject::setHeight(int h, bool percent)
{
    int height = mSceneRect.height();

    if (percent) {
        mPercentHeight = h;
        GameObject * obj = qobject_cast<GameObject*>(parent());
        if (obj)
            height = obj->height() * h / 100;
//        else if(scene())
//           height = scene()->height() * h / 100;

        mSceneRect.setHeight(height);
    }
    else {
        mPercentHeight = 0;
        mSceneRect.setHeight(h);
    }

    updateResizeRects();

    notify("height", mSceneRect.height(), height);
}

void GameObject::setY(int y)
{
    mSceneRect.moveTo(mSceneRect.x(), y );
    updateResizeRects();
    //FIXME: Implement proper relative positions.
    notify("y", this->y());
}

void GameObject::setX(int x)
{
    mSceneRect.moveTo(x , mSceneRect.y());
    updateResizeRects();
    notify("x", this->x());
}

int GameObject::x() const
{
    return mSceneRect.x();
}

int GameObject::y() const
{
    return mSceneRect.y();
}

int GameObject::parentWidth() const
{
    if (! parent())
        return 0;
    GameObject* p = qobject_cast<GameObject*>(parent());

    if (p)
        return p->width();
//    else
//        return Scene::width();
}

int GameObject::width() const
{
    int width = contentWidth();
    //width += mPadding.left() + mPadding.right();

    return width;
}

int GameObject::contentWidth() const
{
    int width = 0;
    if (mPercentWidth)
        width = mPercentWidth / 100 * parentWidth();
    else
        width = mSceneRect.width();

    return width;
}

int GameObject::parentHeight() const
{
    if (! parent())
        return 0;
    GameObject* p = qobject_cast<GameObject*>(parent());
    if (p)
        return p->height();
//    else
    //     return Scene::height();
}

int GameObject::contentHeight() const
{
    int height = 0;

    if (mPercentHeight)
        height = mPercentHeight / 100 * parentHeight();
    else
        height = mSceneRect.height();

    return height;
}

int GameObject::height() const
{
    int height = contentHeight();
    //height += mPadding.top() + mPadding.bottom();

    return height;
}

void GameObject::update()
{
   // emit dataChanged();
}

bool GameObject::isRounded() const
{
    if (mCornerRadius)
        return true;
    return false;
}

void GameObject::setCornerRadius(int r)
{
    if (mCornerRadius != r) {
        mCornerRadius = r;
        QVariantMap data;
        data.insert("cornerRadius", r);
//        emit dataChanged(data);
    }
}

int GameObject::cornerRadius()
{
    return mCornerRadius;
}

void GameObject::paint(QPainter & painter)
{

    //QRect rect(mSceneRect.x(), mSceneRect.y(), contentWidth(), contentHeight());
    QRect rect(mSceneRect.x(), mSceneRect.y(), 320, 240);
    if (! mVisible || ! mOpacity) {
        QPen pen(Qt::white);
        painter.setOpacity(0.5);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawRect(rect);
        painter.setOpacity(0);
        return;
    }

    qreal opacity = opacityF() * painter.opacity();
    painter.setOpacity(opacity);
//    mBackground.paint(painter, rect, mCornerRadius, opacity);
    if (mImage)
        painter.drawPixmap(30, 80,
        320, 240,
        *mImage);

    painter.drawRect(rect);

    QImage out(rect.width(), rect.height(), QImage::Format_ARGB32_Premultiplied);
    out.fill(0);
    QPainter p(&out);
    QPixmap pixmap = *mImage;
    
    //add support for other positions in the future
    pixmap = pixmap.scaled(rect.width(), rect.height());

    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(pixmap));
    p.drawRoundedRect(out.rect(), mCornerRadius, mCornerRadius);
    p.drawPixmap(0, 0,
        320, 240,
        pixmap);
    p.end();
    mScaledBackgroundImage = QPixmap::fromImage(out);
    


    if (mBorderColor.isValid()) {
        if (mBorderWidth)
            painter.setPen(QPen(mBorderColor, mBorderWidth));
        else
            painter.setPen(Qt::NoPen);
        if (mCornerRadius)
            painter.drawRoundedRect(rect, mCornerRadius, mCornerRadius);
        else
            painter.drawRect(rect);
    }
}

GameObject* GameObject::copy()
{
    //return ResourceManager::instance()->createObject(toJsonObject(true), this->parent());
    return this;
}



#if 0


void GameObject::setBackgroundImage(const QString & path)
{
    ImageFile* image = mBackground.image();

    if (image && image->path() == path)
        return;




    QString prevPath("");
    if (mBackground.image())
        mBackground.image()->path();
    mBackground.setImage(image);
    notify("backgroundImage", path, prevPath);
}

ImageFile* GameObject::backgroundImage() const
{
    return mBackground.image();
}

#endif


QVariantMap GameObject::toJsonObject(bool internal)
{
    QVariantMap object;
    return object;
}


void GameObject::resize(int pointIndex, int x, int y)
{
    //QPoint point = rect.center();
    QPoint toPoint(x, y);
    mOriginalResizePointIndex = pointIndex;
    movePoint(pointIndex, toPoint);
    updateResizeRects();

    //if (i < 8)
      //  updateResizeRects();
    //if (i < 8)
    //    emit dataChanged();
}

void GameObject::resize(int x, int y)
{
    if (mOriginalResizePointIndex == -1)
        return;

    QPoint point (x, y);
    movePoint(mOriginalResizePointIndex, point);

    if (mKeepAspectRatio) {
        int w2 = width();
        int h2 = round(w2/mAspectRatio);
        fixPoint(mOriginalResizePointIndex, w2, h2);
    }

    updateResizeRects();
    QVariantMap data;
    data.insert("width", width());
    data.insert("height", height());
    //emit dataChanged(data);
}

void GameObject::fixPoint(int pindex, int w, int h)
{
    QPoint point;
    int x, y;

    switch (pindex){
        case 0:
            point = mSceneRect.bottomRight();
            x = point.x() - w;
            y = point.y() - h;
            mSceneRect.setTopLeft(QPoint(x, y));
            break;
        case 2:
            point = mSceneRect.bottomLeft();
            y = point.y() - h;
            x = point.x() + w;
            mSceneRect.setTopRight(QPoint(x, y));
            break;

        case 4:
            point = mSceneRect.topLeft();
            y = point.y() + h;
            x = point.x() + w;
            mSceneRect.setBottomRight(QPoint(x, y));
            break;

        case 6:
            point = mSceneRect.topRight();
            y = point.y() + h;
            x = point.x() - w;
            mSceneRect.setBottomLeft(QPoint(x, y));
            break;
    }
}

void GameObject::movePoint(int which, QPoint& point)
{
    QPoint point2;

    switch(which)
    {
    case 0:
        point2 = mSceneRect.bottomRight();
        if (point.x() > point2.x())
            point.setX(point2.x());
        if (point.y() > point2.y())
            point.setY(point2.y());
        mSceneRect.setTopLeft(point);
        updateResizeRect(0, mSceneRect.topLeft());
        break;
    case 1:
         point2 = mSceneRect.bottomLeft();
         if (point.y() < point2.y())
            mSceneRect.setY(point.y());
         break;
    case 2:
        point2 = mSceneRect.bottomLeft();
        if (point.x() < point2.x())
            point.setX(point2.x());
        if (point.y() > point2.y())
            point.setY(point2.y());
        mSceneRect.setTopRight(point);
        updateResizeRect(2, mSceneRect.topRight());
        break;
    case 3:
        point2 = mSceneRect.bottomLeft();
        if (point.x() > point2.x())
            mSceneRect.setWidth(point.x()-mSceneRect.x());
        break;
    case 4:
        point2 = mSceneRect.topLeft();
        if (point.x() < point2.x())
            point.setX(point2.x());
        if (point.y() < point2.y())
            point.setY(point2.y());
        mSceneRect.setBottomRight(point);
        updateResizeRect(4, mSceneRect.bottomRight());
        break;
    case 5:
        point2 = mSceneRect.topRight();
        if (point.y() > point2.y())
            mSceneRect.setHeight(point.y()-mSceneRect.y());
        break;
    case 6:
        point2 = mSceneRect.topRight();
        if (point.x() > point2.x())
            point.setX(point2.x());
        if (point.y() < point2.y())
            point.setY(point2.y());
        mSceneRect.setBottomLeft(point);
        updateResizeRect(6, mSceneRect.bottomLeft());
        break;
    case 7:
        point2 = mSceneRect.topRight();
        if (point.x() < point2.x())
            mSceneRect.setX(point.x());
        break;
    }
}

QList<QRect> GameObject::resizeRects()
{
    return mResizeRects;
}

void GameObject::updateResizeRect(int i, const QPoint& point)
{
    int rectWidth = RESIZE_RECT_WIDTH;
    int rectWidthHalf = rectWidth/2;

    if (i >= 0 && i < mResizeRects.size()) {
        QRect rect = mResizeRects.at(i);
        rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
        mResizeRects.replace(i, rect);
    }
}

void GameObject::updateResizeRects()
{
    int rectWidth = RESIZE_RECT_WIDTH;
    int rectWidthHalf = rectWidth/2;

    mResizeRects.clear();
    //top left
    QPoint point = mSceneRect.topLeft();
    QRect rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //middle top
    point.setX(point.x() + mSceneRect.width()/2);
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //top right
    point = mSceneRect.topRight();
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //middle right
    point.setY(point.y()+mSceneRect.height()/2);
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //bottom right
    point = mSceneRect.bottomRight();
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //middle bottom
    point.setX(point.x() - mSceneRect.width()/2);
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //bottom left
    point = mSceneRect.bottomLeft();
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);

    //middle left
    point.setY(point.y() - mSceneRect.height()/2);
    rect = QRect(point.x()-rectWidthHalf, point.y()-rectWidthHalf, rectWidth, rectWidth);
    mResizeRects.append(rect);
}


QRect GameObject::resizeRectAt(int x, int y)
{
    foreach(const QRect& rect, mResizeRects) {
        if (rect.contains(x, y))
            return rect;
    }

    return QRect();
}

bool GameObject::containsResizeRectAt(int x, int y)
{
    foreach(const QRect& rect, mResizeRects) {
        if (rect.contains(x, y))
            return true;
    }

    return false;
}

void GameObject::setHoveredResizeRect(int i)
{
    mOriginalResizePointIndex = i;
    if (i < 0 || i >= mResizeRects.size())
        mOriginalResizePointIndex = -1;
}

void GameObject::stopResizing()
{
    mOriginalResizePointIndex = -1;
}

bool GameObject::visible()
{
    return mVisible;
}

void GameObject::setVisible(bool visible)
{
    mVisible = visible;
    this->notify("visible", visible);
}

GameObject* GameObject::objectAt(qreal x, qreal y)
{
    if (this->contains(x, y))
        return this;
    return 0;
}

void GameObject::selectObjectAt(qreal x, qreal y)
{
    mSelectedObject = objectAt(x, y);
}

GameObject* GameObject::selectedObject()
{
    return mSelectedObject;
}



bool GameObject::hasObjectAsParent()
{
    if (! this->parent())
        return false;

    if (qobject_cast<GameObject*>(this->parent()))
        return true;

    return false;
}

void GameObject::_load(const QVariantMap &data)
{
    QVariantList eventActions;
    QVariantMap actionData;


    if (data.isEmpty())
        return;

    //blockNotifications(true);

    if (data.contains("name") && data.value("name").type() == QVariant::String)
        setObjectName(data.value("name").toString());

    if (data.contains("opacity") && data.value("opacity").canConvert(QVariant::Int))
        setOpacity(data.value("opacity").toInt());




    if (data.contains("x") && data.value("x").canConvert(QVariant::Int)) {
        mSceneRect.setX(data.value("x").toInt());
    }

    if (data.contains("y") && data.value("y").canConvert(QVariant::Int))
        mSceneRect.setY(data.value("y").toInt());




    if (data.contains("cornerRadius") && data.value("cornerRadius").canConvert(QVariant::Int)) {
        setCornerRadius(data.value("cornerRadius").toInt());
    }

    if (data.contains("visible") && data.value("visible").type() == QVariant::Bool)
        setVisible(data.value("visible").toBool());



}

void GameObject::load(const QVariantMap &data)
{
    QVariantMap _data = data;
    //properties that shouldn't be copied!
    _data.remove("x");
    _data.remove("y");
    _data.remove("name");
    _data.remove("visible");
    _data.remove("sync");
    this->_load(_data);
}

void GameObject::notify(const QString & key, const QVariant & value, const QVariant & prev)
{
    QVariantMap data;
    data.insert(key, value);
    if (prev.isValid())
        data.insert("previousValue", prev);

    //emit dataChanged(data);
}
#if 0
bool GameObject::isResource() const
{
    return this->parent() == ResourceManager::instance() ? true : false;
}

void GameObject::copyResourceActions(Interaction::InputEvent event)
{
    QList<Action*> actions = mEventToActions.value(event);
    QList<Action*> copiedActions;
    Action* action = 0;

    for(int i=0; i < actions.size(); i++) {
        if (actions[i]->parent() != this)
            action = ActionInfoManager::typeToAction(actions[i]->toJsonObject(), this);
        else
            action = actions[i];
        copiedActions.append(action);
    }

    mEventToActions.insert(event, copiedActions);
}
#endif
void GameObject::onParentResized(int w, int h)
{
    if (mPercentWidth)
        setWidth(width()*w/100);

    if(mPercentHeight)
        setHeight(height()*h/100);
}

int GameObject::percentWidth() const
{
    return mPercentWidth;
}

int GameObject::percentHeight() const
{
    return mPercentHeight;
}

int GameObject::borderWidth()
{
    return mBorderWidth;
}

void GameObject::setBorderWidth(int w)
{
    if (mBorderWidth == w)
        return;

    mBorderWidth = w;
    this->notify("borderWidth", w);
}

QColor GameObject::borderColor()
{
    return mBorderColor;
}

void GameObject::setBorderColor(const QColor & color)
{
    if (mBorderColor == color)
        return;

    mBorderColor = color;

}

QString GameObject::defaultFontFamily()
{
    return mDefaultFont.family();
}

void GameObject::setDefaultFontFamily(const QString& family)
{
    mDefaultFont.setFamily(family);
}

int GameObject::defaultFontSize()
{
    return mDefaultFont.pixelSize();
}

void GameObject::setDefaultFontSize(int size)
{
    mDefaultFont.setPixelSize(size);
}

void GameObject::setDefaultFont(const QFont& font)
{
    mDefaultFont = font;
}

QFont GameObject::defaultFont()
{
    return mDefaultFont;
}

void GameObject::show()
{
 //   if (mBackground.image() && mBackground.image()->movie())
 //       mBackground.image()->movie()->start();
}

void GameObject::hide()
{
//    if (mBackground.image() && mBackground.image()->movie())
 //       mBackground.image()->movie()->stop();
}

bool GameObject::keepAspectRatio()
{
    return mKeepAspectRatio;
}

void GameObject::setKeepAspectRatio(bool keep)
{
    mKeepAspectRatio = keep;
    if (mKeepAspectRatio && mAspectRatio != 1) {
        int w = width();
        int h = round(w/mAspectRatio);
        mSceneRect.setHeight(h);
        updateResizeRects();
    }
}

bool GameObject::setName(const QString & name)
{
    if (this->isValidName(name)){
        setObjectName(name);
        QVariantMap data;
        data.insert("name", name);
        //emit dataChanged(data);
        return true;
    }

   return false;
}

QString GameObject::name()
{
    return objectName();
}

void GameObject::updateAspectRatio()
{
    mAspectRatio = (float) width() / height();
}

void GameObject::connectToResource()
{
    GameObject::connectToResource();
    //GameObject * resource = qobject_cast<GameObject*>(this->resource());

}
