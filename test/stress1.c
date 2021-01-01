#include <time.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

#include <sdb.h>

int main(int argc, char **argv) {
	int key_num = 100;
	char *key, *value;
	size_t i;
	Sdb *s;

	key = malloc (sizeof(char*) * SDB_KSZ);
	value = malloc (sizeof(char*) * SDB_KSZ);
	s = sdb_new ("./", "f", 0);

	if (!key || !value || !s) {
		fprintf (stderr, "Failed to allocate sdb\n");
		return -1;
	}

	srand (time (NULL));

	for (i = 0; i < SDB_KSZ - 1; i++) {
		key[i] = 'A' + rand () % 26;
		value[i] = 'a' + rand () % 26;
	}

	key[SDB_KSZ - 2] = '\0';
	value[SDB_KSZ - 2] = '\0';

	for (i = 0; i < key_num; i++) {
		key[rand () % 250] = 'a' + i % 26;
		sdb_add (s, key, value, 0);
	}

	sdb_sync (s);
	sdb_disk_unlink (s);
	sdb_free (s);
	free (value);
	free (key);

	return 0;
}
