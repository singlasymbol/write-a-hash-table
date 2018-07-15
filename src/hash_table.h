typedef struct {
	char* key;
	char* val;
} hash_table_item;

typedef struct {
	int count;
	int size;
	hash_table_item ** items;
} hash_table;