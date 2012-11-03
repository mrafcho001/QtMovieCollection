#include "importlist.h"
#include "ui_importlist.h"

ImportList::ImportList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportList)
{
    ui->setupUi(this);
}

ImportList::~ImportList()
{
    delete ui;
}
