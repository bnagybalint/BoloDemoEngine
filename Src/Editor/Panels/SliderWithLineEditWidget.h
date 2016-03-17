#pragma once

#include "Assist/Common.h"

#include "ui_SliderWithLineEditWidget.h"

#include <QWidget>

class SliderWithLineEditWidget : public QWidget
{
	Q_OBJECT

public:
	SliderWithLineEditWidget(QWidget* parent = NULL);
	~SliderWithLineEditWidget();

private:
	Ui::SliderWithLineEditWidget ui;
};

