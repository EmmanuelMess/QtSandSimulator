#ifndef INC_8BITCPPGAME_WINDOW_HPP
#define INC_8BITCPPGAME_WINDOW_HPP

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include "RenderArea.hpp"

class Window : public QWidget {
Q_OBJECT

public:
	Window();

public slots:
	void slotUpdate(void);

private:
	std::vector<std::vector<RenderArea::Color>> simulation;
	RenderArea *renderArea;
};

#endif //INC_8BITCPPGAME_WINDOW_HPP
