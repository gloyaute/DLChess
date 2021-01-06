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
#ifndef __COLOR_H
#define __COLOR_H

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
  struct _color {
    unsigned char color;
    
    void (*free_color)(struct _color **);
    unsigned char (*get_color)(const struct _color *);
    void (*set_color)(struct _color *, const unsigned char);
  };
  
  /**
   * Name of function: new_color
   *
   * Description:
   *
   * Input:
   *
   * Output:
   */
  extern struct _color *new_color(const unsigned char);
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif /* __cplusplus */

#endif /* __COLOR_H */
