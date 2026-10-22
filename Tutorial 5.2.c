
#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue()
{
    int value;

    if ((rear + 1) % MAX == front)
    {
        printf("Queue Overflow!\n");
        return;
    }

    printf("Enter element to insert: ");

    if (scanf("%d", &value) != 1)
        return;

    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = value;
    printf("Element inserted successfully.\n");
}

void dequeue()
{
    if (front == -1)
    {
        printf("Queue Underflow!\n");
        return;
    }

    printf("Deleted element: %d\n", queue[front]);

    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

void display()
{
    int i;

    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements (front to rear):\n");

    i = front;

    while (1)
    {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }

    printf("\n");
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

    if (n > 0)
    {
        printf("Enter %d elements:\n", n);

        for (i = 0; i < n; i++)
        {
            if (scanf("%d", &queue[i]) != 1)
            {
                printf("Invalid input!\n");
                return 1;
            }
        }

        front = 0;
        rear = n - 1;
    }

    do
    {
        printf("\n--- QUEUE MENU ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            return 1;

        switch (choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting Queue program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
