//
// Created by VERB1807 on 4/3/2024.
//

#pragma once

#include "../ui_mainwindow.h"
#include "mainwindow.h"
#include "SettingsWidget.hpp"

namespace ui::MenuBar
{
    inline QMenuBar *menuBar = nullptr;
    inline QMenu *menuFile = nullptr;
    inline QMenu *menuView = nullptr;

    void InitMenuFile();
    void InitMenuView();

    inline void Init()
    {
        menuBar = new QMenuBar(ui::mainWindow->mainWindowWidget);
        menuBar->setObjectName("menubar");
        menuBar->setGeometry(QRect(0, 0, 5130, 21));
        ui::mainWindow->mainWindowWidget->setMenuBar(menuBar);

        InitMenuFile();
        InitMenuView();
    }

    inline void OpenImportDialog()
    {
        QFileDialog dialog;
        dialog.setNameFilter("*.taskk");
        if(!dialog.exec())
            return;
        QStringList fileNames;
        fileNames = dialog.selectedFiles();
        MainWindow* w = (MainWindow*)ui::mainWindow;
        w->ImportTaskkFile(fileNames[0].toStdString());
    }

    inline void InitMenuFile()
    {
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuBar->addAction(menuFile->menuAction());

        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));

        QAction* importAction = new QAction("Import File");

        QObject::connect(importAction, QAction::triggered, importAction, [](){{{{
            OpenImportDialog();
        }}}});

        QAction* settingsAction = new QAction("Settings");

        ui::SettingsWidget::CreateWidget();

        QObject::connect(settingsAction, QAction::triggered, settingsAction, [](){{{{
                    MainWindow* w = (MainWindow*)ui::mainWindow->mainWindowWidget;
                    if (w->GetDockManager() == nullptr || ui::SettingsWidget::dockWidget->isVisible())
                        return;
                    w->GetDockManager()->addDockWidgetFloating(ui::SettingsWidget::dockWidget);
                }}}});

        menuFile->addAction(importAction);
        menuFile->addSeparator();
        menuFile->addAction(settingsAction);
    }

    inline void InitMenuView()
    {
        menuView = new QMenu(menuBar);
        menuView->setObjectName("menuView");
        menuBar->addAction(menuView->menuAction());

        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    }
}