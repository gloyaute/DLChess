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
#include<limits.h>
#include<malloc.h>
#include<stdio.h>

#include<bishop.h>
#include<castle.h>
#include<ia.h>
#include<king.h>
#include<knight.h>
#include<pawn.h>
#include<queen.h>
#include<slist.h>

/* ------------------> Internal functions <------------------ */

int _internal_min_max_ia(int current_score, int best_score) {
  if(current_score > best_score)
    return TRUE;
  return FALSE;
}

unsigned int _internal_get_max_deep_ia(const struct _ia *src) {
  return src->max_deep;
}

void _internal_set_max_deep_ia(struct _ia *dest, unsigned int new_max_deep) {
  dest->max_deep = new_max_deep;
}

void _internal_free_ia(struct _ia **freed) {
  free(*freed);
  *freed = NULL;
}

unsigned char _internal_get_type_ia(const struct _ia *src) {
  return src->type;
}

struct _slist *__internal_generate_moves_ia(const struct _board *board, struct _coordinate *src, char type, struct _color *color) {
  struct _slist *list = NULL;

  switch(type) {
  case 'b': {
    struct _bishop *bishop = NULL;
    if((bishop = new_bishop(src, color, NULL))) {
      list = bishop->get_current_moves(board, bishop);
      bishop->free_bishop(&bishop);
    }
  }
  break;
  case 'c': {
    struct _castle *castle = NULL;
    if((castle = new_castle(src, color, NULL))) {
      list = castle->get_current_moves(board, castle);
      castle->free_castle(&castle);
    }
  }
  break;
  case 'k': {
    struct _king *king = NULL;
    if((king = new_king(src, color, NULL))) {
      list = king->get_current_moves(board, king);
      king->free_king(&king);
    }
  }
  break;
  case 'n': {
    struct _knight *knight = NULL;
    if((knight = new_knight(src, color, NULL))) {
      list = knight->get_current_moves(board, knight);
      knight->free_knight(&knight);
    }
  }
  break;
  case 'p': {
    struct _pawn *pawn = NULL;
    if((pawn = new_pawn(src, color, NULL))) {
      list = pawn->get_current_moves(board, pawn);
      pawn->free_pawn(&pawn);
    }
  }
  break;
  case 'q': {
    struct _queen *queen = NULL;
    if((queen = new_queen(src, color, NULL))) {
      list = queen->get_current_moves(board, queen);
      queen->free_queen(&queen);
    }
  }
  break;
  }
  return list;
}

int call;
int call_white;
int call_black;
void __internal_explore_ia(int deep, const struct _ia *ia, struct _board *board, struct _color *white, struct _color *black, struct _color *current_color, struct _coordinate *dest) {
  struct _piece *current = NULL;
  struct _slist *pieces = NULL;
  struct _slist *moves = NULL;
  struct _cell *tmp = NULL;
  struct _cell *tmp2 = NULL;
  char type;
  int x, y;
  struct _coordinate *src = NULL;
  struct _color *other = NULL;

  src = new_coordinate(-1, -1);

  printf("-----------------------------------------> valeur du deep %d ---> %c \n", deep, current_color->get_color(current_color));
  if(deep == ia->max_deep) {
    printf("Exploration fini \n");
    printf("Valeur de la position %d \n", board->eval_board(board, current_color));
    return;
  }

  switch(current_color->get_color(current_color)) {
  case 'b':
    pieces = board->get_all_black(board);
    current_color = black;
    ++call_black;
    break;
  case 'w':
    pieces = board->get_all_white(board);
    current_color = white;
    ++call_white;
    break;
  }
  
  tmp = pieces->list;
  
  while(tmp) {
    current = (struct _piece *)tmp->data;
    type = current->get_move(current)->get_type(current->get_move(current));
    other = current->get_color(current);
    x = current->get_coordinate(current)->get_x(current->get_coordinate(current));
    y = current->get_coordinate(current)->get_y(current->get_coordinate(current));
    src->set_coordinate(src, x, y);
    
    printf("combien de passage %d ---> w %d, ---> b %d \n", call, call_white, call_black);
    call++;
    moves = __internal_generate_moves_ia(board, src, type, other);
    tmp2 = moves->list;
    
    while(moves->list) {
      struct _piece *backup = NULL;
      int doing_backup = FALSE;
      printf("Affichage des coordonnées %p\n", moves->list);
      src->print_coordinate(src);
      ((struct _coordinate *)moves->list->data)->print_coordinate((struct _coordinate *)moves->list->data);

      if((board->occuped_by_another_color(board, (struct _coordinate *)moves->list->data, current_color))) {
	printf("----------------------------> Autre couleur ? \n");
	doing_backup = TRUE;
	backup = board->move_piece(board, src, (struct _coordinate *)moves->list->data);
      }
      else
	board->move_piece(board, src, (struct _coordinate *)moves->list->data);

      board->show_board(board);

      switch(current_color->get_color(current_color)) {
      case 'b':
	__internal_explore_ia(deep + 1, ia, board, white, black, white, dest);
	break;
      case 'w':
	__internal_explore_ia(deep + 1, ia, board, white, black, black, dest);
      }
      printf("Les coordonnées qui sont rejouees \n");
      ((struct _coordinate *)moves->list->data)->print_coordinate((struct _coordinate *)moves->list->data);
      src->print_coordinate(src);
      board->move_piece(board, (struct _coordinate *)moves->list->data, src);
      if(doing_backup) {
	struct _coordinate *piece_eat = backup->get_coordinate(backup);
	printf("------------------> on reinstalle une piece joue \n");
	piece_eat->print_coordinate(piece_eat);
	backup->print_piece(backup);
	board->set_piece(board, backup);
	backup = NULL;
	doing_backup = FALSE;
      }
      printf("Reinitialisation du board ? \n");
      board->show_board(board);
      moves->list = moves->list->next;
    }
    moves->list = tmp2;
    moves->free_slist(&moves);
    tmp = tmp->next;
  }
  return;
}

int _internal_ia_move(const struct _ia *ia, struct _board *board, struct _coordinate *src, struct _coordinate *dest, char c) {
  struct _color *white = NULL;
  struct _color *black = NULL;
  struct _color *current = NULL;

  printf("Appel la fonction ? ------------> %c \n", c);
  if(!(white = new_color('w'))) {
    return FALSE;
  }
  if(!(black = new_color('b'))) {
    white->free_color(&white);
    return FALSE;
  }
  if(!(current = new_color(c))) {
    white->free_color(&white);
    black->free_color(&black);
    return FALSE;
  }
  call = 0;
  call_white = call_black = 0;
  printf("Demande de deplacement dans l'ia \n");
  __internal_explore_ia(0, ia, board, white, black, current, dest);
  printf("Coordonnées obtenues \n");

  return TRUE;
}

/* ------------------> External functions <------------------ */

/**
 * Name of function: new_ia
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _ia *new_ia(unsigned int max_deep) {
  struct _ia *new = NULL;

  if((new = (struct _ia *)malloc(sizeof(struct _ia)))) {
    new->max_deep = max_deep;
    new->free_ia = _internal_free_ia;
    new->get_type = _internal_get_type_ia;
    new->min_max = _internal_min_max_ia;
    new->set_max_deep = _internal_set_max_deep_ia;
    new->get_max_deep = _internal_get_max_deep_ia;
    new->ia_move = _internal_ia_move;
  }
  return new;
}

