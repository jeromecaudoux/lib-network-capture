#include	<stdlib.h>
#include	"generic_list.h"

#include	<stdio.h>

t_return	list_control_all(t_list param_front_ptr,
				 t_return (*func)(void *value, void *param),
				 void *param)
{
  t_list	front_ptr;
  t_list	tmp_next;

  if (param_front_ptr == NULL)
    return (SUCCESS);
  front_ptr = param_front_ptr;
  while (front_ptr != NULL)
    {
      tmp_next = front_ptr->next;
      if (func(front_ptr->value, param) == ERROR)
	return (ERROR);
      front_ptr = tmp_next;
    }
  return (SUCCESS);
}
