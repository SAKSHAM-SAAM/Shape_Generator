#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <cmath>
RenderArea::RenderArea(QWidget *parent) : QWidget(parent) ,
    mbackgroundColor(0,0,255) ,
    mShapeColor(255,255,255),
    mShape(Astroid)
{
    on_shape_changed();
}
QSize RenderArea::minimumSizeHint() const
{
    return QSize(400,400);
}
QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}
void RenderArea::on_shape_changed (){
    switch (mShape) {
    case Astroid:
        //mbackgroundColor = Qt::red;
        mScale=40;
        mIntervalLength = 2*M_PI;
        mStepCount = 256;
        break;
    case Cycloid:
        //mbackgroundColor = Qt::green;
        mScale= 4;
        mIntervalLength = 6*M_PI;
        mStepCount = 128;
        break;
    case HuygensCycloid:
        //mbackgroundColor = Qt::blue;
        mScale = 4;
        mIntervalLength = 4*M_PI;
        mStepCount = 256;
        break;
    case HypoCycloid:
        //mbackgroundColor = Qt::yellow;
        mScale = 8;
        mIntervalLength = 2*M_PI;
        mStepCount = 256;
        break;
    case Line:
        //mbackgroundColor = Qt::white;
        mScale = 5; // 50
        mIntervalLength = 2*M_PI ; // 1 for line
        mStepCount = 256 ; // 128
        break;
    case Circle:
        mScale = 50;
        mIntervalLength = 2*M_PI;
        mStepCount = 128;
        break;
    default:
        break;
    }
}
QPointF RenderArea::compute (float t){
    switch (mShape) {
    case Astroid:
        return compute_astroid(t);
        break;
    case Cycloid:
        return compute_cycloid(t);
        break;
    case HuygensCycloid:
        return compute_huygens(t);
        break;
    case HypoCycloid:
        return compute_hypo(t);
        break;
    case Line:
        return compute_line(t);
        break;
    case Circle:
        return compute_circle(t);
        break;
    default:
        break;
    }
    return QPointF(0,0);
}
QPointF RenderArea::compute_astroid(float t){
    float sin_t = sin (t);
    float cos_t = cos (t);

    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x,y);
}
QPointF RenderArea::compute_cycloid(float t){
    return QPointF(
                1.5 * (1 - cos(t)), // X co-ord
                1.5 * (t - sin(t))  // T co-ord
                );
}
QPointF RenderArea::compute_huygens(float t){
    return QPointF(
                4 * (3 * cos (t) - cos (3 * t)), // X co-ord
                4 * (3 * sin (t) - sin (3 * t))  // Y co-ord
                ) ;
}
QPointF RenderArea::compute_hypo(float t){
    return QPointF(
                1.5 * (2 * cos (t) + cos (2 * t)), // X co-ord
                1.5 * (2 * sin (t) - sin (2 * t))  // Y co-ord
                );
}
QPointF RenderArea::compute_line(float t){
    return QPointF(
                    1 - t,
                    1 - t
                );
}
QPointF RenderArea::compute_circle(float t){
    return QPointF(
                1 * cos (t),
                1 * sin (t)
                );
}
void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);


    painter.setBrush(mbackgroundColor);
    painter.setPen(mShapeColor);
    // drawing area
    painter.drawRect(this->rect());
    QPoint center = this->rect().center();
    QPointF prevPoint = compute(0);
    QPoint prevPixel ;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());
    // implementing mathematical functions
    float step = mIntervalLength/mStepCount;

    for(float t=0;t<mIntervalLength;t+=step){
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }
}
