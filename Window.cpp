#include "Window.hpp"

#include "RenderArea.hpp"

#include <QtWidgets>

const int IdRole = Qt::UserRole;

Window::Window(): simulation(std::vector<std::vector<RenderArea::Color>>(RenderArea::AREA_WIDTH)) {
	for (int x = 0; x < RenderArea::AREA_WIDTH; ++x) {
		simulation.emplace_back(std::vector<RenderArea::Color>(RenderArea::AREA_HEIGHT));
		for (int y = 0; y < RenderArea::AREA_HEIGHT; ++y) {
			simulation[x].emplace_back(RenderArea::Color::BLACK);
		}
	}

	simulation[5][5] = RenderArea::Color::BLUE;

	renderArea = new RenderArea;
	renderArea->setDraw(simulation);

	auto mainLayout = new QGridLayout;
	mainLayout->setColumnStretch(0, 1);
	mainLayout->setColumnStretch(3, 1);
	mainLayout->addWidget(renderArea, 0, 0, 1, 4);
	setLayout(mainLayout);

	setWindowTitle(tr("Basic Drawing"));

	auto myTimer = new QTimer();
	connect(myTimer, SIGNAL(timeout()), this, SLOT(slotUpdate()));
	myTimer->setTimerType(Qt::PreciseTimer);
	myTimer->start(1000);
}

void Window::slotUpdate() {
	std::vector<std::vector<RenderArea::Color>> simulationNext;

	for (int x = 0; x < RenderArea::AREA_WIDTH; ++x) {
		simulationNext.emplace_back(std::vector<RenderArea::Color>(RenderArea::AREA_HEIGHT));
		for (int y = 0; y < RenderArea::AREA_HEIGHT; ++y) {
			simulationNext[x].emplace_back(RenderArea::Color::BLACK);
		}
	}

	simulation[5][5] = RenderArea::Color::BLUE;

	for (int x = 0; x < simulation.size(); ++x) {
		for (int y = 0; y < simulation[x].size(); ++y) {
			if(simulation[x][y] == RenderArea::Color::BLUE) {
				int nextX = x;
				int nextY = y;

				if(simulation[x][y + 1] == RenderArea::Color::BLACK) {
					nextX = x;
				} else if(x - 1 >= 0 && simulation[x - 1][y + 1] == RenderArea::Color::BLACK) {
					nextX = x - 1;
				} else if(x + 1 < simulation.size() && simulation[x + 1][y + 1] == RenderArea::Color::BLACK) {
					nextX = x + 1;
				}

				if(y + 1 < simulation.size() && simulation[x][y + 1] == RenderArea::Color::BLACK) {
					nextY = y + 1;
				}

				simulationNext[x][y] = RenderArea::Color::BLACK;
				simulationNext[nextX][nextY] =  RenderArea::Color::BLUE;
			}
		}
	}

	simulation = simulationNext;

	renderArea->setDraw(simulationNext);
}