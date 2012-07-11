# Makefile for easyblogger
# created with makefile-creator


####################
#Settings:


CC = g++
CFLAGS =  -Wall -Wextra -pedantic -std=c++11 -O3 
CLIBS = 
INCLUDES = 
TARGET = easyblogger
OBJECTS = \
	build/actions.o \
	build/blogentry.o \
	build/comment.o \
	build/comments.o \
	build/config.o \
	build/date.o \
	build/files.o \
	build/help.o \
	build/id.o \
	build/lines.o \
	build/main.o \
	build/page.o \
	build/settings.o \



####################
#Rules:


$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(CLIBS) -o $(TARGET) $(OBJECTS)

build/%.o:
	@if test ! -d 'build'; then mkdir 'build'; echo "created 'build'" ; fi
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm build/*.o

all: $(TARGET)


####################
#Dependencies:


build/actions.o: src/actions.cpp src/actions.hpp src/blogentry.hpp src/comment.hpp src/comments.hpp src/date.hpp src/files.hpp src/id.hpp src/lines.hpp src/page.hpp src/settings.hpp 

build/blogentry.o: src/blogentry.cpp src/blogentry.hpp src/comment.hpp src/comments.hpp src/date.hpp src/files.hpp src/id.hpp src/lines.hpp src/settings.hpp 

build/comment.o: src/comment.cpp src/comment.hpp src/date.hpp src/id.hpp src/lines.hpp src/settings.hpp 

build/comments.o: src/comments.cpp src/comment.hpp src/comments.hpp src/date.hpp src/files.hpp src/id.hpp src/lines.hpp src/settings.hpp 

build/config.o: src/config.cpp src/actions.hpp src/blogentry.hpp src/comment.hpp src/comments.hpp src/config.hpp src/date.hpp src/files.hpp src/id.hpp src/lines.hpp src/page.hpp src/settings.hpp 

build/date.o: src/date.cpp src/date.hpp src/id.hpp src/lines.hpp src/settings.hpp 

build/files.o: src/files.cpp src/files.hpp src/lines.hpp 

build/help.o: src/help.cpp src/help.hpp 

build/id.o: src/id.cpp src/files.hpp src/id.hpp src/lines.hpp 

build/lines.o: src/lines.cpp src/lines.hpp 

build/main.o: src/main.cpp src/actions.hpp src/blogentry.hpp src/comment.hpp src/comments.hpp src/config.hpp src/date.hpp src/files.hpp src/help.hpp src/id.hpp src/lines.hpp src/page.hpp src/settings.hpp 

build/page.o: src/page.cpp src/blogentry.hpp src/comment.hpp src/comments.hpp src/date.hpp src/files.hpp src/id.hpp src/lines.hpp src/page.hpp src/settings.hpp 

build/settings.o: src/settings.cpp src/blogentry.hpp src/comment.hpp src/comments.hpp src/date.hpp src/files.hpp src/id.hpp src/lines.hpp src/settings.hpp 

