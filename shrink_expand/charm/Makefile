-include ../../common.mk
CHARMC = charmc

all: client

client : client.o
	$(CHARMC) -language c++ -seq -o client client.o -lccs-client

client.o : client.C
	$(CHARMC) -o client.o client.C

clean:
	rm -f *.o client *~
