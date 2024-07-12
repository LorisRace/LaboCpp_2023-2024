ALL:	Loris-Test10b ApplicPhotoShop


Loris-Test10b:	Dimension.o Image.o ImageNG.o MyQT.o Couleur.o ImageRGB.o ImageB.o Exception.o ExceptionRGB.o XYException.o ArrayList.o Iterateur.o Traitements.o PhotoShop.o
				g++ Test10b.cpp -o Loris-Test10b MyQT.o Image.o ImageNG.o Dimension.o Couleur.o ImageRGB.o ImageB.o Exception.o ExceptionRGB.o XYException.o ArrayList.o Iterateur.o Traitements.o PhotoShop.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so




Dimension.o:	Dimension.cpp Dimension.h
				g++ Dimension.cpp -c

Image.o:		Image.cpp Image.h
				g++ Image.cpp -c

ImageNG.o:		ImageNG.cpp ImageNG.h
				g++ ImageNG.cpp -c

MyQT.o:			MyQT.cpp MyQT.h
				g++ -c MyQT.cpp -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++


Couleur.o:		Couleur.cpp Couleur.h
				g++ Couleur.cpp -c

ImageRGB.o:		ImageRGB.cpp ImageRGB.h
				g++ ImageRGB.cpp -c

ImageB.o:		ImageB.cpp ImageB.h
				g++ ImageB.cpp -c

Exception.o:	Exception.cpp Exception.h
				g++ Exception.cpp -c

ExceptionRGB.h:	ExceptionRGB.cpp ExeptionRGB.h
				g++ ExceptionRGB.cpp -c

XYException.o:	XYException.cpp XYException.h
				g++ XYException.cpp -c

ArrayList.o:	ArrayList.cpp ArrayList.h
				g++ ArrayList.cpp  -c

Iterateur.o:	Iterateur.cpp Iterateur.h
				g++ Iterateur.cpp -c

Traitements.o:	Traitements.cpp Traitements.h
				g++ Traitements.cpp -c

PhotoShop.o:	PhotoShop.cpp PhotoShop.h
				g++ PhotoShop.cpp -c


ApplicPhotoShop:	moc_mainwindowphotoshop.o mainwindowphotoshop.o main.o Dimension.o Image.o ImageNG.o MyQT.o Couleur.o ImageRGB.o ImageB.o Exception.o ExceptionRGB.o XYException.o ArrayList.o Iterateur.o Traitements.o PhotoShop.o
	echo Creation de ApplicPhotoShop...
	g++ -o ApplicPhotoShop moc_mainwindowphotoshop.o mainwindowphotoshop.o main.o Dimension.o Image.o ImageNG.o MyQT.o Couleur.o ImageRGB.o ImageB.o Exception.o ExceptionRGB.o XYException.o ArrayList.o Iterateur.o Traitements.o PhotoShop.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

moc_mainwindowphotoshop.o:	moc_mainwindowphotoshop.cpp mainwindowphotoshop.h
	echo Creation de moc_mainwindowphotoshop.o...
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_mainwindowphotoshop.o moc_mainwindowphotoshop.cpp

mainwindowphotoshop.o:	mainwindowphotoshop.cpp mainwindowphotoshop.h ui_mainwindowphotoshop.h 	
	echo Creation de mainwindowphotoshop.o...
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o mainwindowphotoshop.o mainwindowphotoshop.cpp

main.o:	main.cpp
	echo Creation de main.o...
	g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

clean:
		rm -f *.o

clobber:	clean
		rm -f Loris-Test10b
		rm -f ApplicPhotoShop