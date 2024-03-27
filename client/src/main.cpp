#include <QApplication>
#include "ui/ui.hpp"
#include "mainwindow.h"
#include "Handlers/OperationsBarData/OperationsBarData.h"

int main(int argc, char * argv[])
{
    //QApplication a(argc, argv);
	//ui::init_all_widgets();
	//ui::widgets::main_window::main_window->show();
	//return QApplication::exec();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    ui::OperationsBarDataHandler::CreateBar(0, 100, "Test1");
//    ui::OperationsBarDataHandler::CreateTransparentBar(100, 200);
//    ui::OperationsBarDataHandler::CreateBar(200, 300, "Test2");
//    ui::OperationsBarDataHandler::CreateBar(300, 350, "Test3");
//    ui::OperationsBarDataHandler::CreateTransparentBar(350, 375);
//    ui::OperationsBarDataHandler::CreateBar(375, 425, "Test4");

    ui::OperationsBarDataHandler::CreateBar(0, 100, "Testo", 0);
//    ui::OperationsBarDataHandler::CreateBar(100, 150, "Testo", 0);
//    ui::OperationsBarDataHandler::CreateTransparentBar(100, 150, 0);
    OperationData testData;
    testData.start = 180*2;
    testData.end = 250*2;
    testData.operationName = "ewef";
    testData.subData = {{190*2, 210*2, "eee"}, {220*2, 250*2, "what"}};


    ui::OperationsBarDataHandler::InitOperation(150, 300*2, "ASD",{testData});

    return a.exec();
}
