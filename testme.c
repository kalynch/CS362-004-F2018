#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char randomChar[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']' };
char validStringChar[4] = {'r', 'e', 's', 't'};
char randomString[5];


/************************************************************************************
 * Name: generateRandomInRange
 * Descirption: Generates a random integer in a specified range.
 * Parameters: low value, high value
 * Return: random integer
 ************************************************************************************/
int generateRandomInRange(int low, int high)
{
    int num = (rand() % (high - low + 1)) + low;
    return num;
}

char inputChar()
{
    return randomChar[generateRandomInRange(0, 9)];
}


char *inputString()
{
    // Add null terminator so string is valid
    randomString[4] = '\0';

    // Fill string with random values
    int i;
    for (i = 0; i < 4; i++)
    {
        randomString[i] = validStringChar[generateRandomInRange(0, 4)];
    }
    return "";
}

void testme()
{
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1)
    {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' '&& state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'
            && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0'
            && state == 9)
        {
            printf("error ");
            exit(200);
        }
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}


