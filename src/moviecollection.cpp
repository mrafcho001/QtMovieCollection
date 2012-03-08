#include "moviecollection.h"
#include "constants.h"
#include <QFile>
#include <QDesktopServices>
#include <QDir>

MovieCollection::MovieCollection(const QString &name, const QString &fileName)
	: m_dirty(false), m_collectionName(name), m_xmlReader(NULL), m_xmlWriter(NULL)
{
	QDir dir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
	if(!dir.exists())
		dir.mkpath(dir.path());

	m_xmlFilePath = dir.filePath(fileName);

	readFromFile();
}

MovieCollection::MovieCollection(const MovieCollection &mc)
{
	m_dirty = mc.m_dirty;
	m_collectionName = mc.m_collectionName;
	m_xmlFilePath = mc.m_xmlFilePath;
	readFromFile();
}

MovieCollection::~MovieCollection()
{
	if(m_dirty)
		writeToFile();
}

const MovieInfo& MovieCollection::getMovieInfo(const int index) const
{
	return m_movies[index];
}

MovieInfo& MovieCollection::getMovieInfo(const int index)
{
	return m_movies[index];
}

int MovieCollection::count() const
{
	return m_movies.count();
}

QString MovieCollection::getName() const
{
	return m_collectionName;
}

void MovieCollection::setName(const QString name)
{
	m_collectionName = name;
}

void MovieCollection::addMovie(const MovieInfo &mi)
{
	m_movies.append(mi);
}

void MovieCollection::removeMovie(const int index)
{
	m_movies.removeAt(index);
}

void MovieCollection::sync()
{
	if(m_dirty)
		writeToFile();
}

void MovieCollection::readFromFile()
{
	QFile file(m_xmlFilePath);
	if(!file.open(QIODevice::ReadWrite))
		return;

	m_xmlReader = new QXmlStreamReader(&file);

	if(!(m_xmlReader->readNextStartElement()
		 && m_xmlReader->name() == XML_MOVIE_COLLECTION_TOP_ELEMENT))
	{
		delete m_xmlReader;
		file.close();
		return;
	}

	while(!m_xmlReader->atEnd())
	{
		MovieInfo mi;
		while(m_xmlReader->readNextStartElement())
		{
			if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_NAME)
			{
				mi.setName(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_YEAR)
			{
				mi.setYear(m_xmlReader->readElementText().toInt());
			}
			else if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_RATING)
			{
				mi.setRating(m_xmlReader->readElementText().toInt());
			}
			else if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_TAG)
			{
				mi.addTag(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_GENRE)
			{
				mi.addGenre(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_IMDB)
			{
				mi.setIMDBLink(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == XML_MOVIE_COLLECTION_MOVIE_LASTWATCHED)
			{
				mi.setLastWatchedDate(QDate::fromString(m_xmlReader->readElementText()));
			}
		}
		if(!mi.getName().isEmpty())
			m_movies.append(mi);
	}

	delete m_xmlReader;
	file.close();
}

void MovieCollection::writeToFile()
{
	QFile file(m_xmlFilePath);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return;

	m_xmlWriter = new QXmlStreamWriter(&file);

	m_xmlWriter->setAutoFormatting(true);
	m_xmlWriter->writeStartDocument();
	m_xmlWriter->writeStartElement(XML_MOVIE_COLLECTION_TOP_ELEMENT);

	foreach(MovieInfo mi, m_movies)
	{
		m_xmlWriter->writeStartElement(XML_MOVIE_COLLECTION_MOVIE_ELEMENT);
		m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_NAME, mi.getName());
		m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_YEAR, QString::number(mi.getYear()));
		m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_RATING, QString::number(mi.getRating()));
		QStringList sl = mi.getTags();
		foreach(QString tag, sl)
		{
			m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_TAG, tag);
		}
		sl = mi.getGenres();
		foreach(QString genre, sl)
		{
			m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_GENRE, genre);
		}
		m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_IMDB, mi.getIMDBLink());
		m_xmlWriter->writeTextElement(XML_MOVIE_COLLECTION_MOVIE_LASTWATCHED, mi.getLastWatchedDate().toString());
		m_xmlWriter->writeEndElement();
	}

	m_xmlWriter->writeEndElement();
	m_xmlWriter->writeEndDocument();
	delete m_xmlWriter;


	file.close();
}
