
#include <stdio.h>

void BubbleSort(int arr[], int n);
void InsertionSort(int arr[], int n);
void QuickSort(int arr[], int low, int high);
int Partition(int arr[], int low, int high);
void MergeSort(int arr[], int low, int high);
void Merge(int arr[], int low, int mid, int high);

int main()
{
    int original[5], arr[5];
    int n = 5;
    int choice, i;

    printf("Enter 5 elements:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &original[i]);
    }

    do
    {
        printf("\n\nChoose Sorting Method:\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Quick Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        /* Copy original array before every sorting operation */
        for (i = 0; i < n; i++)
        {
            arr[i] = original[i];
        }

        switch (choice)
        {
            case 1:
                BubbleSort(arr, n);
                printf("\nBubble Sort: ");
                break;

            case 2:
                InsertionSort(arr, n);
                printf("\nInsertion Sort: ");
                break;

            case 3:
                QuickSort(arr, 0, n - 1);
                printf("\nQuick Sort: ");
                break;

            case 4:
                MergeSort(arr, 0, n - 1);
                printf("\nMerge Sort: ");
                break;

            case 5:
                printf("\nExiting program.\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
                continue;
        }

        if (choice >= 1 && choice <= 4)
        {
            for (i = 0; i < n; i++)
            {
                printf("%d ", arr[i]);
            }
        }

    } while (choice != 5);

    return 0;
}

void BubbleSort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void InsertionSort(int arr[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void QuickSort(int arr[], int low, int high)
{
    int p;

    if (low < high)
    {
        p = Partition(arr, low, high);
        QuickSort(arr, low, p - 1);
        QuickSort(arr, p + 1, high);
    }
}

void MergeSort(int arr[], int low, int high)
{
    int mid;

    if (low < high)
    {
        mid = low + (high - low) / 2;

        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);
        Merge(arr, low, mid, high);
    }
}

void Merge(int arr[], int low, int mid, int high)
{
    int SA[5];
    int i, j, k;

    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
        {
            SA[k] = arr[i];
            i++;
        }
        else
        {
            SA[k] = arr[j];
            j++;
        }

        k++;
    }

    while (i <= mid)
    {
        SA[k] = arr[i];
        i++;
        k++;
    }

    while (j <= high)
    {
        SA[k] = arr[j];
        j++;
        k++;
    }

    for (i = low; i <= high; i++)
    {
        arr[i] = SA[i];
    }
}
