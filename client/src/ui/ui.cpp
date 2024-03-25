//
// Created by César B. on 3/25/2024.
//

#include "ui.hpp"
#include "ui_creation_helpers.hpp"

void ui::init_all_widgets()
{	widgets::main_window::init();
}

void ui::widgets::main_window::init()
{	main_window = new QMainWindow;
	main_window->setWindowTitle("Taskk");
	main_window->resize(600, 400);
	central_widget::init();
	main_window->setCentralWidget(central_widget::central_widget);
}

void ui::widgets::main_window::central_widget::layout::button_panel_layout::init()
{	button_panel_layout = new QGridLayout;
	label = new QLabel(main_window);
	make_button(button_panel, test_1, "1", 0, 0);
	make_button(button_panel, test_2, "2", 0, 1);
	make_button(button_panel, test_3, "3");
	make_button(button_panel, test_4, "4");
}

void ui::widgets::main_window::central_widget::layout::log_layout::init()
{	log_layout = new QVBoxLayout;
	// label
	label = new QLabel("Log", main_window);
	log_layout->addWidget(label);
	// clear button
	make_button(log, clear, "Clear");
	// log
	log = new QTextBrowser(main_window);
	log->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	log->setFixedHeight(200);
	log_layout->addWidget(log);
}

void ui::widgets::main_window::central_widget::layout::init()
{	layout = new QVBoxLayout;
	button_panel_layout::init();
	log_layout::init();
	layout->addLayout(button_panel_layout::button_panel_layout);
	layout->addLayout(log_layout::log_layout);
}

void ui::widgets::main_window::central_widget::init()
{	central_widget = new QWidget(main_window);
	layout::init();
	central_widget->setLayout(layout::layout);
}
