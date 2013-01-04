#ifndef IMPORTLIST_H
#define IMPORTLIST_H

#include <QDialog>
#include <QFile>
#include <QSettings>
#include "movieinfo.h"

#define IMPORT_GROUP            "import"
#define SELECTED_COLUMNS_ARRAY  "selectedColumns"
#define SELECTED_COLUMNS_COLUMN_KEY "column"
#define LAST_SELECTED_FILE_KEY      "lastFile"

namespace Ui {
class ImportList;
}

class ImportList : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportList(QWidget *parent = 0);
    ~ImportList();

    QList<MovieInfo> importedMovies;

public slots:
    void togglePreview();
    void browseListFile();
    void reloadSelectedFile();
    void addSelectedColumns();
    void removeSelectedColumns();
    void moveSelectedDown();
    void moveSelectedUp();

    void import();

    void reloadPreview();

private:
    Ui::ImportList *ui;

    QSettings m_settings;

    QFile *selectedFile;
};

#endif // IMPORTLIST_H
