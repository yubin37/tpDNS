CC := gcc
CFLAGS :=
LDFLAGS := -Iinclude
vpath %.c src
vpath %.h include

all: tpDNS
tpDNS: tpDNS.c tpDNS.h hash.o packet.o
	$(CC) -o tpDNS tpDNS.c packet.o $(LDFLAGS)
	rm -f *.o 
hash.o: tpHash.c tpHash.h
	$(CC)  -o hash.o -c $< $(LDFLAGS)
packet.o: tpPacket.c tpPacket.h
	$(CC)  -o packet.o -c $< $(LDFLAGS)
clean:
	rm tpDNS
	rm -f *.o
