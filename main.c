#include <stdio.h>
#include <stdlib.h>

typedef struct PATH {
    int x, y;
    struct PATH *prev, *next;
} path;

void add (path **first, path *p, int x, int y)
{
    path *n = calloc(1, sizeof(path));
    n->prev = p;
    n->x = p->x + x;
    n->y = p->y + y;
    (*first)->next = n;
    *first = n;
}

int main()
{
    freopen("map", "r", stdin);
    int n, m, ans = 0;
    scanf("%d %d", &n, &m);
    int a[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    path *first = calloc(1, sizeof(path));
    path *p = first;

    if (a[p->y][p->x]) {
        printf("no solution");
        return 0;
    }
    else
        a[p->y][p->x] = 1;

    for(;;) {
/*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d", a[i][j]);
            }
            putchar('\n');
        }
        putchar('\n');
*/
        int flag = 1;
        #define go(con, row, col)\
        if (con && !a[p->y + row][p->x + col]) {\
            flag = 0;\
            a[p->y + row][p->x + col] = 1;\
            add(&first, p, col, row);\
            if ((first->x == m-1 && first->y == n-1)) break;\
        }

        go(p->x >   0,  0, -1)  // Left
        go(p->y >   0, -1,  0)  // Up
        go(p->x < m-1,  0,  1)  // Right
        go(p->y < n-1,  1,  0)  // Down

        //printf("%p %p %d\n", p, p->next, flag);

        if (flag) {  // blind alley
            if (p->next)  // 還有其他路
                p = p->next;
            else {
                printf("no solution");
                return 0;
            }
        }
        else p = first->prev->next;
    }

    p = first;
    while (p) {  // 數步驟
        p = p->prev;
        ans++;
    }

    printf("ans: %d", ans);
    return 0;
}
