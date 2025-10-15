#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void hangman();
void numberguess();

void header()
{
    cout << "\n===================================================================================================================================================\n";
    cout << "                                                   R A I M A 2 5   M I N I G A M E S\n";
    cout << "===================================================================================================================================================\n\n";
}

int main()
{
    header();
    cout << endl << endl;

    int game = 1;
    while (game == 1)
    {
        cout << "Press 1 to play Hangman or 2 to play Guess the number" << endl;

        int choice; 
        cin >> choice;
        while (choice != 1 && choice != 2)
        {
            cout << "Invalid choice. Either enter 1 or 2" << endl;
            cin >> choice;
        }
        if (choice == 1)
        {
            hangman();
        }
        else if (choice == 2)
        {
            numberguess();
        }
        cout << endl << endl << endl << "Game Over.\nPress 1 to play again or any other key to quit the program" << endl;
        cin >> game;

        system("cls");
    }
    return 0;
}

// ================= HANGMAN SECTION =================

string randomcountry(int countryindex);
void welcome();		
void credits();
int letters(string word);
void check(string word, char guess, int occur[]);
void correct(int[], char, string&, const string&);
int getRandomIndex();

const int maxchar = 26;  
char guessed[maxchar] = {'\0'};
int guessCount = 0;
int attempts = 8;

string countries[30] = {
    "greenland", "canada", "mexico", "china", "india", "australia", "japan", "norway", "colombia",
    "argentina", "france", "germany", "italy", "spain", "england", "brazil", "russia",
    "egypt", "palestine", "qatar", "iran", "turkey", "pakistan",
    "belgium", "sweden", "greece", "switzerland", "portugal", "nepal", "ireland",
};

int getRandomIndex()
{
    srand(time(0));
    return rand() % 30;
}

void hangman()
{
    int countryindex = getRandomIndex();         
    string country = randomcountry(countryindex);

    int occur[3] = {0};
    char x; 
    string guessedword;

    welcome();
    credits();

    cin.ignore();  // clear newline before enter
    cout << "Press enter to begin" << endl << endl;
    cin.get();

    int length = letters(country);
    guessedword = string(length, '_');

    cout << "The computer has selected a random country." << endl
         << "The country has " << length << " letters." << endl << endl
         << "You have 8 tries." << endl;

    while (attempts != 0 && guessedword != country)
    {
        cout << endl << "Make your guess" << endl;
        cin >> x;
        x = tolower(x);

        bool alreadyGuessed = false;
        for (int i = 0; i < guessCount; ++i)
        {
            if (guessed[i] == x)
            {
                alreadyGuessed = true;
                break;
            }
        }

        if (alreadyGuessed)
        {
            cout << "You've already guessed '" << x << "'. Try a different letter." << endl;
            continue;
        }

        guessed[guessCount] = x;
        ++guessCount;

        system("cls");
        welcome();

        check(country, x, occur);
        correct(occur, x, guessedword, country);

        cout << guessedword;
    }

    if (attempts == 0)
    {
        cout << endl << "Oh no. You're out of attempts." << endl;
        cout << endl << "It was " << country;
    }
    else if (guessedword == country)
    {
        cout << endl << "🎉 Congratulations! You guessed the country correctly." << endl;
        cout << endl << "It was " << country;
    }

    // Reset for next round
    attempts = 8;
    guessCount = 0;
    fill(begin(guessed), end(guessed), '\0');
}

string randomcountry(int countryindex)
{
    return countries[countryindex];
}

int letters(string word)
{
    return word.length();
}

void check(string word, char y, int occur[])
{
    int count = 0;
    bool occurance = false;

    for (int i = 0; i < 3; ++i)
        occur[i] = 0;

    for (int i = 0; i < (int)word.length(); i++)
    {
        if (word[i] == y)
        {
            occur[count] = i;
            ++count;
            occurance = true;
        }
    }

    if (!occurance)
        occur[0] = 16; // special marker for incorrect
}

// stages
void stage1(); void stage2(); void stage3(); void stage4();
void stage5(); void stage6(); void stage7(); void stage8();

void correct(int guessedIndices[], char a, string& guessedword, const string& country)
{
    int currentIndex = 0;

    if (guessedIndices[0] == 16)
    {
        attempts--;
        cout << "Invalid choice. Attempts Left : " << attempts << endl;

        switch (attempts)
        {
            case 7: stage1(); break;
            case 6: stage2(); break;
            case 5: stage3(); break;
            case 4: stage4(); break;
            case 3: stage5(); break;
            case 2: stage6(); break;
            case 1: stage7(); break;
            case 0: stage8(); break;
        }
    }
    else
    {
        cout << endl << "Correct Choice (Hint: The country has " << letters(country) << " letters)" << endl;
    }

    for (int i = 0; i < (int)country.length(); ++i)
    {
        if (currentIndex < 3 && i == guessedIndices[currentIndex])
        {
            guessedword[i] = a;
            ++currentIndex;
        }
    }

    cout << endl;
}

void welcome() 
{
    cout << "  _    _                                          \n";
    cout << " | |  | |                                         \n";
    cout << " | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __  \n";
    cout << " |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n";
    cout << " | |  | | (_| | | | | (_| | | | | | | (_| | | | |\n";
    cout << " |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n";
    cout << "                     __/ |                         \n";
    cout << "                    |___/                          \n";
}

void credits()
{
    cout << "\n=================================================\n";
    cout << "               C R E D I T S\n";
    cout << "=================================================\n\n";
    cout << "           Raima Komal 2025251\n\n\n";
}

// stages
void stage1(){cout<<"  +---+ \n  |   | \n  O   | \n      | \n      | \n      | \n ========= \n";}
void stage2(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n      | \n      | \n ========= \n";}
void stage3(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n /    | \n      | \n ========= \n";}
void stage4(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n /|   | \n      | \n ========= \n";}
void stage5(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n /|\\  | \n      | \n ========= \n";}
void stage6(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n /|\\  | \n  |   | \n ========= \n";}
void stage7(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n /|\\  | \n  |   | \n /    | \n ========= \n";}
void stage8(){cout<<"  +---+ \n  |   | \n  O   | \n  |   | \n /|\\  | \n  |   | \n / \\  | \n ========= \n";}

// ================= NUMBER GUESS SECTION =================

void numberguess()
{
    srand(time(0));
    int x = rand() % 1000 + 1;

    cout << "The computer has generated a random number (from 1 to 1000)." << endl;
    cout << "Please try to guess it. Don't worry you will get all the help you need." << endl;

    int guess;
    cout << "Please make your guess (From 1 to 1000)" << endl;
    cin >> guess;

    while (guess < 1 || guess > 1000)
    {
        cout << "Invalid choice. The number should be between 1 and 1000. Please try again." << endl;
        cin >> guess;
    }

    while (guess != x)
    {
        if (guess > x)
            cout << "Try lower" << endl;
        else
            cout << "Try higher" << endl;
        cin >> guess;
    }

    cout << "🎉 Yayyyy you were right!" << endl;
}