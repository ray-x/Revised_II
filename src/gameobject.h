#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QPixmap>
#include <QRectF>
#include <QResizeEvent>
#include <QString>
#include <QHash>
#define RESIZE_RECT_WIDTH 7


#include <QString>

class Interaction
{

public:
    enum InputEvent {
        None = 0,
        MousePress = 1,
        MouseRelease = 2,
        MouseMove = 3
    };


    static QString toString(InputEvent ev) {
        switch (ev) {
            //TODO: Rename events
        case None:
            return "None";
        case MousePress:
            return "onMousePress";
        case MouseRelease:
            return "onMouseRelease";
        case MouseMove:
            return "onMouseMove";
        }

        return "";
    }

    Q_DECLARE_FLAGS(InputEvents, InputEvent);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Interaction::InputEvents);


class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0);





signals:

public slots:

public:

    explicit GameObject(QObject* parent=0, const QString& name="GameObject", QPixmap *img=nullptr);
    GameObject(const QVariantMap& data, QObject* parent=0);
    virtual ~GameObject();
    bool contains(qreal, qreal);
    QRect sceneRect() const;
    virtual void resize(int, int);
    virtual void resize(int, int, int);
    virtual void move(int x, int y);
    void dragMove(int x, int y);
    void stopMove();
    QList<QRect> previousSceneRects() const;
    void stopResizing();
    int percentWidth() const;
    int percentHeight() const;
    bool isValidName(const QString&);

    int borderWidth();
    void setBorderWidth(int);
    QColor borderColor();
    void setBorderColor(const QColor&);

    virtual void show();
    virtual void hide();

    void fixPoint(int, int, int);

    /*int backgroundColorOpacity() const;
    void setBackgroundColorOpacity(int);

    int backgroundImageOpacity() const;
    void setBackgroundImageOpacity(int);*/



    int opacity() const;
    qreal opacityF() const;
    virtual void setOpacity(int);

    int width() const;
    int height() const;
    int contentWidth() const;
    int contentHeight() const;
    virtual void setWidth(int, bool percent=false);
    virtual void setHeight(int, bool percent=false);
    virtual void setX(int);
    virtual void setY(int);
    int x() const;
    int y() const;

    bool isRounded() const;
    int cornerRadius();
    void setCornerRadius(int);

    //ImageFile* backgroundImage() const;
    //void setBackgroundImage(const QString&);

    bool visible();
    void setVisible(bool);

    void update();
//    void setEventActions(Interaction::InputEvent, const QList<Action*> &);
    void removeEventActionAt(Interaction::InputEvent, int, bool del=false);
    void removeEventActions(Interaction::InputEvent, bool del=false);
    void moveSharedEventActions(GameObject*, GameObject*, Interaction::InputEvent);
    void moveAllSharedEventActions(GameObject*, GameObject*);
    virtual void paint(QPainter&);
    GameObject* copy();
    virtual QVariantMap toJsonObject(bool internal=true);
    bool containsResizeRectAt(int, int);
    QRect resizeRectAt(int, int);
    QList<QRect> resizeRects();
    void updateResizeRect(int, const QPoint&);
    void setHoveredResizeRect(int);
    virtual GameObject* objectAt(qreal, qreal);
    void selectObjectAt(qreal, qreal);
    GameObject* selectedObject();

    int padding(const QString&);
    void setPadding(const QString&, int);

    void filterResourceData(QVariantMap&);
    QVariantMap fillWithResourceData(QVariantMap);

    bool isResource() const;

    bool setName(const QString&);
    QString name();

    bool hasObjectAsParent();
    bool keepAspectRatio();
    void setKeepAspectRatio(bool);

    static QString defaultFontFamily();
    static void setDefaultFontFamily(const QString&);
    static int defaultFontSize();
    static void setDefaultFontSize(int);
    static QFont defaultFont();
    static void setDefaultFont(const QFont&);

public slots:
    void onResizeEvent(QResizeEvent*);
    virtual void load(const QVariantMap &);
    void onParentResized(int, int);


//    private slots:
//        void eventActionChanged();

signals:

    void positionChanged(int, int);
    void resized(int, int);
    void destroyed(GameObject* object=0);
    void synced();

private:
    //void init(const QString &, int, int, QObject*);
    void init(const QString&);
    void updateResizeRects();
    void movePoint(int, QPoint&);
    int parentWidth() const;
    int parentHeight() const;
    void updateScaledBackgroundImage();
    void _load(const QVariantMap&);

    void copyResourceActions(Interaction::InputEvent);
    void sync();
    void unsync();


protected:
    QRect mSceneRect;
    QRect mBoundingRect;
    QRect mPreviousSceneRect;
    QRect mPreviousResizeRect;
    int mPercentWidth;
    int mPercentHeight;
    float mXDif;
    float mYDif;

    QList<QRect> mPreviousSceneRects;

    void notify(const QString&, const QVariant&, const QVariant& prev=QVariant());
    void updateAspectRatio();
    virtual void connectToResource();

private: //variables
    QList<QRect> mResizeRects;
    bool mVisible;
    int mOriginalResizePointIndex;
    float mAspectRatio;
    int mOriginalWidth;
    int mBorderWidth;
    int mOpacity;
    QColor mBorderColor;
    GameObject* mSelectedObject;
    bool mKeepAspectRatio;
    int mCornerRadius;
    QPixmap mScaledBackgroundImage;
    QPixmap *mImage;
//    Background mBackground;

};

#endif // GAMEOBJECT_H
