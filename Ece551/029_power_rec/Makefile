CFLAGES = -ggdb3 -Wall -Werror -pedantic -std=gnu99
power: power.o test-power.o
	gcc $(CFLAGES) -o power power.o test-power.o
power.o: power.c
	gcc $(CFLAGES) -c power.c
test-power.o: test-power.c
	gcc $(CFLAGES) -c test-power.c
.PHONY: clean
clean:
	rm -f *.o *~ power
