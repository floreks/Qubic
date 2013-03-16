#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("QThread test");

    QThread *firstThread = new QThread; // creating our thread object
    QThread *secondThread = new QThread;
    timer.moveToThread(firstThread); // moving our working class to thread pipe
    updater.moveToThread(secondThread);

    connect(firstThread,SIGNAL(started()),&timer,SLOT(start())); // connecting start functions
    connect(firstThread, SIGNAL(finished()),&timer,SLOT(deleteLater()));
    connect(&timer,SIGNAL(timeUpdated(QString)),this,SLOT(onTimerUpdate(QString))); // working with emited signals

    connect(secondThread,SIGNAL(started()),&updater,SLOT(start()));
    connect(secondThread,SIGNAL(finished()),&updater,SLOT(deleteLater()));
    qRegisterMetaType<POINT>("POINT"); // as qt doesn't now windows api structures we need to register it in their metasystem
    connect(&updater,SIGNAL(mouseMove(POINT)),this,SLOT(onMouseMove(POINT)));

    firstThread->start(); // starting threads
    secondThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Working with signals from our threads

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
