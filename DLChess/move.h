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
#ifndef __MOVE_H
#define __MOVE_H

#ifndef NULL
#define NULL            ((void *)0)
#endif /* NULL */

#if !defined FALSE || !defined TRUE
#define TRUE  (1)
#define FALSE (0)
#endif /* !defined FALSE || !defined TRUE */

#ifndef SIZE_PIECE_MATRIX
#define SIZE_PIECE_MATRIX    (25)
#endif /* SIZE_PIECE_MATRIX */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */
  
  struct _move {
    int *matrix;
    unsigned int vector;
    char type;

    void (*free_move)(struct _move **);
    char (*get_type)(const struct _move *);
    unsigned int (*get_vector)(const struct _move *);
    void (*set_type)(struct _move *, const char);
    void (*set_vector)(struct _move *, const unsigned int);
  };
  
  /**
   * Name of function: new_move
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _move *new_move(const char);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __MOVE_H */
