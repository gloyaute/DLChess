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

#include<slist.h>

/* ------------------> Internal functions <------------------ */

void _internal_free_cell(struct _cell **freed) {
  free(*freed);
  *freed = NULL;
}

void _internal_set_data_cell(struct _cell *dest, void *data) {
  dest->data = data;
}

void *_internal_get_data_cell(const struct _cell *src) {
  return src->data;
}

void _internal_print_cell(const struct _cell *src) {
  src->print_data(src->data);
}

/* ------------------> External functions <------------------ */

/*
 * Name of function: new_cell
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _cell *new_cell(void *data, void (*print_data)(const void *data)) {
  struct _cell *new = NULL;
  
  if((new = (struct _cell *)malloc(sizeof(struct _cell)))) {
    new->next = NULL;
    new->data = data;
    new->free_cell = _internal_free_cell;
    new->get_data = _internal_get_data_cell;
    new->set_data = _internal_set_data_cell;
    new->print_cell = _internal_print_cell;
    new->print_data = print_data;
  }
  return new;
}

/* ------------------> Internal functions <------------------ */

struct _slist *_internal_insert_end_slist(struct _slist *dest, void *data, void (*print_data)(const void *data)) {
  struct _cell *new = NULL;
  struct _cell *tmp = dest->list;
  
  if((new = new_cell(data, print_data))) {
    if(!dest) {
      struct _slist *test = new_slist();
      test->list = new;
      return test;
    }
    if(!dest->list) {
      dest->list = new;
      return dest;
    }
    while(dest->list->next)
      dest->list = dest->list->next;
    dest->list->next = new;
    dest->list = tmp;
    return dest;
  }
  return NULL;
}

struct _slist *_internal_insert_top_slist(struct _slist *dest, void *data, void (*print_data)(const void *data)) {
  struct _cell *new = NULL;
  
  if((new = new_cell(data, print_data))) {
    new->next = dest->list;
    dest->list = new;
  }
  return dest;
}

struct _cell *_internal_remove_first_slist(struct _slist *src) {
  struct _cell *removed = NULL;

  if(src->list) {
    removed = src->list;
    src->list = src->list->next;
  }
  return removed;
}

struct _cell *_internal_remove_end_slist(struct _slist *src) {
  struct _cell *removed = NULL;
  struct _cell *tmp = src->list;

  if(src->list && src->list->next) {
    while(src->list->next->next) {
      src->list = src->list->next;
    }
    removed = src->list->next;
    src->list->next = NULL;
    src->list = tmp;
  }
  return removed;
}

void __internal_free_list(struct _cell **freed) {
  if(*freed) {
    __internal_free_list(&(*freed)->next);
    (*freed)->free_cell(freed);
  }
}

void _internal_free_slist(struct _slist **freed) {
  if((*freed)->list) {
    __internal_free_list(&(*freed)->list);
  }
  (*freed)->list = NULL;
  free(*freed);
  *freed = NULL;
}

void _internal_print_slist(struct _slist *printed) {
  struct _cell *tmp = printed->list;
  
  while(printed->list) {
    printed->list->print_cell(printed->list);
    printed->list = printed->list->next;

  }
  printed->list = tmp;
}

int _internal_contains_value(struct _slist *container, void *data, int (*compare_data)(void *data1, void *data2)) {
  struct _cell *tmp = container->list;
  int contains = FALSE;

  while(container->list && !compare_data(data, container->list->data)) 
    container->list = container->list->next;
  if(container->list)
    contains = TRUE;
  container->list = tmp;
  return contains;
}

void *_internal_remove_at_slist(struct _slist *container, void *data, int (*compare_data)(void *, void *)) {
  struct _cell *tmp = container->list;
  void *contains = NULL;

  while(container->list && container->list->next && !compare_data(data, container->list->next->data)) 
    container->list = container->list->next;
  if(container->list && container->list->next) {
    contains = container->list->data;
    container->list->next = container->list->next->next;
  }
  container->list = tmp;
  return contains;
}

/* ------------------> External functions <------------------ */

/*
 * Name of function: new_slist
 *
 * Description:
 *
 * Input:
 *
 * Output:
 */
struct _slist *new_slist(void) {
  struct _slist *new = NULL;
  
  if((new = (struct _slist *)malloc(sizeof(struct _slist)))) {
    new->list = NULL;
    new->insert_end = _internal_insert_end_slist;
    new->insert_top = _internal_insert_top_slist;
    new->remove_first = _internal_remove_first_slist;
    new->remove_end = _internal_remove_end_slist;
    new->free_slist = _internal_free_slist;
    new->print_slist = _internal_print_slist;
    new->contains_value = _internal_contains_value;
    new->remove_at = _internal_remove_at_slist;
  }

  return new;
}

/*  void print_string(void *string) { */
/*    printf("La chaine %s \n", (char *)string); */
/*  } */

/*  int main(int argc, char **argv) { */
/*    struct _slist *test = NULL; */

/*    test = new_slist(); */
  
/*    test->insert_end(test, "toto", print_string); */
/*    test->insert_end(test, "titi", print_string); */
/*    test->insert_end(test, "coucou", print_string); */
/*    test->remove_end(test); */
/*    test->remove_end(test); */
/*    test->insert_top(test, "test", print_string); */
/*    test->insert_top(test, "test2", print_string); */
/*    test->remove_first(test); */
  
/*    test->print_slist(test); */

/*    return 1; */
/*  } */
