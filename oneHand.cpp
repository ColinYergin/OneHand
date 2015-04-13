#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char LeftChar(char convert) {
	//Matches by equating left and right hand
	string d = "asdfgqwertzxcvb";
	string s = ";lkjhpoiuy/.,mn";
	
	//Matches based on keyboard column
	//string s = "qwertyuiopasdfghjkl;";
	//string d = "zxcvbnm,./";
	
	for(unsigned int i = 0; i < s.length(); i++) {
		if(s[i] == convert) return d[i % d.length()];
	}
	return convert;
}

string Lefty(string convert) {
	for(unsigned int i = 0; i < convert.length(); i++) {
		convert[i] = LeftChar(convert[i]);
	}
	return convert;
}

int main() {
	ifstream words("unigramsSorted.txt");
	string input;
	cin >> input;
	
	input = Lefty(input);
	
	int found = 0;
	string w;
	words >> w;
	while(found < 3 && !words.eof()) {
		if(Lefty(w) == input) {
			found++;
			cout << w << ":";
			int val = 0;
			words >> val;
			cout << val << endl;
			words >> w;
		} else {
			words >> w;
			words >> w;
		}
	}
	
	return 0;
}
