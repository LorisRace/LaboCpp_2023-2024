Loris-Test2:	Test2.cpp Dimension.o ImageNG.o
				g++ Test2.cpp Dimension.o ImageNG.o -oLoris-Test2

Dimension.o:	Dimension.cpp Dimension.h
				g++ Dimension.cpp -c

ImageNG.o:		ImageNG.cpp ImageNG.h
				g++ ImageNG.cpp -c


clean:
		rm -f *.o

clobber:	clean
		rm -f Loris-Test2 		