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

#include<king.h>

#ifndef KING_SCORE
#define KING_SCORE     (10000)
#endif /* KING_SCORE */

/* ------------------> Internal functions <------------------ */

void _internal_free_king(struct _king **freed) {
  (*freed)->interface->free_piece(&(*freed)->interface);
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_king(const struct _king *src) {
  return src->interface->get_coordinate(src->interface);
}

void _internal_set_coordinate_king(const struct _king *dest, struct _coordinate *new) {
  dest->interface->set_coordinate(dest->interface, new);
}

struct _color *_internal_get_color_king(const struct _king *src) {
  return src->interface->get_color(src->interface);
}

struct _move *_internal_get_move_king(const struct _king *src) {
  return src->interface->get_move(src->interface);
}

int _internal_insert_move_list_king(const struct _king *src, struct _slist *moves, const struct _board *board, int x, int y) {
  return src->interface->insert_move_list(moves, board, x, y, src->get_color(src));
}

struct _slist *_internal_get_current_moves_king(const struct _board *board, const struct _king *src) {
  struct _slist *moves = NULL;
  int x = src->get_coordinate(src)->get_x(src->get_coordinate(src));
  int y = src->get_coordinate(src)->get_y(src->get_coordinate(src));

  if((moves = new_slist())) {
    /* On génére le déplacement vers la droite */
    src->insert_move_list(src, moves, board, x, y + 1);
    /* On génére le déplacement vers la gauche */
    src->insert_move_list(src, moves, board, x, y - 1);
    /* On génére le déplacement vers le haut */
    src->insert_move_list(src, moves, board, x + 1, y);
    /* On génére le déplacement vers le bas */
    src->insert_move_list(src, moves, board, x - 1, y);
    /* On génére le déplacement vers le haut gauche */
    src->insert_move_list(src, moves, board, x + 1, y - 1);
    /* On génére le déplacement vers le haut droit */
    src->insert_move_list(src, moves, board, x + 1, y + 1);
    /* On génére le déplacement vers le bas gauche */
    src->insert_move_list(src, moves, board, x - 1, y - 1);
    /* On génére le déplacement vers le bas droit */
    src->insert_move_list(src, moves, board, x - 1, y + 1);
  }
  return moves;
}

struct _draw *_internal_get_draw_king(const struct _king *src) {
  return src->interface->get_draw(src->interface);
}

struct _score *_internal_get_score_king(const struct _king *src) {
  return src->interface->get_score(src->interface);
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_king
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _king *new_king(struct _coordinate *coordinate, struct _color *color, struct _draw *draw) {
  struct _king *new = NULL;
  struct _move *king = NULL;
  struct _score *score = NULL;
 
  if((new = (struct _king *)malloc(sizeof(struct _king)))) {
    if(!(king = new_move('k'))) {
      free(new);
      return NULL;
    }
    if(!(score = new_score(KING_SCORE))) {
      king->free_move(&king);
    }
    if(!(new->interface = new_piece(coordinate, color, king, draw, score))) {
      king->free_move(&king);
      score->free_score(&score);
      free(new);
      return NULL;
    }
    new->free_king = _internal_free_king;
    new->set_coordinate = _internal_set_coordinate_king;
    new->get_coordinate = _internal_get_coordinate_king;
    new->get_color = _internal_get_color_king;
    new->get_move = _internal_get_move_king;
    new->get_current_moves = _internal_get_current_moves_king;
    new->get_draw = _internal_get_draw_king;
    new->get_score = _internal_get_score_king;
    new->insert_move_list = _internal_insert_move_list_king;
  }
  return new;
}
