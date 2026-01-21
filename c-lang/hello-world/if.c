// https://www.learn-c.org/en/Conditions
#include <stdbool.h>
#include <stdio.h>

bool guessNumber(int guess) {
    
    if (guess == 555) {
        printf("Correct. You guessed it!\n");
        return true;
    }

    if (guess < 555) {
        printf("Your guess is too low\n");
        return true;
    }

    if (guess > 555) {
        printf("Your guess is too high\n");

        return true;
    }


    return false;
}

int main() {
    guessNumber(500);
    guessNumber(600);
    guessNumber(555);
    return 0;
}