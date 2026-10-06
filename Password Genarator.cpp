#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

// --------------------------------------------------
// CENTER TEXT
// --------------------------------------------------

void printCentered(const string& text, int width = 60)
{
    int spaces = (width - text.length()) / 2;

    if (spaces < 0)
        spaces = 0;

    cout << string(spaces, ' ') << text << endl;
}

// --------------------------------------------------
// MAIN TITLE
// --------------------------------------------------

void showTitle()
{
    cout << "\n";
    cout << "============================================================\n";

    printCentered("C++ PASSWORD GENERATOR");

    cout << "============================================================\n";

    printCentered("Secure  |  Smart  |  Personalized");

    cout << "\n";
}

// --------------------------------------------------
// PASSWORD STRENGTH CHECKER
// --------------------------------------------------

string checkStrength(const string& password)
{
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSymbol = false;

    for (char ch : password)
    {
        if (isupper(static_cast<unsigned char>(ch)))
            hasUpper = true;

        else if (islower(static_cast<unsigned char>(ch)))
            hasLower = true;

        else if (isdigit(static_cast<unsigned char>(ch)))
            hasDigit = true;

        else
            hasSymbol = true;
    }

    int score = 0;

    if (hasUpper) score++;
    if (hasLower) score++;
    if (hasDigit) score++;
    if (hasSymbol) score++;

    if (password.length() >= 8 && score == 4)
        return "STRONG";

    else if (password.length() >= 6 && score >= 3)
        return "MEDIUM";

    else
        return "WEAK";
}

// --------------------------------------------------
// RANDOM PASSWORD GENERATOR
// --------------------------------------------------

string generateRandomPassword(int length)
{
    const string uppercase =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const string lowercase =
        "abcdefghijklmnopqrstuvwxyz";

    const string numbers =
        "0123456789";

    const string symbols =
        "!@#$%^&*";

    const string allCharacters =
        uppercase + lowercase + numbers + symbols;

    random_device rd;
    mt19937 generator(rd());

    string password;

    uniform_int_distribution<int> upperDist(
        0, uppercase.length() - 1
    );

    uniform_int_distribution<int> lowerDist(
        0, lowercase.length() - 1
    );

    uniform_int_distribution<int> numberDist(
        0, numbers.length() - 1
    );

    uniform_int_distribution<int> symbolDist(
        0, symbols.length() - 1
    );

    uniform_int_distribution<int> allDist(
        0, allCharacters.length() - 1
    );

    // Basic requirements are automatically included
    password += uppercase[upperDist(generator)];
    password += lowercase[lowerDist(generator)];
    password += numbers[numberDist(generator)];
    password += symbols[symbolDist(generator)];

    // Fill remaining characters
    while (password.length() < static_cast<size_t>(length))
    {
        password += allCharacters[allDist(generator)];
    }

    // Randomize password
    shuffle(
        password.begin(),
        password.end(),
        generator
    );

    return password;
}

// --------------------------------------------------
// PERSONALIZED PASSWORD GENERATOR
// --------------------------------------------------

string generatePersonalizedPassword(
    string requirements,
    int length
)
{
    const string uppercase =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const string lowercase =
        "abcdefghijklmnopqrstuvwxyz";

    const string numbers =
        "0123456789";

    const string symbols =
        "!@#$%^&*";

    const string allCharacters =
        uppercase +
        lowercase +
        numbers +
        symbols;

    random_device rd;
    mt19937 generator(rd());

    // ----------------------------------------------
    // EXTRACT WORD AND NUMBER FROM USER INPUT
    // ----------------------------------------------

    string word = "";
    string number = "";

    stringstream ss(requirements);
    string part;

    bool wordFound = false;

    while (ss >> part)
    {
        string lettersOnly;
        string digitsOnly;

        for (char ch : part)
        {
            if (isalpha(static_cast<unsigned char>(ch)))
            {
                lettersOnly += ch;
            }

            if (isdigit(static_cast<unsigned char>(ch)))
            {
                digitsOnly += ch;
            }
        }

        if (!lettersOnly.empty() && !wordFound)
        {
            word = lettersOnly;
            wordFound = true;
        }

        if (!digitsOnly.empty())
        {
            number += digitsOnly;
        }
    }

    // If user did not provide a word
    if (word.empty())
    {
        word = "Pass";
    }

    // If user did not provide a number
    if (number.empty())
    {
        number = "7";
    }

    // ----------------------------------------------
    // USE FULL NAME OR A MEANINGFUL PART
    // ----------------------------------------------

    int nameLength;

    if (word.length() <= 4)
    {
        nameLength = word.length();
    }
    else
    {
        // Use approximately half of the name
        nameLength = word.length() / 2;
    }

    nameLength = max(1, nameLength);

    string namePart =
        word.substr(0, nameLength);

    // First character uppercase
    namePart[0] =
        toupper(
            static_cast<unsigned char>(namePart[0])
        );

    // Remaining characters lowercase
    for (size_t i = 1; i < namePart.length(); i++)
    {
        namePart[i] =
            tolower(
                static_cast<unsigned char>(namePart[i])
            );
    }

    // ----------------------------------------------
    // CHECK MINIMUM LENGTH
    // ----------------------------------------------

    // Name + number + symbol
    int minimumLength =
        namePart.length() +
        number.length() +
        1;

    if (length < minimumLength)
    {
        return "";
    }

    // ----------------------------------------------
    // BUILD PASSWORD
    // ----------------------------------------------

    string password;

    // User's requirement stays together
    password += namePart;

    // User's number/date stays completely
    password += number;

    // Add symbol automatically
    uniform_int_distribution<int> symbolDist(
        0,
        symbols.length() - 1
    );

    password += symbols[symbolDist(generator)];

    // ----------------------------------------------
    // FILL REMAINING CHARACTERS
    // ----------------------------------------------

    uniform_int_distribution<int> allDist(
        0,
        allCharacters.length() - 1
    );

    while (password.length() < static_cast<size_t>(length))
    {
        password += allCharacters[allDist(generator)];
    }

    // Do NOT shuffle.
    // This keeps the user's name/date readable.

    return password;
}

