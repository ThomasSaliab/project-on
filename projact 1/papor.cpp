#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum Difficulty
{
    Easy = 1,
    Medium,
    Hard,
    Expert
};

enum OperationType
{
    Add = 1,
    Subtract,
    Multiply,
    Divide,
    Mix
};

int ReadPositiveNumber(string message, int max = 10)
{
    int num;
    do
    {
        cout << message << " (1-" << max << "): ";
        cin >> num;
    } while (num <= 0 || num > max);
    return num;
}

int GenerateRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

pair<int, int> GenerateOperands(Difficulty level)
{
    switch (level)
    {
    case Easy:
        return {GenerateRandomNumber(1, 10), GenerateRandomNumber(1, 10)};
    case Medium:
        return {GenerateRandomNumber(10, 50), GenerateRandomNumber(10, 50)};
    case Hard:
        return {GenerateRandomNumber(-50, 50), GenerateRandomNumber(-50, 50)};
    case Expert:
        return {GenerateRandomNumber(-100, 100), GenerateRandomNumber(-100, 100)};
    default:
        return {0, 0};
    }
}

int PerformOperation(int a, int b, OperationType op)
{
    switch (op)
    {
    case Add:
        return a + b;
    case Subtract:
        return a - b;
    case Multiply:
        return a * b;
    case Divide:
        return (b != 0) ? a / b : 0;
    default:
        return 0;
    }
}

string GetOperatorSymbol(OperationType op)
{
    switch (op)
    {
    case Add:
        return "+";
    case Subtract:
        return "-";
    case Multiply:
        return "*";
    case Divide:
        return "/";
    default:
        return "?";
    }
}

OperationType ChooseOperation(OperationType selected)
{
    if (selected == Mix)
        return static_cast<OperationType>(GenerateRandomNumber(1, 4));
    return selected;
}

void AskQuestion(int index, int total, Difficulty level, OperationType operation)
{
    pair<int, int> operands = GenerateOperands(level);
    OperationType op = ChooseOperation(operation);

    int correctAnswer = PerformOperation(operands.first, operands.second, op);

    cout << "\nQuestion [" << index << "/" << total << "]\n";
    cout << operands.first << " " << GetOperatorSymbol(op) << " " << operands.second << " = ";

    int userAnswer;
    cin >> userAnswer;

    if (userAnswer == correctAnswer)
    {
        cout << "✅ Correct!\n";
        system("color 2A");
    }
    else
    {
        cout << "❌ Wrong. Correct answer: " << correctAnswer << "\n";
        system("color 4F");
    }
}

void PlayQuiz()
{
    int questionCount = ReadPositiveNumber("How many questions do you want?", 20);
    Difficulty level = static_cast<Difficulty>(ReadPositiveNumber("Select difficulty: [1] Easy [2] Medium [3] Hard [4] Expert", 4));
    OperationType operation = static_cast<OperationType>(ReadPositiveNumber("Select operation: [1] Add [2] Subtract [3] Multiply [4] Divide [5] Mix", 5));

    for (int i = 1; i <= questionCount; i++)
    {
        AskQuestion(i, questionCount, level, operation);
    }
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void GameLoop()
{
    char choice;
    do
    {
        ResetScreen();
        PlayQuiz();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;

    } while (tolower(choice) == 'y');

    ResetScreen();
    cout << "Thanks for playing!\n";
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    GameLoop();
    return 0;
}
