#include "gui.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon("stupid.gif"));
	compiler *tmp = new compiler;
	tmp->show();
	return app.exec();
}