#ifndef MOVIELISTMODEL_H
#define MOVIELISTMODEL_H

#include <QAbstractListModel>
#include "moviecollection.h"

class MovieListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	MovieListModel(const QString &fileName, QObject *parent = 0);
    MovieListModel(MovieCollection *mc, QObject *parent = 0);

	int rowCount(const QModelIndex &) const;
	int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role);
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool insertRow(int row, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    bool removeRow(int row, const QModelIndex &parent);

    bool insertMovie(int row, const MovieInfo &mi, const QModelIndex &parent);
	
signals:
	
public slots:

private:

	MovieCollection *m_movieCollection;
	QStringList m_header;
	
};

#endif // MOVIELISTMODEL_H
