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

#include<move.h>

#ifndef BISHOP_VECTORS
#define BISHOP_VECTORS (4)
#endif /* BISHOP_VECTORS */

#ifndef CASTLE_VECTORS
#define CASTLE_VECTORS (4)
#endif /* CASTLE_VECTORS */

#ifndef KING_VECTORS
#define KING_VECTORS (8)
#endif /* KING_VECTORS */

#ifndef KNIGHT_VECTORS
#define KNIGHT_VECTORS (8)
#endif /* KNIGHT_VECTORS */

#ifndef PAWN_VECTORS
#define PAWN_VECTORS (2)
#endif /* PAWN_VECTORS */

#ifndef QUEEN_VECTORS
#define QUEEN_VECTORS (8)
#endif /* QUEEN_VECTORS */

/* ------------------> Move matrices <------------------ */

static int bishop_matrix[BISHOP_VECTORS * 2] = {
  1, 1, -1, 1, -1, -1, 1, -1};

static int castle_matrix[CASTLE_VECTORS * 2] = {
  0, 1, 0, -1, 1, 0, -1, 0};

static int king_matrix[KING_VECTORS * 2] = {
  1, 1, -1, 1, -1, -1, 1, -1, 0, 1, 0, -1, 1, 0, -1, 0};

static int knight_matrix[KNIGHT_VECTORS * 2] = {
  2, 1, 1, 2, -1, 2, -2, 1, -2, -1, -1, -2, 1, -2, 2, -1};

static int pawn_matrix[PAWN_VECTORS * 2] = {
  1, 0, 2, 0};

static int queen_matrix[QUEEN_VECTORS * 2] = {
  1, 1, -1, 1, -1, -1, 1, -1, 0, 1, 0, -1, 1, 0, -1, 0};

/* ------------------> Internal functions <------------------ */

void _internal_free_move(struct _move **freed) {
  free(*freed);
  *freed = NULL;
}

void _internal_init_move_move(struct _move *dest) {
  switch(dest->type) {
  case 'b':
    dest->matrix = bishop_matrix;
    dest->vector = BISHOP_VECTORS;
    break;
  case 'c':
    dest->matrix = castle_matrix;
    dest->vector = CASTLE_VECTORS;
    break;
  case 'k':
    dest->matrix = king_matrix;
    dest->vector = KING_VECTORS;
    break;
  case 'n':
    dest->matrix = knight_matrix;
    dest->vector = KNIGHT_VECTORS;
    break;
  case 'p':
    dest->matrix = pawn_matrix;
    dest->vector = PAWN_VECTORS;
    break;
  case 'q':
    dest->matrix = queen_matrix;
    dest->vector = QUEEN_VECTORS;
    break;
  }
}

char _internal_get_type_move(const struct _move *src) {
  return src->type;
}

void _internal_set_type_move(struct _move *dest, const char type) {
  dest->type = type;
  _internal_init_move_move(dest);
}

unsigned int _internal_get_vector_move(const struct _move *src) {
  return src->vector;
}

void _internal_set_vector_move(struct _move *dest, const unsigned int vector) {
  dest->vector = vector;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_move
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _move *new_move(const char type) {
  struct _move *new = NULL;
  
  if((new = (struct _move *)malloc(sizeof(struct _move)))) {
    new->type = type;
    new->free_move = _internal_free_move;
    _internal_init_move_move(new);
    new->get_type = _internal_get_type_move;
    new->set_type = _internal_set_type_move;
    new->set_vector = _internal_set_vector_move;
    new->get_vector = _internal_get_vector_move;
    /*    new->init_move = _internal_init_move_move; */
  }
  return new;
}
