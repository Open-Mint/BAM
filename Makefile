bam: main.cpp Bam.h Bam.cpp MainWindow.h MainWindow.cpp
	g++ -o bam main.cpp Bam.h Bam.cpp MainWindow.h MainWindow.cpp -lsfml-graphics -lsfml-window -lsfml-system
