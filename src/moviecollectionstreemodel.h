#ifndef MOVIEGROUPSMODEL_H
#define MOVIEGROUPSMODEL_H

#include <QAbstractItemModel>
#include <QSettings>
#include "moviecollection.h"

class MovieCollectionsTreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit MovieCollectionsTreeModel(QObject *parent = 0);
	~MovieCollectionsTreeModel();

	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex &index) const;

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;

	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);

	bool removeRows(int row, int count, const QModelIndex &parent);

    Qt::ItemFlags flags(const QModelIndex &index) const;
	
signals:
	
public slots:

    void SaveCollectionChanges();

private:

	QSettings m_settings;
	QList<MovieCollection*> m_collections;
	
};

#endif // MOVIEGROUPSMODEL_H
