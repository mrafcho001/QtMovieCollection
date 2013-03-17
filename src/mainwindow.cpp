#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movielistmodel.h"
#include "moviefilterproxymodel.h"
#include "moviecollectionstreemodel.h"
#include "addnewmoviedialog.h"
#include "importlist.h"

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

    //Setup Movie Tree View
    MovieCollectionsTreeModel *mc_model = new MovieCollectionsTreeModel(this);
    ui->tvCollectionView->setModel(mc_model);
    ui->tvCollectionView->setHeaderHidden(true);
    ui->tvCollectionView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->tvCollectionView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(collectionChanged(QModelIndex,QModelIndex)));

    ui->tvCollectionView->selectionModel()->setCurrentIndex(ui->tvCollectionView->model()->index(0, 0), QItemSelectionModel::Select);

    //Item double clicks
    connect(ui->tvMovieList, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(editMovie(const QModelIndex&)));

    QHeaderView *hv = ui->tvMovieList->header();
    hv->setSortIndicatorShown(true);
    hv->setClickable(true);
    hv->setStretchLastSection(false);
    hv->setResizeMode(0, QHeaderView::Stretch);
    for(int i = 1; i < hv->count(); i++)
        hv->setResizeMode(i, QHeaderView::ResizeToContents);
    ui->tvMovieList->setSortingEnabled(true);

    //Right clicks
    ui->tvMovieList->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tvMovieList->addAction(ui->actionUpdateWatchedDate);
    ui->tvMovieList->addAction(ui->actionDeleteMovie);
    ui->tvMovieList->addAction(ui->actionAddNewMovie);


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
    connect(ui->actionUpdateWatchedDate, SIGNAL(triggered()), this, SLOT(updateLastWatchedDate()));


    //Quit Action
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));

    //Save Changes
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(SaveChanges()));

    //Import from list
    connect(ui->actionImport_List, SIGNAL(triggered()), this, SLOT(ImportFromList()));

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
    MovieInfo mi;
    AddNewMovieDialog *newMovieDialog = new AddNewMovieDialog(this);
    newMovieDialog->setMovieInfoPtr(&mi);

    if(newMovieDialog->exec() == QDialog::Accepted)
    {
        MovieListModel *model = (MovieListModel*)((MovieFilterProxyModel*)ui->tvMovieList->model())->sourceModel();
        model->insertMovie(0, mi, QModelIndex());
    }
}

void MainWindow::editMovie(const QModelIndex & index)
{
    MovieFilterProxyModel *filterModel = static_cast<MovieFilterProxyModel*>(ui->tvMovieList->model());
    MovieListModel *model = static_cast<MovieListModel*>(filterModel->sourceModel());
    MovieInfo *mi = model->getMovieInfoPtr(index);

    AddNewMovieDialog *editMovie = new AddNewMovieDialog(this);
    editMovie->setMovieInfoPtr(mi);

    if(editMovie->exec() == QDialog::Accepted)
        model->movieUpdated(index);
}

void MainWindow::updateLastWatchedDate()
{
    QModelIndexList selected = ui->tvMovieList->selectionModel()->selectedRows();
    MovieFilterProxyModel* fm = static_cast<MovieFilterProxyModel*>(ui->tvMovieList->model());
    MovieListModel *model = static_cast<MovieListModel*>(fm->sourceModel());

    foreach(QModelIndex index, selected)
    {
        model->getMovieInfoPtr(fm->mapToSource(index))->setLastWatchedDate(QDate::currentDate());
    }
}

void MainWindow::SaveChanges()
{
    MovieCollectionsTreeModel *model = (MovieCollectionsTreeModel*)ui->tvCollectionView->model();
    model->SaveCollectionChanges();
}

void MainWindow::ImportFromList()
{
    ImportList *il = new ImportList(this);
    if(il->exec() == QDialog::Accepted)
    {
        MovieListModel *model = (MovieListModel*)((MovieFilterProxyModel*)ui->tvMovieList->model())->sourceModel();

        QList<MovieInfo>::iterator itr = il->importedMovies.begin();
        for(; itr != il->importedMovies.end(); ++itr)
            model->insertMovie(0, *itr, QModelIndex());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
