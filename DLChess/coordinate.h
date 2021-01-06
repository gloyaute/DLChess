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
#ifndef __COORDINATE_H
#define __COORDINATE_H

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
  
  /**
   * 
   */
  struct _coordinate {
    int x;
    int y;
    
    void (*free_coordinate)(struct _coordinate **);
    int (*get_x)(const struct _coordinate *);
    int (*get_y)(const struct _coordinate *);
    void (*set_x)(struct _coordinate *, const int);
    void (*set_y)(struct _coordinate *, const int);
    void (*set_coordinate)(struct _coordinate *, const int, const int);
    void (*print_coordinate)(const void *);
    unsigned char *(*to_string)(const struct _coordinate *, unsigned char);
    int (*compare_coordinate)(void *, void *);
  };
  
  /**
   * Name of function: new_coordinate
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _coordinate *new_coordinate(const int, const int);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __COORDINATE_H */
