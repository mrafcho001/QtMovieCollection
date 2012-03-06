#ifndef FILTERSEARCHWIDGET_H
#define FILTERSEARCHWIDGET_H

#include <QWidget>
#include <QRegExp>

namespace Ui {
class FilterSearchWidget;
}

class FilterSearchWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit FilterSearchWidget(QWidget *parent = 0);
	~FilterSearchWidget();

signals:
	void filterChanged(QString text, QRegExp::PatternSyntax ps, Qt::CaseSensitivity cs);

private slots:
	void handleChanges();
	void automaticChanged(bool checked);
	void hideSelf();
	
private:
	Ui::FilterSearchWidget *ui;
};

#endif // FILTERSEARCHWIDGET_H
