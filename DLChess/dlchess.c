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
#include<stdio.h>
#include<stdlib.h>

#include<ia.h>
#include<parser.h>
#include<referee.h>

#include<pawn.h>

/* ------------------> Internal functions <------------------ */

void _internal_dlchess_usage(void) {
}

/* ------------------> External functions <------------------ */

int main(int argc, char **argv) {
  struct _referee *referee = NULL;
  struct _parser *white_performer = NULL;
  struct _ia *black_performer = NULL;

  /* Se trouve dans un switch car on pourra changer la couleur de l'ia et on peut jouer avec deux parsers ou deux ias */
  if(!(white_performer = new_parser())) {
    fprintf(stderr, "Problem during white_performer allocation !\n");
    return EXIT_FAILURE;
  }

  if(!(black_performer = new_ia(5))) {
    fprintf(stderr, "Problem during white_performer allocation !\n");
    white_performer->free_parser(&white_performer);
    return EXIT_FAILURE;
  }

  if(!(referee = new_referee(8, 8, white_performer, 'p', black_performer, 'i'))) {
    fprintf(stderr, "Problem during referee allocation !\n");
    white_performer->free_parser(&white_performer);
    black_performer->free_ia(&black_performer);
    return EXIT_FAILURE;
  }
 
  /* On lance le jeu d'échec */
  if(!(referee->perform(referee))) {
    fprintf(stderr, "Problem during perform !\n");
    white_performer->free_parser(&white_performer);
    black_performer->free_ia(&black_performer);
    return EXIT_FAILURE;
  }
 
  /* Libération de tous les objets */
  white_performer->free_parser(&white_performer);
  black_performer->free_ia(&black_performer);
  referee->free_referee(&referee);

  return EXIT_SUCCESS;
}
