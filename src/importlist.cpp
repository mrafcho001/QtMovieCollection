#include "importlist.h"
#include "ui_importlist.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

class UserRoleData
{
    public:
    enum PositionInMap { Name = 0, Year = 1, Quality = 2, IMDB = 3 };

    UserRoleData(): regexp(""), mapPosition(Name) { }
    UserRoleData(QString regex, PositionInMap position): regexp(regex), mapPosition(position) { }
    QString regexp;
    PositionInMap mapPosition;
};
Q_DECLARE_METATYPE(UserRoleData);


ImportList::ImportList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportList), selectedFile(NULL)
{
    ui->setupUi(this);

    //Set up preview table
    ui->twPreview->setHidden(true);
    ui->pbRefresh->setHidden(true);

    connect(ui->gbPreview, SIGNAL(clicked()), this, SLOT(togglePreview()));
    connect(ui->pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->pbImport, SIGNAL(clicked()), this, SLOT(import()));

    //Browse File and Preview Related
    connect(ui->pbBrowse, SIGNAL(clicked()), this, SLOT(browseListFile()));
    connect(ui->leFilePath, SIGNAL(editingFinished()), this, SLOT(reloadSelectedFile()));
    connect(ui->leFilePath, SIGNAL(returnPressed()), this, SLOT(reloadSelectedFile()));
    connect(ui->pbRefresh, SIGNAL(clicked()), this, SLOT(reloadSelectedFile()));

    //Column Management Related
    connect(ui->pbAdd, SIGNAL(clicked()), this, SLOT(addSelectedColumns()));
    connect(ui->pbRemove, SIGNAL(clicked()), this, SLOT(removeSelectedColumns()));
    connect(ui->pbMoveUp, SIGNAL(clicked()), this, SLOT(moveSelectedUp()));
    connect(ui->pbMoveDown, SIGNAL(clicked()), this, SLOT(moveSelectedDown()));


    QListWidgetItem *item = new QListWidgetItem("Name", ui->lwAvailableColumns);
    item->setToolTip("Movie Title; Can contain any character");
    item->setData(Qt::UserRole, QVariant::fromValue(UserRoleData(QString("\"(.*)\""), UserRoleData::Name)));
    ui->lwAvailableColumns->addItem(item);

    item = new QListWidgetItem("Year", ui->lwAvailableColumns);
    item->setToolTip("Year when the movie came out; format: YYYY");
    item->setData(Qt::UserRole, QVariant::fromValue(UserRoleData(QString("([0-9]*)"), UserRoleData::Year)));
    ui->lwAvailableColumns->addItem(item);

    item = new QListWidgetItem("Quality", ui->lwAvailableColumns);
    item->setToolTip("Should be one of the following string: \"Xvid\", \"BDRIP\", \"720p\", or \"1080p\"");
    item->setData(Qt::UserRole, QVariant::fromValue(UserRoleData(QString("\"(.*)\""), UserRoleData::Quality)));
    ui->lwAvailableColumns->addItem(item);

    item = new QListWidgetItem("IMDB Link", ui->lwAvailableColumns);
    item->setToolTip("Valid link to IMDB Page.");
    item->setData(Qt::UserRole, QVariant::fromValue(UserRoleData(QString("\"(.*)\""), UserRoleData::IMDB)));
    ui->lwAvailableColumns->addItem(item);

    QStringList selectedColumns;
    m_settings.beginGroup(IMPORT_GROUP);

    int size = m_settings.beginReadArray(SELECTED_COLUMNS_ARRAY);
    for(int i = 0; i < size; i++)
    {
        m_settings.setArrayIndex(i);
        selectedColumns.push_front(m_settings.value(SELECTED_COLUMNS_COLUMN_KEY).toString());
    }
    m_settings.endArray();

    ui->leFilePath->setText(m_settings.value(LAST_SELECTED_FILE_KEY).toString());
    reloadSelectedFile();

    m_settings.endGroup();

    QStringList::iterator itr = selectedColumns.begin();
    for(; itr != selectedColumns.end(); ++itr)
    {
        for(int i = 0; i < ui->lwAvailableColumns->count(); i++)
        {
            if(ui->lwAvailableColumns->item(i)->text() == *itr)
            {
                ui->lwColumnOrder->insertItem(0, ui->lwAvailableColumns->takeItem(i));
                break;
            }
        }
    }
}

