//
// Created by VERB1807 on 4/5/2024.
//

#pragma once

#include <QSplineSeries>
#include <QBarSeries>
#include <QGraphicsRectItem>

struct OperationBar;

namespace ui::EfficiencyChartHandler
{
    inline QGraphicsRectItem selectedItem;
    inline QGraphicsRectItem hoverItem;

    inline QSplineSeries* series = nullptr;
    inline QBarSeries* barSeries = nullptr;

    void CreateSeries(std::map<int, int> seriesData, int selectedIndex);
    void InitSeries(OperationBar data, int hLayoutIndex);

    void Clear();
}
