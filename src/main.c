#include "hash_table.c"
int main() {
    hash_table* ht = new_hash_table();
    delete_hash_table(ht);
}