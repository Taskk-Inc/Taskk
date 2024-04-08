#pragma once
#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
//#include "../../ui_mainwindow.h"

struct OperationBar
{
    class POperationButton* mainButton;
    float startUS;
    float endUS;
    uint64_t timestamp;

    std::vector<OperationBar> childOperations;
};

struct OperationData
{
    float start;
    float end;
    QString operationName;

    std::vector<OperationData> subData;
};

struct HorizontalBoxData
{
    QHBoxLayout* horizonalLayout;
    QSpacerItem* spacerItem;

    std::vector<POperationButton*> buttons;
};

struct SessionStruct
{
    int64_t start_timestamp;
    int64_t end_timestamp;

    std::vector<OperationData> operations;
};

namespace ui::OperationsBarDataHandler
{
    inline std::vector<OperationBar*> bars;
    inline std::vector<OperationBar*> hierarchyBars;
    inline OperationBar* selected;
    inline std::vector<HorizontalBoxData*> horizontalLayouts;
    inline float zoomAmount = 1;

    inline struct {
        float ratioPixels = 500;
    } Settings;

    void CreateHLayout();
    void InsertInLayout(QWidget* object, int index);

    OperationBar* CreateBar(float start, float end, QString barName, int layoutIndex);
    void UpdateBarZoom();

    void CreateTransparentBar(float start, float end, int layoutIndex);

    void FillSpace(int layoutIndex, float endFill);
    void CreateDeepOperation(OperationData data, int layoutIndex, OperationBar* parentOperation);
    void InitOperation(float start, float end, QString operationName, std::vector<OperationData> subData, uint64_t start_timestamp);
    void InitSession(SessionStruct session);
    void Clear();

    void SetSelected(OperationBar* selected);
}

class POperationButton: public QPushButton
{
    Q_OBJECT
private:
    bool selected = false;
public:
    OperationBar* operationBar;
    QLabel* nameLabel;
    QLabel* microLabel;
    int layoutIndex = -1;

    explicit POperationButton(QWidget *parent = nullptr): QPushButton(parent) {};
    explicit POperationButton(const QString &text, QWidget *parent = nullptr): QPushButton(text, parent) {};

    void setSelected(bool val)
    {
        if (selected == val) return;
        selected = val;

        if (val)
            setStyleSheet(
                    "QPushButton {border: 2px solid rgb(40, 153, 51); background: rgb(50, 191, 52);} "
            );
        else
            setStyleSheet(
                    "QPushButton {border: 1px solid rgb(40, 83, 153); border-radius: 0px;background: rgb(50, 104, 191);} "
                    "QPushButton:hover{border: 1px solid rgb(36, 82, 156); background: rgb(43, 95, 179);}"
            );
    }

    [[nodiscard]] bool isSelected() const {return selected;}

    void onClick(bool val)
    {
        ui::OperationsBarDataHandler::SetSelected(operationBar);
    }
};
