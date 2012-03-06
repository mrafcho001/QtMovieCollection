#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filtersearchwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void toggleFilterBar();
	void updateFilter(QString text, QRegExp::PatternSyntax ps, Qt::CaseSensitivity cs);
	
private:
	Ui::MainWindow *ui;
	FilterSearchWidget *filterBar;
};

#endif // MAINWINDOW_H
