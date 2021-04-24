#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;
vector<string>v;
string display_hangman(int tries)
{
	string HANGMAN_PICS[] = { "+---+\n    |\n    |\n    |\n===","+---+\nO   |\n    |\n    |\n===",
	"+---+\nO   |\n|   |\n    |\n==="," +---+\n O   |\n/|   |\n     | \n ===" ,
	" +---+\n O   |\n/|\\  |\n     | \n ==="," +---+\n O   |\n/|\\  |\n/    | \n ===",
	" +---+\n O   |\n/|\\  |\n/ \\  | \n ==="
	};
	return HANGMAN_PICS[tries];
}
string get_random_word()
{ 
	  srand(time(NULL));
	  vector<string> words;
	  ifstream file("E:/FCICB/Level 1/python/projects/words.txt");
	  string line;
	  while (getline(file, line)) words.push_back(line);

	  string s =words[rand() % words.size()] ;
	  return s;
}
void blank_letters() {
	string word = get_random_word();
	string complete_word = word, letters = "", w = "";
	if (word.size() == 4)
	{
		w += word[0];
		w += '_';
		w += word[2];
		w += '_';
		letters += word[1];
		letters += word[3];
	}
	if (word.size() == 5)
	{
		w += word[0];
		w += '_';
		w += word[2];
		w += '_';
		w += word[4];
		letters += word[1];
		letters += word[3];
	}
	if (word.size() >= 6)
	{
		w += word[0];
		w += '_';
		w += '_';
		w += word[3];
		w += '_';
		for (int h = 5; h < word.size(); ++h)
			w += word[h];
		letters += word[1];
		letters += word[2];
		letters += word[4];
	}

	v.push_back(w);
	v.push_back(letters);
	v.push_back(complete_word);
}
string getGuess(string guess, string alreadyGuessed)
{
	string s = "abcdefghijklmnopqrstuvwxyz";
	if (guess.size() != 1) {
		cout << "Please enter a single letter.\n";
		return "-1";
	}
	else if (alreadyGuessed.find(guess[0]) < alreadyGuessed.length())
	{
		cout << "You have already guessed that letter. Choose again.\n";
		return "-1";
	}
	else if (s.find(guess) >= s.length())
	{
		cout << "Please enter a LETTER.\n";
		return "-1";
	}
	else return guess;
}
void play_game()
{
	cout << "Hangman Game!\nWelcome...\n============================\n";
	string alreadyGuessed = "";
	blank_letters();
	string blank_word = v[0], missedLetters = v[1], complete_word = v[2];
	string guessed = "-1", guess;
	int tries = 0;
	while ((guessed == "-1") && tries < 6)
	{
		cout << blank_word << endl << "Guess a letter: ";
		cin >> guess;
		while (getGuess(guess, alreadyGuessed) == "-1")
		{
			cout << blank_word << endl << "Guess a letter: ";
			cin >> guess;
			tries += 1;
		}
		string g = getGuess(guess, alreadyGuessed), str_string;
		if (missedLetters.find(g) < missedLetters.size())
		{
			alreadyGuessed += g;
			cout << "Nice one, " << guess << " is in the word!";
			for (int i = 0; i < complete_word.size(); ++i)
			{
				char x = guess[0];
				if (complete_word[i] != x)
					continue;
				else {
					blank_word.replace(i, 1, g);
					break;
				}
			}
		}
		else if (missedLetters.find(g) > missedLetters.size())
		{
			cout << "oops!! this letter is wrong...\n";
			tries += 1;
		}
		if (blank_word.find('_') >= blank_word.size())
		{
			guessed = "1";

		}
		cout << display_hangman(tries) << endl;
	}
	if (guessed != "-1")
	{
		cout << blank_word << endl << "Good Job, you guessed the word!";
	}
	else
	{
		cout << "I'm sorry, but you ran out of tries. The word was " << complete_word << ". Maybe next time!";
	}
}
int main()
{
	while (true)
	{
		play_game();
		char c;
		cout << "Play Again [Y/N] ";
		cin >> c;
		if (c != 'Y'&&c != 'y')
			break;
	}
}
