#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("Martin Bakiev");
	QCoreApplication::setApplicationName("QtMovieCollection");

	MainWindow w;
	w.show();
	
	return a.exec();
}
