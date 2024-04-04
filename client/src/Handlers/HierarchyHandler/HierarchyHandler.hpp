//
// Created by VERB1807 on 4/4/2024.
//

#pragma once
#include <QTreeWidgetItem>

struct OperationBar;
class PTreeWidgetItem;

namespace ui::HierarchyHandler
{
    inline std::vector<PTreeWidgetItem*> items;

    PTreeWidgetItem* CreateItem(OperationBar& operation, PTreeWidgetItem* parent);
    void InitParent(OperationBar* operation);
    void InitTree(std::vector<OperationBar*> operations);

    void Clear();
}

class PTreeWidgetItem : public QTreeWidgetItem
{
public:
    OperationBar* operation;

    explicit PTreeWidgetItem(const QStringList &strings, int type = Type) : QTreeWidgetItem(strings, type) {};
};