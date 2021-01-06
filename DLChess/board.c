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

#include<board.h>

#include<bishop.h>
#include<castle.h>
#include<color.h>
#include<draw.h>
#include<king.h>
#include<knight.h>
#include<pawn.h>
#include<piece.h>
#include<queen.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_board(struct _board **freed) {
  free(*freed);
  *freed = NULL;
}

void _internal_set_row_board(struct _board *dest, unsigned int new) {
  dest->row = new;
}

unsigned int _internal_get_row_board(const struct _board *src) {
  return src->row;
}

void _internal_set_col_board(struct _board *dest, unsigned int new) {
  dest->col = new;
}

unsigned int _internal_get_col_board(const struct _board *src) {
  return src->col;
}

int _internal_inside_board(const struct _board *board, const struct _coordinate *inside) {
  int x = inside->get_x(inside);
  int y = inside->get_y(inside);
  
  if(x < 0 || x > (board->row - 1) || y < 0 || y > (board->col - 1))
    return FALSE;
  
  return TRUE;
}

int _internal_row_char_to_int_board(const struct _board *board, unsigned char src) {
  unsigned int dest = -1;
  
  if(src - 'a' >= 0 && src - 'a' < (board->row))
    dest = board->row - (src - 'a') - 1;
  return dest;
}

int _internal_occuped_by_another_piece_board(const struct _board *src, const struct _coordinate *tested) {
  int x = tested->get_x(tested);
  int y = tested->get_y(tested);

  return (src->board[x * src->col + y] == NULL) ? (FALSE) : (TRUE);
}

int _internal_occuped_by_another_color_board(const struct _board *src, const struct _coordinate *tested, const struct _color *color) {
  int x = tested->get_x(tested);
  int y = tested->get_y(tested);
  int ret = FALSE;
  unsigned char c = color->get_color(color);

  if((src->board[x * src->col + y]) && (src->board[x * src->col + y]->get_color(src->board[x * src->col + y])->get_color(src->board[x * src->col + y]->get_color(src->board[x * src->col + y]))) != c)
    ret = TRUE;
  return ret;
}

int __internal_init_board_pawn(struct _board *board, struct _color *color, struct _draw *draw) {
  int i = 0;
  int row = 1;

  if(color->get_color(color) == 'w') 
    row = board->row - row - 1;

  for(i = 0; i < board->col; ++i) {
    struct _coordinate *coordinate = NULL;
    struct _pawn *pawn = NULL;
    
    if(!(coordinate = new_coordinate(row, i)))
      return FALSE;
    
    if(!(pawn = new_pawn(coordinate, color, draw))) {
      free(coordinate);
      return FALSE;
    }
    board->board[row * board->col + i] = pawn->interface;
    if(color->get_color(color) == 'w')
      board->whites->insert_end(board->whites, pawn->interface, pawn->interface->print_piece);
    else
      board->blacks->insert_end(board->blacks, pawn->interface, pawn->interface->print_piece);
  }
  return TRUE;
}

int __internal_init_board_main(struct _board *board, struct _color *color) {
  int col;
  int row = 0;

  if(color->get_color(color) == 'w')
    row = board->row - row - 1;


  for(col = 0; col < board->col; ++col) {
    struct _coordinate *coordinate = NULL;
    struct _piece *current = NULL;

    if(!(coordinate = new_coordinate(row, col))) {
      return FALSE;
    }
    
    switch(col) {
    case 7:
    case 0: {
      struct _castle *castle = NULL;
      struct _draw *draw = NULL;

      if(color->get_color(color) == 'b') {
	if(!(draw = new_draw('r'))) {
	  return FALSE;
	}
      }
      else
	if(!(draw = new_draw('R'))) {
	  return FALSE;
	}

      if(!(castle = new_castle(coordinate, color, draw))) {
	free(draw);
	return FALSE;
      }
      current = castle->interface;
    }
      break;
    case 6:
    case 1: {
      struct _knight *knight = NULL;
      struct _draw *draw = NULL;

      if(color->get_color(color) == 'b') {
	if(!(draw = new_draw('n'))) {
	  return FALSE;
	}
      }
      else
	if(!(draw = new_draw('N'))) {
	  return FALSE;
	}

      if(!(knight = new_knight(coordinate, color, draw))) {
	free(draw);
	return FALSE;
      }
      current = knight->interface;
    }
      break;
    case 5:
    case 2: {
      struct _bishop *bishop = NULL;
      struct _draw *draw = NULL;

      if(color->get_color(color) == 'b') {
	if(!(draw = new_draw('b'))) {
	  return FALSE;
	}
      }
      else
	if(!(draw = new_draw('B'))) {
	  return FALSE;
	}

      if(!(bishop = new_bishop(coordinate, color, draw))) {
	free(draw);
	return FALSE;
      }
      current = bishop->interface;
    }
      break;
    case 3: {
      struct _queen *queen = NULL;
      struct _draw *draw = NULL;

      if(color->get_color(color) == 'b') {
	if(!(draw = new_draw('q'))) {
	  return FALSE;
	}
      }
      else
	if(!(draw = new_draw('Q'))) {
	  return FALSE;
	}

      if(!(queen = new_queen(coordinate, color, draw))) {
	free(draw);
	return FALSE;
      }
      current = queen->interface;
    }
    break;
    case 4: {
      struct _king *king = NULL;
      struct _draw *draw_king = NULL;

      if(color->get_color(color) == 'b') {
	if(!(draw_king = new_draw('k'))) {
	  return FALSE;
	}
      }
      else
	if(!(draw_king = new_draw('K'))) {
	  return FALSE;
	}

      if(!(king = new_king(coordinate, color, draw_king))) {
	free(draw_king);
	return FALSE;
      }
      current = king->interface;
      if(color->get_color(color) == 'w')
	board->white_king = current;
      else
	board->black_king = current;
    }
      break;
    }
    board->board[row * board->col + col] = current;
    if(color->get_color(color) == 'w' && col != 4)
      board->whites->insert_end(board->whites, current, current->print_piece);
    else if(color->get_color(color) == 'b' && col != 4)
      board->blacks->insert_end(board->blacks, current, current->print_piece);
  }
  return TRUE;
}

