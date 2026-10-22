
#include <stdio.h>

int BS(int arr[], int l, int r, int target);

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target, result;

    printf("Enter target number: ");
    scanf("%d", &target);

    result = BS(arr, 0, n - 1, target);

    if (result != -1)
    {
        printf("Target found at index %d\n", result);
    }
    else
    {
        printf("Target is not found\n");
    }

    return 0;
}

int BS(int arr[], int l, int r, int target)
{
    int mid;

    if (l > r)
        return -1;

    mid = l + (r - l) / 2;

    if (arr[mid] == target)
        return mid;
    else if (arr[mid] > target)
        return BS(arr, l, mid - 1, target);
    else
        return BS(arr, mid + 1, r, target);
}
