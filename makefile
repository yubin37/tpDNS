CC := gcc
CFLAGS :=
LDFLAGS := -Iinclude
vpath %.c src
vpath %.h include

all: tpDNS
tpDNS: tp_dns.c hash.o packet.o log.o
	$(CC) -o tpDNS tp_dns.c packet.o  log.o  $(LDFLAGS)
	rm -f *.o 
hash.o: tp_hash.c tp_hash.h
	$(CC)  -o hash.o -c $< $(LDFLAGS)
packet.o: tp_packet.c tp_packet.h
	$(CC)  -o packet.o -c $< $(LDFLAGS)
log.o: tp_log.c tp_log.h
	$(CC) -o log.o -c $< $(LDFLAGS)
clean:
	rm tpDNS
	rm -f *.o
