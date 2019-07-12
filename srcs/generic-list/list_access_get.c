#include	<stdlib.h>
#include	"generic_list.h"

void		*list_get_elem_at_front(t_list list)
{
  if (list == NULL)
    return (NULL);
  return (list->value);
}

void		*list_get_elem_at_back(t_list list)
{
  if (list == NULL)
    return (NULL);
  while (list->next != NULL)
    list = list->next;
  return (list->value);
}

void		*list_get_elem_like(t_list list,
				    t_bool (*func_cmp)(void *value,
						       void *param),
				    void *param)
{
  if (list == NULL)
    return (0);
  while (list != NULL)
    {
      if (func_cmp(list->value, param) == glTRUE)
	return (list->value);
      list = list->next;
    }
  return (NULL);
}

void		*list_get_elem_like_ptr(t_list list, void *cmp)
{
  if (list == NULL)
    return (0);
  while (list != NULL)
    {
      if (list->value == cmp)
	return (list->value);
      list = list->next;
    }
  return (NULL);
}

void		*list_get_elem_at_position(t_list list,
					   unsigned int position)
{
  unsigned int	cursor;

  if (list == NULL)
    return (0);
  cursor = 0;
  while (list != NULL)
    {
      if (cursor == position)
	return (list->value);
      cursor++;
      list = list->next;
    }
  return (0);
}
