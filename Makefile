
CC = g++
CFLAGS = -ansi -pedantic -Wall -std=c++11 -g #-DMAP

MAIN = analog
SRCS = main.cpp  GestionMenu.cpp  LectureLog.cpp Requete.cpp
OBJS = $(SRCS:.cpp=.o)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.cpp %.h
	$(CC) $(CFLAGS) -c $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c $^

.PHONY : launch

launch :
	./analog
