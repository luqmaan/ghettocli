curse:
	gcc -lncurses -Wall -o curse.out dir.c curse.c && ./curse.out

dir:
	gcc -wall -o dir.out dir.c && ./dir.out

stacktrace:
	gcc -wall -o dir.out stacktrace.c  dir.c && ./dir.out

tests: tests_dir

tests_dir:
	echo "dir.c =============="
	cd tests && gcc -wall -o dir.out ../dir.c dir.c && ./dir.out

