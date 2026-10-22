#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32
#define ROUNDS 6
#define NAME_LEN 100

typedef struct Team {
    int id;
    char name[NAME_LEN];
    struct Team *next;
} Team;

typedef struct Match {
    int t1, t2, winner;
    int done; /* 0 = pending, 1 = completed */
} Match;

Team *head = NULL;
Match m[ROUNDS][MAX] = {0};
int count[ROUNDS] = {0};
int total = 0, roundNo = 0;
int q[MAX], front = 0, rear = 0;
int started = 0, finished = 0;

/* Remove leftover characters from the input line. */
void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard */
    }
}

/* Read a line of text and remove its trailing newline. */
void readLine(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

Team *findTeam(int id) {
    Team *t = head;

    while (t != NULL) {
        if (t->id == id) {
            return t;
        }
        t = t->next;
    }

    return NULL;
}

void registerTeam(void) {
    int id;
    char name[NAME_LEN];
    Team *t, *p;

    if (started || total == MAX) {
        printf("Registration closed or full!\n");
        return;
    }

    printf("Enter Team ID: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid or duplicate ID!\n");
        return;
    }
    clearInputBuffer();

    if (id <= 0 || findTeam(id) != NULL) {
        printf("Invalid or duplicate ID!\n");
        return;
    }

    printf("Enter Team Name: ");
    readLine(name, sizeof(name));

    if (name[0] == '\0') {
        printf("Team name cannot be empty!\n");
        return;
    }

    t = (Team *)malloc(sizeof(Team));
    if (t == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    t->id = id;
    strncpy(t->name, name, NAME_LEN - 1);
    t->name[NAME_LEN - 1] = '\0';
    t->next = NULL;

    if (head == NULL) {
        head = t;
    } else {
        p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = t;
    }

    total++;
    printf("Team registered!\n");
}

void displayTeams(void) {
    Team *t = head;

    if (t == NULL) {
        printf("No teams registered.\n");
        return;
    }

    while (t != NULL) {
        printf("%d - %s\n", t->id, t->name);
        t = t->next;
    }
}

void displaySchedule(void) {
    int i;
    Team *team1, *team2, *winner;

    if (!started) {
        printf("Start tournament first.\n");
        return;
    }

    if (finished) {
        printf("Tournament finished.\n");
        return;
    }

    printf("\n--- Round %d ---\n", roundNo + 1);

    for (i = 0; i < count[roundNo]; i++) {
        team1 = findTeam(m[roundNo][i].t1);

        printf("Match %d: ", i + 1);
        if (team1 != NULL) {
            printf("%s", team1->name);
        } else {
            printf("Unknown Team");
        }

        printf(" vs ");

        if (m[roundNo][i].t2 == 0) {
            printf("BYE");
        } else {
            team2 = findTeam(m[roundNo][i].t2);
            if (team2 != NULL) {
                printf("%s", team2->name);
            } else {
                printf("Unknown Team");
            }
        }

        if (m[roundNo][i].done) {
            winner = findTeam(m[roundNo][i].winner);
            printf(" | Winner: %s",
                   winner != NULL ? winner->name : "Unknown Team");
        } else {
            printf(" | Pending");
        }

        printf("\n");
    }
}

void advanceRound(void) {
    int id, next, w, i;
    Team *champion;

    if (count[roundNo] == 1) {
        id = m[roundNo][0].winner;
        champion = findTeam(id);

        printf("\n*** TOURNAMENT CHAMPION ***\n");
        printf("Team ID: %d\n", id);
        printf("Team Name: %s\n",
               champion != NULL ? champion->name : "Unknown Team");

        finished = 1;
        return;
    }

    next = roundNo + 1;
    w = 0;

    for (i = 0; i < count[roundNo]; i++) {
        id = m[roundNo][i].winner;

        if (w % 2 == 0) {
            m[next][w / 2].t1 = id;
            m[next][w / 2].t2 = 0;
            m[next][w / 2].winner = 0;
            m[next][w / 2].done = 0;
        } else {
            m[next][w / 2].t2 = id;
        }

        w++;
    }

    count[next] = w / 2;
    roundNo = next;

    printf("\nNext round generated!\n");
    displaySchedule();
}

void startTournament(void) {
    Team *t;
    int size, byes, i, id, a, b, all;

    if (started || total < 2) {
        printf("Register at least 2 teams first!\n");
        return;
    }

    started = 1;
    front = 0;
    rear = 0;

    t = head;
    while (t != NULL) {
        q[rear++] = t->id;
        t = t->next;
    }

    size = 1;
    while (size < total) {
        size *= 2;
    }

    byes = size - total;
    count[0] = size / 2;

    for (i = 0; i < byes; i++) {
        id = q[front++];
        m[0][i].t1 = id;
        m[0][i].t2 = 0;
        m[0][i].winner = id;
        m[0][i].done = 1;
    }

    for (i = byes; i < count[0]; i++) {
        a = q[front++];
        b = q[front++];

        m[0][i].t1 = a;
        m[0][i].t2 = b;
        m[0][i].winner = 0;
        m[0][i].done = 0;
    }

    printf("Schedule generated!\n");
    displaySchedule();

    all = 1;
    for (i = 0; i < count[0]; i++) {
        if (!m[0][i].done) {
            all = 0;
        }
    }

    if (all) {
        advanceRound();
    }
}

void enterWinner(void) {
    int n, id, all, i;
    Match *p;
    Team *winner;

    if (!started || finished) {
        printf("Tournament is not active.\n");
        return;
    }

    displaySchedule();

    printf("Enter match number and winning Team ID: ");
    if (scanf("%d %d", &n, &id) != 2) {
        clearInputBuffer();
        printf("Invalid input!\n");
        return;
    }
    clearInputBuffer();

    if (n < 1 || n > count[roundNo] || m[roundNo][n - 1].done) {
        printf("Invalid match or match completed!\n");
        return;
    }

    p = &m[roundNo][n - 1];

    if (id != p->t1 && id != p->t2) {
        printf("Winner must belong to this match!\n");
        return;
    }

    p->winner = id;
    p->done = 1;

    winner = findTeam(id);
    printf("Winner: %s\n", winner != NULL ? winner->name : "Unknown Team");

    all = 1;
    for (i = 0; i < count[roundNo]; i++) {
        if (!m[roundNo][i].done) {
            all = 0;
        }
    }

    if (all) {
        advanceRound();
    }
}

int main(void) {
    int choice;

    do {
        printf("\n===== CRICKET TOURNAMENT =====\n");
        printf("1. Register Team\n");
        printf("2. Display Teams\n");
        printf("3. Generate Schedule\n");
        printf("4. View Schedule\n");
        printf("5. Enter Match Winner\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input!\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                registerTeam();
                break;
            case 2:
                displayTeams();
                break;
            case 3:
                startTournament();
                break;
            case 4:
                displaySchedule();
                break;
            case 5:
                enterWinner();
                break;
            case 0:
                printf("Program ended.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    while (head != NULL) {
        Team *t = head;
        head = head->next;
        free(t);
    }

    return 0;
}