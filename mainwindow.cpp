#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui(){
    this->ui->spinScale->setValue(this->ui->renderArea->scale());
    this->ui->spinInterval->setValue(this->ui->renderArea->intervalLength());
    this->ui->spinSteps->setValue(this->ui->renderArea->step());
}

void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Astroid);
    this->ui->renderArea->repaint();

    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    this->ui->renderArea->repaint();

    update_ui();
}


void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();

    update_ui();
}


void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();

    update_ui();
}


void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    this->ui->renderArea->repaint();

    update_ui();
}

void MainWindow::on_btnCircle_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Circle);
    this->ui->renderArea->repaint();

    update_ui();
}

void MainWindow::on_spinInterval_valueChanged(double interval)
{
    this->ui->renderArea->setInterval(interval);
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale(scale);
}

void MainWindow::on_spinSteps_valueChanged(int steps)
{
    this->ui->renderArea->setStep(steps);
}

void MainWindow::on_btnBackgroundColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->BackgroundColor(), this , "Select Color ") ;
    this->ui->renderArea->setBackgroundColor(color);
}

void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->ShapeColor(), this , "Select Color ") ;
    this->ui->renderArea->setShapeColor(color);
}
