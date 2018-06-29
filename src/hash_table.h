typedef struct {
	char* key;
	char* item;
} ht_item;

typedef struct {
	int count;
	int size;
	ht_item ** items;
} ht_hash_table;