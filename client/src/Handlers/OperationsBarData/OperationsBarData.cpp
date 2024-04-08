#include <QLabel>
#include <QShortcut>
#include "OperationsBarData.h"
#include "../../ui/ui_mainwindow.h"
#include "Widgets/TimelineWidget.hpp"
#include "../HierarchyHandler/HierarchyHandler.hpp"
#include "../PropertiesHandler/PropertiesHandler.hpp"
#include "../EfficiencyChartHandler/EfficiencyChartHandler.hpp"
//
// Created by VERB1807 on 3/26/2024.
//

OperationBar *ui::OperationsBarDataHandler::CreateBar(float start, float end, QString barName, int layoutIndex) {
    OperationBar *operationBar = new OperationBar();
    float US = end - start;
    float totalPixels = US / ui::OperationsBarDataHandler::Settings.ratioPixels;

    POperationButton *pushButton = new POperationButton();

    pushButton->setMinimumWidth(totalPixels);
    pushButton->setMaximumWidth(totalPixels);
    pushButton->setMinimumHeight(25);

    pushButton->setStyleSheet(
            "QPushButton {border: 1px solid rgb(40, 83, 153); border-radius: 0px;background: rgb(50, 104, 191);} "
            "QPushButton:hover{border: 1px solid rgb(36, 82, 156); background: rgb(43, 95, 179);}"
    );

    QLabel *testLabel2 = new QLabel(barName);
    testLabel2->move(10, 0);
    testLabel2->setMinimumWidth(50);
    testLabel2->setMinimumHeight(23);
    testLabel2->setParent(pushButton);
    testLabel2->setStyleSheet("font-weight: bold;");

    QLabel *testLabel3 = new QLabel(QString::number(US).append(" μs"));
    testLabel3->move(totalPixels - 60, 0);
    testLabel3->setMinimumWidth(50);
    testLabel3->setMinimumHeight(23);
    testLabel3->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    testLabel3->setParent(pushButton);

    operationBar->mainButton = pushButton;
    operationBar->startUS = start;
    operationBar->endUS = end;
    pushButton->nameLabel = testLabel2;
    pushButton->microLabel = testLabel3;
    pushButton->layoutIndex = layoutIndex;

    pushButton->operationBar = operationBar;
    bars.push_back(operationBar);

    QObject::connect(pushButton, QPushButton::clicked, pushButton, &POperationButton::onClick);

    InsertInLayout(pushButton, layoutIndex);

    return operationBar;
}

void ui::OperationsBarDataHandler::FillSpace(int layoutIndex, float endFill) {
    if (horizontalLayouts.size() > layoutIndex) {
        if (horizontalLayouts[layoutIndex]->buttons.size() > 0) {
            float endFloat = horizontalLayouts[layoutIndex]->buttons[horizontalLayouts[layoutIndex]->buttons.size() -
                                                                     1]->operationBar->endUS;
            if (endFill > endFloat)
                ui::OperationsBarDataHandler::CreateTransparentBar(endFloat, endFill, layoutIndex);
        } else
            ui::OperationsBarDataHandler::CreateTransparentBar(0, endFill, layoutIndex);
    } else if (endFill != 0) {
        while (horizontalLayouts.size() <= layoutIndex)
            ui::OperationsBarDataHandler::CreateHLayout();

        ui::OperationsBarDataHandler::CreateTransparentBar(0, endFill, layoutIndex);
    }
}

void ui::OperationsBarDataHandler::InitOperation(float start, float end, QString operationName, std::vector<OperationData> subData, uint64_t start_timestamp) {
    ui::OperationsBarDataHandler::FillSpace(0, start);
    OperationBar *bar = ui::OperationsBarDataHandler::CreateBar(start, end, operationName, 0);
    bar->timestamp = start_timestamp+start;

    for (OperationData data: subData)
        ui::OperationsBarDataHandler::CreateDeepOperation(data, 1, bar);

    ui::OperationsBarDataHandler::hierarchyBars.push_back(bar);
}

void
ui::OperationsBarDataHandler::CreateDeepOperation(OperationData data, int layoutIndex, OperationBar *parentOperation) {
    ui::OperationsBarDataHandler::FillSpace(layoutIndex, data.start);
    OperationBar *bar = ui::OperationsBarDataHandler::CreateBar(data.start, data.end, data.operationName, layoutIndex);
    bar->timestamp = parentOperation->timestamp + data.start;

    for (OperationData data2: data.subData)
        ui::OperationsBarDataHandler::CreateDeepOperation(data2, layoutIndex + 1, bar);

    parentOperation->childOperations.push_back(*bar);
}

void ui::OperationsBarDataHandler::Clear() {
//    std::cout << "deleteing" << std::endl;
//    for (auto info: ui::OperationsBarDataHandler::bars)
//    {
//        std::cout << "loop1" << std::endl;
//
//        for (auto childObject: info->mainButton->children())
//            childObject->setParent(nullptr);
//        info->mainButton->setParent(nullptr);
//
//        std::cout << "end loop1" << std::endl;
//    }
//    std::cout << "done1" << std::endl;
//   ui::OperationsBarDataHandler::bars.clear();
//   ui::OperationsBarDataHandler::hierarchyBars.clear();
//    std::cout << "done2" << std::endl;
//
//    for (auto info: ui::OperationsBarDataHandler::horizontalLayouts)
//    {
//        for (auto childObject: info->buttons)
//            childObject->setParent(nullptr);
//        info->buttons.clear();
//    }
//    std::cout << "done3" << std::endl;

    for (auto info: ui::OperationsBarDataHandler::horizontalLayouts) {
        delete info->horizonalLayout;
        delete info;
    }

    for (auto info: ui::OperationsBarDataHandler::bars)
    {
        delete info->mainButton;
        delete info;
    }

    ui::OperationsBarDataHandler::horizontalLayouts.clear();
    ui::OperationsBarDataHandler::bars.clear();
    ui::OperationsBarDataHandler::hierarchyBars.clear();
    ui::OperationsBarDataHandler::selected = nullptr;

    ui::HierarchyHandler::Clear();
    ui::EfficiencyChartHandler::Clear();
}

