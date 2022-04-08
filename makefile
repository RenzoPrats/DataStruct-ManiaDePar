CFLAGS= -Wall -Werror

all: cliente

cliente: cliente.c pq_heap.o digrafo_lista_peso.o lista_peso.o
	gcc $^ -o $@

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o cliente