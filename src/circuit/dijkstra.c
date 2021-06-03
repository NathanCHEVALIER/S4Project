#include <stdlib.h>
#include <stdio.h>
#include "../../libs/map/mapGraph.h"
#include "../../libs/map/list.h"

int choose_min(int *dist, int *m, int len)
{
    int x = -1;
    int mini = len + 2;

    for (int i = 0; i < len; i++)
    {
        if (m[i] == 1 && dist[i] < mini)
        {
            x = i;
            mini = dist[i];
        }
    }

    return x;
}

void dijkstra(struct mgraph *g, int src, int pred[], int dist[])
{
    // Init
    int m[g->order];
    for (int i = 0; i < g->order; i++)
    {
        dist[i] = g->order + 1;
        pred[i] = g->order + 1;
        m[i] = 1;
    }
    dist[src] = 0;
    pred[src] = -1;
    struct list *visited = (struct list*)malloc(sizeof(struct list));
    int n = 1;
    int x = src;

    while (x != -1 && n < g->order)
    {
        list_push(visited, x, -1);
        m[x] = 0;
        struct list *l = g->stations[x]->adjs;

        while (l->next != NULL)
        {
            int y = l->next->data;

            if (dist[x] + 1 < dist[y])
            {
                dist[y] = dist[x] + 1;
                pred[y] = x;
            }

            l = l->next;
        }

        x = choose_min(dist, m, g->order);
        n += 1;
    }

}

struct mgraph* shortest_ride(struct mgraph *g, int src, int dst)
{
    int dist[g->order];
    int pred[g->order];

    dijkstra(g, src, pred, dist);

    /*printf("=== Dist === \n");
    for (int i = 0; i < g->order; i++)
    {
        printf("%d|", dist[i]);
    }
    printf("\n");

    printf("=== Pred === \n");
    for (int i = 0; i < g->order; i++)
    {
        printf("%d|", pred[i]);
    }
    printf("\n");*/

    int len = dist[dst] + 1;
    struct mgraph *ride = mgraph_init(1, len);
    int s = dst;
    
    for (int i = 0; i < len; i++)
    {
        s = pred[s];
        //ride->stations[i]->x = g->stations[s]->x;
        //ride->stations[i]->y = g->stations[s]->y;
    }

    return ride;
}