#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define GAMESIZE 100
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
    int gameWin = 0;
    while (turns < GAMESIZE && !gameOver)
    {

        for (int i = 0; i <= turns; i++)
        {
            // turn ON led with color using colorsSequence[try]
            printf("turn led ON %d\n", colorsSequence[i]);
            // emmit buzzer sound in frequency colorsSequence[try]
            delay(1000);
            printf("turn led OFF\n");
            // -----------------------------------------
        }

        for (int i = 0; i <= turns; i++)
        {
            printf("\nyour turn: ");
            // get user inputs from mosquitto publisher
            inputColorCode = getKeyPress();
            // -----------------------------------------
            if (inputColorCode != -1)
            {
                inputSequence[i] = inputColorCode;

                // for (int j = 0; j <= turns; j++)
                // {
                if (inputSequence[i] == colorsSequence[i])
                {
                    // if (i == turns)
                    step++;
                    score++;
                }
                if (score < step)
                {
                    printf("\n!!!!!!!!!!!!! errou\n");
                }
                if (score == GAMESIZE)
                    gameWin = 1;
                // }
                gameCurrentLenght++;
            }
        }
        printf("\ndebug:\n");
        printf("%d -- step\n", step);
        printf("%d -- turns\n", turns);
        printf("%d -- score\n", score);
        turns++;

        delay(2000);
    }
    if (gameWin)
        printf("\n\nMAX GRADE! YOU NAILED IT!");
    else
        printf("\n\nKEEP TRYING, I TRUST YOU!");
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
    int milliSeconds = 1000 * numberOfSeconds;
    clock_t startTime = clock();
    while (clock() < startTime + milliSeconds)
        ;
}