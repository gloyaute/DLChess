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
#include<castle.h>
#include<ia.h>
#include<king.h>
#include<knight.h>
#include<parser.h>
#include<pawn.h>
#include<piece.h>
#include<queen.h>
#include<referee.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_referee(struct _referee **freed) {
  (*freed)->board->free_board(&(*freed)->board);
  free(*freed);
  *freed = NULL;
}

struct _board *_internal_get_board_referee(const struct _referee *src) {
  return src->board;
}

int __internal_coordinate_in_moves(struct _slist *list, struct _coordinate *dest) {
  printf("Affichage liste \n");
  list->print_slist(list);
  printf("Avant affichage \n");
  return list->contains_value(list, dest, dest->compare_coordinate);
}

int __internal_test_move(const struct _referee *referee, struct _coordinate *src, struct _coordinate *dest, char type, struct _color *color) {
  int valid = FALSE;
  struct _slist *list = NULL;

  switch(type) {
  case 'b': {
    struct _bishop *bishop = NULL;
    if((bishop = new_bishop(src, color, NULL))) {
      list = bishop->get_current_moves(referee->board, bishop);
      bishop->free_bishop(&bishop);
    }
  }
  break;
  case 'c': {
    struct _castle *castle = NULL;
    if((castle = new_castle(src, color, NULL))) {
      list = castle->get_current_moves(referee->board, castle);
      castle->free_castle(&castle);
    }
  }
  break;
  case 'k': {
    struct _king *king = NULL;
    if((king = new_king(src, color, NULL))) {
      list = king->get_current_moves(referee->board, king);
      king->free_king(&king);
    }
  }
  break;
  case 'n': {
    struct _knight *knight = NULL;
    if((knight = new_knight(src, color, NULL))) {
      list = knight->get_current_moves(referee->board, knight);
      knight->free_knight(&knight);
    }
  }
  break;
  case 'p': {
    struct _pawn *pawn = NULL;
    if((pawn = new_pawn(src, color, NULL))) {
      list = pawn->get_current_moves(referee->board, pawn);
      pawn->free_pawn(&pawn);
    }
  }
  break;
  case 'q': {
    struct _queen *queen = NULL;
    if((queen = new_queen(src, color, NULL))) {
      list = queen->get_current_moves(referee->board, queen);
      queen->free_queen(&queen);
    }
  }
  break;
  }
  /* On test si la position destination est dans la liste des positions possibles ou non */
  if(__internal_coordinate_in_moves(list, dest)) {
    list->free_slist(&list);
    valid = TRUE;
  }
  return valid;
}

int __internal_test_check(const struct _referee *referee, struct _coordinate *old, struct _coordinate *dest, const struct _color *color) {
  struct _coordinate *king_coordinate = NULL;
  struct _slist *pieces = NULL;
  struct _cell *tmp = NULL;
  struct _piece *king = NULL;
  struct _piece *current = referee->board->get_piece(referee->board, old);
  char c = color->get_color(color);
  char type;
  struct _color *other = NULL;
  int valid = FALSE;
  struct _coordinate *src = NULL;

  printf("-----------------> Dans la fonction __internal_test_check %c\n", c);

  switch(c) {
  case 'w':
    king = referee->board->white_king;
    if(current->get_move(current)->get_type(current->get_move(current)) == 'k') {
      referee->board->move_piece(referee->board, old, dest);
      king_coordinate = dest;
    }
    else
      king_coordinate = king->get_coordinate(king);
    king = referee->board->white_king;
    pieces = referee->board->get_all_black(referee->board);
    break;
  case 'b':
    king = referee->board->black_king;
    if(current->get_move(current)->get_type(current->get_move(current)) == 'k') {
      king_coordinate = dest;
      referee->board->move_piece(referee->board, old, dest);
    }
    else
      king_coordinate = king->get_coordinate(king);
    pieces = referee->board->get_all_white(referee->board);
    break;
  }

  referee->board->show_board(referee->board);

  printf("Avant l'appel au test ? %p \n", pieces->list);

  tmp = pieces->list;

  pieces->print_slist(pieces);

  while(pieces->list) {
    current = (struct _piece *)pieces->list->data;

    type = current->get_move(current)->get_type(current->get_move(current));
    printf("Ici %c \n", type); 
    other = current->get_color(current);
    src = current->get_coordinate(current);

    src->print_coordinate(src);
    printf("-------------------------> Affichage information %c %c \n", type, other->get_color(other));

    if((__internal_test_move(referee, src, king_coordinate, type, other))) {
      printf("------------------------> Coucou ---> on est echec \n");
      referee->board->move_piece(referee->board, dest, old);
      valid = TRUE;
      break;
    }
    pieces->list = pieces->list->next;
  }
  pieces->list = tmp;

  printf("En sortie ? %p \n", pieces);

  return valid;
}

