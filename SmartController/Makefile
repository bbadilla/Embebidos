.PHONY: callLib 


final: callLib
		$(CC) -o main -L./lib -I./include src/main.c src/mqtt.c -lpaho-mqtt3a -lgpio2

callLib:
		cd lib && make
