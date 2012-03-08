#ifndef ADDNEWMOVIEDIALOG_H
#define ADDNEWMOVIEDIALOG_H

#include <QDialog>

namespace Ui {
class AddNewMovieDialog;
}

class AddNewMovieDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit AddNewMovieDialog(QWidget *parent = 0);
	~AddNewMovieDialog();
	
private:
	Ui::AddNewMovieDialog *ui;
};

#endif // ADDNEWMOVIEDIALOG_H
