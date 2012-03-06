#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MovieFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	explicit MovieFilterProxyModel(QObject *parent = 0);

	bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
	
signals:
	
public slots:
	
};

#endif // FILTERPROXYMODEL_H
