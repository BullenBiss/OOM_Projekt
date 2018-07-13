#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool gameActive();
    void update();

private slots:

    void on_PlayButton_clicked();
    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;
    game *Game;
    bool gameBool = false;

};

#endif // MAINWINDOW_H
