#include <QLabel>
#include "OperationsBarData.h"
//
// Created by VERB1807 on 3/26/2024.
//

void ui::OperationsBarDataHandler::CreateBar(float start, float end, QString barName, int layoutIndex)
{
    OperationBar * operationBar = new OperationBar();
	float US = end - start;

	POperationButton * pushButton = new POperationButton();
	pushButton->setMinimumWidth(US * 2);
	pushButton->setMinimumHeight(25);

	pushButton->setStyleSheet(
		"QPushButton {border: 1px solid rgb(40, 83, 153); border-radius: 0px;background: rgb(50, 104, 191);} "
		"QPushButton:hover{border: 1px solid rgb(36, 82, 156); background: rgb(43, 95, 179);}"
	);

	QLabel * testLabel2 = new QLabel(barName);
	testLabel2->move(10, 0);
	testLabel2->setMinimumWidth(50);
	testLabel2->setMinimumHeight(23);
	testLabel2->setParent(pushButton);
	testLabel2->setStyleSheet("font-weight: bold;");

	QLabel * testLabel3 = new QLabel(QString::number(US).append(" μs"));
	testLabel3->move(US * 2 - 60, 0);
	testLabel3->setMinimumWidth(50);
	testLabel3->setMinimumHeight(23);
	testLabel3->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	testLabel3->setParent(pushButton);

	operationBar->mainButton = pushButton;
	operationBar->startUS = start;
	operationBar->endUS = end;

    pushButton->operationBar = operationBar;
	bars.push_back(operationBar);

	QObject::connect(pushButton, QPushButton::clicked, pushButton, &POperationButton::onClick);

    InsertInLayout(pushButton, layoutIndex);
}

void ui::OperationsBarDataHandler::CreateBar(float start, float end, QString barName, std::vector<OperationData> subData)
{
//	OperationBar * createdBar = bars.at(bars.size() - 1);
}

void ui::OperationsBarDataHandler::FillSpace(int layoutIndex, float endFill)
{
    if (horizontalLayouts.size() > layoutIndex)
    {
        if (horizontalLayouts[layoutIndex]->buttons.size() > 0)
        {
            float endFloat = horizontalLayouts[layoutIndex]->buttons[horizontalLayouts[layoutIndex]->buttons.size()-1]->operationBar->endUS;
            if (endFill > endFloat)
                ui::OperationsBarDataHandler::CreateTransparentBar(endFloat, endFill, layoutIndex);
        }
    }
    else if (endFill != 0)
    {
        while (horizontalLayouts.size() <= layoutIndex)
            ui::OperationsBarDataHandler::CreateHLayout();

        ui::OperationsBarDataHandler::CreateTransparentBar(0, endFill, layoutIndex);
    }
}

void ui::OperationsBarDataHandler::InitOperation(float start, float end, QString operationName, std::vector<OperationData> subData)
{
    ui::OperationsBarDataHandler::FillSpace(0, start);
    ui::OperationsBarDataHandler::CreateBar(start, end, operationName, 0);

    for (OperationData data : subData)
        ui::OperationsBarDataHandler::CreateDeepOperation(data, 1);
}

void ui::OperationsBarDataHandler::CreateDeepOperation(OperationData data, int layoutIndex)
{
    ui::OperationsBarDataHandler::FillSpace(layoutIndex, data.start);
    ui::OperationsBarDataHandler::CreateBar(data.start, data.end, data.operationName, layoutIndex);

    for (OperationData data2 : data.subData)
        ui::OperationsBarDataHandler::CreateDeepOperation(data2, layoutIndex+1);
}

void ui::OperationsBarDataHandler::CreateTransparentBar(float start, float end, int layoutIndex)
{
    OperationBar * operationBar = new OperationBar();
    float US = end - start;

    POperationButton * pushButton = new POperationButton();
    pushButton->operationBar = operationBar;
    pushButton->setMinimumWidth(US * 2);
    pushButton->setMinimumHeight(25);

    pushButton->setStyleSheet(
            "QPushButton {border: transparent;}"
    );

    pushButton->setFocusPolicy(Qt::NoFocus);

    operationBar->mainButton = pushButton;

    bars.push_back(operationBar);

    InsertInLayout(pushButton, layoutIndex);
}

void ui::OperationsBarDataHandler::InsertInLayout(QWidget * object, int index)
{
    while (horizontalLayouts.size() <= index)
        ui::OperationsBarDataHandler::CreateHLayout();

	QHBoxLayout * HLayout = horizontalLayouts[index]->horizonalLayout;
	QSpacerItem * HSpacer = horizontalLayouts[index]->spacerItem;

    horizontalLayouts[index]->buttons.push_back((POperationButton*)object);

	HLayout->removeItem(HSpacer);
	HLayout->addWidget(object);
	HLayout->addItem(HSpacer);
}

void ui::OperationsBarDataHandler::CreateHLayout()
{
    HorizontalBoxData* boxData = new HorizontalBoxData();

    QHBoxLayout * HLayout = new QHBoxLayout();
	HLayout->setSpacing(0);
	HLayout->setObjectName(QString("HLayout") + QString::number(ui::OperationsBarDataHandler::horizontalLayouts.size() + 1));

	QSpacerItem * HSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
	HLayout->addItem(HSpacer);

    boxData->spacerItem = HSpacer;
    boxData->horizonalLayout = HLayout;

	ui::mainWindow->verticalLayout_4->addLayout(HLayout);
	ui::mainWindow->verticalLayout_4->removeItem(ui::mainWindow->verticalSpacer);
	ui::mainWindow->verticalLayout_4->addItem(ui::mainWindow->verticalSpacer);

    ui::OperationsBarDataHandler::horizontalLayouts.push_back(boxData);
}