//
// Created by VERB1807 on 4/5/2024.
//

#include <QBarCategoryAxis>
#include "EfficiencyChartHandler.hpp"
#include "Handlers/OperationsBarData/OperationsBarData.h"
#include "Widgets/ChartsWidget.hpp"

void ui::EfficiencyChartHandler::InitSeries(OperationBar data, int hLayoutIndex)
{
    //ui::EfficiencyChartHandler::Clear();
    ui::ChartsWidget::chart->setTitle(QString("Showing operation: ").append(data.mainButton->nameLabel->text()));

    auto table = ui::OperationsBarDataHandler::horizontalLayouts[hLayoutIndex]->buttons;

    std::map<int, int> map = {};
    int n = 1;
    int selectedIndex = -1;

    for (int i = 0; i < table.size(); i++)
    {
        if (table[i]->nameLabel == nullptr) continue;

        if (table[i]->nameLabel->text() == data.mainButton->nameLabel->text())
        {
            if (&table[i]->nameLabel == &data.mainButton->nameLabel)
                selectedIndex = n;
            map.insert({n, table[i]->operationBar->endUS - table[i]->operationBar->startUS});
            n += 1;
        }
    }

    ui::EfficiencyChartHandler::CreateSeries(map, selectedIndex);
}

void ui::EfficiencyChartHandler::CreateSeries(std::map<int, int> seriesData, int selectedIndex)
{
    int maxY;

    int biggestY = -1;

    for (auto data: seriesData)
        if (biggestY < data.second)
            biggestY = data.second;

    maxY = biggestY;
    maxY += int(maxY/4);

    barSeries = new QBarSeries();
    QStringList categories{};
    QBarSet* set = new QBarSet("");

    ui::ChartsWidget::axisX->clear();

    for (int i = 0; i < seriesData.size(); i++)
    {
        if (seriesData[i] == 0) continue;
        categories.append(QString::number(i));
        set->append(seriesData[i]);
    }
    barSeries->append(set);

    ui::ChartsWidget::axisY->setRange(0, maxY);

    ui::ChartsWidget::chart->addSeries(barSeries);

    barSeries->attachAxis(ui::ChartsWidget::axisX);
    barSeries->attachAxis(ui::ChartsWidget::axisY);

//    hoverItem.setBrush(QBrush(Qt::red));
//    hoverItem.setPen(Qt::NoPen);
//
//    selectedItem.setBrush(QBrush(Qt::gray));
//    selectedItem.setPen(Qt::NoPen);

//    QObject::connect(set, &QBarSet::hovered, [](bool status, int /*index*/){
//        QPoint p = ui::ChartsWidget::chartView->mapFromGlobal(QCursor::pos());
//        if(status){
//            QGraphicsItem *it = ui::ChartsWidget::chartView->itemAt(p);
//            hoverItem.setParentItem(it);
//            hoverItem.setRect(it->boundingRect());
//            hoverItem.show();
//            QToolTip::showText(QCursor::pos() + QPoint(0, 10), "HELLO");
//        }
//        else{
//            hoverItem.setParentItem(nullptr);
//            hoverItem.hide();
//            QToolTip::hideText();
//        }
//    });

//    series = new QSplineSeries();
//
//    for (int i = 0; i < seriesData.size(); i++)
//        series->append(i, seriesData[i]);
//
//    ui::ChartsWidget::chart->addSeries(series);
//
//    ui::ChartsWidget::axisX->setRange(0, maxX);
//    ui::ChartsWidget::axisY->setRange(0, maxY);
//
//    series->attachAxis(ui::ChartsWidget::axisX);
//    series->attachAxis(ui::ChartsWidget::axisY);
}

void ui::EfficiencyChartHandler::Clear()
{
    if (barSeries != nullptr)
    {
        barSeries->clear();
        delete barSeries;
        barSeries = nullptr;
        ui::ChartsWidget::chart->setTitle("Showing operation: ");
    } else if (series != nullptr)
    {
        series->clear();
        delete series;
        series = nullptr;
        ui::ChartsWidget::chart->setTitle("Showing operation: ");
    }
}