int __internal_valid_move(const struct _referee *referee, struct _coordinate *src, struct _coordinate *dest, char c) {
  struct _piece *current = referee->board->get_piece(referee->board, src);
  int valid = FALSE;

  if(current) {
    char type = current->get_move(current)->get_type(current->get_move(current));
    struct _color *color = current->get_color(current);
    
    printf("Test de la couleur %p ----> %c \n",color,  type);
    if(color->get_color(color) != c) 
      return FALSE;

    printf("Test move \n");
    if((__internal_test_move(referee, src, dest, type, color))) {
      if(!(__internal_test_check(referee, src, dest, color)))
	valid = TRUE;
    }
  }
  return valid;
}

int __internal_check_mat(const struct _referee *referee, char color) {
  printf("On test si le joueur courant n'est pas echec et mat \n");
  return FALSE;
}

int _internal_performer_referee(struct _referee *referee) {
  int num = 1;
  char *current_color = "white";
  char c = 'w';
  struct _coordinate *src = NULL;
  struct _coordinate *dest = NULL;
  void *current_performer = referee->white_performer;
  unsigned char current_performer_type = referee->white_performer_type;

  /* Initialisation de l'echiquier */
  printf("initialize board... \n");
  referee->board->init_board(referee->board);
  
  if(!(src = new_coordinate(-1, -1)))
    return FALSE;
  if(!(dest = new_coordinate(-1, -1))) {
    src->free_coordinate(&src);
    return FALSE;
  }

  while(!(__internal_check_mat(referee, c))) {
    referee->board->show_board(referee->board);
    
    switch(current_performer_type) {
    case 'p': {
      int first = TRUE;
      
      do {
	if(!first)
	  fprintf(stderr, "Illegal move: %s-%s\n", src->to_string(src, 'h'), dest->to_string(dest, 'h'));
	printf("[ %s, %d ] \n", current_color, num);
	((struct _parser *)current_performer)->parse_move((struct _parser *)current_performer, referee->board, src, dest);
	first = FALSE;
      } while(!(__internal_valid_move(referee, src, dest, c)));
      referee->board->move_piece(referee->board, src, dest);
    }
    break;
    case 'i':
      do {
	((struct _ia *)current_performer)->ia_move((struct _ia *)current_performer, referee->board, src, dest, c);
      } while(!(__internal_valid_move(referee, src, dest, c)));
      referee->board->move_piece(referee->board, src, dest);
      break;
    default:
      return FALSE;
    }
    
    src->set_coordinate(src, -1, -1);
    dest->set_coordinate(dest, -1, -1);
    
    switch(c) {
    case 'w':
      current_color = "black";
      c = 'b';
      current_performer_type = referee->black_performer_type;
      current_performer = referee->black_performer;
      break;
    case 'b':
      c = 'w';
      current_color = "white";
      current_performer_type = referee->white_performer_type;
      current_performer = referee->white_performer;
      ++num;
      break;
    }
  }
  return TRUE;
}

void _internal_turn_end_referee(struct _referee *dest) {

}

/* ------------------> External functions <------------------ */

/*
 * Name of function:
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _referee *new_referee(unsigned int row, unsigned int col, void *white_performer, unsigned char white_performer_type, void *black_performer, unsigned char black_performer_type) {
  struct _referee *new = NULL;
  
  if((new = (struct _referee *)malloc(sizeof(struct _referee)))) {
    if(!(new->board = new_board(row, col))) {
      free(new);
      return NULL;
    }
    new->white_performer = white_performer;
    new->white_performer_type = white_performer_type;
    new->black_performer = black_performer;
    new->black_performer_type = black_performer_type;
    new->get_board = _internal_get_board_referee;
    new->free_referee = _internal_free_referee;
    new->perform = _internal_performer_referee;
    
    new->turn_end = _internal_turn_end_referee;
  }
  return new;
}
