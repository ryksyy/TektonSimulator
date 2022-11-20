#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sim = new simulate();
    connect(sim, SIGNAL(sendData(QString)), this, SLOT(updateResult(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculate_clicked()
{
    sim->runSimulation(10000);
    ui->result->setText("Calculating 1 anvil rate. . .");
}

void MainWindow::updateResult(QString result)
{
    ui->result->setText(result);
}

