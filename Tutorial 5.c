#include <stdio.h>

#define MAX 5

int stack[MAX];
int top = -1;

void push()
{
    int value;

    if (top == MAX - 1)
    {
        printf("Stack Overflow! Stack is full.\n");
    }
    else
    {
        printf("Enter element to push: ");
        if (scanf("%d", &value) != 1)
        {
            printf("Invalid input!\n");
            return;
        }

        top++;
        stack[top] = value;

        printf("%d pushed into the stack.\n", value);
    }
}
void pop()
{
    if (top == -1)
    {
        printf("Stack Underflow! Stack is empty.\n");
    }
    else
    {
        printf("Popped element: %d\n", stack[top]);
        top--;
    }
}
void display()
{
    int i;

    if (top == -1)
    {
        printf("Stack is empty.\n");
    }
    else
    {
        printf("Stack elements (Top to Bottom):\n");

        for (i = top; i >= 0; i--)
        {
            printf("%d\n", stack[i]);
        }
    }
}
int main()
{
    int n, i, choice;

    printf("Enter number of initial elements (0-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX)
    {
        printf("Invalid number of elements!\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &stack[i]) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }
    }

    top = n - 1;

    do
    {
        printf("\n--- STACK MENU ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                push();
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting Stack program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}