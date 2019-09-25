build: movie.c labirintt.c tema3.h list.c list.h queue.c queue.h stack.c stack.h heap.c heap.h 
	gcc -Wall movie.c tema3.h list.c list.h stack.c stack.h queue.c queue.h heap.c heap.h -o movies -g
	gcc -Wall labirintt.c tema3.h list.c list.h stack.c stack.h queue.c queue.h heap.c heap.h -o labirint -g

run: movies labirint
	./movies 
	./labirint 

clean:
	rm -f movies
	rm -f labirint