// --------------------------------------------------
// RANDOM PASSWORD OPTION
// --------------------------------------------------

void randomPassword()
{
    int length;

    cout << "\nEnter password length: ";
    cin >> length;

    if (length < 4)
    {
        cout << "\nPassword length must be at least 4.\n";
        return;
    }

    string password =
        generateRandomPassword(length);

    cout << "\nGenerated Password : "
         << password << endl;

    cout << "Password Strength  : "
         << checkStrength(password)
         << endl;

    char choice;

    cout << "\nDo you like this password? (Y/N): ";
    cin >> choice;

    if (choice == 'N' || choice == 'n')
    {
        char again;

        cout << "Would you like me to generate a new password? (Y/N): ";
        cin >> again;

        if (again == 'Y' || again == 'y')
        {
            randomPassword();
        }
    }
}

// --------------------------------------------------
// PERSONALIZED PASSWORD OPTION
// --------------------------------------------------

void personalizedPassword()
{
    cin.ignore();

    string requirements;

    cout << "\nWhat are your requirements? ";
    getline(cin, requirements);

    int length;

    cout << "Enter password length: ";
    cin >> length;

    string password =
        generatePersonalizedPassword(
            requirements,
            length
        );

    if (password.empty())
    {
        cout << "\nPassword length is too short for your requirements.\n";
        cout << "Please choose a longer password length.\n";
        return;
    }

    cout << "\nGenerated Password : "
         << password
         << endl;

    cout << "Password Strength  : "
         << checkStrength(password)
         << endl;

    char choice;

    cout << "\nDo you like this password? (Y/N): ";
    cin >> choice;

    if (choice == 'N' || choice == 'n')
    {
        char again;

        cout << "Would you like me to generate another one? (Y/N): ";
        cin >> again;

        if (again == 'Y' || again == 'y')
        {
            personalizedPassword();
        }
    }
}

// --------------------------------------------------
// CHECK OWN PASSWORD
// --------------------------------------------------

void checkOwnPassword()
{
    cin.ignore();

    string password;

    cout << "\nEnter your password: ";
    getline(cin, password);

    cout << "\nPassword Strength  : "
         << checkStrength(password)
         << endl;

    char choice;

    cout << "\nWould you like to generate a stronger password? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        int length =
            max(
                12,
                static_cast<int>(password.length())
            );

        string newPassword =
            generateRandomPassword(length);

        cout << "\nSuggested Strong Password : "
             << newPassword
             << endl;

        cout << "Password Strength          : "
             << checkStrength(newPassword)
             << endl;
    }
}

// --------------------------------------------------
// MAIN PROGRAM
// --------------------------------------------------

int main()
{
    int choice;

    while (true)
    {
        showTitle();

        cout << "        1. Generate Random Password\n";
        cout << "        2. Create Personalized Password\n";
        cout << "        3. Check My Own Password\n";
        cout << "        4. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                randomPassword();
                break;

            case 2:
                personalizedPassword();
                break;

            case 3:
                checkOwnPassword();
                break;

            case 4:
                cout << "\n";
                printCentered("Thank you for using Password Generator!");
                cout << "\n";
                return 0;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}