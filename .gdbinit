define plist
  set var $n = $arg0->as.expressions.nodes->head
  while $n
    printf "%s\n", ((t_ast_node *) ($n->content))->token->start
    set var $n = $n->next
  end
end


define pnode
  set var $n = $arg0
  while $n
    printf "%s ", (char *) $n->content
    set var $n = $n->next
  end
end
