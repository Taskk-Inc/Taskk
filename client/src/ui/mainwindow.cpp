#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDropEvent>
#include <QMimeData>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasText())
    {
        QFile file (event->mimeData()->text().remove("file:///"));

        QMessageBox::critical(this, "File Name", file.fileName());
    }
}
