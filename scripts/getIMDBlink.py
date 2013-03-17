#!/usr/bin/python
from xml.dom import minidom
import sys
import re
import urllib


verbose = 0

def getItems(node):
	movies = list()
	for entity in node.getElementsByTagName('ImdbEntity'):
		item = entity.attributes['id'].value, entity.childNodes[0].data
		for s in entity.childNodes[1].childNodes:
			if (s.nodeType == s.TEXT_NODE):
				myear = re.findall('[0-9]{4}', s.data)
				if(len(myear) >= 1):
					item = entity.attributes['id'].value, entity.childNodes[0].data, myear[0]
					break;
				else:
					item = entity.attributes['id'].value, entity.childNodes[0].data, -1

		movies.append(item)

	return movies

def getMatchList(movieTitle, year):
	url = "http://www.imdb.com/xml/find?xml=1&nr=1&tt=on&" + urllib.urlencode({'q': movieTitle})
	content = getUrl(url)

	moviesPop = list()
	moviesExact = list()

	xmldoc = minidom.parseString(content)
	for node in xmldoc.getElementsByTagName('ResultSet'):
		if (node.attributes['type'].value == "title_popular"):
			moviesPop = moviesPop + getItems(node)
		elif (node.attributes['type'].value == "title_exact"):
			moviesExact = moviesExact + getItems(node)

	if not moviesPop and not moviesExact:
		return list()

#Find Exact Match Movie first...
	for item in moviesExact:
		if(item[2] == year):
			if(verbose == 1):
				print "Chosen: ", item[0], ":", item[1], "-", item[2]
			return item

#Find Popular Match Movie next...
	for item in moviesPop:
		if(item[2] == year):
			if(verbose == 1):
				print "Chosen: ", item[0], ":", item[1], "-", item[2]
			return item

#Default to first Popular Movie...
	if(verbose == 1):
		print "Defaulted: ", item[0], ":", item[1], "-", item[2]
	return moviesPop[0]


def main():
	if(len(sys.argv) < 2):
		printHelp()

	args = []
	for arg in sys.argv[1:]:
		if(arg == '-v'):
			verbose = 1
		else:
			args.append(arg)

	matched = []
	if(len(args) == 2):
		matched = getMatchList(args[0], args[1])
	elif(len(args) == 1):
		matched = getMatchList(args[0], -1)
	else:
		printHelp()

	if(len(matched) > 0):
		printMatch(matched)
	else:
		print "No Match"

def printHelp():
	print "Usage:", sys.argv[0], " [Movie Name] [Year] [-v]"
	print "\t-v\tPrints extra information (verbose)"
	exit()

def getMatchedUrl(matched):
	return "http://www.imdb.com/title/" + matched[0] + "/"

def printMatch(matched):
	print "http://www.imdb.com/title/" + matched[0] + "/"


def getUrl(url):
	"Retrieve content of url"
	import pycurl
	from StringIO import StringIO
	storage = StringIO()
	c = pycurl.Curl()
	c.setopt(c.URL, url)
	c.setopt(c.WRITEFUNCTION, storage.write)
	c.perform()
	c.close()
	return storage.getvalue()

if __name__ == "__main__":
	main()
