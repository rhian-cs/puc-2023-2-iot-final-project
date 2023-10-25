#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define GAMESIZE 3
#define NUMBER_OF_COLORS 4

void setup(int *colorsSequence);
void loop(int *colorsSequence, int *inputSequence);
int getKeyPress();
void delay(int number_of_seconds);

int main()
{
    int *colorsSequence;
    colorsSequence = (int *)malloc(GAMESIZE * sizeof(int));
    int *inputSequence;
    inputSequence = (int *)malloc(GAMESIZE * sizeof(int));
    setup(colorsSequence);
    loop(colorsSequence, inputSequence);
    return 0;
}

void setup(int *colorsSequence)
{
    srand(time(NULL));
    for (int i = 0; i < GAMESIZE; i++)
    {
        int random = rand() % NUMBER_OF_COLORS + 1;
        colorsSequence[i] = random;
    }
}

void loop(int *colorsSequence, int *inputSequence)
{
    int inputColorCode;
    int gameCurrentLenght = 0;
    int turns = 0;
    int score = 0;
    int step = 0;
    int gameOver = 0;
    while (turns < GAMESIZE && !gameOver)
    {
        for (int i = 0; i <= turns; i++)
        {
            // here: command to turn on led (colorsSequence[i])
            printf("\nturn led ON %d\n", colorsSequence[i]);
            // here: command to emit buzzer sound (colorsSequence[i])
            delay(1000);

            // here: command to turn off led (colorsSequence[i])
            printf("turn led OFF\n");
        }
        for (int i = 0; i <= turns; i++)
        {
            printf("\nyour turn: ");
            inputSequence[i] = getKeyPress();
            if(inputSequence != -1){
                step++;
                for(int j = 0; j < step; j++){
                    if(inputSequence[j] != colorsSequence[j]){
                        printf("\nERROU\n");
                        gameOver = 1;
                    }
                    else{
                        score++;
                    }
                }
            }
            else i--;
        }
        step=0;
        turns++;
        delay(2000);
    }
    if (!gameOver)
        printf("\n\nMAX GRADE! YOU NAILED IT!\n");
    else
        printf("\n\nKEEP TRYING, I TRUST YOU!\n");
    printf("score=%d\n\n", score);
}

int getKeyPress()
{
    int numericKeyboard1 = 49;
    char buf[100];
    gets(buf);
    int keyPressed = (int)buf[0] - numericKeyboard1 + 1;
    if (keyPressed < 1 || keyPressed > 4)
    {
        printf("use numeric keyboard keys: 1 to 4\n");
        return -1;
    }
    return keyPressed;
}

void delay(int numberOfSeconds)
{
    int milliSeconds = .5 * numberOfSeconds;
    clock_t startTime = clock();
    while (clock() < startTime + milliSeconds)
        ;
}
