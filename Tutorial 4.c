
#include <stdio.h>

#define MAX 100

struct student
{
    int roll;
    char name[80];
    float SGPA;
};

void create(struct student arr[], int n);
void display(struct student arr[], int n);
void search(struct student arr[], int n);

void create(struct student arr[], int n)
{
    int i;

    printf("\nEnter student details\n");

    for (i = 0; i < n; i++)
    {
        printf("\nEnter roll number: ");
        scanf("%d", &arr[i].roll);

        printf("Enter name: ");
        scanf("%79s", arr[i].name);

        printf("Enter SGPA: ");
        scanf("%f", &arr[i].SGPA);
    }
}

void display(struct student arr[], int n)
{
    int i;

    printf("\nStudent Details:\n");

    for (i = 0; i < n; i++)
    {
        printf("\nRoll No: %d\n", arr[i].roll);
        printf("Name: %s\n", arr[i].name);
        printf("SGPA: %.2f\n", arr[i].SGPA);
    }
}

void search(struct student arr[], int n)
{
    int roll, i;

    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);

    for (i = 0; i < n; i++)
    {
        if (arr[i].roll == roll)
        {
            printf("\nStudent found!\n");
            printf("Roll No: %d\n", arr[i].roll);
            printf("Name: %s\n", arr[i].name);
            printf("SGPA: %.2f\n", arr[i].SGPA);
            return;
        }
    }

    printf("\nStudent not found.\n");
}

int main()
{
    struct student s[MAX];
    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of students! Enter between 1 and %d.\n", MAX);
        return 0;
    }

    create(s, n);
    display(s, n);
    search(s, n);

    return 0;
}
