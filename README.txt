Description:

In this program I created a simple data exploring program that can load the information from several data 
files and provide us with a simple interface to retrieve information from these files.

Here we have three tab separated data files that have informations about movies, actors/actresses, and cast:
1) movie.titles.tsv - This file has information about the movies. 
2) movie.names.tsv - This file has information about actors/actresses.  
3) movie.principals.tsv - This file contains the information that shows which actor/actress plays a role in which movie

The main program has two functionalities 
1) searching for movies and printing the casting member associated with a selected movie 
2) searching for actor/actress and printing the associated movies for them.

The first option of the menu is to search for movies. The user will be prompted to enter the search phrases
(separated by ‘+’). The problem returns the records of all movies whose titles match all the search phrases. 
For each movie the program shows the index of the returned results, primaryTitle, and startYear. 

After showing the matched records, the user is prompted to select one record to see its cast members. The 
program shows their primaryName and their character.

The second menu option searches for actors/actresses. Similarly the user is prompted to enter the search 
phrases, and the program returns the list of cast members whose primaryName match the search phrases.
Then the user is prompted to select a record and the program shows all movies that the selected entity has
appeared on. The program shows the primaryTitle, startYear, and character.

If the search phrases do not match any result the program returns “No match found!”: 