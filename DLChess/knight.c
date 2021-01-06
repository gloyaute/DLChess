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

#include<knight.h>

#ifndef KNIGHT_SCORE
#define KNIGHT_SCORE   (325)
#endif /* KNIGHT_SCORE */

/* ------------------> Internal functions <------------------ */

void _internal_free_knight(struct _knight **freed) {
  (*freed)->interface->free_piece(&(*freed)->interface);
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_knight(const struct _knight *src) {
  return src->interface->get_coordinate(src->interface);
}

void _internal_set_coordinate_knight(const struct _knight *dest, struct _coordinate *new) {
  dest->interface->set_coordinate(dest->interface, new);
}

struct _color *_internal_get_color_knight(const struct _knight *src) {
  return src->interface->get_color(src->interface);
}

struct _move *_internal_get_move_knight(const struct _knight *src) {
  return src->interface->get_move(src->interface);
}

int _internal_insert_move_list_knight(const struct _knight *src, struct _slist *moves, const struct _board *board, int x, int y) {
  return src->interface->insert_move_list(moves, board, x, y, src->get_color(src));
}

struct _slist *_internal_get_current_moves_knight(const struct _board *board, const struct _knight *src) {
  struct _slist *moves = NULL;
  int x = src->get_coordinate(src)->get_x(src->get_coordinate(src));
  int y = src->get_coordinate(src)->get_y(src->get_coordinate(src));


  if((moves = new_slist())) {
    /* On génére le déplacement vers (2, 1) */
    src->insert_move_list(src, moves, board, x + 2, y + 1);
    /* On génére le déplacement vers (2, -1) */
    src->insert_move_list(src, moves, board, x + 2, y - 1);
    /* On génére le déplacement vers (-2, 1) */
    src->insert_move_list(src, moves, board, x - 2, y + 1);
    /* On génére le déplacement vers (-2, -1) */
    src->insert_move_list(src, moves, board, x - 2, y - 1);
    /* On génére le déplacement vers le (1, 2) */
    src->insert_move_list(src, moves, board, x + 1, y + 2);
    /* On génére le déplacement vers le (-1, 2) */
    src->insert_move_list(src, moves, board, x - 1, y + 2);
    /* On génére le déplacement vers le (1, -2) */
    src->insert_move_list(src, moves, board, x + 1, y - 2);
    /* On génére le déplacement vers le (-1, -2) */
    src->insert_move_list(src, moves, board, x - 1, y - 2);
  }
  return moves;
}

struct _draw *_internal_get_draw_knight(const struct _knight *src) {
  return src->interface->get_draw(src->interface);
}

struct _score *_internal_get_score_knight(const struct _knight *src) {
  return src->interface->get_score(src->interface);
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_knight
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _knight *new_knight(struct _coordinate *coordinate, struct _color *color, struct _draw *draw) {
  struct _knight *new = NULL;
  struct _move *knight = NULL;
  struct _score *score = NULL;
 
  if((new = (struct _knight *)malloc(sizeof(struct _knight)))) {
    if(!(knight = new_move('n'))) {
      free(new);
      return NULL;
    }
    if(!(score = new_score(KNIGHT_SCORE))) {
      knight->free_move(&knight);
      free(new);
      return NULL;
    }
    if(!(new->interface = new_piece(coordinate, color, knight, draw, score))) {
      free(new);
      knight->free_move(&knight);
      score->free_score(&score);
      return NULL;
    }
    new->free_knight = _internal_free_knight;
    new->set_coordinate = _internal_set_coordinate_knight;
    new->get_coordinate = _internal_get_coordinate_knight;
    new->get_color = _internal_get_color_knight;
    new->get_move = _internal_get_move_knight;
    new->get_current_moves = _internal_get_current_moves_knight;
    new->get_draw = _internal_get_draw_knight;
    new->get_score = _internal_get_score_knight;
    new->insert_move_list = _internal_insert_move_list_knight;
  }
  return new;
}
