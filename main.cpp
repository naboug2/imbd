/**********************************************************
 IMBD
 System: VSCode on MacOS
 Author: Nuha Abougoash
 **********************************************************/

#include <iostream>   
#include <cctype>     
#include <vector>     
#include <sstream>   
#include <string> 
#include <fstream>  

using namespace std;

/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
	stringstream s_stream(line);
	while (s_stream.good()) {
		string item;
		getline(s_stream, item, delimiter);
		items.push_back(item);
	}
}
/********************************************* 1 - MOVIE TITLES *******************************************/

// This struct declares the  titleID, primaryTitle, startYear, & genres for the Title Record file
struct TitleRecord{
   string titleID;
   string primaryTitle;
   string startYear;
   string genres;
};

// This function will read in the lines from the  Title Record file into a vector 
void readTitleRecord(string fileName, vector<TitleRecord>& titleVector){
   vector<string>data; //declare vector to store all the data in
   ifstream titleFile;
   titleFile.open(fileName); //open file
   TitleRecord TR; //create an instance to call struct 
   //if the file is open getline
   if (titleFile.is_open()) {
      string temp; //declare temporary variable
      getline(titleFile, temp);
      //check that it is not the end of the file and get line
      while (!titleFile.eof()){ 
         getline(titleFile, temp);
         splitString(temp, '\t', data); //call splitString function to remove tab between columns
         //assign each struct element to its corresponding spot in the file
         if (data.size() == 9) {
            TR.titleID = data.at(0);
            TR.primaryTitle = data.at(2);
            TR.startYear = data.at(5);
            TR.genres = data.at(8);
            titleVector.push_back(TR); //add the desired columns from the struct into the vector
         }
         data.clear(); //clear data not being used
      }
      titleFile.close(); //close file
   }
   
}
/**************************************** 2 - MOVIE NAMES **************************************************/

// This struct holds the nameID, primaryName, birthYear, deathYear, and primaryProfession columns from the Name Record file
struct NameRecord{
   string nameID;
   string primaryName;
   string birthYear;
   string deathYear;
   string primaryProfession;
};

// This function will read in the lines from the Name Record file into a vector 
void readNameRecord(string fileName, vector<NameRecord>& nameVector){
   vector<string> data; //declare vector to store all the data in
   ifstream nameFile;
   NameRecord NR;
   nameFile.open(fileName); 
   //if the file is open getline
   if(nameFile.is_open()) {
      string temp; //declare temporary variable
      getline(nameFile, temp); //this getline reads file heading
      //check that it is not the end of the file and get line
      while(!nameFile.eof()) {   
         getline(nameFile, temp); //get each line in file
         splitString(temp,'\t', data); //call splitString function to remove tab in betwwen columns file
         //assign each struct element to its corresponding spot in the file
         if (data.size() == 6){
            NR.nameID = data.at(0);
            NR.primaryName= data.at(1);
            NR.birthYear = data.at(2);
            NR.deathYear = data.at(3);
            NR.primaryProfession = data.at(4);
            nameVector.push_back(NR); //add the desired columns from the struct into the vector
         }
         data.clear(); //clear any data not being used
      }
   }
   nameFile.close(); //close the file
}
/**************************************** 3 - MOVIE PRINCIPLES ************************************************/

// This struct holds the titleID, nameID, and character columns from the Principle Record file
struct PrincipalRecord {
   string titleID;
   string nameID;
   string character;
};

// This function will read in the lines from the Principal Record file into a vector 
void readPrincipalRecord(string fileName, vector<PrincipalRecord>& principalVector){
   vector<string> data; //declare vector that will be used to store the data in
   ifstream principalFile;
   principalFile.open(fileName);
   PrincipalRecord PR; 
   //check that the fiel is open
   if(principalFile.is_open()) {
      string temp; //declare temporary variable
      getline(principalFile, temp); //this get line will read header of file
      //read until we get to end of the file
      while(!principalFile.eof()) {  
         getline(principalFile, temp); //read each line in file
         splitString(temp,'\t', data); //call splitString function to remove tab between columns in file
         //assign each element in PR struct to corresponding location in file
         if (data.size() == 6){
            PR.titleID = data.at(0);
            PR.nameID= data.at(2);
            PR.character = data.at(5);
            principalVector.push_back(PR); //add all the data into vector
         } 
         data.clear(); //clear any data that was not used
      }
   }
   principalFile.close(); //close file
}
/**************************************** FIRST MENU OPTION ************************************************/

