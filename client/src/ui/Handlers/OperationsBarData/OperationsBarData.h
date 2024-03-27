#include "mainwindow.h"
#include <vector>
#include <iostream>
#include <QHBoxLayout>
#include <QPushButton>
#include "../../ui_mainwindow.h"

struct OperationBar
{
    class POperationButton* mainButton;
    float startUS;
    float endUS;

    std::vector<OperationBar> bars;
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

namespace ui::OperationsBarDataHandler
{
    inline std::vector<OperationBar*> bars;
    inline OperationBar* selected;
    inline std::vector<HorizontalBoxData*> horizontalLayouts;

    void CreateHLayout();
    void InsertInLayout(QWidget* object, int index);

    void CreateBar(float start, float end, QString barName, int layoutIndex);
    void CreateBar(float start, float end, QString barName, std::vector<OperationData> subData);

    void CreateTransparentBar(float start, float end, int layoutIndex);

    void FillSpace(int layoutIndex, float endFill);
    void CreateDeepOperation(OperationData data, int layoutIndex);
    void InitOperation(float start, float end, QString operationName, std::vector<OperationData> subData);
}

class POperationButton: public QPushButton
{
    Q_OBJECT
private:
    bool selected = false;
public:
    OperationBar* operationBar;

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
        if (ui::OperationsBarDataHandler::selected != nullptr)
        {
            if (ui::OperationsBarDataHandler::selected == operationBar)
            {
                setSelected(false);
                ui::OperationsBarDataHandler::selected = nullptr;
                return;
            }
            else
                ui::OperationsBarDataHandler::selected->mainButton->setSelected(false);
        }

        ui::OperationsBarDataHandler::selected = operationBar;
        setSelected(true);
    }
};