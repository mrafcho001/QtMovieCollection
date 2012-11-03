#ifndef IMPORTLIST_H
#define IMPORTLIST_H

#include <QDialog>

namespace Ui {
class ImportList;
}

class ImportList : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImportList(QWidget *parent = 0);
    ~ImportList();
    
private:
    Ui::ImportList *ui;
};

#endif // IMPORTLIST_H
