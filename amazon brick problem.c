#include<stdio.h>

struct node {
	int *arr;
	int count;
	struct node **adj;
	int acount;
	unsigned long long cache[15];
};

void node_add_adj(struct node *n, struct node*a) {
	n->adj = realloc(n->adj, sizeof(struct node*) * (n->acount + 1));
	n->adj[n->acount++] = a;
}

struct graph {
	int count;
	struct node **nodes;
};

void graph_add_node(struct graph *g, int *perm, int pcount) {
	g->nodes = realloc(g->nodes, sizeof(struct node *) * (g->count + 1));
	g->nodes[g->count] = calloc(1, sizeof(struct node));
	g->nodes[g->count]->count = pcount;
	g->nodes[g->count]->arr = malloc(sizeof(int) * pcount);
	memcpy(g->nodes[g->count]->arr, perm, sizeof(int) * pcount);
	g->count++;
}

void permutation(struct graph *g, int n, int idx, int *perm) {
	if (n == 0) {
		graph_add_node(g, perm, idx);
		return;
	}
	if (n >= 3) {
		perm[idx] = 3;
		permutation(g, n - 3, idx + 1, perm);
	}
	if (n >= 2) {
		perm[idx] = 2;
		permutation(g, n - 2, idx + 1, perm);
	}
}

int is_adjacent(struct node *n1, struct node *n2) {
	int idx1 = 0;
	int idx2 = 0;
	int sum1 = n1->arr[idx1++];
	int sum2 = n2->arr[idx2++];

	while (idx1 < n1->count && idx2 < n2->count && sum1 != sum2) {
		if (sum1 < sum2)
			sum1 += n1->arr[idx1++];
		else
			sum2 += n2->arr[idx2++];
	};

	return sum1 != sum2;
}

void adjancencies(struct graph *g) {
	for (int i = 0; i < g->count; i++) {
		for (int j = 0; j < g->count; j++) {
			if (i == j)
				continue;
			if (is_adjacent(g->nodes[i], g->nodes[j])) {
				node_add_adj(g->nodes[i], g->nodes[j]);
			}
		}
		/* cache result for depth 1 & 2 */
		g->nodes[i]->cache[1] = 1;
		g->nodes[i]->cache[2] = g->nodes[i]->acount;
	}
}

struct graph *graph_init(int n) {
	struct graph *g = calloc(1, sizeof(struct graph));

	int *perm = malloc(sizeof(int) * (n / 2));
	permutation(g, n, 0, perm);
	adjancencies(g);
	return g;
}

void dfs(struct node *n, unsigned long long *total, int depth) {
	if (!n->cache[depth])
		for (int i = 0; i < n->acount; i++)
			dfs(n->adj[i], &(n->cache[depth]), depth - 1);
	*total += n->cache[depth];
}

int main(void) {
	int n = 64;
	int m = 10;

	struct graph *g = graph_init(n);

	for (int depth = 1; depth <= m; depth++) {
		unsigned long long total = 0;
		for (int i = 0; i < g->count; i++)
			dfs(g->nodes[i], &total, depth);
		printf("wall(%d,%2d)=%ld\n", n, depth, total);
	}
	return 0;
}