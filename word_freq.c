#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct word_t {
	const char *p_str;
	size_t len;
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

node_t* create(const word_t* word)
{
	node_t* t_node = malloc(sizeof(node_t));
	if (t_node != NULL) {
		*t_node = (node_t){ *word, 1, NULL };
	}
	return t_node;
}

void insert(node_t** node, const word_t* word) {
	if (*node == NULL) {
		*node = create(word);
	}
	else {
		node_t* t_node = *node;
		while (t_node->next != NULL) {
			if (compare_words(&t_node->word, word)) {
				++t_node->count;
				return;
			}
			t_node = t_node->next;
		}
		t_node->next = create(word);
	}
}

node_t* tokenzie(const char* str) {
	node_t* node = NULL;
	const char* p = NULL;
	size_t len = 0;
	short fl = 0;
	while (*str) {
		if (isspace(*str)) {
			if (fl == 1) {
				word_t word = { p, len };
				insert(&node, &word);
				len = 0;
				fl = 0;
			}
		} else {
			if (len == 0) {
				p = str;
				fl = 1;
			}
			++len;
		}
		++str;
	}
	if (len > 0) {
		word_t word = { p, len };
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
