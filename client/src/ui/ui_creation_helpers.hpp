//
// Created by César B. on 3/25/2024.
//

#pragma once

/// @param ... layout->addWidget() arguments
#define make_button(layout, name, label, ...) \
	do \
	{	name##_button = new QPushButton(label, main_window); \
		QWidget::connect(name##_button, &QPushButton::clicked, [] { name##_button_clicked_cb.broadcast(); }); \
		typedef std::remove_pointer_t<decltype(layout##_layout)> layout_class_t; \
		_add_widget<layout_class_t>(layout##_layout, name##_button).exec(__VA_ARGS__) ; \
	} while(false)

template<typename _layout>
struct _add_widget
{	public:
		_layout * layout;
		QWidget * widget;
		template<typename... _varargs>
		_add_widget(_layout * layout, QWidget * widget, _varargs...) : layout(layout), widget(widget) {}
		void exec() { layout->addWidget(widget); }
		template<typename... _varargs>
		void exec(_varargs... varargs) { layout->addWidget(widget, varargs...); }
};