void ui::OperationsBarDataHandler::UpdateBarZoom() {
    for (auto bar: ui::OperationsBarDataHandler::bars) {
        float US = bar->endUS - bar->startUS;
        US /= ui::OperationsBarDataHandler::Settings.ratioPixels;
        US *= ui::OperationsBarDataHandler::zoomAmount;
        bar->mainButton->setMinimumWidth(US);
        bar->mainButton->setMaximumWidth(US);

        if (bar->mainButton->nameLabel == nullptr || bar->mainButton->microLabel == nullptr) continue;

        bar->mainButton->microLabel->move(US - 60, 0);

        int buttonWidth = bar->mainButton->rect().width();
        int nameLabelWidth = bar->mainButton->nameLabel->fontMetrics().boundingRect(
                bar->mainButton->nameLabel->text()).width();
        int microLabelWidth = bar->mainButton->microLabel->fontMetrics().boundingRect(
                bar->mainButton->microLabel->text()).width();

        bar->mainButton->microLabel->setVisible(microLabelWidth + nameLabelWidth + 25 < buttonWidth);
        bar->mainButton->nameLabel->setVisible(nameLabelWidth + 20 < buttonWidth);
    }
}

void ui::OperationsBarDataHandler::CreateTransparentBar(float start, float end, int layoutIndex) {
    OperationBar *operationBar = new OperationBar();
    float US = end - start;
    float totalPixels = US / ui::OperationsBarDataHandler::Settings.ratioPixels;

    POperationButton *pushButton = new POperationButton();
    pushButton->operationBar = operationBar;
    pushButton->setMinimumWidth(totalPixels);
    pushButton->setMaximumWidth(totalPixels);
    pushButton->setMinimumHeight(25);
    pushButton->setObjectName("Transparent");

    pushButton->setStyleSheet(
            "QPushButton {border: transparent;}"
    );

    pushButton->setFocusPolicy(Qt::NoFocus);

    operationBar->mainButton = pushButton;
    operationBar->endUS = end;
    operationBar->startUS = start;
    pushButton->microLabel = nullptr;
    pushButton->nameLabel = nullptr;

    bars.push_back(operationBar);

    InsertInLayout(pushButton, layoutIndex);
}

void ui::OperationsBarDataHandler::InsertInLayout(QWidget *object, int index) {
    while (horizontalLayouts.size() <= index)
        ui::OperationsBarDataHandler::CreateHLayout();

    QHBoxLayout *HLayout = horizontalLayouts[index]->horizonalLayout;
    QSpacerItem *HSpacer = horizontalLayouts[index]->spacerItem;

    horizontalLayouts[index]->buttons.push_back((POperationButton *) object);

    HLayout->removeItem(HSpacer);
    HLayout->addWidget(object);
    HLayout->addItem(HSpacer);
}

void ui::OperationsBarDataHandler::CreateHLayout() {
    HorizontalBoxData *boxData = new HorizontalBoxData();

    QHBoxLayout *HLayout = new QHBoxLayout();
    HLayout->setSpacing(0);
    HLayout->setObjectName(
            QString("HLayout") + QString::number(ui::OperationsBarDataHandler::horizontalLayouts.size() + 1));

    QSpacerItem *HSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    HLayout->addItem(HSpacer);

    boxData->spacerItem = HSpacer;
    boxData->horizonalLayout = HLayout;

    ui::TimelineWidget::verticalLayout->addLayout(HLayout);
    ui::TimelineWidget::verticalLayout->removeItem(ui::TimelineWidget::verticalSpacer);
    ui::TimelineWidget::verticalLayout->addItem(ui::TimelineWidget::verticalSpacer);

    ui::OperationsBarDataHandler::horizontalLayouts.push_back(boxData);
}

void ui::OperationsBarDataHandler::InitSession(SessionStruct session) {
    ui::OperationsBarDataHandler::Clear();
    ui::OperationsBarDataHandler::zoomAmount = 1;
    for (auto s: session.operations) {
        ui::OperationsBarDataHandler::InitOperation(s.start, s.end, s.operationName, s.subData, session.start_timestamp);
    }
    ui::OperationsBarDataHandler::UpdateBarZoom();

    ui::HierarchyHandler::InitTree(ui::OperationsBarDataHandler::hierarchyBars);
}

void ui::OperationsBarDataHandler::SetSelected(OperationBar *selected) {
    ui::PropertiesHandler::Clear();
    ui::EfficiencyChartHandler::Clear();
    if (ui::OperationsBarDataHandler::selected != nullptr) {
        if (ui::OperationsBarDataHandler::selected == selected) {
            selected->mainButton->setSelected(false);
            ui::OperationsBarDataHandler::selected = nullptr;
            return;
        } else
            ui::OperationsBarDataHandler::selected->mainButton->setSelected(false);
    }

    ui::OperationsBarDataHandler::selected = selected;
    selected->mainButton->setSelected(true);
    ui::PropertiesHandler::InitOperationProperties(*selected);
    ui::EfficiencyChartHandler::InitSeries(*selected->mainButton->operationBar, selected->mainButton->layoutIndex);
}
