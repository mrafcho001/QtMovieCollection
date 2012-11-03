#include "moviecollectionstreemodel.h"
#include "constants.h"

MovieCollectionsTreeModel::MovieCollectionsTreeModel(QObject *parent) :
	QAbstractItemModel(parent)
{
	m_collections.append(new MovieCollection(QString("Collection"), QString("Library.xml")));
	int size = m_settings.beginReadArray(QSETTINGS_MOVIE_COLLECTIONS_ARRAY_NAME);
	for(int i = 0; i < size; i++)
	{
		m_settings.setArrayIndex(i);
		QString name = m_settings.value(QSETTINGS_MOVIE_COLLECTIONS_COLLECTION_NAME).toString();
		QString filename = m_settings.value(QSETTINGS_MOVIE_COLLECTIONS_COLLECTION_FILENAME).toString();

		m_collections.append(new MovieCollection(name, filename));
	}
	m_settings.endArray();
}

MovieCollectionsTreeModel::~MovieCollectionsTreeModel()
{
	foreach(MovieCollection *mc, m_collections)
	{
		delete mc;
	}
}

QModelIndex MovieCollectionsTreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();


	MovieCollection *mc;
	if (!parent.isValid())
		mc = m_collections.value(0);
	else
		mc = m_collections.value(row-1);
	return createIndex(row, column, mc);
}

QModelIndex MovieCollectionsTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	MovieCollection *mc = static_cast<MovieCollection*>(index.internalPointer());
	if(mc == m_collections.value(0))
		return QModelIndex();

	return createIndex(0, 0, m_collections.value(0));
}

int MovieCollectionsTreeModel::rowCount(const QModelIndex &parent) const
{
	if (!parent.isValid())
		return 1;
	else
		return m_collections.count()-1;
}

int MovieCollectionsTreeModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant MovieCollectionsTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	MovieCollection *mc = static_cast<MovieCollection*>(index.internalPointer());

	if(mc)
	{
		return mc->getName();
	}
	return QVariant();
}

bool MovieCollectionsTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(role == Qt::EditRole && index.isValid())
	{
		MovieCollection *mc = static_cast<MovieCollection*>(index.internalPointer());
		if(!mc)
			mc = m_collections.value(0);

		mc->setName(value.toString());
		return true;
	}
	return false;
}

bool MovieCollectionsTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if(parent.isValid())
	{
		beginRemoveRows(parent, row, count);
		for(int i = 0; i < count; i++)
			m_collections.removeAt(row);
		endRemoveRows();
		return true;
	}
	return false;
}

Qt::ItemFlags MovieCollectionsTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;

}

void MovieCollectionsTreeModel::SaveCollectionChanges()
{
    foreach(MovieCollection *mc, m_collections)
        mc->sync();
}
