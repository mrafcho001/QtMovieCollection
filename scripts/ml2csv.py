#!/usr/bin/python
import getIMDBlink
import sys
import re



def main():

	if(len(sys.argv) < 3):
		printHelp()
		exit()

	args = []
	for arg in sys.argv[1:]:
		if(arg == '-v'):
			verbose = 1
		else:
			args.append(arg)

	if(len(args) < 2):
		printHelp()
		exit()

	with open(args[0]) as f:
		movieList = f.readlines()

	outFile = open(args[1], 'w')
	errorFile = 0

	for movie in movieList:
		matchObj = re.match("(.*) \[([0-9]{4})\]", movie)
		if(matchObj):
			print "Processing \"" + matchObj.group(1) + " (" + matchObj.group(2) + ")" + "\"...",
			item = getIMDBlink.getMatchList(matchObj.group(1), matchObj.group(2))
			if item:
				outFile.write("\"" + matchObj.group(1) + "\",")
				outFile.write(str(item[2]) + ",")
				outFile.write("\"" + getIMDBlink.getMatchedUrl(item) + "\"\n") 
				print "Done"
				if(matchObj.group(1) != item[1]):
					print "\t[Name missmatch:", item[1], "]"
			else:
				if errorFile == 0:
					errorFile = open("error_" + args[1], 'w')
				errorFile.write(movie + "\n")
				print "Error!"

	outFile.close()
	if errorFile:
		errorFile.close()



def printHelp():
	print "Usage:", sys.argv[0], " [movie list File] [CSV file ouptut] [-v]\n"
	print "Description:\tThis program takes in a text file with a list of movies and outputs"
	print "\t\ta CSV file with the movie names, year, and acquired IMDB link.\n"
	print "In File Format:\tThe movie names followed by year in square brackets and possibly"
	print "\t\tother garbage after:"
	print "\t\t\tMovie Name [Year] Garbage"
	print "\t\tEx:"
	print "\t\t\tThe Avengers [2012] 1080p BluRay x264"
	print "Switches:"
	print "\t-v\tPrints extra information (verbose)"
	exit()



if __name__ == "__main__":
	main()