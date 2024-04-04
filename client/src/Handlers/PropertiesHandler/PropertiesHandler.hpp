//
// Created by VERB1807 on 4/4/2024.
//

#pragma once

#include <vector>
#include <QHBoxLayout>
#include <QLabel>

struct SessionStruct;
struct OperationBar;

struct OperationProperty
{
    QHBoxLayout* horizontalLayout;
    QLabel* operationLabel;
    QLabel* timestampLabel;
    QLabel* secondsLabel;
};

namespace  ui::PropertiesHandler {
    inline std::vector<OperationProperty*> propertiesLayout;

    void CreateProperty(OperationBar operationBar);
    void Clear();

//    void InitSessionProperties(SessionStruct session);
    void InitOperationProperties(OperationBar operationBar);
};


