#include	<stdlib.h>
#include	"generic_list.h"

unsigned int	list_get_size(t_list list)
{
  unsigned int	cursor;

  cursor = 0;
  while (list != NULL)
    {
      cursor++;
      list = list->next;
    }
  return (cursor);
}

t_bool	list_is_empty(t_list list)
{
  if (list == NULL)
    return (glTRUE);
  return (glFALSE);
}

void            list_dump(t_list list, t_value_displayer val_disp)
{
  while (list != NULL)
    {
      val_disp(list->value);
      list = list->next;
    }
}
