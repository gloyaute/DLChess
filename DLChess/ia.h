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
#ifndef __IA_H
#define __IA_H

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

#if !defined FALSE || !defined TRUE
#define TRUE  (1)
#define FALSE (0)
#endif /* !defined FALSE || !defined TRUE */

#include<board.h>
#include<coordinate.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */
  
  struct _ia {
    unsigned char type;
    unsigned int max_deep;

    void (*free_ia)(struct _ia **);
    unsigned int (*get_max_deep)(const struct _ia *);
    void (*set_max_deep)(struct _ia *, unsigned int);
    unsigned char (*get_type)(const struct _ia *);
    int (*min_max)(int current_score, int best_score);
    int (*ia_move)(const struct _ia *, struct _board *, struct _coordinate *, struct _coordinate *, char);
  };
  
  /*
   * Name of function: new_ia
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _ia *new_ia(unsigned int);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __IA_H */
