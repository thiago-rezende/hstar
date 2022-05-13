/**
 * Node structure
 *
 * @file       node.h
 * @brief      Node struture used in a graph for the A* algorithm
 * @maintainer Thiago Rezende <thiago.manoel.rezende@gmail.com>
 */

#ifndef HORUS_NODE_H
#define HORUS_NODE_H

#include <math.h>
#include <stddef.h>

#include <horus/core/types.h>

#include <glib.h>

/**
 * Node structure
 */
typedef struct node
{
  /* node position */
  f64 x;
  f64 y;

  /* f(x) = g(x) + h(x) */
  f64 f;
  f64 g;
  f64 h;

  /* parent in found path */
  struct node *parent;

  /* node neighbors */
  GPtrArray *neighbors;
} node_t;

/**
 * @brief Allocates a new node with a given position
 *
 * @param x coordinate
 * @param y coordinate
 * @return node_t* node
 */
node_t *node_new(f64 x, f64 y);

/**
 * @brief Deallocates a node
 *
 * @param node node
 */
void node_free(node_t *node);

/**
 * @brief Adds a new connection to a node
 *
 * @param node node
 * @param target target
 */
void node_add_connection(node_t *node, node_t *target);

/**
 * @brief Calculate the euclidean distance between two nodes
 *
 * @param a node
 * @param b node
 * @return f64 distance
 */
f64 node_distance(node_t *a, node_t *b);

/**
 * @brief Compare two nodes based on their heuristic functions
 *
 * Returns -1 if a's heuristic function is better
 * Returns 0 if a's heuristic function is equal
 * Returns 1 if a's heuristic function is greater
 *
 * @param a node
 * @param b node
 * @param user_data unused
 * @return i32 result
 */
i32 node_compare(const void *a, const void *b, void *user_data);

/**
 * @brief Print the path to a given target if found
 *
 * @param target target
 */
void node_print_path(node_t *target);

#endif // !HORUS_NODE_H
