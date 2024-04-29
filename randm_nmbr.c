#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

// Function prototype
int limitchecker(int *lower, int *upper);
int generateRandomNumber(int lower, int upper);
int checkGuess(int guess, int target, int range, int *isClose);
int determineAttempts(int lower, int upper);
void singleplayermode();
void multiplayer();

// Function to arrange the limits in correct order
int limitchecker(int *lower, int *upper) {
    int temp;
    if (*lower > *upper) {
        temp = *lower;
        *lower = *upper;
        *upper = temp;
    }
}

// Function to generate a random number between 'lower' and 'upper'
int generateRandomNumber(int lower, int upper) {
    int a = (rand() % (upper - lower + 1)) + lower;
    return a;
}

// Function to check if the guess is correct and close to the target
int checkGuess(int guess, int target, int range, int *isClose) {
    const int threshold = range / 10; // threshold for closeness
    if (guess == target) {
        *isClose = 0; // exact match
        return 1;      // Correct guess
    } else if (abs(target - guess) <= threshold) {
        *isClose = 1; // close
    } else {
        *isClose = 0; // not Close
    }
    if (guess < target) {
        return -1; // guess is too low
    } else {
        return 0; // guess is too high
    }
}

// Function to determine the number of attempts based on the range
int determineAttempts(int lower, int upper) {
    int attempts = (upper - lower) / 15 + 1; // made formula i.e. taking ref 50 range 5 chance
    return attempts;
}

// Single player mode function
void singleplayermode() {
    int lower, upper; // range of numbers
    char choice;      // choice to play (y/n)
    int target, guess, attempts = 0;
    int isClose = 0; // variable to indicate if the guess is close

    game1:

    printf("Welcome to the Number Guessing Game!\n");
    printf("Enter the upper limit and lower limit: \n"); // asking user for input
    scanf("%d%d", &lower, &upper);
    limitchecker(&lower, &upper); // arrange the user input
    int range = upper - lower;

    srand(time(NULL)); // setup the random number generator to be more unpredictable
    target = generateRandomNumber(lower, upper); // generate the random number

    int maxAttempts = determineAttempts(lower, upper); // determine the maximum number of attempts
    printf("You have %d attempts to guess the number.\n", maxAttempts);
    // Game loop
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        int result = checkGuess(guess, target, range, &isClose); // check the guess

        if (result == 1) {
            printf("Congratulations! You guessed the number %d correctly in %d attempts.\n", target, attempts);
            FILE *file = fopen("leaderboard.txt", "a");
            if (file != NULL) {
                fprintf(file, "Player 1: Win\n");
                fclose(file);
            } else {
                printf("Error: Unable to open file for writing.\n");
            }
            break; // end the game
        } else if (result == -1) {
            if (isClose == 1)
                printf("You're close! ");
            printf("Try again! The number I'm thinking of is higher than %d.\n", guess);
        } else {
            if (isClose == 1)
                printf("You're close! ");
            printf("Try again! The number I'm thinking of is lower than %d.\n", guess);
        }

        if (attempts >= maxAttempts) {
            printf("Sorry, you have used all your attempts. The correct number was %d.\n", target);
            FILE *file = fopen("leaderboard.txt", "a");
            if (file != NULL) {
                fprintf(file, "Player 1: Lose\n");
                fclose(file);
            } else {
                printf("Error: Unable to open file for writing.\n");
            }
            break; // end the game
        }
    } while (1);

    do {
        printf("Do you want to play again?(y/n): \n"); // asking users choice
        getchar();
        scanf("%c", &choice);

        if (choice == 'n') {
            printf("GoodBye!");
            exit(0); // end of the game
        } else if (choice == 'y') {
            goto game1; // games starts again
        } else {
            printf("wrong input\n"); // remind the user about wrong input
        }
    } while (choice != 'y' && choice != 'n'); // forces user to choose from two option only
}

//function that will hide the input that is user is giving
void hideInput() {
    system("stty -echo");
}

//function that will work file again
void showInput() {
    system("stty echo");
}

// Multiplayer mode function
void multiplayer() {
    int lower, upper; // range of numbers
    int target;       // the player one arranged number
    char choice;      // choice to play (y/n)
    int guess, attempts = 0;
    int isClose = 0; // variable to indicate if the guess is close

    game:

    printf("Welcome to the Multiplayer of Number Guessing Game!\n");
    printf("Player 1 enter the upper limit and lower limit: \n"); // asking user for input
    scanf("%d%d", &lower, &upper);
    limitchecker(&lower, &upper); // arrange the user input
    int range = upper - lower; 

    hideInput(); // Hide input for the target number
    printf("Enter the number you want p2 to guess: ");
    scanf("%d", &target);
    showInput(); // Show input for the guesses

    int temp = target;
    while (temp > 0) {
        printf("*");
        temp = temp / 10;
    }
    printf("\n");

    int maxAttempts = determineAttempts(lower, upper); // determine the maximum number of attempts
    printf("Player 2 have %d attempts to guess the number.\n", maxAttempts);
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        int result = checkGuess(guess, target, range, &isClose); // check the guess

        if (result == 1) {
            printf("Congratulations! You guessed the number %d correctly in %d attempts.\n", target, attempts);
            FILE *file = fopen("leaderboard.txt", "a");
            if (file != NULL) {
                fprintf(file, "Player 2: Win\n");
                fclose(file);
            } else {
                printf("Error: Unable to open file for writing.\n");
            }
            break; // end the game
        } else if (result == -1) {
            if (isClose == 1)
                printf("You're close! ");
            printf("Try again! The number I'm thinking of is higher than %d.\n", guess);
        } else {
            if (isClose == 1)
                printf("You're close! ");
            printf("Try again! The number I'm thinking of is lower than %d.\n", guess);
        }

        if (attempts >= maxAttempts) {
            printf("Sorry, you have used all your attempts. The correct number was %d.\n", target);
            FILE *file = fopen("leaderboard.txt", "a");
            if (file != NULL) {
                fprintf(file, "Player 2: Lose\n");
                fclose(file);
            } else {
                printf("Error: Unable to open file for writing.\n");
            }
            break; // end the game
        }
    } while (1);

    do {
        printf("Do you want to play again?(y/n): \n"); // asking users choice
        getchar();
        scanf("%c", &choice);

        if (choice == 'n') {
            printf("GoodBye!");
            exit(0); // end of the game
        } else if (choice == 'y') {
            goto game; // games starts again
        } else {
            printf("wrong input\n"); // remind the user about wrong input
        }
    } while (choice != 'y' && choice != 'n'); // forces user to choose from two option only
}

int main() {
    int choice;
    printf("Welcome to the game select single player(1) or multiplayer(2)\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        singleplayermode();
        break;
    case 2:
        multiplayer();
        break;
    default:
        printf("Invalid choice. Exiting...\n");
        break;
    }

    return 0;
}
