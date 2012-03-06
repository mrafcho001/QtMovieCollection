#ifndef MOVIELISTMODEL_H
#define MOVIELISTMODEL_H

#include <QAbstractListModel>
#include "collectionmanager.h"

class MovieListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit MovieListModel(QObject *parent = 0);

	int rowCount(const QModelIndex &) const;
	int columnCount(const QModelIndex &) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	
signals:
	
public slots:

private:

	CollectionManager m_movieCollection;
	QStringList m_header;
	
};

#endif // MOVIELISTMODEL_H