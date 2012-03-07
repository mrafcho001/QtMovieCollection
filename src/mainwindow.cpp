#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movielistmodel.h"
#include "moviefilterproxymodel.h"

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

	MovieListModel *model = new MovieListModel(QString("Library.xml"), this);
	MovieFilterProxyModel *filterModel = new MovieFilterProxyModel(this);
	filterModel->setSourceModel(model);
	filterModel->setDynamicSortFilter(true);

	ui->treeView->setModel(filterModel);

	filterBar = new FilterSearchWidget(this);
	ui->verticalLayout->addWidget(filterBar);
	filterBar->hide();
	connect(filterBar, SIGNAL(filterChanged(QString,QRegExp::PatternSyntax,Qt::CaseSensitivity)),
			this, SLOT(updateFilter(QString,QRegExp::PatternSyntax,Qt::CaseSensitivity)));

	connect(ui->actionShowFIlter, SIGNAL(triggered()), this, SLOT(toggleFilterBar()));
}

void MainWindow::toggleFilterBar()
{
	if(filterBar->isHidden())
	{
		filterBar->show();
		filterBar->setFocus();
	}
	else
		filterBar->hide();
}

void MainWindow::updateFilter(QString text, QRegExp::PatternSyntax ps, Qt::CaseSensitivity cs)
{
	MovieFilterProxyModel *model = (MovieFilterProxyModel*)ui->treeView->model();
	model->setFilterRegExp(QRegExp(text, cs, ps));
	model->setFilterKeyColumn(1);
}

MainWindow::~MainWindow()
{
	delete ui;
}
