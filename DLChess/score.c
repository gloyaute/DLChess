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

#include<score.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_score(struct _score **freed) {
  free(*freed);
  *freed = NULL;
}

unsigned int _internal_get_score(const struct _score *src) {
  return src->score;
}

void _internal_set_score(struct _score *dest, const unsigned int score) {
  dest->score = score;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_score
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _score *new_score(const unsigned int score) {
  struct _score *new = NULL;
  
  if((new = (struct _score *)malloc(sizeof(struct _score)))) {
    new->score = score;
    new->free_score = _internal_free_score;
    new->set_score = _internal_set_score;
    new->get_score = _internal_get_score;
  }
  return new;
}
