/**
 * A* algorithm visualization
 *
 * @file    visualization.c
 * @author  Thiago Rezende (thiago.manoel.rezende@gmail.com)
 * @brief   A* algorithm visualization using raylib
 * @version 0.1
 * @date    2022-05-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>

#include <horus/horus.h>
#include <horus/astar.h>

#include <raylib.h>

#include <glib.h>

/* Map info */
const u8 map_width = 30;
const u8 map_height = 17;

/* Window info */
const u16 window_width = 1280;
const u16 window_height = 730;

/* Node info */
const u16 node_size = 42;
const u16 node_border = 20;

/* Graph */
GPtrArray *graph;

/* Graph utils */
GPtrArray *graph_new();
void graph_reset(GPtrArray *graph);
void graph_free(GPtrArray *graph);

/* Drawing utils */
void draw_lines(GPtrArray *graph, Color color);
void draw_nodes(GPtrArray *graph, Color color, Color visited_color, Color obstacle_color);
void draw_path(node_t *start, node_t *target, Color start_color, Color target_color, Color path_color);

int main(void)
{
    printf("[HStar.Visualization v1.0.0]\n");

    /* Graph setup */
    graph = graph_new();
    node_t *start = graph->pdata[(map_height / 2) * map_width + 1];
    node_t *target = graph->pdata[(map_height / 2) * map_width + map_width - 2];

    /* Window setup */
    InitWindow(window_width, window_height, "[HStar.Visualization v1.0.0]");

    SetTargetFPS(60);

    /* Initial A* solve */
    astar(start, target);

    /* Main loop */
    while (!WindowShouldClose())
    {
        /* Update */
        Vector2 mouse_position = GetMousePosition();
        u32 seleected_node_x = mouse_position.x / node_size;
        u32 seleected_node_y = mouse_position.y / node_size;

        /* Mouse interaction */
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (seleected_node_x >= 0 && seleected_node_x < map_width)
                if (seleected_node_y >= 0 && seleected_node_y < map_height)
                {
                    node_t *node = (node_t *)graph->pdata[seleected_node_y * map_width + seleected_node_x];

                    if (IsKeyDown(KEY_LEFT_SHIFT))
                        start = node;
                    else if (IsKeyDown(KEY_LEFT_CONTROL))
                        target = node;
                    else
                        node->obstacle = !node->obstacle;

                    graph_reset(graph);
                    astar(start, target);
                }
        }

        /* Draw */
        BeginDrawing();

        ClearBackground(RAYWHITE);

        /* Draw lines */
        draw_lines(graph, GRAY);

        /* Draw nodes */
        draw_nodes(graph, LIGHTGRAY, GRAY, BLUE);

        /* Draw path */
        draw_path(start, target, GREEN, RED, ORANGE);

        EndDrawing();
    }

    /* Graph teardown */
    graph_free(graph);

    /* Window teardown */
    CloseWindow();

    return 0;
}

GPtrArray *graph_new()
{
    GPtrArray *graph = g_ptr_array_sized_new(map_width * map_height);
    g_ptr_array_set_free_func(graph, (GDestroyNotify)node_free);
    for (size_t y = 0; y < map_height; y++)
        for (size_t x = 0; x < map_width; x++)
            g_ptr_array_add(graph, node_new(x, y));

    for (int x = 0; x < map_width; x++)
    {
        for (int y = 0; y < map_height; y++)
        {
            node_t *node = g_ptr_array_index(graph, y * map_width + x);
            if (y > 0)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y - 1) * map_width + (x + 0)));
            if (y < map_height - 1)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y + 1) * map_width + (x + 0)));
            if (x > 0)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y + 0) * map_width + (x - 1)));
            if (x < map_width - 1)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y + 0) * map_width + (x + 1)));

            /* Diagonals */
            if (y > 0 && x > 0)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y - 1) * map_width + (x - 1)));
            if (y < map_height - 1 && x > 0)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y + 1) * map_width + (x - 1)));
            if (y > 0 && x < map_width - 1)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y - 1) * map_width + (x + 1)));
            if (y < map_height - 1 && x < map_width - 1)
                g_ptr_array_add(node->neighbors, g_ptr_array_index(graph, (y + 1) * map_width + (x + 1)));
        }
    }

    return graph;
}

void graph_reset(GPtrArray *graph)
{
    for (size_t i = 0; i < graph->len; i++)
    {
        node_t *node = (node_t *)graph->pdata[i];

        node->f = 0.0;
        node->g = 0.0;
        node->h = 0.0;

        node->visited = false;

        node->parent = NULL;
    }
}

void graph_free(GPtrArray *graph)
{
    g_ptr_array_free(graph, TRUE);
}

void draw_lines(GPtrArray *graph, Color color)
{
    for (size_t i = 0; i < graph->len; i++)
    {
        node_t *node = (node_t *)graph->pdata[i];
        node_t **neighbors = (node_t **)node->neighbors->pdata;
        size_t length = node->neighbors->len;

        for (size_t i = 0; i < length; i++)
            DrawLineEx((Vector2){node->x * node_size + node_size / 1.4, node->y * node_size + node_size / 1.4},
                       (Vector2){neighbors[i]->x * node_size + node_size / 1.4, neighbors[i]->y * node_size + node_size / 1.4}, 1.0f, color);
    }
}

void draw_nodes(GPtrArray *graph, Color color, Color visited_color, Color obstacle_color)
{
    for (size_t i = 0; i < graph->len; i++)
    {
        node_t *node = (node_t *)graph->pdata[i];
        if (node->obstacle)
        {
            DrawRectangle(node->x * node_size + node_border, node->y * node_size + node_border, node_size - node_border, node_size - node_border, obstacle_color);
            continue;
        }

        if (node->visited)
        {
            DrawRectangle(node->x * node_size + node_border, node->y * node_size + node_border, node_size - node_border, node_size - node_border, visited_color);
            continue;
        }

        DrawRectangle(node->x * node_size + node_border, node->y * node_size + node_border, node_size - node_border, node_size - node_border, color);
    }
}

void draw_path(node_t *start, node_t *target, Color start_color, Color target_color, Color path_color)
{
    DrawRectangle(start->x * node_size + node_border, start->y * node_size + node_border, node_size - node_border, node_size - node_border, start_color);
    DrawRectangle(target->x * node_size + node_border, target->y * node_size + node_border, node_size - node_border, node_size - node_border, target_color);

    node_t *node = target;

    while (node->parent)
    {
        DrawLineEx((Vector2){node->x * node_size + node_size / 1.4, node->y * node_size + node_size / 1.4},
                   (Vector2){node->parent->x * node_size + node_size / 1.4, node->parent->y * node_size + node_size / 1.4}, 5.0f, path_color);

        node = node->parent;
    }
}
