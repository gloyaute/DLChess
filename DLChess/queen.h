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
#ifndef __QUEEN_H
#define __QUEEN_H

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

#if !defined FALSE || !defined TRUE
#define TRUE  (1)
#define FALSE (0)
#endif /* !defined FALSE || !defined TRUE */

#include<piece.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */
  
  struct _queen {
    struct _piece *interface;
    
    void (*free_queen)(struct _queen **);
    struct _color *(*get_color)(const struct _queen *);
    struct _coordinate *(*get_coordinate)(const struct _queen *);
    void (*set_coordinate)(const struct _queen *, struct _coordinate *);
    struct _move *(*get_move)(const struct _queen *);
    struct _slist *(*get_current_moves)(const struct _board *, const struct _queen *);
    struct _draw *(*get_draw)(const struct _queen *);
    struct _score *(*get_score)(const struct _queen *);
    int (*insert_move_list)(const struct _queen *, struct _slist *, const struct _board *, int, int);
  };
  
  /*
   * Name of function: new_queen
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _queen *new_queen(struct _coordinate *coordinate, struct _color *color, struct _draw *draw);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __QUEEN_H */
