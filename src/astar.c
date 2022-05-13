#include <stdio.h>

#include <horus/astar.h>

node_t *astar(node_t *start, node_t *target)
{
    GQueue *closed_list = g_queue_new();
    GQueue *open_list = g_queue_new();

    start->h = node_distance(start, target);
    start->f = start->g + start->h;

    g_queue_insert_sorted(open_list, start, node_compare, NULL);

    while (!g_queue_is_empty(open_list))
    {
        node_t *node = (node_t *)g_queue_peek_head(open_list);

        /* return the first found path */
        // if (node == target)
        //   return node;

        printf("[expanding] <p:%p> <x:%.2f, y:%.2f> <f:%.2f> <g:%.2f> <h:%.2f>\n", (void *)node, node->x, node->y, node->f, node->g, node->h);

        for (size_t i = 0; i < node->neighbors->len; i++)
        {
            node_t *neighbor = node->neighbors->pdata[i];

            f64 total_cost = node->g + node_distance(node, neighbor);

            if (!g_queue_find(closed_list, neighbor) && !g_queue_find(open_list, neighbor))
            {
                neighbor->parent = node;
                neighbor->g = total_cost;
                neighbor->h = node_distance(neighbor, target);
                neighbor->f = neighbor->g + neighbor->h;

                g_queue_insert_sorted(open_list, neighbor, node_compare, NULL);
            }
            else
            {
                if (total_cost < neighbor->g)
                {
                    neighbor->parent = node;
                    neighbor->g = total_cost;
                    neighbor->h = node_distance(neighbor, target);
                    neighbor->f = neighbor->g + neighbor->h;

                    if (g_queue_find(closed_list, neighbor))
                    {
                        g_queue_remove(closed_list, neighbor);
                        g_queue_insert_sorted(open_list, neighbor, node_compare, NULL);
                    }
                }
            }

            printf("|> [neighbor] <p:%p> <x:%.2f, y:%.2f> <f:%.2f> <g:%.2f> <h:%.2f>\n", (void *)neighbor, neighbor->x, neighbor->y, neighbor->f, neighbor->g, neighbor->h);
        }

        printf("\n");

        g_queue_remove(open_list, node);
        g_queue_insert_sorted(closed_list, node, node_compare, NULL);
    }

    g_queue_free(open_list);
    g_queue_free(closed_list);

    return target;
}
