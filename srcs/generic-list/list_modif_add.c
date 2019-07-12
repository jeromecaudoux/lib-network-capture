#include	<stdlib.h>
#include	"generic_list.h"

t_bool		list_add_elem_at_front(t_list *front_ptr, void *elem)
{
  t_list	new;

  if ((new = malloc(sizeof(t_node))) == NULL)
    return (glFALSE);
  new->value = elem;
  new->next = *front_ptr;
  *front_ptr = new;
  return (glTRUE);
}

t_bool		list_add_elem_at_back(t_list *front_ptr, void *elem)
{
  t_list	new_back;
  t_list	tmp;

  if ((new_back = malloc(sizeof(t_node))) == NULL)
    return (glFALSE);
  new_back->value = elem;
  new_back->next = NULL;
  if (*front_ptr == NULL)
    {
      *front_ptr = new_back;
      return (glTRUE);
    }
  tmp = *front_ptr;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new_back;
  return (glTRUE);
}

t_bool		list_add_elem_at_position(t_list *front_ptr, void *elem,
					  unsigned int position)
{
  t_list	tmp;
  t_list	new;
  t_list	last;
  unsigned int	cursor;

  if (position == 0 || front_ptr == NULL)
    return (list_add_elem_at_front(front_ptr, elem));
  cursor = 1;
  last = *front_ptr;
  tmp = last->next;
  if (tmp == NULL)
    return (list_add_elem_at_back(front_ptr, elem));
  if ((new = malloc(sizeof(t_node))) == NULL)
    return (glFALSE);
  new->value = elem;
  while (tmp != NULL)
    {
      if (position == cursor)
	{
	  last->next = new;
	  new->next = tmp;
	  return (glTRUE);
	}
      cursor++;
      last = tmp;
      tmp = tmp->next;
    }
  return (glFALSE);
}
