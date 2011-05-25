
CC= g++ 
CFLAGS= -Wall -Wextra -W -O3 -pedantic
TARGET= easyblogger
OBJECTS= main.o files.o settings.o lines.o help.o blogentry.o id.o page.o sites.o config.o date.o

$(TARGET):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o

files.o:files.hpp lines.hpp

main.o:settings.hpp help.hpp sites.hpp

settings.o:settings.hpp files.hpp

lines.o:lines.hpp

help.o:help.hpp

blogentry.o:blogentry.hpp id.hpp lines.hpp files.hpp date.hpp

id.o:id.hpp files.hpp

page.o:page.hpp blogentry.hpp files.hpp settings.hpp

sites.o:sites.hpp page.hpp settings.hpp blogentry.hpp id.hpp files.hpp lines.hpp date.hpp

config.o:config.hpp settings.hpp sites.hpp

date.o:date.hpp
