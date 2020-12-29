# Makefile for week03

all:	msg_rcv msg_send structs

msg_rcv:	msg_rcv.c
	gcc -o msg_rcv msg_rcv.c

msg_send:	msg_send.c
	gcc -o msg_send msg_send.c

structs:	structs.c
	gcc -o structs structs.c

clean:
	rm -f msg_rcv msg_send structs
