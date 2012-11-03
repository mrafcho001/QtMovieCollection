#ifndef COLLECTIONMANAGER_H
#define COLLECTIONMANAGER_H

#include "movieinfo.h"

#include <QtCore>
#include <QList>

class MovieCollection
{
public:
	MovieCollection(const QString &name, const QString &fileName);
    MovieCollection(const MovieCollection &mc);
	~MovieCollection();

	const MovieInfo& getMovieInfo(const int index) const;
	MovieInfo& getMovieInfo(const int index);

	void setDirty();

	int count() const;

	QString getName() const;
	void setName(const QString name);

	void addMovie(const MovieInfo &mi);
    void removeMovie(const int index);

    void insertMovie(int row, const MovieInfo &mi);
    void insertNewMoview(int row);

    void removeAt(int row);

	void sync();

	void setXMLFileLocation(const QString &xmlFile);

	void readFromFile();
	void writeToFile();
protected:

	bool m_dirty;
	QString m_collectionName;
	QString m_xmlFilePath;
	QXmlStreamReader *m_xmlReader;
	QXmlStreamWriter *m_xmlWriter;

	QList<MovieInfo> m_movies;
};

#endif // COLLECTIONMANAGER_H
