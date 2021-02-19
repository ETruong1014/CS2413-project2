/*
 * project2.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: erictruong1014
 */


#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
			A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
			B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	int Size();
	char* getWord();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);
}

char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size () {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {

	int i = 0;
	while (B[i] != '\0') {
		i++;
	}
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j = 0; j < size; j++) {
		strArray[j] = B[j];
	}

	return *this;
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {

	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);

	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	bool same = true;
	int i = 0; //index of comparison

	if (size != B.size) {
		same = false;
	}
	else {
		while (i < size) {
			if (strArray[i] != B.strArray[i]) {
				same = false;
				break;
			}
		}
	}

	return same;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	// TODO
	bool less = true;
	int i = 0; //index of comparison

	while (i < size && i < B.size) {
		if (strArray[i] > B.strArray[i]) {
			less = false;
			break;
		}
	}
	if (less) { //check if a word starts with the same letters as the other word, but not the same length
		if (size >= B.size) {
			less = false;
		}
	}
	return less;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	bool greater = true;
	int i = 0; //index of comparison

	while (i < size && i < B.size) {
		if (strArray[i] < B.strArray[i]) {
			greater = false;
			break;
		}
	}
	if (greater) { //check if a word starts with the same letters as the other word, but not the same length
		if (size <= B.size) {
			greater = false;
		}
	}
	return greater;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);

	char c;
	int i = 0;
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) )
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
private:
	int binarySearchAndInsert (myString& wordToFind, int l, int r);
	myString* _words;
	int* _frequencies;
	int _size;

