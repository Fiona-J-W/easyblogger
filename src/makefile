# Makefile for ../easyblogger
# created with makefile-creator


####################
#Settings:


CC = g++
CFLAGS =  -Wall -Wextra -pedantic -std=c++11 -O3 
CLIBS = 
INCLUDES = 
TARGET = ../easyblogger
OBJECTS = \
	../build/actions.o \
	../build/blogentry.o \
	../build/comment.o \
	../build/comments.o \
	../build/config.o \
	../build/date.o \
	../build/files.o \
	../build/help.o \
	../build/id.o \
	../build/lines.o \
	../build/main.o \
	../build/page.o \
	../build/settings.o \



####################
#Rules:


$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(CLIBS) -o $(TARGET) $(OBJECTS)

../build/%.o:
	@if test ! -d '../build'; then mkdir '../build'; echo "created '../build'" ; fi
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm ../build/*.o

all: $(TARGET)


####################
#Dependencies:


../build/actions.o: actions.cpp actions.hpp blogentry.hpp comment.hpp comments.hpp date.hpp files.hpp id.hpp lines.hpp page.hpp settings.hpp 

../build/blogentry.o: blogentry.cpp blogentry.hpp comment.hpp comments.hpp date.hpp files.hpp id.hpp lines.hpp settings.hpp 

../build/comment.o: comment.cpp comment.hpp date.hpp id.hpp lines.hpp settings.hpp 

../build/comments.o: comments.cpp comment.hpp comments.hpp date.hpp files.hpp id.hpp lines.hpp settings.hpp 

../build/config.o: config.cpp actions.hpp blogentry.hpp comment.hpp comments.hpp config.hpp date.hpp files.hpp id.hpp lines.hpp page.hpp settings.hpp 

../build/date.o: date.cpp date.hpp id.hpp lines.hpp settings.hpp 

../build/files.o: files.cpp files.hpp lines.hpp 

../build/help.o: help.cpp help.hpp 

../build/id.o: id.cpp files.hpp id.hpp lines.hpp 

../build/lines.o: lines.cpp lines.hpp 

../build/main.o: main.cpp actions.hpp blogentry.hpp comment.hpp comments.hpp config.hpp date.hpp files.hpp help.hpp id.hpp lines.hpp page.hpp settings.hpp 

../build/page.o: page.cpp blogentry.hpp comment.hpp comments.hpp date.hpp files.hpp id.hpp lines.hpp page.hpp settings.hpp 

../build/settings.o: settings.cpp blogentry.hpp comment.hpp comments.hpp date.hpp files.hpp id.hpp lines.hpp settings.hpp 

