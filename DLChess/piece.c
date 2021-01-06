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

#include<piece.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_piece(struct _piece **freed) {
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_piece(const struct _piece *src) {
  return src->coordinate;
}

void _internal_set_coordinate_piece(struct _piece *dest, struct _coordinate *coordinate) {
  dest->coordinate->set_coordinate(dest->coordinate, coordinate->get_x(coordinate), coordinate->get_y(coordinate));
}

struct _color *_internal_get_color_piece(const struct _piece *src) {
  return src->color;
}

void _internal_set_color_piece(struct _piece *dest, struct _color *new) {
  dest->color = new;
}

struct _move *_internal_get_move_piece(const struct _piece *src) {
  return src->move;
}

void _internal_set_move_piece(struct _piece *dest, struct _move *new) {
  dest->move = new;
}

void _internal_set_draw_piece(struct _piece *dest, struct _draw *new) {
  dest->draw = new;
}

struct _draw *_internal_get_draw_piece(const struct _piece *src) {
  return src->draw;
}

unsigned char _internal_draw_piece(const struct _piece *src) {
  return src->draw->get_draw(src->draw);
}

struct _slist *_internal_get_current_moves_piece(const struct _board *board, const struct _piece *src) {
  return NULL;
}

struct _score *_internal_get_score_piece(const struct _piece *src) {
  return src->score;
}

void _internal_set_score_piece(struct _piece *dest, struct _score *new) {
  dest->score = new;
}

int _internal_insert_move_list_piece(struct _slist *moves, const struct _board *board, int x, int y, struct _color *color) {
  struct _coordinate *coordinate = NULL;

  if((coordinate = new_coordinate(x, y))) {
    if(!(board->inside_board(board, coordinate)))
      return FALSE;

    if((board->occuped_by_another_piece(board, coordinate))) {
      if((board->occuped_by_another_color(board, coordinate, color))) {
	printf("prise -->  %d %d \n", x, y);
	if(board->inside_board(board, coordinate))
	  moves->insert_top(moves, coordinate, coordinate->print_coordinate);
	return FALSE;
      }
      return FALSE;
    }
    if(board->inside_board(board, coordinate))
      moves->insert_top(moves, coordinate, coordinate->print_coordinate);
  }
  return TRUE;
}

void _internal_print_piece(const void *data) {
  printf("%c", ((struct _piece *)data)->draw_piece((struct _piece *)data));
}

int _internal_compare_piece(void *comp1, void *comp2) {
  struct _piece *piece1 = (struct _piece *)comp1;
  struct _piece *piece2 = (struct _piece *)comp2;
  int equals = FALSE;

  int i = piece1->coordinate->compare_coordinate(piece1->coordinate, piece2->coordinate);
  if(!i)
    return piece1->score->get_score(piece1->score) == piece2->score->get_score(piece2->score);
  return equals;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_piece
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _piece *new_piece(struct _coordinate *coordinate, struct _color *color, struct _move *move, struct _draw *draw, struct _score *score) {
  struct _piece *new = NULL;
  
  if((new = (struct _piece *)malloc(sizeof(struct _piece)))) {
    new->free_piece = _internal_free_piece;
    new->set_coordinate = _internal_set_coordinate_piece;
    new->get_coordinate = _internal_get_coordinate_piece;
    if(!(new->coordinate = new_coordinate(coordinate->get_x(coordinate), coordinate->get_y(coordinate)))) {
      new->free_piece(&new);
      return NULL;
    }
    new->set_color = _internal_set_color_piece;
    new->get_color = _internal_get_color_piece;
    new->set_color(new, color);
    new->get_move = _internal_get_move_piece;
    new->set_move = _internal_set_move_piece;
    new->set_move(new, move);
    new->get_current_moves = _internal_get_current_moves_piece;
    new->set_draw = _internal_set_draw_piece;
    new->get_draw = _internal_get_draw_piece;
    new->set_draw(new, draw);
    new->draw_piece = _internal_draw_piece;
    new->get_score = _internal_get_score_piece;
    new->set_score = _internal_set_score_piece;
    new->set_score(new, score);
    new->insert_move_list = _internal_insert_move_list_piece;
    new->print_piece = _internal_print_piece;
    new->compare_piece = _internal_compare_piece;
  }
  return new;
}
