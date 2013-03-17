#include "addnewmoviedialog.h"
#include "ui_addnewmoviedialog.h"

AddNewMovieDialog::AddNewMovieDialog(QWidget *parent) :
	QDialog(parent),
    ui(new Ui::AddNewMovieDialog)
{
    ui->setupUi(this);

    connect(ui->pbAddGenre, SIGNAL(clicked()), this, SLOT(AddNewGenre()));
    connect(ui->pbAddNewMovie, SIGNAL(clicked()), this, SLOT(AcceptChanges()));
    connect(ui->pbAddTag, SIGNAL(clicked()), this, SLOT(AddNewtag()));
    connect(ui->pbCancel, SIGNAL(clicked()), this, SLOT(CancelChanges()));
    connect(ui->pbRemoveSelectedGenre, SIGNAL(clicked()), this, SLOT(RemoveSelectedGenres()));
    connect(ui->pbRemoveSelectedTags, SIGNAL(clicked()), this, SLOT(RemoveSelectedTags()));
}

AddNewMovieDialog::~AddNewMovieDialog()
{
    delete ui;
}

void AddNewMovieDialog::setMovieInfoPtr(MovieInfo *ptr)
{
    this->mi = ptr;

    ui->leName->setText(mi->getName());
    ui->leYear->setText(QString::number(mi->getYear()));
    ui->leIMDB->setText(mi->getIMDBLink());
    ui->leRating->setText(QString::number(mi->getRating()));
    ui->deLastWatched->setDate(mi->getLastWatchedDate());

    ui->lwGenreList->addItems(mi->getGenres());
    ui->lwTagList->addItems(mi->getTags());
}


void AddNewMovieDialog::AcceptChanges()
{
    mi->setName(ui->leName->text());
    mi->setYear(ui->leYear->text().toInt());
    mi->setIMDBLink(ui->leIMDB->text());
    mi->setRating(ui->leRating->text().toInt());
    mi->setLastWatchedDate(ui->deLastWatched->date());

    mi->clearGenres();
    for(int i = 0; i < ui->lwGenreList->count(); i++)
        mi->addGenre(ui->lwGenreList->item(i)->text());

    mi->clearTags();
    for(int i = 0; i < ui->lwTagList->count(); i++)
        mi->addTag(ui->lwTagList->item(i)->text());
    this->done(QDialog::Accepted);
}

void AddNewMovieDialog::CancelChanges()
{
    this->done(QDialog::Rejected);
}

void AddNewMovieDialog::AddNewGenre()
{
    if(ui->leNewGenre->text().count() < 1)
        return;

    ui->lwGenreList->addItem(ui->leNewGenre->text());
    ui->leNewGenre->clear();
}

void AddNewMovieDialog::AddNewtag()
{
    if(ui->leNewTag->text().count() < 1)
        return;

    ui->lwTagList->addItem(ui->leNewTag->text());
    ui->leNewTag->clear();
}

void AddNewMovieDialog::RemoveSelectedGenres()
{
    QList<QListWidgetItem*> toRemove = ui->lwGenreList->selectedItems();
    foreach(QListWidgetItem* item, toRemove)
        ui->lwGenreList->removeItemWidget(item);
}

void AddNewMovieDialog::RemoveSelectedTags()
{
    QList<QListWidgetItem*> toRemove = ui->lwTagList->selectedItems();
    foreach(QListWidgetItem* item, toRemove)
        ui->lwTagList->removeItemWidget(item);
}
