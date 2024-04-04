#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDropEvent>
#include <QMimeData>
#include <QFile>
#include <QMessageBox>
#include <jansson.h>
#include <fstream>
#include "Handlers/DataHandler/DataHandler.hpp"
#include "Widgets/TimelineWidget.hpp"
#include "Widgets/ExtendedPropertiesWidget.hpp"
#include "Widgets/MenuBar.hpp"
#include <nlohmann/json.hpp>
using nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::ActiveTabHasCloseButton, true);

    m_DockManager = new ads::CDockManager(this);

//    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget("CentralWidget");
//    CentralDockWidget->setFeature(ads::CDockWidget::NoTab, true);
//    m_DockManager->setCentralWidget(CentralDockWidget);

    ui::MenuBar::Init();

    ui::TimelineWidget::CreateWidget();
    ui::ExtendedProperties::CreateWidget();

    m_DockManager->addDockWidget(ads::CenterDockWidgetArea, ui::TimelineWidget::dockWidget);
    m_DockManager->addDockWidget(ads::BottomDockWidgetArea, ui::ExtendedProperties::dockWidget);

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

        ImportTaskkFile(file.fileName().toStdString());

//        std::ifstream f(file.fileName().toStdString());
//        json data = json::parse(f);
//        SessionStruct ses = DataHandler::ParseData(data);
//        ui::OperationsBarDataHandler::InitSession(ses);
//        json_auto_t* jsonData = json_load_file(file.fileName().toStdString().c_str(), JSON_ALLOW_NUL, nullptr);
    }
}

void MainWindow::ImportTaskkFile(std::string filePath) {
    std::ifstream f(filePath);
    json data = json::parse(f);
    SessionStruct ses = DataHandler::ParseData(data);
    ui::OperationsBarDataHandler::InitSession(ses);
}
