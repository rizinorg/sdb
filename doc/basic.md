Usage Example
=============

Let's create a database!

	$ sdb d hello=world
	$ sdb d hello
	world

Using arrays (>=0.6):

	$ sdb - '[]list=1,2' '[0]list' '[0]list=foo' '[]list' '[+1]list=bar'
	1
	foo
	2
	foo
	bar
	2

Using the commandline without any disk database:

	$ sdb - foo=bar foo a=3 +a -a
	bar
	4
	3

	$ sdb -
	foo=bar
	foo
	bar
	a=3
	+a
	4
	-a
	3
	
Remove the database

	$ rm -f d
