#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
	ht_item* i = malloc(sizeof(ht_item));
	i -> key = strdup(k);
	i -> val = strdup(v);
	return i;
}

ht_hash_table* ht_new() {
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));
	ht -> size = 53;
	ht -> count = 0;

	ht -> items = calloc((size_t)ht->size, sizeof(ht_item*));
}

static void ht_del_item(ht_item* i) {
	free(i -> key);
	free(i -> val);
	free(i);
}

void del_ht(ht_hash_table* ht) {
	for(int i = 0; i < ht -> size ; i++) {
		ht_item* i = ht -> items[i];
		if(i != null) {
			ht_del_item(i);
		}
	}
	free(ht -> items);
	free(ht);
}