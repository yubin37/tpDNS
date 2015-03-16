tpDNS: tpDNS.c include/tpDNS.h include/tpHash.h src/tpHash.c
	gcc -o tpDNS tpDNS.c 
clean:
	rm tpDNS
