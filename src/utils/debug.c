#include "../../includes/minishell.h"

static int depth = 0;
static char *indent = "  ";

static void begin_scope() {
	depth++;
}

static void end_scope() {
	depth--;
}

static void print_with_ident(const char *str) {
	int i;

	i = 0;

	while (i < depth) {
		ft_printf("%s", indent);
		i++;
	}

	ft_printf("%s\n", str);
}

static void debug_node_command(AstNode *node) {
	print_with_ident("Command {");
	begin_scope();
	print_with_ident(node->token->start);
	end_scope();
	print_with_ident("}");
}

static void debug_node_and(AstNode *node) {
	print_with_ident("AND {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void debug_node_or(AstNode *node) {
	print_with_ident("OR {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void debug_node_pipe(AstNode *node) {
	print_with_ident("PIPE {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void debug_node_redirect(AstNode *node) {
	print_with_ident("Redirect {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void debug_node_redirect_append(AstNode *node) {
	print_with_ident("Append {");
	begin_scope();
	debug_command_tree(node->as.binaryExpression.left);
	debug_command_tree(node->as.binaryExpression.right);
	end_scope();
	print_with_ident("}");
}

static void debug_node_semicolon(AstNode *node) {
	print_with_ident("Semicolon {");
	begin_scope();
	t_lkd_lst *list = get_head_node(node);
	t_lkd_node *head = list->head;
	uint i = 0; 
	while (i < list->size ) {
		debug_command_tree(head->content);
		head = head->next;
		i++;
	}
	end_scope();
	print_with_ident("}");
}

void debug_command_tree(AstNode *root) {
	switch (root->type) {
		case NODE_COMMAND:
			debug_node_command(root);
		break;
		case NODE_AND:
			debug_node_and(root);
		break;

		case NODE_OR:
			debug_node_or(root);
		break;

		case NODE_REDIRECT:
			debug_node_redirect(root);
		break;

		case NODE_REDIRECT_APPEND:
			debug_node_redirect_append(root);
		break;

		case NODE_PIPE:
			debug_node_pipe(root);
		break;

		case NODE_SEMICOLON:
			debug_node_semicolon(root);
		break;

		default: 
			ft_printf("Node invalido: %s\n", root->token->start);
			exit(1);
		break;
	}
}	

void debug_token(Token *token) {
	
	switch(token->type) {
		case TOKEN_COMMAND:
			ft_printf("Token{TOKEN_COMMAND, %s}\n", token->start);
		break;
		case TOKEN_OPERATOR: 
			ft_printf("Token{TOKEN_OPERATOR, %s}\n", token->start);
		break;
		default:
			ft_printf("Token{TOKEN_ERROR, %s}\n", token->start);
		break;
	}
}
