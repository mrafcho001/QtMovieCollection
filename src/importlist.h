#ifndef IMPORTLIST_H
#define IMPORTLIST_H

#include <QDialog>
#include <QFile>

namespace Ui {
class ImportList;
}

class ImportList : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportList(QWidget *parent = 0);
    ~ImportList();

public slots:
    void togglePreview();
    void browseListFile();
    void reloadSelectedFile();
    void addSelectedColumns();
    void removeSelectedColumns();
    void moveSelectedDown();
    void moveSelectedUp();

private:
    Ui::ImportList *ui;

    QFile *selectedFile;
};

#endif // IMPORTLIST_H
