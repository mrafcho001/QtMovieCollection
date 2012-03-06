#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movielistmodel.h"

#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->splitter->setStretchFactor(0, 0);
	ui->splitter->setStretchFactor(1,10);
	QList<int> sizes;
	sizes << 150 <<1000;
	ui->splitter->setSizes(sizes);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(switchModels()));

	MovieListModel *model = new MovieListModel(this);

	ui->treeView->setModel(model);
}

void MainWindow::switchModels()
{
	QStringListModel *model = new QStringListModel(this);
	QStringList list;
	list << "One" << "Two" << "Three" << "Four" << "Five";
	model->setStringList(list);
	ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
	delete ui;
}