public:
	bagOfWords ();
	bagOfWords (int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void setSize(int i);

	void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortWords(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
	~bagOfWords();
};

// default constructor - initializes with no words
bagOfWords::bagOfWords()
{
	_size = 0;
	_words = new myString[0];
	_frequencies = new int[0];
}

// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords)
{
	_size = numOfWords;
	_words = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

myString* bagOfWords::get_Words()
{
	return _words;
}

int* bagOfWords::get_Freq()
{
	return _frequencies;
}

int bagOfWords::get_size()
{
	return _size;
}

void bagOfWords::setSize(int i)
{
	_size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display()
{

	// TODO
	cout << "Bag of Words: " << _size << endl;
	for (int i = 0; i < _size; i++) {
		cout << _words[i] << ": " << _frequencies[i] << endl;
	}
}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq()
{
	myString tempWord;
	int tempFreq;
	for (int i = 0; i < _size; i++) { //bubble sort
		for (int j = 0; j < _size - 1; j++) {
			if (_frequencies[j] == _frequencies[j+1]) { //if frequencies are equal, sort alphabetically
				tempWord = _words[j];
				_words[j] = _words[j+1];
				_words[j+1] = tempWord;
			}
			else if (_frequencies[j] > _frequencies[j+1]) {
				tempWord = _words[j];
				tempFreq = _frequencies[j];
				_words[j] = _words[j+1];
				_frequencies[j] = _frequencies[j+1];
				_words[j+1] = tempWord;
				_frequencies[j+1] = tempFreq;
			}
		}
	}
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords()
{
	myString tempWord;
	int tempFreq;
	for (int i = 0; i < _size; i++) { //bubble sort
		for (int j = 0; j < _size - 1; j++) {
			if (_words[j] > _words[j+1]) {
				tempWord = _words[j];
				tempFreq = _frequencies[j];
				_words[j] = _words[j+1];
				_frequencies[j] = _frequencies[j+1];
				_words[j+1] = tempWord;
				_frequencies[j+1] = tempFreq;
			}
		}
	}
}

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{

	// TODO
	bool found; //if stop word is found;
	bagOfWords* bagWithoutStop = new bagOfWords(_size - numStopWords);

	for (int i = 0; i < _size; i++) {
		found = false;
		for (int j = 0; j < numStopWords; j++) { //iterate through stopWords until the end or until a stop word is found
			if (_words[i] == stopWords[j]) {
				found = true;
				break;
			}
		}
		if (!found) {
			(*bagWithoutStop)._words[i] = _words[i];
			(*bagWithoutStop)._frequencies[i] = _frequencies[i];
		}
	}
	return bagWithoutStop;
}

// to search for a given word in _words - returns 0 if not found, 1 if found
int bagOfWords::binarySearchAndInsert (myString& wordToFind, int l, int r)
{

	if (r >= l) {
		int m = l + (r - l) / 2; //midpoint of array

		if (_words[m] == wordToFind) {
			return 1; //word found
		}
		else if (_words[m] > wordToFind) {
			return binarySearchAndInsert(wordToFind, l, m - 1);
		}
		else if (_words[m] < wordToFind) {
			return binarySearchAndInsert(wordToFind, m + 1, r);
		}
	}
	return 0; //word not found
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
	// TODO
	if (_size == 0) { //adding the first word
		delete [] _words; //delete empty array
		delete [] _frequencies; //delete empty array
		_size = 1;
		_words = new myString[1];
		_frequencies = new int[1];
		_words[0] = newWord;
		_frequencies[0] = 1;
	}
	else if (binarySearchAndInsert(newWord, 0, _size - 1) == 0) { //word not currently in the list
		_size++;
		myString* new_words = new myString[_size];
		int* new_frequencies = new int[_size];
		int insertIdx = 0;

		for (int i = 0; i < _size - 1; i++) { //find index to insert word alphabetically
			if (newWord < _words[i]) {
				break;
			}
			insertIdx++;
		}

		for (int i = 0; i < insertIdx; i++) { //copy values from _words and _frequencies until insertIdx
			new_words[i] = _words[i];
			new_frequencies[i] = _frequencies[i];
		}
		new_words[insertIdx] = newWord;
		new_frequencies[insertIdx] = 1;
		if (insertIdx != (_size - 1)) { //word was not inserted at end of list
			for (int i = insertIdx + 1; i < _size; i++) {
				new_words[i] = _words[i];
				new_frequencies[i] = _frequencies[i];
			}
		}

		delete [] _words;
		delete [] _frequencies;

		_words = new myString[_size];
		_frequencies = new int[_size];
		for (int i = 0; i < _size; i++) { //copying values to _words and _frequencies
			_words[i] = new_words[i];
			_frequencies[i] = new_frequencies[i];
		}

		delete [] new_words;
		delete [] new_frequencies;
	}
}

// destructor
bagOfWords::~bagOfWords() {
	if (_words != NULL) delete [] _words;
	if (_frequencies != NULL) delete [] _frequencies;
	_size = 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

	int numStopWords;
	char* token;
	myString* tokenString;

	//read the first number from the file that contains the number of stop words
	cin >> numStopWords;
	cout << "Number of Stop words: " << numStopWords << endl;
	myString* stopWordsList = new myString[numStopWords];

	//read the stop words
	for (int i=0; i < numStopWords; i++)
	{
		token = getNextToken ();
		stopWordsList[i] = token; //calls the overloaded = operator on myString class
	}

	//Now read a text and put them in the bagOfWords instance.
	bagOfWords* myBag = new bagOfWords ();

	token = getNextToken ();

	while (token != NULL)
	{
		tokenString = new myString (token); //create a myString object with the token
		(*myBag).addWord(*tokenString); //add token to myBag
		token = getNextToken ();
	}

	// this should display the token and frequency;
	// note that becuase you are using binary search and insert the tokens will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*myBag).display ();

	(*myBag).sortFreq ();
	cout << endl;
	cout << "myBag - Sorted based on frequency:" << endl;
	(*myBag).display ();

	(*myBag).sortWords();
	cout << endl;
	cout << "myBag - Sorted alphabetically:" << endl;
	(*myBag).display ();

	bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
	cout << endl;
	cout << "newBag - Sorted alphabetically:" << endl;
	(*newBag).display();

	(*newBag).sortFreq ();
	cout << endl;
	cout << "newBag - Sorted based on frequency:" << endl;
	(*newBag).display ();

	delete [] stopWordsList;
	delete myBag;
	delete newBag;
}
