#include "collectionmanager.h"
#include <QFile>

CollectionManager::CollectionManager()
	: m_read(false), m_xmlReader(NULL), m_xmlWriter(NULL)
{
	m_xmlFileLocation = "/home/mrafcho001/.moviecollection/moviecollection.xml";
	readFromFile();
}

CollectionManager::~CollectionManager()
{
	writeToFile();
}

const MovieInfo& CollectionManager::getMovieInfo(const int index) const
{
	return m_movies[index];
}

MovieInfo& CollectionManager::getMovieInfo(const int index)
{
	return m_movies[index];
}

int CollectionManager::count() const
{
	return m_movies.count();
}

void CollectionManager::addMovie(const MovieInfo &mi)
{
	m_movies.append(mi);
}

void CollectionManager::removeMovie(const int index)
{
	m_movies.removeAt(index);
}

void CollectionManager::sync()
{
	writeToFile();
}

void CollectionManager::readFromFile()
{
	m_read = true;
	QFile file(m_xmlFileLocation);
	if(!file.open(QIODevice::ReadOnly))
		return;

	m_xmlReader = new QXmlStreamReader(&file);

	if(!(m_xmlReader->readNextStartElement() && m_xmlReader->name() == "movies"))
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
			if(m_xmlReader->name() == "name")
			{
				mi.setName(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == "year")
			{
				mi.setYear(m_xmlReader->readElementText().toInt());
			}
			else if(m_xmlReader->name() == "rating")
			{
				mi.setRating(m_xmlReader->readElementText().toInt());
			}
			else if(m_xmlReader->name() == "tag")
			{
				mi.addTag(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == "genre")
			{
				mi.addGenre(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == "imdblink")
			{
				mi.setIMDBLink(m_xmlReader->readElementText());
			}
			else if(m_xmlReader->name() == "lastwatched")
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

void CollectionManager::writeToFile()
{
	QFile file(m_xmlFileLocation);
	if(!file.open(QIODevice::WriteOnly))
		return;

	m_xmlWriter = new QXmlStreamWriter(&file);

	m_xmlWriter->setAutoFormatting(true);
	m_xmlWriter->writeStartDocument();
	m_xmlWriter->writeStartElement("movies");

	foreach(MovieInfo mi, m_movies)
	{
		m_xmlWriter->writeStartElement("movie");
		m_xmlWriter->writeTextElement("name", mi.getName());
		m_xmlWriter->writeTextElement("year", QString::number(mi.getYear()));
		m_xmlWriter->writeTextElement("rating", QString::number(mi.getRating()));
		QStringList sl = mi.getTags();
		foreach(QString tag, sl)
		{
			m_xmlWriter->writeTextElement("tag", tag);
		}
		sl = mi.getGenres();
		foreach(QString genre, sl)
		{
			m_xmlWriter->writeTextElement("genre", genre);
		}
		m_xmlWriter->writeTextElement("imdblink", mi.getIMDBLink());
		m_xmlWriter->writeTextElement("lastwatched", mi.getLastWatchedDate().toString());
		m_xmlWriter->writeEndElement();
	}

	m_xmlWriter->writeEndElement();
	m_xmlWriter->writeEndDocument();
	delete m_xmlWriter;


	file.close();
}
