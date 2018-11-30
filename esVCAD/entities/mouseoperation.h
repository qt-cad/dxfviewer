#ifndef MOUSEOPERATION_H
#define MOUSEOPERATION_H
#include <QMouseEvent>
class MouseOperation{
protected:
    MouseOperation(){}
public:
    virtual~MouseOperation(){}
public:
    //鼠标事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event){}
    virtual void mouseMoveEvent(QMouseEvent *event){}
    virtual void mousePressEvent(QMouseEvent *event){}
    virtual void mouseReleaseEvent(QMouseEvent *event){}
    virtual void wheelEvent(QWheelEvent*event){}//滚轮
    virtual void dragEnterEvent(QDragEnterEvent *event){}
    virtual void dragMoveEvent(QDragMoveEvent *event){}
    virtual void dragLeaveEvent(QDragLeaveEvent *event){}
    virtual void dropEvent(QDropEvent *event){}
};
#endif // MOUSEOPERATION_H
