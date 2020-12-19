#include <sdb.h>
#if defined _WIN32
#include <synchapi.h>
#define sleep Sleep
#else
#include <assert.h>
#endif

int main() {
	Sdb *s = sdb_new0 ();
	sdb_set (s, "key", "val", 0);
	sdb_expire_set (s, "key", 3, 0);
	sleep (1);
	if (sdb_const_get (s, "key", 0) == NULL) {
		exit(1);
	}
	sleep (3);
	if (sdb_const_get (s, "key", 0) == NULL) {
		exit(1);
	}
	sdb_free (s);
	return 0;
}
