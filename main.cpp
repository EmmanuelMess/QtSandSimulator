#include <QApplication>
#include <QPushButton>
#include "Window.hpp"

int main(int argc, char *argv[]) {
	//Q_INIT_RESOURCE(basicdrawing);

	QApplication app(argc, argv);
	Window window;
	window.show();
	return app.exec();
}