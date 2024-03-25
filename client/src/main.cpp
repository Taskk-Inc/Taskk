#include <QApplication>
#include <QPushButton>
#include "ui/ui.hpp"

int main(int argc, char * argv[])
{	QApplication a(argc, argv);
	ui::init_all_widgets();
	ui::widgets::main_window::main_window->show();
	return QApplication::exec();
}
