#include "addnewmoviedialog.h"
#include "ui_addnewmoviedialog.h"

AddNewMovieDialog::AddNewMovieDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddNewMovieDialog)
{
	ui->setupUi(this);
}

AddNewMovieDialog::~AddNewMovieDialog()
{
	delete ui;
}
