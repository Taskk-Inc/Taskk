//
// Created by VERB1807 on 4/4/2024.
//

#include "PropertiesHandler.hpp"
#include "Handlers/OperationsBarData/OperationsBarData.h"
#include "Widgets/ExtendedPropertiesWidget.hpp"
#include <chrono>

void ui::PropertiesHandler::CreateProperty(OperationBar operationBar)
{
    QLabel* nameLabel = new QLabel(operationBar.mainButton->nameLabel->text());

    std::time_t time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::microseconds(operationBar.timestamp)).count();
    QLabel* timestampLabel = new QLabel(asctime(localtime(&time)));
    timestampLabel->setMaximumHeight(15);

    QLabel* timeLabel = new QLabel(QString::number(operationBar.endUS - operationBar.startUS).append(" μs"));
    timeLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);

    QHBoxLayout* hb = new QHBoxLayout();

    hb->addWidget(nameLabel);
    hb->addWidget(timestampLabel);
    hb->addWidget(timeLabel);

    ui::ExtendedPropertiesWidget::verticalLayout->addLayout(hb);
    ui::ExtendedPropertiesWidget::verticalLayout->removeItem(ui::ExtendedPropertiesWidget::verticalSpacer);
    ui::ExtendedPropertiesWidget::verticalLayout->addItem(ui::ExtendedPropertiesWidget::verticalSpacer);

    OperationProperty* prop = new OperationProperty;
    prop->horizontalLayout = hb;
    prop->operationLabel = nameLabel;
    prop->timestampLabel = timestampLabel;
    prop->secondsLabel = timeLabel;

    ui::PropertiesHandler::propertiesLayout.push_back(prop);
}

void ui::PropertiesHandler::InitOperationProperties(OperationBar operationBar)
{
    //ui::PropertiesHandler::CreateProperty(operationBar);
    for (int i = 0; i < operationBar.childOperations.size(); i++)
    {
        ui::PropertiesHandler::CreateProperty(operationBar.childOperations[i]);
        ui::PropertiesHandler::InitOperationProperties(operationBar.childOperations[i]);
    }
}

void ui::PropertiesHandler::Clear()
{
    for (auto d: ui::PropertiesHandler::propertiesLayout)
    {
        delete d->horizontalLayout;
        delete d->secondsLabel;
        delete d->timestampLabel;
        delete d->operationLabel;
    }
    ui::PropertiesHandler::propertiesLayout.clear();
}