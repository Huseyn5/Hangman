#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>       
using namespace std;

class LoadfromFile
{
    string name;
    vector<string> listofwords;
public:
    LoadfromFile(string name = "Words.txt") : name(name)
    {
        ifstream file;
        file.open(name);
        if (!file.is_open()) cout << "cant open a fiile\n";
        else
        {
            string str;
            while (file >> str)
            {
                listofwords.push_back(str);
            }
        }
    }
    void setname(string newname)
    {
        this->name = newname;
    }
    vector<string> getlist() { return listofwords; }
};
class Game 
{
private:
    vector <string> listofwords; 
    const int chances = 6;
    int fails = 0;
    //LoadfromFile* f;
    string word;                   
    vector <char> usedletters = {};

    bool wasentered(const char letter)
    {
        return (std::find(usedletters.begin(), usedletters.end(), letter) < usedletters.end()); 
    }

    void setword() { word = listofwords[rand() % listofwords.size()]; }

    void show()
    {
        system("cls");

        cout << "Welcome to the game << HANGMAN >>!\n"
        << "Yous should guess the word by entering letters.\n"
        << "You have " << chances - fails << " chances to make an error.\n\n";
        switch (fails)
        {
        case 1:
            cout << "\n\n\n\n\n\n\n\n\n\n\n $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n $                          $\n";
            break;
        case 2:
            cout << "        $$$$$$$$$$$$$$$\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n";
            break;
        case 3:
            cout << "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n";
            break;
        case 4:
            cout << "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n";
            break;
        case 5:
            cout << "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "      /   \\           $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n";
            break;
        case 6:
            cout << "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "      / | \\           $\n"
                "        |             $\n"
                "                      $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n";
            break;
        case 7:
            cout << "        $$$$$$$$$$$$$$$\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        |             $\n"
                "        O             $\n"
                "      / | \\           $\n"
                "        |             $\n"
                "       / \\            $\n"
                "                      $\n"
                "                      $\n"
                " $$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                " $                          $\n";
            break;
        default:
            break;
        }
        cout << "\n\nCurrent word: ";
        for (const auto& letter : word)
        {
            if (wasentered(letter))
            {
                cout << letter << ' ';
            }
            else
            {
                cout << "_ ";
            }
        }
        cout << endl;
    }
    char enterletter()
    {
        cout << "Enter letter: ";
        string input{ "" };
        std::getline(cin, input);
        char letter = tolower(input[0]);
        while (wasentered(letter) || (input.length() > 1))
        {
            if (input.length() > 1)
            {
                cin.clear();
            }
            cout << "Repeat input: ";
            std::getline(cin, input);
            letter = input[0];
        }
        usedletters.push_back(letter);
        return letter;
    }
    bool win()
    {
        for (const auto& wordletters : word)
        {
            if (!wasentered(wordletters))
            {
                return false;
            }
        }
        return true;
    }
    void newturn()
    {
        show();                                
        char letter = enterletter();           
        bool rightLetter = false;
        for (const auto& wordletters : word)
        {
            if ((letter == wordletters) || (tolower(letter) == wordletters))
            {
                rightLetter = true;
                break;
            }
        }
        if (rightLetter)
        {
            cout << "Congratulations, You found the letter!\n";
        }
        else
        { 
            cout << "This letter does not exist in the letter! ";
            fails++;
            show();
        }
    }
public:
    Game(const string wordToGuess = "", unsigned int maxFails = 6, string filename = "Words.txt") : chances(maxFails)
    {  
        LoadfromFile f(filename);
        listofwords = f.getlist();
        if (wordToGuess == "") { setword(); }
        else { word = wordToGuess; }
    }
    void Start()
    {
        char repeat; 
        do
        {
            time_t now1 = time(0);
            tm* ltm = localtime(&now1);
            int hour1 = 1 + ltm->tm_hour;
            int min1 = 1 + ltm->tm_min;
            int sec1 = 1 + ltm->tm_sec;
            if (word == "") { setword(); }
            while (!win() && (fails <= chances))
            {
                newturn();
            }
            time_t now2 = time(0);
            tm* ltm2 = localtime(&now2);
            int hour2 = 1 + ltm2->tm_hour;
            int min2 = 1 + ltm2->tm_min;
            int sec2 = 1 + ltm2->tm_sec;
            hour2 -= hour1;
            if (min2 - min1 < 0) { hour2--, min2 += (60 - min1); }
            else { min2 -= min1; }
            if (sec2 - sec1 < 0) { min2--, sec2 += (60 - min1); }
            else { sec2 -= sec1; }
            cout << endl << "Time: " << hour2<< " hours\t";
            cout << min2 << " minutes\t";
            cout << sec2 << " seconds\t" << endl;

            if (win())
            {
                cout << "\nYou guessed the word << " << word << " >> and survived!\n\n" << endl;
            }
            else
            {
                cout << "You could not guess the word <<" << word << ">> and were hanged up!\n\n" << endl;
            }
            do
            {
                cout << "Do you want to repeat the game? ( y - Yes, n - No)\n"; cin >> repeat;
            } while (repeat != 'y' && repeat != 'n');
                fails = -1;
                cin.clear();
                usedletters.clear();
                word.clear();
            
        } while (repeat == 'y');

    }
};

int main()
{  
    srand((time(0)));
    Game Game{ };
    Game.Start();
}