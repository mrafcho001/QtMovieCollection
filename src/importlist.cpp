#include "importlist.h"
#include "ui_importlist.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

ImportList::ImportList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportList), selectedFile(NULL)
{
    ui->setupUi(this);

    ui->twPreview->setHidden(true);

    connect(ui->gbPreview, SIGNAL(clicked()), this, SLOT(togglePreview()));
    connect(ui->pbCancel, SIGNAL(clicked()), this, SLOT(reject()));

    //Browse File Related
    connect(ui->pbBrowse, SIGNAL(clicked()), this, SLOT(browseListFile()));
    connect(ui->leFilePath, SIGNAL(returnPressed()), this, SLOT(reloadSelectedFile()));

    //Column Management Related
    connect(ui->pbAdd, SIGNAL(clicked()), this, SLOT(addSelectedColumns()));
    connect(ui->pbRemove, SIGNAL(clicked()), this, SLOT(removeSelectedColumns()));
    connect(ui->pbMoveUp, SIGNAL(clicked()), this, SLOT(moveSelectedUp()));
    connect(ui->pbMoveDown, SIGNAL(clicked()), this, SLOT(moveSelectedDown()));

    QListWidgetItem *item = new QListWidgetItem("Name", ui->lwAvailableColumns);
    item->setToolTip("Movie Title; Can contain any character");
    ui->lwAvailableColumns->addItem(item);

    item = new QListWidgetItem("Year", ui->lwAvailableColumns);
    item->setToolTip("Year when the movie came out; format: YYYY");
    ui->lwAvailableColumns->addItem(item);

    item = new QListWidgetItem("Quality", ui->lwAvailableColumns);
    item->setToolTip("Should be one of the following string: \"Xvid\", \"BDRIP\", \"720p\", or \"1080p\"");
    ui->lwAvailableColumns->addItem(item);

    item = new QListWidgetItem("IMDB Link", ui->lwAvailableColumns);
    item->setToolTip("Valid link to IMDB Page.");
    ui->lwAvailableColumns->addItem(item);
}

ImportList::~ImportList()
{
    delete ui;
}

void ImportList::togglePreview()
{
    if(ui->gbPreview->isChecked())
        ui->twPreview->show();
    else
        ui->twPreview->hide();
}

void ImportList::browseListFile()
{
    ui->leFilePath->setText(QFileDialog::getOpenFileName(this));
    reloadSelectedFile();
}

void ImportList::reloadSelectedFile()
{
    if(selectedFile == NULL)
        selectedFile = new QFile(this);
    else
        selectedFile->close();

    selectedFile->setFileName(ui->leFilePath->text());

    QPalette palette = ui->leFilePath->palette();
    if(!selectedFile->exists())
        palette.setColor(QPalette::Text, Qt::red);
    else
        palette.setColor(QPalette::Text, Qt::black);
    ui->leFilePath->setPalette(palette);
}

void ImportList::addSelectedColumns()
{
    QList<QListWidgetItem *> items = ui->lwAvailableColumns->selectedItems();

    foreach(QListWidgetItem *item, items)
        ui->lwColumnOrder->addItem(ui->lwAvailableColumns->takeItem(ui->lwAvailableColumns->row(item)));
}

void ImportList::removeSelectedColumns()
{
    QList<QListWidgetItem *> items = ui->lwColumnOrder->selectedItems();

    foreach(QListWidgetItem *item, items)
        ui->lwAvailableColumns->addItem(ui->lwColumnOrder->takeItem(ui->lwColumnOrder->row(item)));
}

void ImportList::moveSelectedDown()
{
    int row = ui->lwColumnOrder->currentRow();

    if(row < ui->lwColumnOrder->count() - 1)
    {
        ui->lwColumnOrder->insertItem(row + 1, ui->lwColumnOrder->takeItem(row));
        ui->lwColumnOrder->setCurrentRow(row+1);
    }
}

void ImportList::moveSelectedUp()
{
    int row = ui->lwColumnOrder->currentRow();

    if(row > 0)
    {
        ui->lwColumnOrder->insertItem(row - 1, ui->lwColumnOrder->takeItem(row));
        ui->lwColumnOrder->setCurrentRow(row - 1);
    }
}
