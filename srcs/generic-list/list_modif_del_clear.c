#include	<stdlib.h>
#include	"generic_list.h"

void		list_clear(t_list *front_ptr,
			   void (*free_func)(void *elem))
{
  t_list	last;

  while (*front_ptr)
    {
      last = (*front_ptr)->next;
      if (free_func != NULL)
	free_func((*front_ptr)->value);
      free(*front_ptr);
      *front_ptr = NULL;
      *front_ptr = last;
    }
}

t_bool	list_del_elem_at_front(t_list *front_ptr)
{
  t_list next_front;

  if (*front_ptr != NULL)
    {
      next_front = *front_ptr;
      next_front = next_front->next;
      free(*front_ptr);
      *front_ptr = next_front;
      return (glTRUE);
    }
  return (glFALSE);
}

t_bool	list_del_elem_at_back(t_list *front_ptr)
{
  t_list tmp;

  if (*front_ptr != NULL)
    {
      tmp = *front_ptr;
      while (tmp->next != NULL)
	{
	  if (tmp->next->next == NULL)
	    {
	      free(tmp->next->next);
	      tmp->next = NULL;
	      return (glTRUE);
	    }
	  tmp = tmp->next;
	}
      free(tmp);
      *front_ptr = NULL;
    }
  return (glFALSE);
}

t_bool	list_del_elem_like(t_list *front_ptr, void *value,
			   void (*free_func)(void *value))
{
  t_list tmp;
  t_list last;

  if (*front_ptr == NULL)
    return (glFALSE);
  tmp = *front_ptr;
  last = tmp;
  while (tmp != NULL)
    {
      if (tmp->value == value)
	{
	  if (last != tmp)
	    last->next = tmp->next;
	  else
	    *front_ptr = tmp->next;
	  if (free_func != NULL)
	    free_func(tmp->value);
	  free(tmp);
	  if (list_get_size(*front_ptr) == 0)
	    *front_ptr = NULL;
	  return (glTRUE);
	}
      last = tmp;
      tmp = tmp->next;
    }
  return (glFALSE);
}

t_bool		list_del_elem_at_position(t_list *front_ptr,
					  unsigned int position)
{
  t_list	last;
  t_list	tmp;
  unsigned int	cursor;

  if (*front_ptr == NULL)
    return (glFALSE);
  if (position == 0)
    return (list_del_elem_at_front(front_ptr));
  cursor = 1;
  last = *front_ptr;
  tmp = last->next;
  while (tmp != NULL)
    {
      if (cursor == position)
	{
	  last->next = tmp->next;
	  free(tmp);
	  return (glTRUE);
	}
      cursor++;
      last = tmp;
      tmp = tmp->next;
    }
  return (glFALSE);
}
