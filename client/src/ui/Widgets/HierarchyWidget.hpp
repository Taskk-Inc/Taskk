//
// Created by VERB1807 on 4/4/2024.
//

#pragma once
#include <ads/DockManager.h>
#include <QScrollArea>
#include <QTreeWidget>
#include "../ui_mainwindow.h"
#include "mainwindow.h"
#include "MenuBar.hpp"
#include "Handlers/HierarchyHandler/HierarchyHandler.hpp"

namespace ui::HierarchyWidget
{
    inline ads::CDockWidget* dockWidget = nullptr;
    inline QTreeWidget* tree = nullptr;

    inline void CreateWidget()
    {
        tree = new QTreeWidget;
        tree->setColumnCount(1);
        tree->setHeaderHidden(true);

        tree->show();

        QObject::connect(tree, QTreeWidget::itemClicked, tree, [](QTreeWidgetItem* item, int col){
            PTreeWidgetItem* pItem = (PTreeWidgetItem*)item;
            std::cout << "selection changed: " << pItem->operation->mainButton->nameLabel->text().toStdString() << std::endl;
            ui::OperationsBarDataHandler::SetSelected(pItem->operation);
            item->setSelected(false);
        });

        dockWidget = new ads::CDockWidget("Hierarchy");
        dockWidget->setWidget(tree);

        ui::MenuBar::menuView->addAction(dockWidget->toggleViewAction());
    }

}