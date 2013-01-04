#!/usr/bin/python
from xml.dom import minidom
import sys
import re

def main():
	if(len(sys.argv) < 2):
		print "Usage:", sys.argv[0], " [Movie Name] [Year] [-v]"
		print "\t-v\tPrints extra information (verbose)"
		exit()

	verbose = 0
	for arg in sys.argv:
		if(arg == '-v'):
			verbose = 1

	url = "http://www.imdb.com/xml/find?xml=1&nr=1&tt=on&q=" + sys.argv[1].replace(' ', '%20')
	content = getUrl(url)
	movies = list()

	xmldoc = minidom.parseString(content)
	for node in xmldoc.getElementsByTagName('ResultSet'):
		if (node.attributes['type'].value == "title_popular"):
			for entity in node.getElementsByTagName('ImdbEntity'):
				item = entity.attributes['id'].value, entity.childNodes[0].data
				
				for s in entity.childNodes[1].childNodes:
					if (s.nodeType == s.TEXT_NODE):
						year = re.findall('[0-9]{4}', s.data)
						if(len(year) >= 1):
							item = entity.attributes['id'].value, entity.childNodes[0].data, year[0]
						else:
							item = entity.attributes['id'].value, entity.childNodes[0].data, 0

				movies.append(item)

	foundMatch = 0
	for item in movies:
		if(item[2] == sys.argv[2]):
			if(verbose == 1):
				print "Chosen: ", item[0], ":", item[1], "-", item[2]
			printMatch(item)
			foundMatch = 1

	if(foundMatch == 0):
		item = movies[0]
		if(verbose == 1):
			print "Defaulted: ", item[0], ":", item[1], "-", item[2]
		printMatch(item)

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


main()