int _internal_init_board(struct _board *board) {
  struct _color *black = NULL;
  struct _color *white = NULL;
  struct _draw *draw_black_pawn = NULL;
  struct _draw *draw_white_pawn = NULL;

  if(!(black = new_color('b'))) {
    return FALSE;
  }

  if(!(white = new_color('w'))) {
    free(black);
    return FALSE;
  }

  if(!(draw_black_pawn = new_draw('p'))) {
    free(black);
    free(white);
    return FALSE;
  }
  
  if(!(draw_white_pawn = new_draw('P'))) {
    free(black);
    free(white);
    free(draw_black_pawn);
    return FALSE;
  }

  if(!(__internal_init_board_pawn(board, black, draw_black_pawn))) {
    /* Penser à la libération */
    free(black);
    free(white);
    free(draw_black_pawn);
    return FALSE;
  }
  
  if(!(__internal_init_board_pawn(board, white, draw_white_pawn))) {
    /* Penser à la libération */
    free(black);
    free(white);
    free(draw_black_pawn);
    return FALSE;
  }

  if(!(__internal_init_board_main(board, white))) {
    /* Penser à la libération */
    free(black);
    free(white);
    free(draw_black_pawn);
    return FALSE;
  }

  if(!(__internal_init_board_main(board, black))) {
    /* Penser à la libération */
    free(black);
    free(white);
    free(draw_black_pawn);
    return FALSE;
  }
  
  return TRUE;
}

void _internal_show_board(const struct _board *board) {
  int row;
  int col;

  printf("show position :");
  
  for(row = 0; row < board->row; ++row) {
    printf("\n\t %c  ", 'a' + (board->row - row - 1));
    for(col = 0; col < board->col; ++col) {
      if(board->board[row * board->col + col])
	printf("%c ", board->board[row * board->col + col]->draw_piece(board->board[row * board->col + col]));
      else
	printf("0 ");
    }
  }
  printf("\n\n\t    ");
  for(col = 0; col < board->col; ++col) {
    printf("%d ", col);
  }
  printf("\n");
}

struct _slist *_internal_get_all_white_board(const struct _board *src) {
  return src->whites;
}

struct _slist *_internal_get_all_black_board(const struct _board *src) {
  return src->blacks;
}

struct _piece *_internal_get_piece_board(const struct _board *src, const struct _coordinate *coordinate) {
  int x = coordinate->get_x(coordinate);
  int y = coordinate->get_y(coordinate);

  return src->board[x * src->col + y];
}

/* ---> Dev */
struct _piece *_internal_move_piece_board(struct _board *board, struct _coordinate *src, struct _coordinate *dest) {
  int x = src->get_x(src), y = src->get_y(src);
  int dx = dest->get_x(dest), dy = dest->get_y(dest);
  struct _piece *current = board->board[x * board->col + y];
  char separator = '-';
  struct _piece *remove = NULL;

  printf("dans la fonction internal move piece %p \n", current);
  current->print_piece(current);
  
  printf("Information %d %d \n", x, y);
  printf("Dans la fonction move_piece_board %d et %d \n", dx, dy);
  if(board->occuped_by_another_color(board, dest, current->get_color(current))) {
    struct _piece *removed = NULL;
    remove = board->board[dx * board->col + dy];
    separator = 'x';

    if(current->get_color(current)->get_color(current->get_color(current)) == 'w')
      removed = board->blacks->remove_at(board->blacks, remove, remove->compare_piece);
    else
      removed = board->whites->remove_at(board->whites, remove, remove->compare_piece);
  }
  board->board[dx * board->col + dy] = current;
  printf("Avant modif sur les coordinate \n");
  current->set_coordinate(current, dest);
  board->board[x * board->col + y] = NULL;
  printf("your move is %s%c%s \n", src->to_string(src, 'h'), separator, dest->to_string(dest, 'h'));
  return remove;
}

