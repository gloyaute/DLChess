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

#include<draw.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_draw(struct _draw **freed) {
  free(*freed);
  *freed = NULL;
}

void _internal_set_draw(struct _draw *dest, unsigned char new) {
  dest->draw = new;
}

unsigned char _internal_get_draw(struct _draw *src) {
  return src->draw;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_draw
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _draw *new_draw(unsigned char draw) {
  struct _draw *new = NULL;
  
  if((new = (struct _draw *)malloc(sizeof(struct _draw)))) {
    new->draw = draw;
    new->free_draw = _internal_free_draw;
    new->set_draw = _internal_set_draw;
    new->get_draw = _internal_get_draw;
  }
  return new;
}