// The following function searches for movies. The user will be prompted to input search phrases.
// The function will return the records of all movies whose titles match the search phrases and prints the casting member associated with the selected movie
void Menu1(vector<TitleRecord> titleVector, vector<NameRecord> nameVector, vector<PrincipalRecord> principleVector, string input){
   cout << "---------------" << endl;
   vector<TitleRecord> storeTitle; //vector to store all title names that match the inputed phrases
   //for loop to change all letters to lowercase
   for (int i=0; i < input.size(); i++) {
      input[i] = tolower(input[i]);
   }
   vector<string> newVector; //vector to store data after split function is called on inputed phrases
   splitString(input, '+', newVector); // call splittring function to remove the '+' between search phrases
   int count = 0; //initialize counter
   //loop through each element in titelVector
   for (int i = 0; i < titleVector.size(); i++ ) {
      bool match = true; // set bool value to true for when phrases match
      string title;
      //for loop to go through each primaryTitle in titleVector
      for (int j = 0; j < titleVector[i].primaryTitle.size(); j++) {
         title += tolower(titleVector[i].primaryTitle[j]); //change primaryTitle to lower case and store into title vector 
      }
      //for loop to go through each element in newVector
      for (int k = 0; k < newVector.size(); k++) {
         if (title.find(newVector[k]) == -1) {
            match = false; 
            break; //break out of loop if no matches found
         }                                        
      }
      if(match) {
         storeTitle.push_back(titleVector[i]); //if match is found, append it to titleVector                                  
         count++; //increment count
         cout << count - 1 << ":" << endl;
         cout << "Title: " << titleVector[i].primaryTitle << endl;
         cout << "Year: " << titleVector[i].startYear << endl;
         //this loop will go through titleVector and search for any ',' and change them into ' ' at the corresponding index
         for (int l = 0; l < titleVector[i].genres.size(); l++) {
            if (titleVector[i].genres[l] == ',') {
               titleVector[i].genres[l] = ' ';
            }
         }
         cout << "Genre: " << titleVector[i].genres << endl;
         cout << "---------------" << endl;
      }
   }
   //if no matches were found in storTitle vector then print out "No match foudnd!"
   if (storeTitle.size() == 0) {
      cout << "No match found!" << endl; 
   }
   cout << "Select a movie to see its actor/actresses (-1 to go back to the previous menu): ";
   int movieNum;
   cin >> movieNum; // prompt user to enter movie number 
   //check if input succeeded
   if (cin.fail()){
      return;
   }
   //if user does not input -1
   if(movieNum != -1){
      string titleName = storeTitle[movieNum].titleID; //set variable equal to corresping index in storeTitle based off users input 
      //loop through prinicpleVector
      for(int i = 0; i < principleVector.size(); i++ ) {
         //if titleID match titleName
         if (principleVector[i].titleID == titleName) { 
            //loop through nameVector
            for (int j = 0; j < nameVector.size(); j++) {
               //check if nameID in nameVector matches nameID in principleVector
               if (nameVector[j].nameID == principleVector[i].nameID) {
                  cout << nameVector[j].primaryName << " " << principleVector[i].character << endl; 
               }
            }
         }
      }
      cout << "Enter search phrase (type done to go back to previous menu): ";
      cin >> input; //prompt user to enter search phrases
      //check if input succeded
      if(cin.fail()){
         return;
      }
      if (input == "done") {
         return;
      }
      else {
         Menu1(titleVector, nameVector, principleVector, input);  //resursivley call Menu1 
      }
   }
}
/**************************************** SECOND MENU OPTION ************************************************/

