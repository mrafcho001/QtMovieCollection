#include "movielistmodel.h"
#include <QDebug>

MovieListModel::MovieListModel(const QString &fileName, QObject *parent) :
	QAbstractListModel(parent)
{
	m_header << "Name" << "Year" << "Rating";
	m_movieCollection = new MovieCollection(QString("Library"), fileName);
}


int MovieListModel::rowCount(const QModelIndex &/*parent*/) const
{
	return m_movieCollection->count();
}

int MovieListModel::columnCount(const QModelIndex &/*parent*/) const
{
	return m_header.count();
}

QVariant MovieListModel::data(const QModelIndex &index, int role) const
{
	if(role == Qt::DisplayRole && index.isValid())
	{
		MovieInfo mi = m_movieCollection->getMovieInfo(index.row());
		switch(index.column())
		{
		case 0:
			return mi.getName();
		case 1:
			return mi.getYear();
		case 2:
			return mi.getRating();
		}
	}
	return QVariant();
}

QVariant MovieListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return m_header.value(section);
	}
	return QVariant();
}
