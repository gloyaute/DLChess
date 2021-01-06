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
#ifndef __PIECE_H
#define __PIECE_H

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

#if !defined FALSE || !defined TRUE
#define TRUE  (1)
#define FALSE (0)
#endif /* !defined FALSE || !defined TRUE */

#include<board.h>
#include<color.h>
#include<coordinate.h>
#include<draw.h>
#include<move.h>
#include<score.h>
#include<slist.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */
  
  struct _piece {
    struct _coordinate *coordinate;
    struct _color *color;
    struct _move *move;
    struct _draw *draw;
    struct _score *score;

    void (*free_piece)(struct _piece **);
    struct _color *(*get_color)(const struct _piece *);
    void (*set_color)(struct _piece *, struct _color *);
    struct _coordinate *(*get_coordinate)(const struct _piece *);
    void (*set_coordinate)(struct _piece *, struct  _coordinate *);
    struct _move *(*get_move)(const struct _piece *);
    void (*set_move)(struct _piece *, struct _move *);
    struct _slist *(*get_current_moves)(const struct _board *, const struct _piece *);
    void (*set_draw)(struct _piece *, struct _draw *);
    struct _draw *(*get_draw)(const struct _piece *);
    unsigned char (*draw_piece)(const struct _piece *);
    struct _score *(*get_score)(const struct _piece *src);
    void (*set_score)(struct _piece *dest, struct _score *new);
    int (*insert_move_list)(struct _slist *, const struct _board *, int, int, struct _color *);
    void (*print_piece)(const void *);
    int (*compare_piece)(void *, void *);
  };
  
  /*
   * Name of function: new_piece
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _piece *new_piece(struct _coordinate *, struct _color *, struct _move *, struct _draw *, struct _score *);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __PIECE_H */
