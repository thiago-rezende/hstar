#include <stdio.h>

#include <horus/node.h>

node_t *node_new(f64 x, f64 y)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    node->f = 0.0;
    node->g = 0.0;
    node->h = 0.0;

    node->x = x;
    node->y = y;

    node->obstacle = false;

    node->visited = false;

    node->parent = NULL;

    node->neighbors = g_ptr_array_new();

    return node;
}

void node_free(node_t *node)
{
    if (node != NULL)
        g_ptr_array_free(node->neighbors, TRUE);

    free(node);
}

void node_add_connection(node_t *node, node_t *target)
{
    if (node == NULL)
        return;

    g_ptr_array_add(node->neighbors, target);
}

f64 node_distance(node_t *a, node_t *b)
{
    if (a == NULL || b == NULL)
        return 0;

    return sqrt(pow((a->x - b->x), 2) + pow(a->y - b->y, 2));
}

i32 node_compare(const void *a, const void *b, void *user_data)
{
    (void)user_data; /* unused */

    node_t *node_a = (node_t *)a;
    node_t *node_b = (node_t *)b;

    if (node_a->f < node_b->f)
        return -1;

    if (node_a->f > node_b->f)
        return 1;

    return 0;
}

static void __node_print_path_recursive(node_t *node)
{
    if (node == NULL)
        return;

    __node_print_path_recursive(node->parent);

    printf("[node] <p:%p> <x:%.2f, y:%.2f> <f:%.2f> <g:%.2f> <h:%.2f>\n", (void *)node, node->x, node->y, node->f, node->g, node->h);
}

void node_print_path(node_t *node)
{
    printf("[path]\n");
    __node_print_path_recursive(node);
    printf("\n");
}
