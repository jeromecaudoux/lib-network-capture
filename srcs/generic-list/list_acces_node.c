#include	<stdlib.h>
#include	"generic_list.h"

t_node  *list_get_first_node_with_value(t_list list, void *value,
					t_value_comparator val_comp)
{
  if (list == NULL)
    return (0);
  while (list != NULL)
    {
      if (val_comp(value, list->value) == 0)
	return (list);
      list = list->next;
    }
  return (0);
}
