/* Project Checklist
   Read File[x]
   Parse Properly[x]
	 Make Storage[x]
	 Count Total Words[x]
   Count Unique Words[x]
	 EOF Inputting [x]
   Wildcard Interpretation[x]

	 Completed!
	*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

void wordExists (string word, vector<string>& wordList, vector<int>& wordCounts)
{
	for (unsigned int i = 0; i < wordList.size(); i++){

		if (wordList.size() == 0){ //empty
			wordList.push_back(word);
			wordCounts.push_back(1);
			return;
		}

		if (wordList.at(i) == word){ //exists
			wordCounts.at(i)++;
			return;
		}
	}
wordList.push_back(word);
wordCounts.push_back(1);
return;
}


bool questionMarkSolver(string searchWord, string savedWord)
{
	if (searchWord == savedWord){ return true;} // 1

	if (savedWord.empty() && isalpha(searchWord.at(0))) {return false;} //2

	if (searchWord.size() < savedWord.size()) {return false;} //3

	if (savedWord.empty() && searchWord.at(0) == '?'){
		return questionMarkSolver(searchWord.substr(1), savedWord);  //4
}

	if (searchWord.at(0) == savedWord.at(0)){ //5
			 return questionMarkSolver(searchWord.substr(1), savedWord.substr(1));
}

	if (searchWord.at(0) == '?'){ //6

		if (questionMarkSolver (searchWord.substr(1), savedWord.substr(1)) == false){
				 return questionMarkSolver(searchWord.substr(1), savedWord);
			}
		else{return true;}
}
		return false;

}//end of function


int main(int argc, char const *argv[]) {

  ifstream infile;
  infile.open(argv[1]);
  string line;
	vector<string> wordList;
	vector<int> wordCounts;

  while( getline (infile, line)){ //the ammo, preparing the bullets
    for (unsigned int i = 0; i < line.size(); ++i){
      if (isalpha(line.at(i))){
        line.at(i) = tolower(line.at(i));
      }
      if (ispunct(line.at(i)) || isdigit(line.at(i)) || isspace(line.at(i))){
        line.at(i) = ' ';
    }
  }

	istringstream inSS; //input string sstream
  inSS.clear();
  inSS.str(line);
  string valid; //holder for individual words
		while (inSS >> valid){ //the gun, holding the bullets, shoots them into vector
				wordExists (valid, wordList, wordCounts);
		}
  } //end of processing

	int uniqueWordCount = wordCounts.size();
	int totalWords = 0;

	for (unsigned int i = 0; i < wordCounts.size(); i++){
			totalWords = totalWords + wordCounts.at(i);
		}

		cout << "The number of words found in the file was " << totalWords << endl;
		cout << "The number of distinct words found in the file was " << uniqueWordCount << endl;
		cout << endl;

		string searchWord;

		cout << "Please enter a word: ";

		while (getline(cin, searchWord)){
			 for (unsigned int i = 0; i < wordList.size(); i++){ //goes through every word
					if (questionMarkSolver(searchWord, wordList.at(i)) == true){
						cout << "The word " << wordList.at(i) << " appears " << wordCounts.at(i) << " times in the document" << "\n" << endl;
					}
			 }
			 cout << "Please enter a word: ";
		 }// end of "until eof"

infile.close();

  return 0;
} //end of main
