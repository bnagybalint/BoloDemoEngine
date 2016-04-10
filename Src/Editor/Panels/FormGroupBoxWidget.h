#pragma once

#include "Assist/Common.h"

#include "ui_FormGroupBoxWidget.h"

#include <QWidget>

class FormGroupBoxWidget : public QWidget
{
	Q_OBJECT

public:
	FormGroupBoxWidget(QWidget* parent = NULL);
	~FormGroupBoxWidget();

private:
	Ui::FormGroupBoxWidget ui;
};

