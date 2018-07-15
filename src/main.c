#include "hash_table.h"

int main() {
    hash_table* ht = new_hash_table();
    delete_hash_table_item(ht);
}