//The Menu2 function searches for actors/actresses. The user will be prompted to enter search phrases and teh proram will return a list of cast member who match the search
// Then user will be prompted to select a record and all the movies the chosen actor has played in will appear. 
void Menu2( vector<TitleRecord> titleVector, vector<NameRecord> nameVector, vector<PrincipalRecord> principalVector, string input) {
   vector<NameRecord> storeName; //vector to store all actor names that match the inputed phrases
   //for loop to change all letters to lowercase
   for(int i =0; i < input.size(); i++) {
      input[i] = tolower(input[i]);
   }
   vector<string> newVector; //vector to store data after split function is called on inputed phrases
   splitString(input, '+', newVector); // call splittring function to remove the '+' between search phrases
   int count;
   //loop through each element in nameVector
   for(int i = 0; i < nameVector.size(); i++) {
      bool match = true;  // set bool value to true for when phrases match
      string name; 
      //loop through primaryName in nameVector
      for (int j = 0; j < nameVector[i].primaryName.size(); j++) {
         name += tolower(nameVector[i].primaryName[j]); //store in naemVector after chnage primaryName into lowercase
      }
      //loop through each element in newVector to check if it matches the inputes phrase
      for(int k = 0; k < newVector.size(); k++) {
         //if name is found at corresponding index in newVector
         if (name.find(newVector[k]) == -1) { 
            match = false; //set match to false
            break; //break out of loop
         }
      }
      if (match) {
         storeName.push_back(nameVector[i]); //if match is found, append it to nameVector 
         count++; //increment counter
         cout << count - 1 << ":" << endl;
         cout << nameVector[i].primaryName << endl;
         cout << nameVector[i].primaryProfession << "," << endl;
         cout << "(" << nameVector[i].birthYear << "-" << nameVector[i].deathYear << ")" << endl;
         cout << "---------------" << endl;
      }
   }
   // If the search phrases do not match any result the program returns “No match found!”
   if( storeName.size() == 0) {
      cout << "No match found!" << endl;
   }
   cout << "Select a movie to see it actor/actress(-1 to go back to the previous menu): ";
   int movieNum;
   cin >> movieNum; //prompt user to input movie 
   //check if input succeeded
   if (cin.fail()) { 
        return ;
   }
   //if user does not input -1 
   if (movieNum != -1) {
      string movieName = storeName[movieNum].nameID; //set variable equal to corresping index in storeName based off users input
      //loop through each element in principalVector
      for (int i = 0; i < principalVector.size(); i++) {
         //if nameId in principalVector matches movieName
         if (principalVector[i].nameID == movieName) {
            //loop through each element in nameVector
            for (int j = 0; j < nameVector.size(); j++) {
               //if nameID in nameVector matches nameID in principle Vector 
               if (nameVector[j].nameID == principalVector[i].nameID) {
                  //loop through titleVector
                  for (int k = 0; k < titleVector.size(); k++) {
                     // if titleID in titleVector matches titleID in principleVector cout the following
                     if (titleVector[k].titleID == principalVector[i].titleID) {
                        cout << titleVector[k].primaryTitle << " " << titleVector[k].startYear << " " << principalVector[i].character << endl;
                     }
                  }
               }
            }
         }
      }
      cout << "Enter search phrase (type done to go back to previous menu): ";
      cin >> input;
      //check if input succeeded
      if(cin.fail()){
         return;
      }
      if (input == "done") {
         return;
      }
      else {
         Menu2(titleVector, nameVector, principalVector, input); //resursivley call Menu2
      }
   }
}

/**********************************************************************************************************/

int run(string titlesFile, string namesFile, string principalsFile) {
   string input;
   // declare all the required vectors
   vector<TitleRecord> titleVector;
   vector<NameRecord> nameVector;
   vector<PrincipalRecord> principleVector;
   //call all the functions to read in the tsv files
   readTitleRecord(titlesFile, titleVector);
   readNameRecord(namesFile, nameVector);
   readPrincipalRecord(principalsFile, principleVector);

   int menuNumber = 0; 
   //as long as input succeeded
   while (!cin.fail()) {
      cout << "Select a menu option:\n"
      << "1. Search for movies\n"
      << "2. Search for actors/actresses\n"
      << "3. Exit\n"
      << "Your choice -> ";
      cin >> menuNumber; //prompt user into iput menu number
      //check if input succeeded
      if (cin.fail()) {
         return 0;
      }
      //if user inputs 1
      if (menuNumber == 1) { 
         cout << "Enter search phrase: ";
         cin >> input; //prompt user to enter search phrase for movie
         Menu1(titleVector, nameVector, principleVector, input); //call Menu1 function
      }
      else if (menuNumber == 2) { 
         cout << "Enter search phrase: ";
         cin >> input; //prompt user to enter search phrase for actos/actresses
         Menu2(titleVector, nameVector, principleVector, input); //call Menu2 function
      }
      else { 
         exit(0); 
      }
   }
	return 0;	
}

int main() {
	string titlesFile =	"movie.titles.tsv";
	string namesFile = "movie.names.tsv";
	string principalsFile = "movie.principals.tsv";

	run(titlesFile, namesFile, principalsFile);
	return 0;
}
