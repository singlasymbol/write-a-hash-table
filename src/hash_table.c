#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static hash_table_item* hash_table_new_item(const char* k, const char* v) {
	hash_table_item* new_item = malloc(sizeof(hash_table_item));
	new_item -> key = strdup(k);
	new_item -> val = strdup(v);
	return new_item;
}

hash_table* new_hash_table() {
	hash_table* ht = malloc(sizeof(hash_table));
	ht -> size = 53;
	ht -> count = 0;

	ht -> items = calloc((size_t)ht->size, sizeof(hash_table_item*));
	return ht;
}

static void delete_hash_table_item(hash_table_item* item) {
	free(item -> key);
	free(item -> val);
	free(item);
}

void delete_hash_table(hash_table* ht) {
	for(int i = 0; i < ht -> size ; i++) {
		hash_table_item* item = ht -> items[i];
		if(item != NULL) {
			delete_hash_table_item(item);
		}
	}
	free(ht -> items);
	free(ht);
}