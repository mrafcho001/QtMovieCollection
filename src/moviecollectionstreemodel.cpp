#include "moviecollectionstreemodel.h"
#include "constants.h"

MovieCollectionsTreeModel::MovieCollectionsTreeModel(QObject *parent) :
	QAbstractItemModel(parent)
{
	int size = m_settings.beginReadArray(QSETTINGS_MOVIE_COLLECTIONS_ARRAY_NAME);
	for(int i = 0; i < size; i++)
	{
		m_settings.setArrayIndex(i);
		QString name = m_settings.value(QSETTINGS_MOVIE_COLLECTINOS_COLLECTION_NAME).toString();
		QString filename = m_settings.value(QSETTINGS_MOVIE_COLLECTINOS_COLLECTIN_FILENAME).toString();
		MovieCollection mc(name, filename);
		m_collections.append(mc);
	}
	m_settings.endArray();
}

MovieCollectionsTreeModel::~MovieCollectionsTreeModel()
{

}

QModelIndex MovieCollectionsTreeModel::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex MovieCollectionsTreeModel::parent(const QModelIndex &index) const
{

}

int MovieCollectionsTreeModel::rowCount(const QModelIndex &parent) const
{

}

int MovieCollectionsTreeModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QVariant MovieCollectionsTreeModel::data(const QModelIndex &index, int role) const
{

}

bool MovieCollectionsTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

QVariant MovieCollectionsTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

bool MovieCollectionsTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{

}

Qt::ItemFlags MovieCollectionsTreeModel::flags(const QModelIndex &index) const
{

}
