#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movielistmodel.h"
#include "moviefilterproxymodel.h"
#include "moviecollectionstreemodel.h"
#include "addnewmoviedialog.h"

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

	MovieCollectionsTreeModel *mc_model = new MovieCollectionsTreeModel(this);
	ui->tvCollectionView->setModel(mc_model);
	ui->tvCollectionView->setHeaderHidden(true);
	ui->tvCollectionView->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(ui->tvCollectionView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
			this, SLOT(collectionChanged(QModelIndex,QModelIndex)));

	ui->tvCollectionView->selectionModel()->setCurrentIndex(ui->tvCollectionView->model()->index(0, 0), QItemSelectionModel::Select);

    //Initialize Filter Action
	filterBar = new FilterSearchWidget(this);
	ui->verticalLayout->addWidget(filterBar);
	filterBar->hide();
	connect(filterBar, SIGNAL(filterChanged(QString,QRegExp::PatternSyntax,Qt::CaseSensitivity)),
			this, SLOT(updateFilter(QString,QRegExp::PatternSyntax,Qt::CaseSensitivity)));

    connect(ui->actionShowFilter, SIGNAL(triggered()), this, SLOT(toggleFilterBar()));
    ui->actionShowFilter->setIcon(QIcon::fromTheme("view-filter"));

    //Initialize Add Movie Button
    connect(ui->actionAddNewMovie, SIGNAL(triggered()), this, SLOT(addMovie()));
    ui->actionAddNewMovie->setIcon(QIcon(":/icons/movie-add"));

    //Other Toolbar Buttons
    ui->actionDeleteMovieGroup->setIcon(QIcon(":/icons/movie-collection-delete.png"));
	ui->actionNewMovieGroup->setIcon(QIcon(":/icons/movie-collection-add"));
    ui->actionDeleteMovie->setIcon(QIcon(":/icons/movie-delete"));

    //Other Actions


    //Save Changes
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(SaveChanges()));

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
	MovieFilterProxyModel *model = (MovieFilterProxyModel*)ui->tvMovieList->model();
	model->setFilterRegExp(QRegExp(text, cs, ps));
	model->setFilterKeyColumn(1);
}

void MainWindow::collectionChanged(QModelIndex current, QModelIndex previous)
{
	Q_UNUSED(previous);
	MovieCollection *mc = static_cast<MovieCollection*>(current.internalPointer());

	MovieListModel *model = new MovieListModel(mc, this);
	MovieFilterProxyModel *filterModel = new MovieFilterProxyModel(this);
	filterModel->setSourceModel(model);
	filterModel->setDynamicSortFilter(true);

	ui->tvMovieList->setModel(filterModel);
}

void MainWindow::addMovie()
{
    MovieListModel *model = (MovieListModel*)((MovieFilterProxyModel*)ui->tvMovieList->model())->sourceModel();
    MovieInfo mi;

    AddNewMovieDialog *newMovieDialog = new AddNewMovieDialog(this);
    newMovieDialog->setMovieInfoPtr(&mi);
    if(newMovieDialog->exec() == QDialog::Accepted)
        model->insertMovie(0, mi, QModelIndex());
}

void MainWindow::SaveChanges()
{
    MovieCollectionsTreeModel *model = (MovieCollectionsTreeModel*)ui->tvCollectionView->model();
    model->SaveCollectionChanges();
}

MainWindow::~MainWindow()
{
	delete ui;
}
