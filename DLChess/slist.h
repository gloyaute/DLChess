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
#ifndef __SLIST_H
#define __SLIST_H

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

#if !defined FALSE || !defined TRUE
#define TRUE  (1)
#define FALSE (0)
#endif /* !defined FALSE || !defined TRUE */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* __cplusplus */

  struct _cell {
    struct _cell *next;
    void *data;
    
    void (*free_cell)(struct _cell **freed);
    void *(*get_data)(const struct _cell *src);
    void (*set_data)(struct _cell *dest, void *data);
    void (*print_cell)(const struct _cell *src);
    void (*print_data)(const void *data);
  };
  
  struct _slist {
    struct _cell *list;

    struct _slist *(*insert_end)(struct _slist *, void *, void (*print_data)(const void *));
    struct _slist *(*insert_top)(struct _slist *, void *, void (*print_data)(const void *));
    struct _cell *(*remove_first)(struct _slist *);
    struct _cell *(*remove_end)(struct _slist *);
    void *(*remove_at)(struct _slist *, void *data, int (*compare_data)(void *, void *));
    void (*free_slist)(struct _slist **);
    void (*print_slist)(struct _slist *);
    int (*contains_value)(struct _slist *, void *, int (*compare_data)(void *, void *));
  };
  
  /*
   * Name of function: new_slist
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _slist *new_slist(void);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __SLIST_H */
