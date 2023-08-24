default: apgasclient

all: apgasclient charmclient

apgasclient: apgas/Client.class

apgas/Client.class: apgas/Client.java
	javac $<

charmclient:
	make -C charm
