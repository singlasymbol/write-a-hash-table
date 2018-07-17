#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define HT_PRIME_1 151
#define HT_PRIME_2 157
//just keeping them more than 128.

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


/*
	Writing a hash function.
	This hash function is supposed to return back a number between 0 to m, the bucket array length or the hashtable size.
	Ideally, hash function should return an even distribution of bucket indexes for an average set of inputs.
	If not, it may lead to collisions. As, collisions reduce the efficiency of the table.

	The prime number being used should be more than the size of alphabet
*/

static int calculateHash(const char * s, const int primeNumber, const int m) {
	long hash = 0;
	const int length = strlen(s);

	for(int i = 0; i < length; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
	}

	return (int) hash;
}


/*
	An ideal hash function would always return an even distribution. 
	However, for any hash function, there is a 'pathological' set of inputs, which all hash to the same value. 
	To find this set of inputs, run a large set of inputs through the function.
	All inputs which hash to a particular bucket form a pathological set.

	The existence of pathological input sets means there are no perfect hash functions for all inputs.
	The best we can do is to create a function which performs well for the expected data set.

	Pathological inputs also poses a security issue.
	If a hash table is fed a set of colliding keys by some malicious user, then searches for those keys will take much longer (O(n)) than normal (O(1)).
	This can be used as a denial of service attack against systems which are underpinned by hash tables, such as DNS and certain web services

	So, the question is how do we avoid Collisions?
	There are two techniques to do so - Open Addressing and Seperate Chaining.

	Here we will use open addressing with Double hashing.
	This makes use of two hash functions to calculate the index an item should be stored at after i collisions.
*/

static int getHash( const char* s, const int hashTableLength, const int attempt) {
	const int hash_a = calculateHash(s, HT_PRIME_1, hashTableLength);
	const int hash_b = calculateHash(s, HT_PRIME_2, hashTableLength);
	return (hash_a + (attempt * (hash_b + 1))) % hashTableLength; //adding 1 + hash_b so that it is never zero.
}

void insertInHashTable(hash_table* ht, const char* key, const char* value) {
	int attempt = 0;
	hash_table_item* item = hash_table_new_item(key, value);
	int index = getHash(key, ht -> size , attempt++);
	hash_table_item * currItem = ht -> items[index];

	while(currItem != NULL) {
		if(currItem != HT_DELETED_ITEM) {
			if(strcmp(currItem -> key, key) == 0) {
				delete_hash_table_item(currItem);
				ht -> items[index] = currItem;
				return;
			}
			int index = getHash(key, ht -> size , attempt++);
			hash_table_item * currItem = ht -> items[index];
		}
	}
	ht -> items[index] = currItem;
	ht -> size++;
}

void search(const char * key, hash_table * ht) {
	int attempt = 0;
	int index = getHash(key, ht -> size, attempt++);
	hash_table_item * item = ht -> items[index];

	while(item != NULL) {
		if(strcmp(item -> key, key ) == 0) {
			return item -> value;
		}
		index = getHash(key, ht -> size, attempt++);
		item = ht -> items[index];
	}

	return NULL;
}

static hash_table_item HT_DELETED_ITEM = {NULL, NULL}

void delete_item(hash_table* ht, const char * key) {
	int attempt = 0;
	int index = getHash(key, ht -> item, attempt++);
	hash_table_item * item = ht -> items[index];

	while(item != NULL) {
		if(item != &HT_DELETED_ITEM) {
			if(strcmp(item -> key, key) == 0) {
				delete_hash_table_item(item);
				ht -> items[index] = &HT_DELETED_ITEM
			}
		}
		int index = getHash(key, ht -> item, attempt++);
		hash_table_item * item = ht -> items[index];
	}
	ht -> size++;
}

