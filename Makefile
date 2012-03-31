EXEC = quick_sort threaded_quick_sort

all: $(EXEC)

clean:
	rm -f $(EXEC)

quick_sort: quick_sort.c
	$(CC) --std=c99 -o quick_sort quick_sort.c

threaded_quick_sort: threaded_quick_sort.c
	$(CC) --std=c99 -lpthread -o threaded_quick_sort threaded_quick_sort.c
