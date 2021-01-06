/* $Id: Exp$
 *
 * dlchess - dlchess is a free chess program
 *
 * Copyright (C) 2004 Gautier Loyaute
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 * 
 * Name of file: $RCSfile$
 */
#include<malloc.h>
#include<stdio.h>

#include<coordinate.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_coordinate(struct _coordinate **freed) {
  free(*freed);
  *freed = NULL;
}

int _internal_get_x_coordinate(const struct _coordinate *src) {
  return src->x;
}

int _internal_get_y_coordinate(const struct _coordinate *src) {
  return src->y;
}

void _internal_set_x_coordinate(struct _coordinate *dest, const int x) {
  dest->x = x;
}

void _internal_set_y_coordinate(struct _coordinate *dest, const int y) {
  dest->y = y;
}

void _internal_set_coordinate(struct _coordinate *dest, const int x, const int y) {
  dest->x = x;
  dest->y = y;
}

unsigned char *_internal_to_string_coordinate(const struct _coordinate *src, unsigned char base) {
  unsigned char *string = NULL;
  
  if((string = (unsigned char *)malloc(sizeof(unsigned char) * 2))) {
    sprintf(string, "%c%d", (base - src->get_x(src)), src->get_y(src));
  }
  return string;
}

void _internal_print_coordinate(const void *src) {
  printf("Coordonnées (%d, %d) \n", ((struct _coordinate *)src)->get_x(src), ((struct _coordinate *)src)->get_y(src));
}

int _internal_compare_coordinate(void *src1, void *src2) {
  struct _coordinate *coordinate1 = (struct _coordinate *)src1;
  struct _coordinate *coordinate2 = (struct _coordinate *)src2;
  
  printf("Valeur comparee (%d, %d) et (%d, %d) \n", coordinate1->x, coordinate1->y, coordinate2->x, coordinate2->y);

  if(coordinate1->x == coordinate2->x && coordinate1->y == coordinate2->y)
    return TRUE;
  return FALSE;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_coordinate
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _coordinate *new_coordinate(const int x, const int y) {
  struct _coordinate *new = NULL;
  
  if((new = (struct _coordinate *)malloc(sizeof(struct _coordinate)))) {
    new->x = x;
    new->y = y;
    new->free_coordinate = _internal_free_coordinate;
    new->get_x = _internal_get_x_coordinate;
    new->get_y = _internal_get_y_coordinate;
    new->set_x = _internal_set_x_coordinate;
    new->set_y = _internal_set_y_coordinate;
    new->set_coordinate = _internal_set_coordinate;
    new->print_coordinate = _internal_print_coordinate;
    new->to_string = _internal_to_string_coordinate;
    new->compare_coordinate = _internal_compare_coordinate;
  }
  return new;
}
