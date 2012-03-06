#include "moviefilterproxymodel.h"
#include <QDate>

MovieFilterProxyModel::MovieFilterProxyModel(QObject *parent) :
	QSortFilterProxyModel(parent)
{
}

bool MovieFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
	QVariant leftData = sourceModel()->data(left);
	QVariant rightData = sourceModel()->data(right);

	//Handle any special cases
	switch(leftData.type())
	{
	case QVariant::String:
		return leftData.toString() < rightData.toString();
	case QVariant::Int:
		return leftData.toInt() < rightData.toInt();
	case QVariant::Date:
		return leftData.toDate() < leftData.toDate();
	default:
		return true;
	}
}

bool MovieFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	int nCols = sourceModel()->columnCount();
	QModelIndex *colIndexes = new QModelIndex[nCols];

	for(int i = 0; i < nCols; i++)
	{
		colIndexes[i] = sourceModel()->index(source_row, i, source_parent);
	}

	int passes = false;

	for(int i = 0; i < nCols; i++)
	{
		passes = passes || sourceModel()->data(colIndexes[i]).toString().contains(filterRegExp());
	}
	return passes;
}
