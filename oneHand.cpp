#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Word {
public:
	int count;
	string word;
	
	Word(int count_in, const string &word_in) : count(count_in), word(word_in) {}
};

char SubChar(char convert, string dest = "?") {
	string s, d;
	if(dest == "?") {
		//Matches by equating left and right hand
		//d = "asdfgqwertzxcvb";
		//s = ";lkjhpoiuy/.,mn";
		
		//Matches based on keyboard column
		//s = "qwertyuiopasdfghjkl;";
		//d = "zxcvbnm,./";
		
		//General full alphabet substitution case
		//s = "abcdefghijklmnopqrstuvwxyz;',./";
		//d = "abcdcdba";
	} else {
		s = "abcdefghijklmnopqrstuvwxyz;',./";
		d = dest;
	}
	
	for(unsigned int i = 0; i < s.length(); i++) {
		if(s[i] == convert) return d[i % d.length()];
	}
	return convert;
}

string SubString(string convert, string dest = "?") {
	for(unsigned int i = 0; i < convert.length(); i++) {
		convert[i] = SubChar(convert[i], dest);
	}
	return convert;
}

void RunMode(vector<Word> &words, string dest = "?") {
	string input = " ";
	getline(cin, input);
	
	while(!input.empty()) {
		input = SubString(input, dest);
		
		for(unsigned int i = 0; i < words.size(); i++) {
			Word& wordi = words[i];
			if(SubString(wordi.word, dest) == input) {
				cout << wordi.word << ":" << wordi.count << endl;
				break;
			}
		}
		getline(cin, input);
	}
}

float SubEval(vector<Word> words, string dest, float depth = 1) {
	unsigned long int score = 0;
	unsigned long int total = 0;
	if(depth > 1) depth = 1;
	//cout << "converting..." << endl;
	for(unsigned int i = 0; i < words.size(); i++) {
		words[i].word = SubString(words[i].word, dest);
	}
	//cout << "Evaluating..." << endl;
	for(unsigned int i = 0; i < words.size()*depth; i++) {
		unsigned int j;
		for(j = 0; words[j].word != words[i].word; j++);
		if(j != i) {
			score += words[i].count;
		}
		total += words[i].count;
	}
	return float(total-score)/total;
}

void Optimize(vector<Word> &words, int bucket_count) {
	srand(time(NULL));
	string first = "abcdefghijklmnopqrstuvwxyz";
	string buckets = "abcdefghijklmnopqrstuvwxyz";
	buckets.resize(bucket_count);
	for(unsigned int i = 0; i < first.length(); i++) {
		first[i] = buckets[rand() % bucket_count];
	}
	float depth = 0.000025;
	
	string second = first;
	cout << "Testing " << first;
	float firstscore = SubEval(words, first, depth);
	cout << " : " << firstscore << endl;
	int iter = 1;
	while(1) {
		for(unsigned int i = 0; i < first.length(); i++) {
			if(rand() % (iter/8+2) == 0) {
				second[i] = buckets[rand() % bucket_count];
			} else {
				second[i] = first[i];
			}
		}
		cout << "Testing " << second;
		float secondscore = SubEval(words, second, depth);
		cout << " : " << secondscore << endl;
		
		if(secondscore > firstscore) {
			firstscore = secondscore;
			first = second;
			cout << second << " won." << endl << endl;
		} else {
			if(abs(secondscore - firstscore) < .0000000001 && first != second) {
				depth = depth*2;
				cout << "Depth: " << depth << endl;
				cout << "Testing " << first;
				firstscore = SubEval(words, first, depth);
				cout << " : " << firstscore << endl;
			}
			second = first;
		}
		
		iter++;
	}
}

int main() {
	ifstream wordList("unigramsSorted.txt");
	vector<Word> words;
	string name;
	int count;
	wordList >> name;
	wordList >> count;
	while(!wordList.eof()) {
		words.push_back(Word(count, name));
		wordList >> name;
		wordList >> count;
	}
	wordList.close();
	
	//RunMode(words, "cegagagaagcfdcfddebhdbdbfd"); //A decent 8 character sub
	//RunMode(words, "dbcbcceeaaaacbebeedabcdcae"); //A decent 5 character sub
	//RunMode(words, "bbabaaaaabbbbabbbbbaaabaab"); //A two character sub
	//Optimize(words, 2);
	
	//								abcdefghijklmnopqrstuvwxyz;',./
	//RunMode(words, "azzaqaaaqaaazzqqqqaqqzqzqzaazzz"); //row buckets
	//RunMode(words, "lllllllrrrrrrrrrllllrlllrlrrrrr"); //Left Right buckets
	//RunMode(words, "agdddfghkjkljhl;afsgjfssha;'kl;"); //columns
	RunMode(words, "abcdefggefdsvbwqqrstrvwxtzaacxz"); //mirror
	
	return 0;
}
