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

    InitStylesheet();

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
    }
}

void MainWindow::ImportTaskkFile(std::string filePath) {
    std::ifstream f(filePath);
    json data = json::parse(f);
    SessionStruct ses = DataHandler::ParseData(data);
    ui::OperationsBarDataHandler::InitSession(ses);
}

void MainWindow::InitStylesheet() {
    m_DockManager->setStyleSheet("/*\n"
                                 " * Default style sheet on Windows Platforms with focus highlighting flag enabled\n"
                                 " */\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CDockContainerWidget\n"
                                 " *****************************************************************************/\n"
                                 "ads--CDockContainerWidget {\n"
                                 "    background: palette(window);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CDockSplitter\n"
                                 " *****************************************************************************/\n"
                                 "ads--CDockContainerWidget > QSplitter {\n"
                                 "    padding: 1 0 1 0;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CDockSplitter::handle {\n"
                                 "    background-color: palette(dark);\n"
                                 "    /* uncomment the following line if you would like to change the size of\n"
                                 "       the splitter handles */\n"
                                 "    /* height: 1px; */\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CDockAreaWidget\n"
                                 " *****************************************************************************/\n"
                                 "ads--CDockAreaWidget {\n"
                                 "    background: palette(window);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CDockAreaTitleBar {\n"
                                 "    background: transparent;\n"
                                 "    border-bottom: 2px solid palette(light);\n"
                                 "    padding-bottom: 0px;\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockAreaWidget[focused=\"true\"] ads--CDockAreaTitleBar {\n"
                                 "    border-bottom: 2px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CTitleBarButton {\n"
                                 "    padding: 0px 0px;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "#tabsMenuButton::menu-indicator {\n"
                                 "    image: none;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "#dockAreaCloseButton {\n"
                                 "    qproperty-icon: url(:/ads/images/close-button.svg),\n"
                                 "    url(:/ads/images/close-button-disabled.svg) disabled;\n"
                                 "    qproperty-iconSize: 16px;\n"
                                 "}\n"
                                 "\n"
                                 "#detachGroupButton {\n"
                                 "    qproperty-icon: url(:/ads/images/detach-button.svg),\n"
                                 "    url(:/ads/images/detach-button-disabled.svg) disabled;\n"
                                 "    qproperty-iconSize: 16px;\n"
                                 "}\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CDockWidgetTab\n"
                                 " *****************************************************************************/\n"
                                 "ads--CDockWidgetTab {\n"
                                 "    background: palette(light);\n"
                                 "    border-color: palette(light);\n"
                                 "    border-style: solid;\n"
                                 "    border-width: 0 0px 0 0;\n"
                                 "    padding: 0 0px;\n"
                                 "    qproperty-iconSize: 16px 16px;/* this is optional in case you would like to change icon size*/\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab[activeTab=\"true\"] {\n"
                                 "    background: palette(light);\n"
                                 "    /*background: palette(highlight);*/\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab QLabel {\n"
                                 "    color: palette(foreground);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab[activeTab=\"true\"] QLabel {\n"
                                 "    color: palette(white);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "#tabCloseButton {\n"
                                 "    margin-top: 2px;\n"
                                 "    background: none;\n"
                                 "    border: none;\n"
                                 "    padding: 0px -2px;\n"
                                 "    qproperty-icon: url(:/ads/images/close-button.svg),\n"
                                 "    url(:/ads/images/close-button-disabled.svg) disabled;\n"
                                 "    qproperty-iconSize: 16px;\n"
                                 "}\n"
                                 "\n"
                                 "#tabCloseButton:hover {\n"
                                 "    /*border: 1px solid rgba(0, 0, 0, 32);*/\n"
                                 "    background: rgba(0, 0, 0, 24);\n"
                                 "}\n"
                                 "\n"
                                 "#tabCloseButton:pressed {\n"
                                 "    background: rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "/* Focus related styling */\n"
                                 "ads--CDockWidgetTab[focused=\"true\"] {\n"
                                 "    background: palette(highlight);\n"
                                 "    border-color: palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab[focused=\"true\"] > #tabCloseButton {\n"
                                 "    qproperty-icon: url(:/ads/images/close-button-focused.svg)\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab[focused=\"true\"] > #tabCloseButton:hover {\n"
                                 "    background: rgba(255, 255, 255, 48);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab[focused=\"true\"] > #tabCloseButton:pressed {\n"
                                 "    background: rgba(255, 255, 255, 92);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CDockWidgetTab[focused=\"true\"] QLabel {\n"
                                 "    color: palette(white);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CDockWidget\n"
                                 " *****************************************************************************/\n"
                                 "ads--CDockWidget {\n"
                                 "    background: palette(light);\n"
                                 "    border-color: palette(light);\n"
                                 "    border-style: solid;\n"
                                 "    border-width: 1px 0 0 0;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "QScrollArea#dockWidgetScrollArea {\n"
                                 "    padding: 0px;\n"
                                 "    border: none;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " *\n"
                                 " * Styling of auto hide functionality\n"
                                 " *\n"
                                 " *****************************************************************************/\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CAutoHideTab\n"
                                 " *****************************************************************************/\n"
                                 "ads--CAutoHideTab {\n"
                                 "    qproperty-iconSize: 16px 16px;/* this is optional in case you would like to change icon size*/\n"
                                 "    background: none;\n"
                                 "    border: none;\n"
                                 "    padding-left: 2px;\n"
                                 "    padding-right: 0px;\n"
                                 "    text-align: center;\n"
                                 "    min-height: 20px;\n"
                                 "    padding-bottom: 2px;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideTab:hover\n"
                                 "{\n"
                                 "    color: palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"0\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"2\"]  {\n"
                                 "    border-top: 6px solid rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"1\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"3\"] {\n"
                                 "    border-bottom: 6px solid rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"false\"][sideBarLocation=\"0\"],\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"false\"][sideBarLocation=\"2\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"0\"][activeTab=\"true\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"2\"][activeTab=\"true\"]  {\n"
                                 "    border-top: 6px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"false\"][sideBarLocation=\"1\"],\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"false\"][sideBarLocation=\"3\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"1\"][activeTab=\"true\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"false\"][sideBarLocation=\"3\"][activeTab=\"true\"] {\n"
                                 "    border-bottom: 6px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/**\n"
                                 " * Auto hide tabs with icon only\n"
                                 " */\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"0\"] {\n"
                                 "    border-top: 6px solid rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"1\"] {\n"
                                 "    border-left: 6px solid rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"2\"] {\n"
                                 "    border-right: 6px solid rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"3\"] {\n"
                                 "    border-bottom: 6px solid rgba(0, 0, 0, 48);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/**\n"
                                 " * Auto hide tabs with icon only hover\n"
                                 " */\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"true\"][sideBarLocation=\"0\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"0\"][activeTab=\"true\"] {\n"
                                 "    border-top: 6px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"true\"][sideBarLocation=\"1\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"1\"][activeTab=\"true\"] {\n"
                                 "    border-left: 6px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"true\"][sideBarLocation=\"2\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"2\"][activeTab=\"true\"] {\n"
                                 "    border-right: 6px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideTab:hover[iconOnly=\"true\"][sideBarLocation=\"3\"],\n"
                                 "ads--CAutoHideTab[iconOnly=\"true\"][sideBarLocation=\"3\"][activeTab=\"true\"] {\n"
                                 "    border-bottom: 6px solid palette(highlight);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CAutoHideSideBar\n"
                                 " *****************************************************************************/\n"
                                 "ads--CAutoHideSideBar{\n"
                                 "    background: palette(window);\n"
                                 "    border: none;\n"
                                 "    qproperty-spacing: 12;\n"
                                 "}\n"
                                 "\n"
                                 "#sideTabsContainerWidget {\n"
                                 "    background: transparent;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideSideBar[sideBarLocation=\"0\"] {\n"
                                 "    border-bottom: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideSideBar[sideBarLocation=\"1\"] {\n"
                                 "    border-right: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideSideBar[sideBarLocation=\"2\"] {\n"
                                 "    border-left: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideSideBar[sideBarLocation=\"3\"] {\n"
                                 "    border-top: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CAutoHideDockContainer\n"
                                 " *****************************************************************************/\n"
                                 "ads--CAutoHideDockContainer {\n"
                                 "    background: palette(window);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer ads--CDockAreaTitleBar {\n"
                                 "    background: palette(highlight);\n"
                                 "    padding: 0px;\n"
                                 "    border: none;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/*\n"
                                 " * This is required because the ads--CDockAreaWidget[focused=\"true\"] will\n"
                                 " * overwrite the ads--CAutoHideDockContainer ads--CDockAreaTitleBar rule\n"
                                 " */\n"
                                 "ads--CAutoHideDockContainer ads--CDockAreaWidget[focused=\"true\"] ads--CDockAreaTitleBar {\n"
                                 "    background: palette(highlight);\n"
                                 "    padding: 0px;\n"
                                 "    border: none;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "#autoHideTitleLabel {\n"
                                 "    padding-left: 4px;\n"
                                 "    color: palette(light);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CAutoHideDockContainer titlebar buttons\n"
                                 " *****************************************************************************/\n"
                                 "#dockAreaAutoHideButton {\n"
                                 "    qproperty-icon: url(:/ads/images/vs-pin-button.svg),\n"
                                 "    url(:/ads/images/vs-pin-button-disabled.svg) disabled;\n"
                                 "    qproperty-iconSize: 16px;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer #dockAreaAutoHideButton {\n"
                                 "    qproperty-icon: url(:/ads/images/vs-pin-button-pinned-focused.svg);\n"
                                 "    qproperty-iconSize: 16px;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer #dockAreaMinimizeButton {\n"
                                 "    qproperty-icon: url(:/ads/images/minimize-button-focused.svg);\n"
                                 "    qproperty-iconSize: 16px;\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer #dockAreaCloseButton{\n"
                                 "    qproperty-icon: url(:/ads/images/close-button-focused.svg)\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer ads--CTitleBarButton:hover {\n"
                                 "    background: rgba(255, 255, 255, 48);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer ads--CTitleBarButton:pressed {\n"
                                 "    background: rgba(255, 255, 255, 96);\n"
                                 "}\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CAutoHideDockContainer Titlebar and Buttons\n"
                                 " *****************************************************************************/\n"
                                 "\n"
                                 "\n"
                                 "/*****************************************************************************\n"
                                 " * CResizeHandle\n"
                                 " *****************************************************************************/\n"
                                 "ads--CResizeHandle {\n"
                                 "    background: palette(window);\n"
                                 "}\n"
                                 "\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer[sideBarLocation=\"0\"] ads--CResizeHandle {\n"
                                 "    border-top: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer[sideBarLocation=\"1\"] ads--CResizeHandle {\n"
                                 "    border-left: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer[sideBarLocation=\"2\"] ads--CResizeHandle {\n"
                                 "    border-right: 1px solid palette(dark);\n"
                                 "}\n"
                                 "\n"
                                 "ads--CAutoHideDockContainer[sideBarLocation=\"3\"] ads--CResizeHandle {\n"
                                 "    border-top: 1px solid palette(dark);\n"
                                 "}");

    //qApp->setStyleSheet(styleSheet);
}
