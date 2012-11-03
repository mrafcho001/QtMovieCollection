#ifndef MOVIEINFO_H
#define MOVIEINFO_H
#include <QString>
#include <QDate>
#include <QStringList>


class MovieInfo
{
public:
	MovieInfo();

	QString getName();
	int getYear();
	int getRating();
	QStringList getTags();
	QStringList getGenres();
	QString getIMDBLink();
	QDate getLastWatchedDate();

	void setName(QString name);
	void setYear(int year);
	void setRating(int rating);
	void setIMDBLink(QString imdbLink);
	void setLastWatchedDate(QDate date);

	void addTag(QString tag);
	void addGenre(QString genre);

	bool removeTag(QString tag);
    bool removeTag(int index);
    void clearTags();

	bool removeGenre(QString genre);
    bool removeGenre(int index);
    void clearGenres();

private:
	QString m_name;
	int m_year;
	int m_rating;
	QStringList m_tags;
	QStringList m_genres;
	QString m_imdbLink;
	QDate m_lastWatched;
};

#endif // MOVIEINFO_H
