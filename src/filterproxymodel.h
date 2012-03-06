#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class FilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	explicit FilterProxyModel(QObject *parent = 0);
	
signals:
	
public slots:
	
};

#endif // FILTERPROXYMODEL_H
