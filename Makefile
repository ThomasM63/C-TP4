CC = g++
CFLAGS = -ansi -pedantic -Wall -std=c++11 -g #-DMAP

MAIN = analog
SRCS = analog.cpp  GestionMenu.cpp Requete.cpp LectureLog.cpp
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
