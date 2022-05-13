/**
 * @file    main.c
 * @author  Thiago Rezende (thiago.manoel.rezende@gmail.com)
 * @brief   Simple A* algorithm implemantation
 * @version 0.1
 * @date    2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>

#include <horus/horus.h>
#include <horus/astar.h>

int main(void)
{
  printf("[HStar v1.0.0]\n");

  /* start setup */
  node_t *start = node_new(0, 0);
  start->g = 0;

  /* target setup */
  node_t *target = node_new(10, 10);

  /* nodes setup */
  node_t *n1, *n2, *n3, *n4, *n5;

  n1 = node_new(2, 5);
  n2 = node_new(3, 0);
  n3 = node_new(5, 4);
  n4 = node_new(7, 8);
  n5 = node_new(7, 2);

  /* graph setup */
  node_add_connection(start, n1);
  node_add_connection(start, n2);
  node_add_connection(start, n3);

  node_add_connection(n1, n3);

  node_add_connection(n2, n4);

  node_add_connection(n3, n4);
  node_add_connection(n3, n5);

  node_add_connection(n4, target);

  node_add_connection(n5, target);

  /* A* algorithm */
  node_t *reverse_path = astar(start, target);

  printf("\n");

  node_print_path(reverse_path);

  /* teardown */
  node_free(n1);
  node_free(n2);
  node_free(n3);
  node_free(n4);
  node_free(n5);

  node_free(start);
  node_free(target);

  return 0;
}
