
CC= g++ 
CFLAGS= -Wall -Wextra -W -O3 -pedantic
BUILDDIR= ../build/
OBJECTS= $(BUILDDIR)main.o $(BUILDDIR)files.o $(BUILDDIR)settings.o $(BUILDDIR)lines.o $(BUILDDIR)help.o $(BUILDDIR)blogentry.o $(BUILDDIR)id.o $(BUILDDIR)page.o $(BUILDDIR)sites.o $(BUILDDIR)config.o $(BUILDDIR)date.o
TARGET= $(BUILDDIR)easyblogger

$(TARGET):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILDDIR)%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(BUILDDIR)*.o

$(BUILDDIR)files.o:files.hpp lines.hpp

$(BUILDDIR)main.o:settings.hpp help.hpp sites.hpp

$(BUILDDIR)settings.o:settings.hpp files.hpp

$(BUILDDIR)lines.o:lines.hpp

$(BUILDDIR)help.o:help.hpp

$(BUILDDIR)blogentry.o:blogentry.hpp id.hpp lines.hpp files.hpp date.hpp

$(BUILDDIR)id.o:id.hpp files.hpp

$(BUILDDIR)page.o:page.hpp blogentry.hpp files.hpp settings.hpp

$(BUILDDIR)sites.o:sites.hpp page.hpp settings.hpp blogentry.hpp id.hpp files.hpp lines.hpp date.hpp

$(BUILDDIR)config.o:config.hpp settings.hpp sites.hpp

$(BUILDDIR)date.o:date.hpp
