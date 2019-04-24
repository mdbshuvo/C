#This is a makefile for this project

all: Banking_management

Banking_management: main.o new.o view.o delete.o search.o update.o viewhistory.o
	gcc main.o new.o view.o delete.o search.o update.o viewhistory.o -o Banking_management

main.o: main.c
	gcc -c main.c

new.o: new.c
	gcc -c new.c

view.o: view.c
	gcc -c view.c

delete.o: delete.c
	gcc -c delete.c

search.o: search.c
	gcc -c search.c

update.o: update.c
	gcc -c update.c

viewhistory.o: viewhistory.c
	gcc -c viewhistory.c

clean:
	del *.o *.exe

rebuild: clean all
