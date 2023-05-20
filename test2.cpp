#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <algorithm>

using namespace std;

// Start art screen
void start() {
    cout << " _______  _______  ______   _______    ______   _     _   ______  _______  _______  ______    ______ " << endl 
         << "(_______)(_______)(______) (_______)  (____  \\ (_)   (_) / _____)(_______)(_______)(_____ \\  / _____)" << endl 
         << " _        _     _  _     _  _____      ____)  ) _     _ ( (____      _     _____    _____) )( (____  " << endl 
         << "| |      | |   | || |   | ||  ___)    |  __  ( | |   | | \\____ \\    | |   |  ___)  |  __  /  \\____ \\ " << endl 
         << "| |_____ | |___| || |__/ / | |_____   | |__)  )| |___| | _____) )   | |   | |_____ | |  \\ \\  _____) )" << endl 
         << " \\______) \\_____/ |_____/  |_______)  |______/  \\_____/ (______/    |_|   |_______)|_|   |_|(______/" << endl
         << "                                         PRESS ENTER                                                  " << endl;
}

void menu() {
    cout << "GAME MECHANICS:" << endl
        << "1. laksdjfhlkajsdhf" << endl
        << "2. asdfasdfasddf" << endl
        << "3. adsfasdfasdf" << endl;
}

// Loading animation
void LoadingAnimation() {
    system("color 0A"); // Change console color to green
    char bar1 = 177, bar2 = 219; // Define variable bar1 and bar2
    // Print a loading message
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t Loading...";
    cout << "\n\n\n\t\t\t\t"; // Empty line
    // Print 25 bar1
    for (int bar = 0; bar < 25; bar++)
        cout << bar1;
    cout << "\r"; // Move the cursor to the beginning of the line
    cout << "\t\t\t\t"; // Empty line

    // Print 25 bar2
    for (int bar = 0; bar < 25; bar++) {
        cout << bar2;
        std::this_thread::sleep_for(std::chrono::milliseconds(80)); // Pause for 80 milliseconds
    }
    system("cls"); // Clear console screen
}

void pressAnyKey() {
    getchar();
}

// Function to display a question and get the player's answer
bool askQuestion(const string& question, char correctAnswer, int& score) {
    cout << question << " (Choose 'a' or 'b'): ";
    auto startTime = std::chrono::steady_clock::now();

    char playerAnswer;
    cin >> playerAnswer;

    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    if (elapsedTime >= 10) {
        cout << "Time's up!" << endl;
        return false;
    }
    else {
        if (playerAnswer == correctAnswer) {
            if (elapsedTime <= 3)
                score += 3;
            else if (elapsedTime <= 6)
                score += 2;
            else
                score += 1;
        }
        return true;
    }
}

int main() {
    // Declarations
    string playerName;

    // Start screen
    start();
    pressAnyKey();
    system("cls");

    LoadingAnimation();

    // After loading animation
    menu();
    cout << "Enter your Name to play the Game: ";
    cin >> playerName;

    system("cls");

    int score = 0;

    // Questions and answers
    string questions[10] = {
        "1. What is the capital of France?\n(a) Paris\n(b) London",
        "2. What is the command to print 'Hello, World!' in C++?\n(a) cout << 'Hello, World!';\n(b) printf('Hello, World!');",
        // Add more questions here...
    };
    char answers[10] = { 'a', 'a', /* Add more correct answers here... */ };

    for (int i = 0; i < 10; i++) {
        cout << "\nQuestion " << (i + 1) << endl;
        if (askQuestion(questions[i], answers[i], score)) {
            cout << "Correct! ";
        }
        else {
            cout << "Incorrect! ";
        }
        cout << "Current Score: " << score << endl;

        // Wait for 1 second before moving to the next question
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cout << "\nQuiz finished!" << endl;
    cout << "Final Score: " << score << " points out of 30" << endl;

    return 0;
}
