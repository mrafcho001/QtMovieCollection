#include "movielistmodel.h"
#include <QDebug>

MovieListModel::MovieListModel(const QString &fileName, QObject *parent) :
	QAbstractListModel(parent)
{
    m_header << "Name" << "Year" << "Rating" << "Last Watched" << "Quality";
    m_movieCollection = new MovieCollection(QString("Library"), fileName);
}

MovieListModel::MovieListModel(MovieCollection *mc, QObject *parent)
{
    m_header << "Name" << "Year" << "Rating" << "Last Watched" << "Quality";
    m_movieCollection = mc;
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
        case 3:
            return mi.getLastWatchedDate();
        case 4:
            return mi.getQuality();
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

bool MovieListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row+count-1);
    MovieInfo mi;
    for(int i = row; i < row+count-1; i++)
        this->m_movieCollection->insertNewMoview(i);
    endInsertRows();

    return true;
}

bool MovieListModel::insertRow(int row, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row);
    this->m_movieCollection->insertNewMoview(row);
    endInsertRows();

    return true;
}

bool MovieListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row+count-1);
    for(int i = row; i < row+count; i++)
        this->m_movieCollection->removeAt(i);
    endRemoveRows();

    return true;
}

bool MovieListModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row);
    this->m_movieCollection->removeAt(row);
    endRemoveRows();

    return true;
}

bool MovieListModel::insertMovie(int row, const MovieInfo &mi, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row);
    this->m_movieCollection->insertMovie(row, mi);
    endInsertRows();

    return true;
}

MovieInfo *MovieListModel::getMovieInfoPtr(const QModelIndex &index)
{
    if(index.isValid())
    {
        return m_movieCollection->getMovieInfoPtr(index.row());
    }
    return NULL;
}

void MovieListModel::movieUpdated(const QModelIndex &index)
{
    emit dataChanged(index, index);
}

