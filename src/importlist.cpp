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
    qDebug() << "Running handler";
    QList<QListWidgetItem *> items = ui->lwAvailableColumns->selectedItems();

    foreach(QListWidgetItem *item, items)
    {
        ui->lwAvailableColumns->removeItemWidget(item);
        ui->lwColumnOrder->addItem(item);
    }
}
