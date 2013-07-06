curse:
	gcc -lncurses -Wall -o curse.out more.c dir.c curse.c && ./curse.out

dir:
	gcc -wall -o dir.out dir.c && ./dir.out

stacktrace:
	gcc -wall -o dir.out stacktrace.c  dir.c && ./dir.out

tests: tests_dir tests_more

tests_dir:
	echo "TEST: dir.c =============="
	cd tests && gcc -wall -o dir.out ../dir.c dir.c && ./dir.out


tests_more:
	echo "TEST: more.c =============="
	cd tests && gcc -wall -o more.out ../more.c more.c && ./more.out


