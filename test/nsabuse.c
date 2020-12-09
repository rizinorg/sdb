#include "sdb.h"

int main () {
	Sdb *s = sdb_new0 ();
	if (!s) {
		eprintf ("SDB FAIL\n");
	}
	Sdb *n = sdb_ns (s, "bar", 1);
	sdb_set (n, "user.username", "some user", 0);
	sdb_set (n, "user.password", "jklsdf8r3o", 0);
	sdb_ns_set (s, "food", n);
	sdb_ns_set (sdb_ns (s, "food", 1), "words", n);
	sdb_free (s);
	return 0;
}
