#include "../../includes/minishell.h"
#include <string.h>

static char * get_substr(uint start, uint end, const char *s) {
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

static uint real_string_size(const char *s, uint t_size) {
	uint sub_size;
	uint value_size;
	uint i;

	sub_size = 0;
	value_size = 0;
	i = 0;
	while (i < t_size) {
		if (s[i] == '$') {
			uint ini_pos = i + 1; // ignorando o $
			while (!ft_isspace(s[i]) && s[i]) {
				sub_size++;
				i++;
			}
			value_size += ft_strlen(getenv(get_substr(ini_pos, i, s)));
			get_substr(0, 0, NULL);
		}
		else
			i++;
	}
	return (t_size - sub_size + value_size);
}

static StringBuilder *mk_string_builder(char *s, uint size) {
	StringBuilder *sb;

	sb = (StringBuilder *) ft_calloc(1, sizeof(StringBuilder));

	if (!sb)
		return (NULL);

	sb->size = size;
	sb->start = s;

	return (sb);
}


StringBuilder *string_builder(const char *s, uint t_size) {
	uint j;
	uint i;
	char *new_str;
	char *tmp_str;

	i  = 0;
	j  = 0;

	new_str = ft_calloc(real_string_size(s, t_size) + 1, sizeof(char));

	if (!new_str)
		return (NULL); 

	while (i < t_size) {
		if (s[i] == '$') {
			uint ini_pos = i + 1; // ignorando o $
			while(!ft_isspace(s[i])) 
				i++;
			tmp_str = get_substr(ini_pos, i, s);

			ft_strlcpy(new_str + j, getenv(tmp_str), ft_strlen(getenv(tmp_str) - 1)); // ajustando o tamanho do buffer
			j += ft_strlen(getenv(tmp_str));

			free(tmp_str);
		} else
			new_str[j++] = s[i++];
	}
	return (mk_string_builder(new_str, j));
}
