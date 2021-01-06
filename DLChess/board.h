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
#ifndef __BOARD_H
#define __BOARD_H

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

#if !defined FALSE || !defined TRUE
#define TRUE  (1)
#define FALSE (0)
#endif /* !defined FALSE || !defined TRUE */

#include<color.h>
#include<coordinate.h>
#include<slist.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */
  
  struct _board {
    unsigned int row;
    unsigned int col;
    struct _slist *whites;
    struct _slist *blacks;
    struct _piece *white_king;
    struct _piece *black_king;
    struct _piece **board;
    
    void (*free_board)(struct _board **);
    unsigned int (*get_row)(const struct _board *);
    void (*set_row)(struct _board *, unsigned int);
    unsigned int (*get_col)(const struct _board *);
    void (*set_col)(struct _board *, unsigned int);
    int (*inside_board)(const struct _board *, const struct _coordinate *);
    int (*row_char_to_int)(const struct _board *, unsigned char);
    int (*init_board)(struct _board *);
    void (*show_board)(const struct _board *);
    int (*occuped_by_another_piece)(const struct _board *, const struct _coordinate *);
    int (*occuped_by_another_color)(const struct _board *, const struct _coordinate *, const struct _color *);
    struct _slist *(*get_all_white)(const struct _board *);
    struct _slist *(*get_all_black)(const struct _board *);
    struct _piece *(*get_piece)(const struct _board *, const struct _coordinate *);
    void (*set_piece)(struct _board *, struct _piece *);
    int (*in_range_value)(const struct _board *, char, int, char, int);
    struct _piece *(*move_piece)(struct _board *, struct _coordinate *, struct _coordinate *);
    int (*eval_board)(const struct _board *, struct _color *);
  };

  /*
   * Name of function: new_board
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _board *new_board(const unsigned int, const unsigned int);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H */
