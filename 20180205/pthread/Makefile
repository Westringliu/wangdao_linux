SOURCE:=$(wildcard *.c)
thread_pool_server:${SOURCE}
		gcc $^ -o $@ -pthread
clean:
		rm thread_pool_server

