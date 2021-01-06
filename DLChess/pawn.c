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

#include<pawn.h>

#include<slist.h>

#ifndef PAWN_SCORE
#define PAWN_SCORE     (100)
#endif /* PAWN_SCORE */

/* ------------------> Internal functions <------------------ */

void _internal_free_pawn(struct _pawn **freed) {
  (*freed)->interface->free_piece(&(*freed)->interface);
  free(*freed);
  *freed = NULL;
}

struct _coordinate *_internal_get_coordinate_pawn(const struct _pawn *src) {
  return src->interface->get_coordinate(src->interface);
}

void _internal_set_coordinate_pawn(const struct _pawn *dest, struct _coordinate *new) {
  dest->interface->set_coordinate(dest->interface, new);
}

struct _color *_internal_get_color_pawn(const struct _pawn *src) {
  return src->interface->get_color(src->interface);
}

struct _move *_internal_get_move_pawn(const struct _pawn *src) {
  return src->interface->get_move(src->interface);
}

int _internal_insert_move_list_pawn(const struct _pawn *src, struct _slist *moves, const struct _board *board, int x, int y) {
  struct _coordinate *coordinate = NULL;

  if((coordinate = new_coordinate(x, y))) {
    if(board->inside_board(board, coordinate)) {
      moves->insert_top(moves, coordinate, coordinate->print_coordinate);
      return TRUE;
    }
  }
  return FALSE;
}

struct _slist *_internal_get_current_moves_pawn(const struct _board *board, const struct _pawn *src) {
  struct _slist *moves = NULL;
  struct _coordinate *coordinate = NULL;
  int x = src->get_coordinate(src)->get_x(src->get_coordinate(src));
  int y = src->get_coordinate(src)->get_y(src->get_coordinate(src));
  unsigned char pawn_color = src->get_color(src)->get_color(src->get_color(src));

  if((moves = new_slist())) {
    if(!(coordinate = new_coordinate(-1, -1))) {
      moves->free_slist(&moves);
      return NULL;
    }

    switch(pawn_color) {
    case 'w':
      coordinate->set_coordinate(coordinate, x - 1, y);
      if(!(board->occuped_by_another_piece(board, coordinate))) {
	src->insert_move_list(src, moves, board, x - 1, y);
	if(x == board->get_row(board) - 2) {
	  coordinate->set_coordinate(coordinate, x - 2, y);
	  if(!(board->occuped_by_another_piece(board, coordinate))) 
	    src->insert_move_list(src, moves, board, x - 2, y);
	}
      }

      coordinate->set_coordinate(coordinate, x - 1, y - 1);
      if((board->occuped_by_another_color(board, coordinate, src->get_color(src))))
	src->insert_move_list(src, moves, board, x - 1, y - 1);
      
      coordinate->set_coordinate(coordinate, x - 1, y + 1);
      if((board->occuped_by_another_color(board, coordinate, src->get_color(src))))
	src->insert_move_list(src, moves, board, x - 1, y + 1);
      break;
    case 'b':
      coordinate->set_coordinate(coordinate, x + 1, y);
      if(!(board->occuped_by_another_piece(board, coordinate))) {
	src->insert_move_list(src, moves, board, x + 1, y);
	if(x == 1) {
	  coordinate->set_coordinate(coordinate, x + 2, y);
	  if(!(board->occuped_by_another_piece(board, coordinate))) 
	    src->insert_move_list(src, moves, board, x + 2, y);
	}

      }
      
      coordinate->set_coordinate(coordinate, x + 1, y - 1);
      if((board->occuped_by_another_color(board, coordinate, src->get_color(src))))
	src->insert_move_list(src, moves, board, x + 1, y - 1);
      
      coordinate->set_coordinate(coordinate, x + 1, y + 1);
      if((board->occuped_by_another_color(board, coordinate, src->get_color(src))))
	src->insert_move_list(src, moves, board, x + 1, y + 1);
      break;
    default:
      moves->free_slist(&moves);
      return NULL;
      break;
    }
  }
  return moves;
}

struct _draw *_internal_get_draw_pawn(const struct _pawn *src) {
  return src->interface->get_draw(src->interface);
}

struct _score *_internal_get_score_pawn(const struct _pawn *src) {
  return src->interface->get_score(src->interface);
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_pawn
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _pawn *new_pawn(struct _coordinate *coordinate, struct _color *color, struct _draw *draw) {
  struct _pawn *new = NULL;
  struct _move *pawn = NULL;
  struct _score *score = NULL;

  if((new = (struct _pawn *)malloc(sizeof(struct _pawn)))) {
    if(!(pawn = new_move('p'))) {
      free(new);
      return NULL;
    }
    if(!(score = new_score(PAWN_SCORE))) {
      pawn->free_move(&pawn);
      free(new);
      return NULL;
    }
    if(!(new->interface = new_piece(coordinate, color, pawn, draw, score))) {
      pawn->free_move(&pawn);
      score->free_score(&score);
      free(new);
      return NULL;
    }
    new->free_pawn = _internal_free_pawn;
    new->set_coordinate = _internal_set_coordinate_pawn;
    new->get_coordinate = _internal_get_coordinate_pawn;
    new->get_color = _internal_get_color_pawn;
    new->get_move = _internal_get_move_pawn;
    new->get_current_moves = _internal_get_current_moves_pawn;
    new->get_draw = _internal_get_draw_pawn;
    new->get_score = _internal_get_score_pawn;
    new->insert_move_list = _internal_insert_move_list_pawn;
  }
  return new;
}
