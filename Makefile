CC = g++
CFLAGS = -ansi -pedantic -Wall -std=c++11 -g #-DMAP

MAIN = main
SRCS = Requete.cpp LectureLog.cpp analog.cpp Page.cpp
OBJS = $(SRCS:.cpp=.o)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.cpp %.h
	$(CC) $(CFLAGS) -c $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c $^

.PHONY : launch

launch :
	./main
