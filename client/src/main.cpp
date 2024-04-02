#include <QApplication>
#include "ui/ui.hpp"
#include "mainwindow.h"
#include "Handlers/OperationsBarData/OperationsBarData.h"

void init()
{
}

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

//    ui::OperationsBarDataHandler::CreateBar(0, 100, "Testo", 0);
//    ui::OperationsBarDataHandler::CreateBar(100, 150, "Testo", 0);
//    ui::OperationsBarDataHandler::CreateTransparentBar(100, 150, 0);

//    OperationData testData;
//    testData.start = 0;
//    testData.end = 200;
//    testData.operationName = "ewef";
//
//    OperationData deepData;
//    deepData.start = 220;
//    deepData.end = 400;
//    deepData.operationName = "DEEP";
//    deepData.subData = {{240, 300, "testo"}};
//
//    testData.subData = {{150, 190, "eee", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", {{155, 190, "s", {{160, 190, "s", {{165, 190, "s", {{170, 190, "s", }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}};
//
//    ui::OperationsBarDataHandler::InitOperation(0, 4000, "ASD",{testData, deepData});

    init();

    ui::OperationsBarDataHandler::UpdateBarZoom();

    return a.exec();
}

