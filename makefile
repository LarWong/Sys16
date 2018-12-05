all: shmegegge.c
	gcc -o share shmegegge.c
clean:
	rm -f share *.o *~ *gch
run:
	./share
