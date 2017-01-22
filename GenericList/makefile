#makefile

FindPath:  testMap.o map.o List.o status.o
	gcc -o FindPath test.o Map.o List.o status.o

test.o:  testMap.c map.h 
	gcc -c -Wall -Wno-error testMap.c

Map.o:  map.c List.h 
	gcc -c -Wall -Wno-error map.c

List.o:  List.c status.h 
	gcc -c -Wall -Wno-error List.c

status.o:  status.c status.h 
	gcc -c -Wall -Wno-error status.c