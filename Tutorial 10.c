
#include <stdio.h>
#include <stdbool.h>

#define SIZE 64

struct UART
{
    char buffer[SIZE];
    int front;
    int rear;
    int count;
};

void initialize(struct UART *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

bool isEmpty(struct UART *q)
{
    return q->count == 0;
}

bool isFull(struct UART *q)
{
    return q->count == SIZE;
}

void enqueue(struct UART *q, char data)
{
    if (isFull(q))
    {
        printf("Buffer is full!\n");
        return;
    }

    q->buffer[q->rear] = data;
    q->rear = (q->rear + 1) % SIZE;
    q->count++;
}

char dequeue(struct UART *q)
{
    char data;

    if (isEmpty(q))
    {
        return '\0';
    }

    data = q->buffer[q->front];
    q->front = (q->front + 1) % SIZE;
    q->count--;

    return data;
}

void sendData(struct UART *tx)
{
    char data;

    printf("\nTransmitted Data: ");

    while (!isEmpty(tx))
    {
        data = dequeue(tx);
        printf("%c", data);
    }

    printf("\n");
}

void receiveData(struct UART *rx)
{
    char data;

    printf("\nReceived Data: ");

    while (!isEmpty(rx))
    {
        data = dequeue(rx);
        printf("%c", data);
    }

    printf("\n");
}

int main()
{
    struct UART tx, rx;
    char data;

    initialize(&tx);
    initialize(&rx);

    printf("Enter data to transmit: ");
    while ((data = getchar()) != '\n' && data != EOF)
    {
        enqueue(&tx, data);
    }

    sendData(&tx);

    printf("\nEnter received data: ");
    while ((data = getchar()) != '\n' && data != EOF)
    {
        enqueue(&rx, data);
    }

    receiveData(&rx);

    return 0;
}
