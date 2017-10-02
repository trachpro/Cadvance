# Simple makefile for BT Library sample programs


TARGETS=${patsubst %.c,%,${wildcard ./*.c}}

default:	${TARGETS}

%:	%.c
	${CC} -o $@ $< -L../lib -lbt -I../inc

clean:
	rm -f ${TARGETS}

phonebook:
	gcc -o phonebook phonebook.c -L../lib -lbt -I../inc

miti:
	gcc -o mini miti.c -L../lib -lbt -I../inc