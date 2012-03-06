#ifndef COLLECTIONMANAGER_H
#define COLLECTIONMANAGER_H

#include "movieinfo.h"

#include <QtCore>
#include <QList>

class CollectionManager
{
public:
	CollectionManager();
	~CollectionManager();

	const MovieInfo& getMovieInfo(const int index) const;
	MovieInfo& getMovieInfo(const int index);

	int count() const;

	void addMovie(const MovieInfo &mi);
	void removeMovie(const int index);

	void sync();

	void setXMLFileLocation(const QString &xmlFile);

	void readFromFile();
	void writeToFile();
protected:

	QString m_xmlFileLocation;
	bool m_read;
	QXmlStreamReader *m_xmlReader;
	QXmlStreamWriter *m_xmlWriter;

	QList<MovieInfo> m_movies;
};

#endif // COLLECTIONMANAGER_H
