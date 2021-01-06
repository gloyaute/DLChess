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

#include<queen.h>

#ifndef QUEEN_SCORE
#define QUEEN_SCORE    (1000)
#endif /* QUEEN_SCORE */

/* ------------------> Internal functions <------------------ */

void _internal_free_queen(struct _queen **freed) {
  (*freed)->interface->free_piece(&(*freed)->interface);
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_queen(const struct _queen *src) {
  return src->interface->get_coordinate(src->interface);
}

void _internal_set_coordinate_queen(const struct _queen *dest, struct _coordinate *new) {
  dest->interface->set_coordinate(dest->interface, new);
}

struct _color *_internal_get_color_queen(const struct _queen *src) {
  return src->interface->get_color(src->interface);
}

struct _move *_internal_get_move_queen(const struct _queen *src) {
  return src->interface->get_move(src->interface);
}

int _internal_insert_move_list_queen(const struct _queen *src, struct _slist *moves, const struct _board *board, int x, int y) {
  return src->interface->insert_move_list(moves, board, x, y, src->get_color(src));
}

struct _slist *_internal_get_current_moves_queen(const struct _board *board, const struct _queen *src) {
  struct _slist *moves = NULL;
  int x = src->get_coordinate(src)->get_x(src->get_coordinate(src));
  int y = src->get_coordinate(src)->get_y(src->get_coordinate(src));
  int i;

  printf("Coordonnees de depart de la dame %d %d \n", x, y);

  if((moves = new_slist())) {
    int row = board->get_row(board) - x - 1;
    int col = board->get_col(board) - y - 1;
    int min = (row > col) ? (col) : (row);

    /* On g�n�re les d�placements bas droit --> ok */
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x + i, y + i); ++i);
    
    /* On g�n�re les d�placements haut gauche --> ok */
    min = (x > y) ? (y) : (x);
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x - i, y - i); ++i);

    /* On g�n�re les d�placements haut droit  */
    min = (x > col) ? (col) : (x);
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x - i, y + i); ++i);

    /* On g�n�re les d�placements bas gauche --> ok */
    min = (y > row) ? (row) : (y);
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x + i, y - i); ++i);

    row = board->get_row(board);
    col = board->get_col(board);

    /* On genere les deplacements vers la droite */
    for(i = y + 1; i < col && src->insert_move_list(src, moves, board, x, i); ++i);

    /* On g�n�re les deplacements vers la gauche */
    for(i = 1; i <= y && src->insert_move_list(src, moves, board, x, y - i); ++i);
      
    /* On g�n�re les deplacements vers le haut */
    for(i = x + 1; i < row && src->insert_move_list(src, moves, board, i, y); ++i);

    /* On g�n�re les d�placements vers le bas */
    for(i = 1; i <= x && src->insert_move_list(src, moves, board, x - i, y); ++i);
  }
  return moves;
}

struct _draw *_internal_get_draw_queen(const struct _queen *src) {
  return src->interface->get_draw(src->interface);
}

struct _score *_internal_get_score_queen(const struct _queen *src) {
  return src->interface->get_score(src->interface);
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_queen
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _queen *new_queen(struct _coordinate *coordinate, struct _color *color, struct _draw *draw) {
  struct _queen *new = NULL;
  struct _move *queen = NULL;
  struct _score *score = NULL;

  if((new = (struct _queen *)malloc(sizeof(struct _queen)))) {
    if(!(queen = new_move('q'))) {
      free(new);
      return NULL;
    }
    if(!(score = new_score(QUEEN_SCORE))) {
      queen->free_move(&queen);
      free(new);
      return NULL;
    }
    if(!(new->interface = new_piece(coordinate, color, queen, draw, score))) {
      queen->free_move(&queen);
      score->free_score(&score);
      free(new);
      return NULL;
    }
    new->free_queen = _internal_free_queen;
    new->set_coordinate = _internal_set_coordinate_queen;
    new->get_coordinate = _internal_get_coordinate_queen;
    new->get_color = _internal_get_color_queen;
    new->get_move = _internal_get_move_queen;
    new->get_current_moves = _internal_get_current_moves_queen;
    new->get_draw = _internal_get_draw_queen;
    new->get_score = _internal_get_score_queen;
    new->insert_move_list = _internal_insert_move_list_queen;
  }
  return new;
}
