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

#include<bishop.h>

#ifndef BISHOP_SCORE
#define BISHOP_SCORE   (325)
#endif /* BISHOP_SCORE */

/* ------------------> Internal functions <------------------ */

void _internal_free_bishop(struct _bishop **freed) {
  (*freed)->interface->free_piece(&(*freed)->interface);
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_bishop(const struct _bishop *src) {
  return src->interface->get_coordinate(src->interface);
}

void _internal_set_coordinate_bishop(const struct _bishop *dest, struct _coordinate *new) {
  dest->interface->set_coordinate(dest->interface, new);
}

struct _color *_internal_get_color_bishop(const struct _bishop *src) {
  return src->interface->get_color(src->interface);
}

struct _move *_internal_get_move_bishop(const struct _bishop *src) {
  return src->interface->get_move(src->interface);
}

struct _draw *_internal_get_draw_bishop(const struct _bishop *src) {
  return src->interface->get_draw(src->interface);
}

int _internal_insert_move_list_bishop(const struct _bishop *src, struct _slist *moves, const struct _board *board, int x, int y) {
  return src->interface->insert_move_list(moves, board, x, y, src->get_color(src));
}

struct _slist *_internal_get_current_moves_bishop(const struct _board *board, const struct _bishop *src) {
  struct _slist *moves = NULL;
  int x = src->get_coordinate(src)->get_x(src->get_coordinate(src));
  int y = src->get_coordinate(src)->get_y(src->get_coordinate(src));
  int i;

  if((moves = new_slist())) {
    int row = board->get_row(board) - x;
    int col = board->get_col(board) - y;
    int min = (row > col) ? (col) : (row);

    /* On génére les déplacements bas droit --> ok */
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x + i, y + i); ++i);
    
    /* On génére les déplacements haut gauche --> ok */
    min = (x > y) ? (y) : (x);
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x - i, y - i); ++i);

    /* On génére les déplacements haut droit  */
    min = (x > col) ? (col) : (x);
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x - i, y + i); ++i);

    /* On génére les déplacements bas gauche --> ok */
    min = (y > row) ? (row) : (y);
    for(i = 1; i <= min && src->insert_move_list(src, moves, board, x + i, y - i); ++i);
  }
  return moves;
}

struct _score *_internal_get_score_bishop(const struct _bishop *src) {
  return src->interface->get_score(src->interface);
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_bishop
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _bishop *new_bishop(struct _coordinate *coordinate, struct _color *color, struct _draw *draw) {
  struct _bishop *new = NULL;
  struct _move *bishop = NULL;
  struct _score *score = NULL;

  if((new = (struct _bishop *)malloc(sizeof(struct _bishop)))) {
    if(!(bishop = new_move('b'))) {
      free(new);
      return NULL;
    }
    if(!(score = new_score(BISHOP_SCORE))) {
      bishop->free_move(&bishop);
      free(new);
      return NULL;
    }
    if(!(new->interface = new_piece(coordinate, color, bishop, draw, score))) {
      free(new);
      bishop->free_move(&bishop);
      score->free_score(&score);
      return NULL;
    }
    new->free_bishop = _internal_free_bishop;
    new->set_coordinate = _internal_set_coordinate_bishop;
    new->get_coordinate = _internal_get_coordinate_bishop;
    new->get_color = _internal_get_color_bishop;
    new->get_move = _internal_get_move_bishop;
    new->get_current_moves = _internal_get_current_moves_bishop;
    new->get_draw = _internal_get_draw_bishop;
    new->get_score = _internal_get_score_bishop;
    new->insert_move_list = _internal_insert_move_list_bishop;
  }
  return new;
}
