all:
	gcc -fno-stack-protector -ggdb -zexecstack -o tcp-server tcp-server.c
clean:
    rm tcp-server
