all:	DP

.PHONY:
	run

DP:	main.c packet.h pkt_ostream.h pkt_oprt.h
	g++ main.c -o DP -g

clean:
	rm DP

run:
	./DP > output