int _internal_in_range_value_board(const struct _board *board, char x, int y, char dx, int dy) {
  if(y < 0 || y > (board->col - 1) || dy < 0 || dy > (board->col - 1))
    return FALSE;
  if(x < 'a' || x > ('a' + board->row - 1) || dx < 'a' || dx > ('a' + board->row - 1))
    return FALSE;
  return TRUE;
}

int _internal_eval_board(const struct _board *src, struct _color *color) {
  int score_current = 0;
  int score_opponent = 0;
  struct _slist *current_pieces = NULL;
  struct _slist *opponent_pieces = NULL;
  struct _cell *tmp = NULL;

  switch(color->get_color(color)) {
  case 'b':
    current_pieces = src->get_all_black(src);
    opponent_pieces = src->get_all_white(src);
    break;
  case 'w':
    current_pieces = src->get_all_white(src);
    opponent_pieces = src->get_all_black(src);
    break;
  }

  /* Eval de la couleur cur */
  tmp = current_pieces->list;
  while(current_pieces->list) {
    struct _score *score = ((struct _piece *)current_pieces->list->data)->get_score((struct _piece *)current_pieces->list->data);
    score_current += score->get_score(score);
    current_pieces->list = current_pieces->list->next;
  }
  current_pieces->list = tmp;

  /* Eval de la couleur opp */
  tmp = opponent_pieces->list;
  while(opponent_pieces->list) {
    struct _score *score = ((struct _piece *)opponent_pieces->list->data)->get_score((struct _piece *)opponent_pieces->list->data);
    score_opponent += score->get_score(score);
    opponent_pieces->list = opponent_pieces->list->next;
  }
  opponent_pieces->list = tmp;

  return (score_current - score_opponent);
}

void _internal_set_piece_board(struct _board *dest, struct _piece *setting) {
  int x = setting->get_coordinate(setting)->get_x(setting->get_coordinate(setting));
  int y = setting->get_coordinate(setting)->get_y(setting->get_coordinate(setting));
  
  switch(setting->get_color(setting)->get_color(setting->get_color(setting))) {
  case 'b':
    dest->blacks->insert_top(dest->blacks, setting, setting->print_piece);
    break;
  case 'w':
    dest->whites->insert_top(dest->whites, setting, setting->print_piece);
    break;
  }
  dest->board[x * dest->col + y] = setting;
}

/* ------------------> External functions <------------------ */

/*
 * Name of function: new_board
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _board *new_board(const unsigned int row, const unsigned int col) {
  struct _board *new = NULL;
  int i;

  if((new = (struct _board *)malloc(sizeof(struct _board)))) {
    if(!(new->board = (struct _piece **)malloc(row * col * sizeof(struct _piece *)))) {
      free(new);
      return NULL;
    }
    
    /* Initialisation des cases de la matrice à NULL */
    for(i = 0; i < row * col; ++i) {
      if(!(new->board[i] = (struct _piece *)malloc(sizeof(struct _piece)))) {
	int j;
	for(j = 0; j < i; ++j)
	  free(new->board[j]);
	free(new->board);
	free(new);
	return NULL;
      }
      new->board[i] = NULL;
    }    
    if(!(new->whites = new_slist())) {
      for(i = 0; i < row * col; ++i)
	free(new->board[i]);
      free(new);
      return NULL;
    }
    if(!(new->blacks = new_slist())) {
      for(i = 0; i < row * col; ++i)
	free(new->board[i]);
      new->whites->free_slist(&new->whites);
      free(new);
      return NULL;
    }
    new->row = row;
    new->col = col;
    new->free_board = _internal_free_board;
    new->set_row = _internal_set_row_board;
    new->get_row = _internal_get_row_board;
    new->set_col = _internal_set_col_board;
    new->get_col = _internal_get_col_board;
    new->inside_board = _internal_inside_board;
    new->init_board = _internal_init_board;
    new->show_board = _internal_show_board;
    new->occuped_by_another_piece = _internal_occuped_by_another_piece_board;
    new->occuped_by_another_color = _internal_occuped_by_another_color_board;
    new->row_char_to_int = _internal_row_char_to_int_board;
    new->get_all_white = _internal_get_all_white_board;
    new->get_all_black = _internal_get_all_black_board;
    new->get_piece = _internal_get_piece_board;
    new->set_piece = _internal_set_piece_board;
    new->in_range_value = _internal_in_range_value_board;
    new->move_piece = _internal_move_piece_board;
    new->eval_board = _internal_eval_board;
  }
  return new;
}
