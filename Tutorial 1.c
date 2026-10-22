
#include <stdio.h>
#include <string.h>

void reverse(char input[]);
int palindrome(char input[]);
void copy(char input[], char output[]);
void substring(char input[]);
int stringlength(char input[]);

int main()
{
    char str[100], output[100];
    int ch, c;

    printf("\nEnter the string: ");
    scanf("%99s", str);

    do
    {
        printf("\n\n1) Copy");
        printf("\n2) Palindrome");
        printf("\n3) Reverse");
        printf("\n4) Substring");
        printf("\n5) Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                copy(str, output);
                break;

            case 2:
                c = palindrome(str);

                if (c == 1)
                    printf("\nThe given string is a palindrome.");
                else
                    printf("\nThe given string is not a palindrome.");
                break;

            case 3:
                reverse(str);
                break;

            case 4:
                substring(str);
                break;

            case 5:
                printf("\nExiting the program.");
                break;

            default:
                printf("\nInvalid choice. Please try again.");
        }

    } while (ch != 5);

    return 0;
}

int palindrome(char input[])
{
    int i = 0;
    int j = stringlength(input) - 1;

    while (i < j)
    {
        if (input[i] != input[j])
            return 0;

        i++;
        j--;
    }

    return 1;
}

void copy(char input[], char output[])
{
    int i;

    for (i = 0; input[i] != '\0'; i++)
        output[i] = input[i];

    output[i] = '\0';

    printf("\nThe copied string is: %s", output);
}

void substring(char input[])
{
    int i, n, position;
    char output[100];

    printf("\nEnter the starting position (0-based): ");
    scanf("%d", &position);

    n = stringlength(input);

    if (position >= 0 && position < n)
    {
        for (i = 0; i < n - position; i++)
            output[i] = input[position + i];

        output[i] = '\0';

        printf("\nInput string: %s", input);
        printf("\nOutput substring: %s", output);
    }
    else
    {
        printf("\nPosition entered is out of range.");
    }
}

int stringlength(char input[])
{
    int i = 0;

    while (input[i] != '\0')
        i++;

    return i;
}

void reverse(char input[])
{
    int n, i;
    char output[100];

    n = stringlength(input);

    for (i = 0; i < n; i++)
        output[n - 1 - i] = input[i];

    output[i] = '\0';

    printf("\nInput string: %s", input);
    printf("\nReversed string: %s", output);
}
