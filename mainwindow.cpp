#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::gameActive()
{
    return gameBool;
}

void MainWindow::on_PlayButton_clicked()
{
    Game = new game;
    gameBool = true;
    Game->initiate();
}

void MainWindow::on_ExitButton_clicked()
{
    this->~MainWindow();
}

void MainWindow::update()
{
}

