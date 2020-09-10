#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>
class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {
        Astroid,
        Cycloid,
        HuygensCycloid,
        HypoCycloid,
        Line,
        Circle
    };

    void setBackgroundColor (QColor color) { mbackgroundColor = color; } // setter
    QColor BackgroundColor() const {return mbackgroundColor;} // getter

    void setShape(ShapeType shape) { mShape = shape; on_shape_changed ();} // setter
    ShapeType shape() const {return mShape;}          // getter

    void setScale (float scale ) {mScale = scale;repaint();} // setter
    float scale () const {return mScale;} // getter

    void setInterval (float interval ) { mIntervalLength = interval; repaint();} // setter
    float intervalLength () const {return mIntervalLength;} // getter

    void setStep (float step ) { mStepCount = step ; repaint();} // setter
    int step () const {return mStepCount;} // getter

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
private:
    QPointF compute (float t); // dispatch function
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute_line(float t);
    QPointF compute_circle(float t);
    void on_shape_changed ();
private:
    QColor mbackgroundColor;
    QColor mShapeColor ;
    ShapeType mShape;
    float mIntervalLength;
    float mScale;
    int mStepCount;
};

#endif // RENDERAREA_H
