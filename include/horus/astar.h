/**
 * A* algorithm
 *
 * @file    astar.h
 * @brief   A* algorithm
 * @author  Thiago Rezende (thiago.manoel.rezende@gmail.com)
 */

#ifndef HORUS_ASTAR_H
#define HORUS_ASTAR_H

#include <stddef.h>

#include <horus/node.h>

node_t *astar(node_t *start, node_t *target);

#endif // !HORUS_ASTAR_H
