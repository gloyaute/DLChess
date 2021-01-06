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

#include<color.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_color(struct _color **freed) {
  free(*freed);
  *freed = NULL;
}

unsigned char _internal_get_color_color(const struct _color *src) {
  return src->color;
}

void _internal_set_color_color(struct _color *dest, const unsigned char color) {
  dest->color = color;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_color
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _color *new_color(const unsigned char color) {
  struct _color *new = NULL;
  
  if((new = (struct _color *)malloc(sizeof(struct _color)))) {
    new->color = color;
    new->free_color = _internal_free_color;
    new->set_color = _internal_set_color_color;
    new->get_color = _internal_get_color_color;
  }
  return new;
}
