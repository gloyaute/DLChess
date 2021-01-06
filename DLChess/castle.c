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

#include<castle.h>

#ifndef CASTLE_SCORE
#define CASTLE_SCORE   (500)
#endif /* CASTLE_SCORE */

/* ------------------> Internal functions <------------------ */

void _internal_free_castle(struct _castle **freed) {
  (*freed)->interface->free_piece(&(*freed)->interface);
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_castle(const struct _castle *src) {
  return src->interface->get_coordinate(src->interface);
}

void _internal_set_coordinate_castle(const struct _castle *dest, struct _coordinate *new) {
  dest->interface->set_coordinate(dest->interface, new);
}

struct _color *_internal_get_color_castle(const struct _castle *src) {
  return src->interface->get_color(src->interface);
}

struct _move *_internal_get_move_castle(const struct _castle *src) {
  return src->interface->get_move(src->interface);
}

int _internal_insert_move_list_castle(const struct _castle *src, struct _slist *moves, const struct _board *board, int x, int y) {
  return src->interface->insert_move_list(moves, board, x, y, src->get_color(src));
}

struct _slist *_internal_get_current_moves_castle(const struct _board *board, const struct _castle *src) {
  struct _slist *moves = NULL;
  int x = src->get_coordinate(src)->get_x(src->get_coordinate(src));
  int y = src->get_coordinate(src)->get_y(src->get_coordinate(src));
  int i;

  if((moves = new_slist())) {
    int row = board->get_row(board);
    int col = board->get_col(board);

    /* On genere les deplacements vers la droite */
    for(i = y + 1; i < col && src->insert_move_list(src, moves, board, x, i); ++i);
    /* On génére les deplacements vers la gauche */
    for(i = 1; i <= y && src->insert_move_list(src, moves, board, x, y - i); ++i);
    /* On génére les deplacements vers le haut */
    for(i = x + 1; i < row && src->insert_move_list(src, moves, board, i, y); ++i);
    /* On génére les déplacements vers le bas */
    for(i = 1; i <= x && src->insert_move_list(src, moves, board, x - i, y); ++i);
  }
  return moves;
}

struct _draw *_internal_get_draw_castle(const struct _castle *src) {
  return src->interface->get_draw(src->interface);
}

struct _score *_internal_get_score_castle(const struct _castle *src) {
  return src->interface->get_score(src->interface);
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_castle
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _castle *new_castle(struct _coordinate *coordinate, struct _color *color, struct _draw *draw) {
  struct _castle *new = NULL;
  struct _move *castle = NULL;
  struct _score *score = NULL;
 
  if((new = (struct _castle *)malloc(sizeof(struct _castle)))) {
    if(!(castle = new_move('c'))) {
      free(new);
      return NULL;
    }
    if(!(score = new_score(CASTLE_SCORE))) {
      castle->free_move(&castle);
      free(new);
      return NULL;
    }
    if(!(new->interface = new_piece(coordinate, color, castle, draw, score))) {
      castle->free_move(&castle);
      score->free_score(&score);
      free(new);
      return NULL;
    }
    new->free_castle = _internal_free_castle;
    new->set_coordinate = _internal_set_coordinate_castle;
    new->get_coordinate = _internal_get_coordinate_castle;
    new->get_color = _internal_get_color_castle;
    new->get_move = _internal_get_move_castle;
    new->get_current_moves = _internal_get_current_moves_castle;
    new->get_draw = _internal_get_draw_castle;
    new->get_score = _internal_get_score_castle;
    new->insert_move_list = _internal_insert_move_list_castle;
  }
  return new;
}
