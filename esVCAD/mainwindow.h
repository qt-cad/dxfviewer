#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <string>
#include "dxf_parser/dxf_creationclass.h"
#include "entities/rect.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonSelFile_clicked();

    void on_pushButtonDxfParse_clicked();


    void on_pushButtonMoveRight_clicked();

    void on_pushButtonMoveLeft_clicked();

    void on_pushButtonMoveUp_clicked();

    void on_pushButtonMoveDown_clicked();

    void on_pushButtonZoomOut_clicked();

    void on_pushButtonZoomIn_clicked();
    void on_listWidgetEntities_clicked(const QModelIndex &index);

public:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent*event);
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
private:
    Ui::MainWindow *ui;
    QString m_sFileName;
    std::vector<Block*>  m_blocks;
    std::vector<Layer*>  m_layers;
    CoordXY m_coordXY;
    QPoint m_dragBeginPoint;
    QPoint m_dragEndPoint;
    QPoint m_scaleBasePoint;
private:
    void ParseDxf(const string &fileName);
    void DeleteEntities();
    void ShowEntities(std::vector<Block*> &blocks);
};

#endif // MAINWINDOW_H
