#ifndef GENERIC_LIST_H_
# define GENERIC_LIST_H_

# include	"types.h"

typedef struct		s_node
{
    void		*value;
    struct s_node	*next;
}			t_node;

typedef t_node *	t_list;
typedef void		(*t_value_displayer)(void *value);
typedef int		(*t_value_comparator)(void *first, void *second);

/*
** Informations
*/
unsigned int    list_get_size(t_list list);
t_bool          list_is_empty(t_list list);
void            list_dump(t_list list, t_value_displayer val_disp);

/*
** Modification
*/
t_bool  list_add_elem_at_front(t_list *front_ptr, void *elem);
t_bool  list_add_elem_at_back(t_list *front_ptr, void *elem);
t_bool  list_add_elem_at_position(t_list *front_ptr, void *elem,
				  unsigned int position);

t_bool  list_del_elem_at_front(t_list *front_ptr);
t_bool  list_del_elem_at_back(t_list *front_ptr);
t_bool  list_del_elem_at_position(t_list *front_ptr, unsigned int position);
t_bool	list_del_elem_like(t_list *front_ptr, void *value,
			   void (*free_func)(void *value));

void    list_clear(t_list *front_ptr, void (*free_func)(void *elem));

/*
** Value Access
*/
void    *list_get_elem_at_front(t_list list);
void    *list_get_elem_at_back(t_list list);
void    *list_get_elem_at_position(t_list list, unsigned int position);
void	*list_get_elem_like_ptr(t_list list, void *cmp);
void	*list_get_elem_like(t_list list,
			    t_bool (*func_cmp)(void *value,
					       void *param),
			    void *param);

/*
** Node Access
*/
t_node  *list_get_first_node_with_value(t_list list, void *value,
					t_value_comparator val_comp);

/*
** Node control
*/
t_return	list_control_all(t_list param_front_ptr,
				 t_return (*func)(void *value, void *param),
				 void *param);

#endif /* !GENERIC_LIST_H_ */
