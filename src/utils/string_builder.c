#include "../../includes/minishell.h"
#include <string.h>

static char * get_substr(int start, int end, const char *s) {
	static char *ptr = NULL;

	if (!s) {
		if (ptr) {
			free(ptr);
			ptr = NULL;
		}
	}
	else
		ptr = ft_strndup(s + start, end - start); 
	return ptr;
}

static int real_string_size(const char *s, int t_size) {
	int sub_size;
	int value_size;
	int i;
	char *env;

	sub_size = 0;
	value_size = 0;
	i = 0;
	while (i < t_size) {
		if (s[i] == '$') {
			int ini_pos = i + 1; // ignorando o $
			while (!ft_isspace(s[i]) && !ft_isquote(s[i]) && s[i]) {
				sub_size++;
				i++;
			}
			env = getenv(get_substr(ini_pos, i, s));
			if (!env) 
				return -1;
			value_size += ft_strlen(env);
			get_substr(0, 0, NULL);
		}
		else
			i++;
	}
	return (t_size - sub_size + value_size);
}

static StringBuilder *mk_string_builder(char *s, int size) {
	StringBuilder *sb;

	sb = (StringBuilder *) ft_calloc(1, sizeof(StringBuilder));

	if (!sb)
		return (NULL);

	sb->size = size;
	sb->start = s;

	return (sb);
}


StringBuilder *string_builder(const char *s, int t_size) {
	int j;
	int i;
	int real_size;
	char *new_str;
	char *env;

	i  = 0;
	j  = 0;

	real_size = real_string_size(s, t_size);
	if (real_size < 0)
		return (NULL);
	new_str = ft_calloc(real_size + 1, sizeof(char));

	if (!new_str)
		return (NULL); 

	while (i < t_size) {
		if (s[i] == '$') {
			int ini_pos = i + 1; // ignorando o $
			while(!ft_isspace(s[i]) && !ft_isquote(s[i])) 
				i++;
			env = getenv(get_substr(ini_pos, i, s));

			if (!env) 
				return (NULL);

			ft_strlcpy(new_str + j, env, ft_strlen(env - 1)); // ajustando o tamanho do buffer
			j += ft_strlen(env);

			get_substr(0, 0, NULL);
		} else
			new_str[j++] = s[i++];
	}
	return (mk_string_builder(new_str, j));
}