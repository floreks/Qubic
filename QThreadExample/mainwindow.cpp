#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("QThread test");

    QThread *firstThread = new QThread;
    QThread *secondThread = new QThread;
    timer.moveToThread(firstThread);
    updater.moveToThread(secondThread);

    connect(firstThread,SIGNAL(started()),&timer,SLOT(start()));
    connect(firstThread, SIGNAL(finished()),&timer,SLOT(deleteLater()));
    connect(&timer,SIGNAL(timeUpdated(QString)),this,SLOT(onTimerUpdate(QString)));

    connect(secondThread,SIGNAL(started()),&updater,SLOT(start()));
    connect(secondThread,SIGNAL(finished()),&updater,SLOT(deleteLater()));
    qRegisterMetaType<POINT>("POINT");
    connect(&updater,SIGNAL(mouseMove(POINT)),this,SLOT(onMouseMove(POINT)));

    firstThread->start();
    secondThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onTimerUpdate(QString time)
{
    ui->label->setText(time);
}

void MainWindow::onMouseMove(POINT pos)
{
    QString text;
    text = "X: ";
    text += QString::number(pos.x+1);
    text += " Y: ";
    text +=QString::number(pos.y+1);

    ui->label_4->setText(text);
}
