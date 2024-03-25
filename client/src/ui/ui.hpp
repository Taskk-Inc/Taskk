//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <string>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include "templates/delegate.hpp"

namespace ui
{	namespace widgets
	{	namespace main_window
		{	void init();
			inline QMainWindow * main_window;
			namespace central_widget
			{	void init();
				inline QWidget * central_widget;
				namespace layout
				{	void init();
					inline QVBoxLayout * layout;
					namespace button_panel_layout
					{	void init();
						inline QGridLayout * button_panel_layout;
						inline QLabel * label;
						inline QPushButton * test_1_button;
						inline QPushButton * test_2_button;
						inline QPushButton * test_3_button;
						inline QPushButton * test_4_button;
						inline templates::delegate<void()> test_1_button_clicked_cb;
						inline templates::delegate<void()> test_2_button_clicked_cb;
						inline templates::delegate<void()> test_3_button_clicked_cb;
						inline templates::delegate<void()> test_4_button_clicked_cb;
					}
					namespace log_layout
					{	void init();
						inline QVBoxLayout * log_layout;
						inline QLabel * label;
						inline QPushButton * clear_button;
						inline QTextBrowser * log;
						inline templates::delegate<void()> clear_button_clicked_cb;
					}
				}
			}
		}
	}
	void init_all_widgets();
	void log(std::string);
}
