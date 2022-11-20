#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simulate.h"
#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow ; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    simulate *sim = nullptr;

private slots:
    void on_calculate_clicked();
    void updateResult(QString);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
