#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libGenerator.hpp"
#define Linux
#include "dlLoader.hpp"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_dataSet(-50.0, 50.0, 0.1),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_dataSet);
    // make the plot respond to mouse drag and wheel.
    // TODO: hookup a slot to capture this & maybe update
    // some scroll bars
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exec()
{
    // generate a shared library with the contents of the edit control
    // as a single function with the signature "double compute(x)"
    LibGenerator lg("./compute", ui->lineEditFunc->text().toStdString());
    // load it into memory.
    DlLoader dl("./compute.so");
    computeFunc f = dl.func<computeFunc>("compute");
    if(f)
    {
        // successfully loaded the compiled shared object lib.
        // invoke it on the data set
        m_dataSet.compute(-50.0, 50.0, 0.1, f);
        // remove any existing graphs
        ui->plot->removeGraph(0);
        // create a new one and replot it
        ui->plot->addGraph();
        // TODO: keep aspect ratio 1:1
        auto axes = ui->plot->selectedAxes();
        for(auto & axis : axes)
        {
            switch(axis->axisType())
            {
                    
            }
            /*
             atLeft
             0x01 Axis is vertical and on the left side of the axis rect
             atRight
             0x02 Axis is vertical and on the right side of the axis rect
             atTop
             0x04 Axis is horizontal and on the top side of the axis rect
             atBottom
             0x08 Axis is horizontal and on the bottom side of the axis rect
            */
        }
        // ui->plot->axisRect()->
        ui->plot->graph(0)->setData(m_dataSet.x(), m_dataSet.y());
        ui->plot->graph(0)->setAntialiased(true);
        ui->plot->xAxis->setRange(m_dataSet.minX(), m_dataSet.maxX());
        ui->plot->yAxis->setRange(m_dataSet.minY(), m_dataSet.maxY());
        ui->plot->replot();
    }

}
