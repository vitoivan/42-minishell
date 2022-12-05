#include "./libft.h"


void ft_lst_print_str(t_list *lst)
{
  t_node *node;

  node = lst->head;
  ft_printf("[");
  while (node->next) {
    ft_printf("%s, ", (char *) node->content);
    node = node->next;
  }
  ft_printf("%s]", (char *) node->content);
}
