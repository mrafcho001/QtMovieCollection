#ifndef ADDNEWMOVIEDIALOG_H
#define ADDNEWMOVIEDIALOG_H

#include <QDialog>
#include "movieinfo.h"

namespace Ui {
class AddNewMovieDialog;
}

class AddNewMovieDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit AddNewMovieDialog(QWidget *parent = 0);
    ~AddNewMovieDialog();

    void setMovieInfoPtr(MovieInfo *ptr);

public slots:

    void AcceptChanges();
    void CancelChanges();

    void AddNewGenre();
    void AddNewtag();

    void RemoveSelectedGenres();
    void RemoveSelectedTags();
	
private:
    Ui::AddNewMovieDialog *ui;

    MovieInfo *mi;
};

#endif // ADDNEWMOVIEDIALOG_H
