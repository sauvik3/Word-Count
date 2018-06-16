#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

typedef struct word_t {
	const char *p;
	int l;
} word_t;

typedef struct node_t {
	word_t *w;
	int n;
	struct node_t *nxt;
} node_t;

int compare_words(const word_t *w1, const word_t *w2) {
	for (int i = 0; i< w1->l; ++i) {
		if (w1->p[i] != w2->p[i]) {
			return 0;
		}
	}
	return 1;
}

node_t * word_pos(node_t *node, const word_t *word) {
	while (node) {
		if (compare_words(node->w, word) == 1) {
			return node;
		}
		node = node->nxt;
	}
	return NULL;
}

void insert(node_t **node, word_t word) {
	if (!*node) {
		*node = (node_t *)malloc(sizeof(node_t));
		word_t *wt = (word_t *)malloc(sizeof(word_t));
		memcpy(wt, &word, sizeof(word_t));
		(*node)->w = wt;
		(*node)->n = 1;
		(*node)->nxt = NULL;
	}
	else {
		node_t * pos = word_pos(*node, &word);
		if (pos) {
			++pos->n;
		}
		else {
			node_t *t_node = *node;
			while (t_node->nxt) {
				t_node = t_node->nxt;
			}
			t_node->nxt = (node_t *)malloc(sizeof(node_t));
			word_t *wt = (word_t *)malloc(sizeof(word_t));
			memcpy(wt, &word, sizeof(word_t));
			t_node->nxt->w = wt;
			t_node->nxt->n = 1;
			t_node->nxt->nxt = NULL;
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
			insert(&node, word);
			if (str[1]) {
				p = ++str;
			}
			l = 0;
		}
	}
	if (l>1) {
		word_t word = { p, --l };
		insert(&node, word);
	}
	return node;
}

void print_freq(const node_t *node) {
	while (node) {
		printf("%.*s", node->w->l, node->w->p);
		printf(" : %d\n", node->n);
		node = node->nxt;
	}
}

void free_nodes(node_t *node) {
	while (node) {
		node_t *t = node;
		node = node->nxt;
		if (t->w) {
			free(t->w);
		}
		free(t);
	}
}

int main() {
	char str[] = "abcd aes v sdfsg abcd aes ku  ";
	node_t *node = tokenzie(str);
	print_freq(node);
	free_nodes(node);

	return 0;
}