ImportList::~ImportList()
{
    delete ui;
}

void ImportList::togglePreview()
{
    if(ui->gbPreview->isChecked())
    {
        ui->twPreview->show();
        ui->pbRefresh->show();
    }
    else
    {
        ui->twPreview->hide();
        ui->pbRefresh->hide();
    }
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

    if(ui->gbPreview->isChecked())
    {
        //Render preview
        reloadPreview();
    }
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

void ImportList::import()
{
    if(!selectedFile->isOpen() && !selectedFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int mapsize = ui->lwColumnOrder->count()+ui->lwAvailableColumns->count();
    int map[mapsize];
    // 0 - name, 1 - year, 2 - quality, 3 - IMDB
    for(int i = 0; map[i] = 0, i < mapsize; i++);

    QString regexp;
    for(int i = 0; i < ui->lwColumnOrder->count(); i++)
    {
        UserRoleData userData = ui->lwColumnOrder->item(i)->data(Qt::UserRole).value<UserRoleData>();
        regexp = regexp + userData.regexp + ",";

        map[(int)userData.mapPosition] = i+1;
    }

    regexp.chop(1);

    QRegExp regEx(regexp);

    QTextStream in(selectedFile);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        regEx.indexIn(line);
        QStringList caps = regEx.capturedTexts();
        caps[0] = "";

        MovieInfo mi;
        mi.setName(caps[map[0]]);
        mi.setYear(caps[map[1]].toInt());
        mi.setQuality(caps[map[2]]);
        mi.setIMDBLink(caps[map[3]]);

        importedMovies.push_back(mi);
    }

    m_settings.beginGroup(IMPORT_GROUP);
    m_settings.setValue(LAST_SELECTED_FILE_KEY, ui->leFilePath->text());

    m_settings.beginWriteArray(SELECTED_COLUMNS_ARRAY);
    for(int i = 0; i < ui->lwColumnOrder->count(); i++)
    {
        m_settings.setArrayIndex(i);
        m_settings.setValue(SELECTED_COLUMNS_COLUMN_KEY, ui->lwColumnOrder->item(i)->text());
    }
    m_settings.endArray();

    m_settings.endGroup();

    this->accept();
}

void ImportList::reloadPreview()
{
    if(ui->lwColumnOrder->count() == 0 )
        return;
    if(!selectedFile->isOpen() && !selectedFile->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList header;
    QString regexp;

    for(int i = 0; i < ui->lwColumnOrder->count(); i++)
    {
        regexp = regexp + ui->lwColumnOrder->item(i)->data(Qt::UserRole).value<UserRoleData>().regexp + ",";
        header << ui->lwColumnOrder->item(i)->text();
    }
    regexp.chop(1);

    ui->twPreview->setRowCount(0);
    ui->twPreview->setColumnCount(header.count());
    ui->twPreview->setHorizontalHeaderLabels(header);

    QRegExp regEx(regexp);

    QTextStream in(selectedFile);
    for(int i = 0; i < 3 && !in.atEnd(); i++)
    {
        QString line = in.readLine();
        regEx.indexIn(line);
        QStringList caps = regEx.capturedTexts();

        ui->twPreview->insertRow(i);
        for(int j = 0; j < ui->twPreview->columnCount() && j < caps.count()-1; j++)
            ui->twPreview->setItem(i, j, new QTableWidgetItem(caps[j+1]));
    }

    ui->twPreview->resizeRowsToContents();

    selectedFile->close();
}
