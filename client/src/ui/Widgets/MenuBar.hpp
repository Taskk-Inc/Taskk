//
// Created by VERB1807 on 4/3/2024.
//

#pragma once

#include "../ui_mainwindow.h"
#include "mainwindow.h"

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

        QAction* action = new QAction("Import File");

        QObject::connect(action, QAction::triggered, action, [](){ {{{OpenImportDialog();}}} });

        menuFile->addAction(action);
        menuFile->addAction(new QAction("Settings"));
    }

    inline void InitMenuView()
    {
        menuView = new QMenu(menuBar);
        menuView->setObjectName("menuView");
        menuBar->addAction(menuView->menuAction());

        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    }
}