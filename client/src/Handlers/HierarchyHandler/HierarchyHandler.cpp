//
// Created by VERB1807 on 4/4/2024.
//

#include "HierarchyHandler.hpp"
#include "../OperationsBarData/OperationsBarData.h"
#include "Widgets/HierarchyWidget.hpp"

PTreeWidgetItem* ui::HierarchyHandler::CreateItem(OperationBar& operation, PTreeWidgetItem* parent) {
    QString operationName = operation.mainButton->nameLabel->text();
    PTreeWidgetItem* treeItem = new PTreeWidgetItem(QStringList() << operationName);
    treeItem->operation = &operation;

    for (int i = 0; i < operation.childOperations.size(); i++)
        ui::HierarchyHandler::CreateItem(operation.childOperations[i], treeItem);

    if (parent != nullptr)
        parent->addChild(treeItem);

    return treeItem;
}

void ui::HierarchyHandler::InitParent(OperationBar* operation) {
    QString operationName = operation->mainButton->nameLabel->text();
    std::cout << "Creating parent -> " << operationName.toStdString() << std::endl;
    PTreeWidgetItem* parent = new PTreeWidgetItem(QStringList() << operationName);
    parent->operation = operation;

    for (int i = 0; i < operation->childOperations.size(); i++)
        ui::HierarchyHandler::CreateItem(operation->childOperations[i], parent);

    ui::HierarchyWidget::tree->addTopLevelItem(parent);
    ui::HierarchyHandler::items.push_back(parent);
}

void ui::HierarchyHandler::InitTree(std::vector<OperationBar*> operations) {
    if (operations.empty()) return;

    for (int i = 0; i < operations.size(); i++)
        InitParent(operations[i]);
}

void ui::HierarchyHandler::Clear() {
    for (auto d: ui::HierarchyHandler::items)
        delete d;

    ui::HierarchyHandler::items.clear();
}

