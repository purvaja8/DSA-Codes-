
#include <stdio.h>
#include <limits.h>

#define MAX 20

int main()
{
    int cost[MAX][MAX];
    int visited[MAX] = {0};
    int n, i, j, edges = 0;
    int min, u = -1, v = -1;
    int totalCost = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);

            if (i != j && cost[i][j] == 0)
                cost[i][j] = INT_MAX;
        }
    }

    visited[0] = 1;

    printf("\nEdges in Minimum Spanning Tree:\n");

    while (edges < n - 1)
    {
        min = INT_MAX;
        u = -1;
        v = -1;

        for (i = 0; i < n; i++)
        {
            if (visited[i])
            {
                for (j = 0; j < n; j++)
                {
                    if (!visited[j] && cost[i][j] < min)
                    {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u == -1)
        {
            printf("Graph is disconnected. MST cannot be formed.\n");
            return 1;
        }

        printf("%d - %d : %d\n", u, v, min);

        totalCost += min;
        visited[v] = 1;
        edges++;
    }

    printf("Total cost of MST = %d\n", totalCost);

    return 0;
}
