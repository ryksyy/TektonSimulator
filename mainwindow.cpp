#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sim = new simulate();
    connect(sim, SIGNAL(sendData(float)), this, SLOT(updateResult(float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculate_clicked()
{
    sim->setGear(5,5,false);
}

void MainWindow::updateResult(float chance)
{
    ui->result->setText(QString::number(chance));
}

