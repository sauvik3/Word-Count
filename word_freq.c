#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

typedef struct word_t {
	const char *p_str;
	int len;
} word_t;

typedef struct node_t {
	word_t word;
	int count;
	struct node_t *next;
} node_t;

int compare_words(const word_t *w1, const word_t *w2) {
	for (int i = 0; i< w1->len; ++i) {
		if (w1->p_str[i] != w2->p_str[i]) {
			return 0;
		}
	}
	return 1;
}

node_t * word_pos(node_t *node, const word_t *word) {
	while (node) {
		if (compare_words(&node->word, word) == 1) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void insert(node_t **node, word_t *word) {
	if (!*node) {
		*node = (node_t *)malloc(sizeof(node_t));
		**node = (node_t) { *word, 1, NULL };
	}
	else {
		node_t * pos = word_pos(*node, word);
		if (pos) {
			++pos->count;
		}
		else {
			node_t *t_node = *node;
			while (t_node->next) {
				t_node = t_node->next;
			}
			t_node->next = (node_t *)malloc(sizeof(node_t));
			*t_node->next = (node_t) { *word, 1, NULL };
		}
	}
}

node_t *tokenzie(const char *str) {
	node_t *node = NULL;
	const char *p = str;
	int l = 0;
	while (*str++) {
		++l;
		if (isspace(*str)) {
			word_t word = { p, l };
			insert(&node, &word);
			if (str[1]) {
				p = ++str;
			}
			l = 0;
		}
	}
	if (l>1) {
		word_t word = { p, l };
		insert(&node, &word);
	}
	return node;
}

void print_freq(const node_t *node) {
	while (node) {
		printf("%.*s : %d\n", node->word.len, node->word.p_str, node->count);
		node = node->next;
	}
}

void free_nodes(node_t *node) {
	while (node) {
		node_t *t = node;
		node = node->next;
		free(t);
	}
}

int main() {
	char str[] = "abcd aes v sdfsg abcd aes ku";
	node_t *node = tokenzie(str);
	print_freq(node);
	free_nodes(node);

	return 0;
}
