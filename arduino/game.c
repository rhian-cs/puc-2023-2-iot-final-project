#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define GAMESIZE 10
#define NUMBER_OF_COLORS 4

void setup(int *colorsSequence);
void loop(int *colorsSequence);
int getKeyPress();

int main()
{
    int *colorsSequence;
    colorsSequence = (int *)malloc(GAMESIZE * sizeof(int));
    setup(colorsSequence);
    loop(colorsSequence);

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

void loop(int *colorsSequence)
{
    // for (int i = 0; i < GAMESIZE; i++)
    // {
    //     printf("%d-", colorsSequence[i]);
    // }
    int colorCode;
    int try = 0;
    int score = 0;
    while (try < GAMESIZE)
    {
        printf("from vec=%d\n", colorsSequence[try]);
        colorCode = getKeyPress();
        if (colorCode != -1)
        {

            printf("color code=%d\n", colorCode);
            if (colorCode == colorsSequence[try])
            {
                score++;
            }
            try++;
        }
        printf("score=%d\n", score);
    }
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