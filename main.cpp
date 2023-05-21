#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>
#include <windows.h>
#include <vector> //leaderboards
#include <fstream> // for file input/output
#include <sstream> // for string stream

using namespace std;

// Start art screen
void start()
{
    cout << " _______  _______  ______   _______    ______   _     _   ______  _______  _______  ______    ______ " << endl
         << "(_______)(_______)(______) (_______)  (____  \\ (_)   (_) / _____)(_______)(_______)(_____ \\  / _____)" << endl
         << " _        _     _  _     _  _____      ____)  ) _     _ ( (____      _     _____    _____) )( (____  " << endl
         << "| |      | |   | || |   | ||  ___)    |  __  ( | |   | | \\____ \\    | |   |  ___)  |  __  /  \\____ \\ " << endl
         << "| |_____ | |___| || |__/ / | |_____   | |__)  )| |___| | _____) )   | |   | |_____ | |  \\ \\  _____) )" << endl
         << " \\______) \\_____/ |_____/  |_______)  |______/  \\_____/ (______/    |_|   |_______)|_|   |_|(______/" << endl
         << "                                         PRESS ENTER                                                  " << endl;
}

void menu()
{
    cout << "GAME MECHANICS:" << endl
         << "1. laksdjfhlkajsdhf" << endl
         << "2. asdfasdfasddf" << endl
         << "3. adsfasdfasdf" << endl;
}

// Loading animation
void LoadingAnimation()
{
    char bar1 = 177, bar2 = 219; // defining variable bar1 and bar2
    // print a loading message
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t Loading...";
    cout << "\n\n\n\t\t\t\t"; // empty line
    // print 25 bar1
    for (int bar = 0; bar < 25; bar++)
        cout << bar1;

    cout << "\r"; // to move the cursor to the beginning of the line
    cout << "\t\t\t\t"; // empty line

    // print 25 bar2
    for (int bar = 0; bar < 25; bar++)
    {
        cout << bar2;
        Sleep(80); // pause for 80 milliseconds
    }
}
//basta doon sa start screen
void pressAnyKey()
{
    cin.ignore();
    cin.get();
    //getchar();
}

//  questions
void getQuestions(string questions[])
{
    questions[0] = "1. User Input?\n(a) CIN\n(b) COUT\n";
    questions[1] = "2. What is the command to print 'Hello, World!' in C++?\n(a) cout << 'Hello, World!';\n(b) printf('Hello, World!')\n";
    questions[2] = "3. Use to display something on the screen?\n(a) CIN\n(b) COUT\n";
    questions[3] = "4. ";
    questions[4] = "5. ";
    questions[5] = "6. ";
    questions[6] = "7. ";
    questions[7] = "8. ";
    questions[8] = "9. ";
    questions[9] = "10. ";

}

//scoring and timer
bool askQuestion(const string& question, char correctAnswer, int& score, bool& timeExpired)
{
    cout << question << " (Choose 'a' or 'b'): ";
    auto startTime = chrono::steady_clock::now();

    char playerAnswer;
    cin >> playerAnswer;

    auto endTime = chrono::steady_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

    if (elapsedTime >= 10)
    {
        cout << "Time's up!" << endl;
        timeExpired = true; // set timeExpired to true
        return false;
    }
    else
    {
        if (playerAnswer == correctAnswer)
        {
            if (elapsedTime <= 3)
                score += 3;
            else if (elapsedTime <= 6)
                score += 2;
            else
                score += 1;
        }
        //------------------------------------------------
        return playerAnswer == correctAnswer;
    }
}
struct PlayerScore
{
    string playerName;
    int score;

    PlayerScore(const string& name, int score) : playerName(name), score(score) {}
};

bool comparePlayerScores(const PlayerScore& a, const PlayerScore& b)
{
    return a.score > b.score;
}

void displayLeaderboard(const vector<PlayerScore>& scores)
{
    cout << "\nLEADERBOARD\n";
    cout << "-------------------------\n";
    cout << "Player\t\tScore\n";
    cout << "-------------------------\n";

    for (const PlayerScore& score : scores)
    {
        cout << score.playerName << "\t\t" << score.score << "\n";
    }

    cout << "-------------------------\n";
}

void saveLeaderboard(const vector<PlayerScore>& scores)
{
    ofstream outputFile("leaderboard.txt");

    if (outputFile.is_open())
    {
        for (const PlayerScore& score : scores)
        {
            outputFile << score.playerName << " " << score.score << "\n";
        }

        outputFile.close();
    }
    else
    {
        cout << "Unable to save leaderboard." << endl;
    }
}

vector<PlayerScore> loadLeaderboard()
{
    vector<PlayerScore> scores;

    ifstream inputFile("leaderboard.txt");

    if (inputFile.is_open())
    {
        string line;

        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string playerName;
            int score;

            if (iss >> playerName >> score)
            {
                scores.push_back(PlayerScore(playerName, score));
            }
        }

        inputFile.close();
    }
    else
    {
        cout << "Unable to load leaderboard." << endl;
    }

    return scores;
}

int main()
{
    // Declarations
    string playerName;
    char playAgain;

    // Start screen
    start();
    pressAnyKey();
    system("cls");

    LoadingAnimation();

    // After loading animation
    system("cls");
    menu();

    do {
        cout << "Enter your Name to play the Game: ";
        cin >> playerName;
        system("cls");

        // Declaration again
        int score = 0;
        string questions[10];
        getQuestions(questions);

        // Answer key answer[10]
        char answers[10] = { 'a', 'a', 'a','a', 'a', 'a', 'a', 'a' ,'a', 'a' };
        //para di ko madelete askQuestion(questions[i], answers[i], score, timeExpired)
        bool timeExpired = false; // Initialize timeExpired to false
        
        for (int i = 0; i < 10; i++) { // Use the correct number of questions
            cout << "\nQuestion " << (i + 1) << endl;
            bool isAnswerCorrect = askQuestion(questions[i], answers[i], score, timeExpired);
            
            if (isAnswerCorrect) {
                cout << "Correct! ";
            }else {
                cout << "Incorrect! ";
            }
            cout << "Current Score: " << score << endl;

            // 1 second before moving to the next question
            Sleep(800);
            //this_thread::sleep_for(chrono::seconds(1));

            if (timeExpired) {
                break; // Move to the next question
            }
        }

        cout << "\nQuiz finished!" << endl;
        cout << "Final Score: " << score << " points out of 30" << endl;

        system("cls");

        vector<PlayerScore> leaderboard = loadLeaderboard();

        leaderboard.push_back(PlayerScore(playerName, score));

        sort(leaderboard.begin(), leaderboard.end(), comparePlayerScores);

        displayLeaderboard(leaderboard);

        saveLeaderboard(leaderboard);

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
