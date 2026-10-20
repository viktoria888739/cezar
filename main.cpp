#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <limits>

void encryptWord(const char* original, char* encrypted, int key)
{
    while (*original != '\0')
    {
        if (*original >= 'a' && *original <= 'z')
        {
            *encrypted =
                static_cast<char>('a' + (*original - 'a' + key) % 26);
        }
        else if (*original >= 'A' && *original <= 'Z')
        {
            *encrypted =
                static_cast<char>('A' + (*original - 'A' + key) % 26);
        }
        else
        {
            *encrypted = *original;
        }

        ++original;
        ++encrypted;
    }

    *encrypted = '\0';
}

void revealOneLetter(const char* original, char* encrypted)
{
    while (*original != '\0' && *encrypted != '\0')
    {
        if (*original != *encrypted)
        {
            *encrypted = *original;
            return;
        }

        ++original;
        ++encrypted;
    }
}

bool checkAnswer(
    const char* userGuess,
    const char* original,
    int& attempts)
{
    if (std::strcmp(userGuess, original) == 0)
    {
        return true;
    }

    --attempts;
    return false;
}

int main()
{
    constexpr int bufferSize = 64;
    const char original[] = "pointer";
    char encrypted[bufferSize] = {};
    char userGuess[bufferSize] = {};

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    const int key = std::rand() % 5 + 1;

    encryptWord(original, encrypted, key);

    int attempts = 3;

    std::cout << "Word Decoder\n";
    std::cout << "Encrypted word: " << encrypted << '\n';
    std::cout << "Enter the original word or type \"hint\".\n";

    while (attempts > 0)
    {
        std::cout << "\nAttempts left: " << attempts << '\n';
        std::cout << "Encrypted word: " << encrypted << '\n';
        std::cout << "Your input: ";

        if (!std::cin.getline(userGuess, bufferSize))
        {
            if (std::cin.eof())
            {
                std::cout << "\nInput ended.\n";
                return 0;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            userGuess[0] = '\0';
        }

        if (std::strcmp(userGuess, "hint") == 0)
        {
            revealOneLetter(original, encrypted);
            std::cout << "Hint: " << encrypted << '\n';
            continue;
        }

        if (checkAnswer(userGuess, original, attempts))
        {
            std::cout << "Correct! You decoded the word.\n";
            return 0;
        }

        if (attempts > 0)
        {
            std::cout << "Wrong answer. Try again.\n";
        }
    }

    std::cout << "No attempts left. The word was: "
              << original << '\n';

    return 0;
}