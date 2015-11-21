Assignment9:
	gcc -c -fpic library.cpp
	gcc -shared -o library.so library.o
	g++ -std=c++11 -o Assignment9 Assignment9.cpp -ldl
clean:
	rm *.o
	rm Assignment9
