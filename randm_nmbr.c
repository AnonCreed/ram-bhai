#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random number between 'lower' and 'upper'
int generateRandomNumber(int lower, int upper) {
    int a= (rand() % (upper - lower + 1)) + lower;
    return a;
}

// Function to check if the guess is correct and close to the target
int checkGuess(int guess, int target, int *isClose) {
    const int threshold = 10; // Threshold for closeness
    if (guess == target) {
        *isClose = 0; // Exact match
        return 1; // Correct guess
    } else if (abs(target - guess) <= threshold) {
        *isClose = 1; // Close
    }
    else{
        *isClose = 0; // Not Close
    }
    if (guess < target) {
        return -1; // Guess is too low
    } else {
        return 0; // Guess is too high
    }
}

// Function to determine the number of attempts based on the range
int determineAttempts(int lower, int upper) {
    if (upper - lower <= 50)
        return 5; // For smaller range, fewer attempts
    else
        return 5; // For larger range, more attempts
}

int main() {
    int lower,upper ; // Range of numbers
    int target, guess, attempts = 0;
    int isClose = 0; // Variable to indicate if the guess is close

    printf("Welcome to the Number Guessing Game!\n");
    printf("Enter the upper limit and lower limit: \n"); // Asking user for input
    scanf("%d%d",&upper,&lower);

    srand(time(NULL)); // Seed the random number generator
    target = generateRandomNumber(lower, upper); // Generate the random number

    int maxAttempts = determineAttempts(lower, upper); // Determine the maximum number of attempts
    printf("You have %d attempts to guess the number.\n", maxAttempts);
    // Game loop
    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        attempts++;

        int result = checkGuess(guess, target, &isClose); // Check the guess

        if (result == 1) {
            printf("Congratulations! You guessed the number %d correctly in %d attempts.\n", target, attempts);
            break; // End the game
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
            break; // End the game
        }
    } while (1);

    return 0;
}
