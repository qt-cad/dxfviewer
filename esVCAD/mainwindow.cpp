#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/dxf/dl_dxf.h"
#include <QFileDialog>
#include <QMessageBox>
#include <entities/coordxy.h>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->pushButtonMoveDown->setVisible(false);
    ui->pushButtonMoveUp->setVisible(false);
    ui->pushButtonMoveLeft->setVisible(false);
    ui->pushButtonMoveRight->setVisible(false);
    ui->pushButtonZoomIn->setVisible(false);
    ui->pushButtonZoomOut->setVisible(false);
    ui->pushButtonDxfParse->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DeleteEntities()
{
     std::vector<Block*>::iterator it=m_blocks.begin();
     for(;it!=m_blocks.end();++it){
         delete *it;
         *it=NULL;
     }
     m_blocks.clear();
}

void MainWindow::ShowEntities(std::vector<Block*> &blocks)
{

    ui->listWidgetEntities->clear();
    for(int i=0;i<blocks.size();++i)
    {
        Block *block=blocks[i];
        if(!block->IsEmpty())
        {
            for(int k=0;k<block->GetElementSize();++k)
            {
                QString s=QString::fromStdString(block->ElementAt(k)->ToString());
                ui->listWidgetEntities->addItem(s);
            }
        }


    }
}
void MainWindow::ParseDxf(const string &fileName)
{
    DL_Dxf dxf ;
    Dxf_CreationClass dxf_creationClass;
    if (!dxf.in(fileName, &dxf_creationClass)) { // if file open failed
        //std::cerr << file << " could not be opened.\n";
        QMessageBox::information(NULL, "dxf错误", "could not be opened.\n", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else
    {
        DeleteEntities();
        std::vector<Block*> blocks=dxf_creationClass.GetBlocks();
        m_coordRange=dxf_creationClass.GetCoordRange();
        //进行坐标转换
        int width=ui->m_graphicsFrame->width();
        int height=ui->m_graphicsFrame->height();
        double xScale=m_coordRange.GetWidth()/width;
        double yScale=m_coordRange.GetHeihgt()/height;
        double scale=std::max(xScale,yScale);
        Point leftTop(m_coordRange.GetLeftTop());

        double params[5]={scale,height,leftTop.GetX(),leftTop.GetY(),width};

        int count=blocks.size();
        for(int i=0;i<count;++i)
        {
            if(!blocks[i]->IsEmpty()&&blocks[i]->IsUse())
            {
                Block *block=blocks[i]->Clone();
                block->Transform(params,5);
                m_blocks.push_back(block);
            }

        }
        ShowEntities(m_blocks);
        ui->m_graphicsFrame->PaintEntities(m_blocks);

    }
}

void MainWindow::on_pushButtonSelFile_clicked()
{
    QFileDialog *fd=new QFileDialog(this);
    fd->setWindowTitle("请选择dxf文件");
    fd->setNameFilter(tr("dxf(*.dxf)"));
      if(fd->exec()==QFileDialog::Accepted) // ok
      {
        QStringList fileNameLists=fd->selectedFiles();
        if(fileNameLists.size()>0){
            m_sFileName=fileNameLists.at(0);
            on_pushButtonDxfParse_clicked();
        }else{
            QMessageBox::information(NULL, "dxf选择错误", "请选择dxf文件", QMessageBox::Yes, QMessageBox::Yes);
        }

      }
}

void MainWindow::on_pushButtonDxfParse_clicked()
{
    if(m_sFileName!=""){
      ParseDxf(m_sFileName.toStdString());
    }
}

void MainWindow::on_pushButtonShowEntities_clicked()
{

}

void MainWindow::on_pushButtonMoveRight_clicked()
{
    int dx=20;
    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Transfer(dx,0.0,0.0);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::on_pushButtonMoveLeft_clicked()
{
    int dx=-20;
    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Transfer(dx,0.0,0.0);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::on_pushButtonMoveUp_clicked()
{
    int dy=-20;
    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Transfer(0.0,dy,0.0);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::on_pushButtonMoveDown_clicked()
{
    int dy=20;
    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Transfer(0.0,dy,0.0);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::on_pushButtonZoomOut_clicked()
{
    double scale=2;
    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Scale(scale);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::on_pushButtonZoomIn_clicked()
{
    double scale=0.5;
    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Scale(scale);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    //进行坐标转换
    if(event->buttons()==Qt::MiddleButton)
    {
        int width=ui->m_graphicsFrame->width();
        int height=ui->m_graphicsFrame->height();
        double xScale=m_coordRange.GetWidth()/width;
        double yScale=m_coordRange.GetHeihgt()/height;
        double scale=std::max(xScale,yScale);
        Point leftTop(m_coordRange.GetLeftTop());
        double params[4]={scale,height,leftTop.GetX(),leftTop.GetY()};

        int count=m_blocks.size();
        for(int i=0;i<count;++i)
        {
            Block *block=m_blocks[i];
            block->Transform(params,4);
        }
        ui->m_graphicsFrame->PaintEntities(m_blocks);
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::MiddleButton)
    {
           m_dragEndPoint=event->pos();
           int dx=m_dragEndPoint.x()-m_dragBeginPoint.x();
           int dy=m_dragEndPoint.y()-m_dragBeginPoint.y();
           int count=m_blocks.size();
           for(int i=0;i<count;++i)
           {
               m_blocks[i]->Transfer(dx,dy,0.0);
           }
           ui->m_graphicsFrame->PaintEntities(m_blocks);
           m_dragBeginPoint=m_dragEndPoint;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::MiddleButton)
    {
        m_dragBeginPoint=event->pos();
    }
    else if(event->buttons()==Qt::LeftButton)
    {
        m_scaleBasePoint=event->pos();
    }

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}
void MainWindow::wheelEvent(QWheelEvent*event)
{
    double scale=0.9;
    if(event->delta()>0)
    {
        scale=1.1;
    }
    else
    {
        scale=0.9;
    }

    int count=m_blocks.size();
    for(int i=0;i<count;++i)
    {
        m_blocks[i]->Transfer(-m_scaleBasePoint.x(),-m_scaleBasePoint.y(),0.0);
        m_blocks[i]->Scale(scale);
        m_blocks[i]->Transfer(m_scaleBasePoint.x(),m_scaleBasePoint.y(),0.0);
    }
    ui->m_graphicsFrame->PaintEntities(m_blocks);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}
void MainWindow::dropEvent(QDropEvent *event)
{
    //注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    //如果想读取整个目录，则在不同的操作平台下，自己编写函数实现读取整个目录文件名
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;
     m_sFileName = urls.first().toLocalFile();
     if(m_sFileName!=""){
       ParseDxf(m_sFileName.toStdString());
     }
}

void MainWindow::on_listWidgetEntities_clicked(const QModelIndex &index)
{
    int currenRow = ui->listWidgetEntities->currentRow();
    if(currenRow>0)
    {

    }
}
