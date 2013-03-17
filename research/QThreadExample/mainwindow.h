#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ctimer.h"
#include "cupdater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CTimer timer;
    CUpdater updater;
private:
    Ui::MainWindow *ui;
private slots:
    void onTimerUpdate(QString time);
    void onMouseMove(QPoint pos);
};

#endif // MAINWINDOW_H
