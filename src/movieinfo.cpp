#include "movieinfo.h"

MovieInfo::MovieInfo() :
    m_name(""), m_year(1990), m_rating(0), m_lastWatched(QDate::currentDate())
{
}

QString MovieInfo::getName()
{
	return m_name;
}

int MovieInfo::getYear()
{
	return m_year;
}

int MovieInfo::getRating()
{
	return m_rating;
}

QStringList MovieInfo::getTags()
{
	return m_tags;
}

QStringList MovieInfo::getGenres()
{
	return m_genres;
}

QString MovieInfo::getIMDBLink()
{
	return m_imdbLink;
}

QDate MovieInfo::getLastWatchedDate()
{
    return m_lastWatched;
}

QString MovieInfo::getQuality()
{
    return quality;
}

void MovieInfo::setName(QString name)
{
	m_name = name;
}

void MovieInfo::setYear(int year)
{
	m_year = year;
}

void MovieInfo::setRating(int rating)
{
	m_rating = rating;
}

void MovieInfo::setIMDBLink(QString imdbLink)
{
	m_imdbLink = imdbLink;
}

void MovieInfo::setLastWatchedDate(QDate date)
{
    m_lastWatched = date;
}

void MovieInfo::setQuality(QString quality)
{
    this->quality = quality;
}

void MovieInfo::addTag(QString tag)
{
	m_tags.append(tag);
}

void MovieInfo::addGenre(QString genre)
{
	m_genres.append(genre);
}

bool MovieInfo::removeTag(QString tag)
{
	if(m_tags.contains(tag, Qt::CaseInsensitive))
	{
		m_tags.removeAll(tag);
		return true;
	}
	else
		return false;
}

bool MovieInfo::removeTag(int index)
{
	if(index >= m_tags.count())
		return false;

	m_tags.removeAt(index);
    return true;
}

void MovieInfo::clearTags()
{
    m_tags.clear();
}

bool MovieInfo::removeGenre(QString genre)
{
	if(m_genres.contains(genre, Qt::CaseInsensitive))
	{
		m_genres.removeAll(genre);
		return true;
	}
	else
		return false;
}

bool MovieInfo::removeGenre(int index)
{
	if(index >= m_genres.count())
		return false;

	m_genres.removeAt(index);
    return true;
}

void MovieInfo::clearGenres()
{
    m_genres.clear();
}
