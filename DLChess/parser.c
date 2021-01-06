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

#include<parser.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_parser(struct _parser **freed) {
  free(*freed);
  *freed = NULL;
}

unsigned char _internal_get_type_parser(const struct _parser *src) {
  return src->type;
}

int _internal_parse_move_parser(struct _parser *parse, const struct _board *board, struct _coordinate *src, struct _coordinate *dest) {
  unsigned char x, dx;
  int y, dy;
  int ix, idx;
  int first = TRUE;

  do {
    if(!first) {
      fprintf(stderr, "Parse error !\n");
    }
    scanf(" %c%d-%c%d", &x, &y, &dx, &dy);
    first = FALSE;
  } while(!(board->in_range_value(board, x, y, dx, dy)));

  if((ix = board->row_char_to_int(board, x)) == -1 || (idx = board->row_char_to_int(board, dx)) == -1)
    return FALSE;
  
  src->set_coordinate(src, ix, y);
  dest->set_coordinate(dest, idx, dy);
  
  if(!board->inside_board(board, src) && !board->inside_board(board, dest))
    return FALSE;
  return TRUE;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_parser
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _parser *new_parser(void) {
  struct _parser *new = NULL;

  if((new = (struct _parser *)malloc(sizeof(struct _parser)))) {
    new->free_parser = _internal_free_parser;
    new->get_type = _internal_get_type_parser;
    new->parse_move = _internal_parse_move_parser;
  }
  return new;
}
