#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDropEvent>
#include <QMimeData>
#include <QFile>
#include <QMessageBox>
#include <jansson.h>
#include <fstream>
#include "Handlers/DataHandler/DataHandler.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

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
        if (event->mimeData()->hasText())
        {
            QFile file (event->mimeData()->text().remove("file:///"));
            if (!file.fileName().endsWith(".taskk", Qt::CaseInsensitive))
                return event->ignore();

            event->acceptProposedAction();
        }
    else event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasText())
    {
        QFile file (event->mimeData()->text().remove("file:///"));

        std::ifstream f(file.fileName().toStdString());
        json data = json::parse(f);
        SessionStruct ses = DataHandler::ParseData(data);
        ui::OperationsBarDataHandler::InitSession(ses);
//        json_auto_t* jsonData = json_load_file(file.fileName().toStdString().c_str(), JSON_ALLOW_NUL, nullptr);
//        std::cout << json_string_value(jsonData) << std::endl;
//        std::cout << "ww" << std::endl;
    }
}
