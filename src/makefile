
CC= g++
CFLAGS= -Wall -Wextra -W -O3 -pedantic -g
BUILDDIR= ../build/
OBJECTS= $(BUILDDIR)main.o $(BUILDDIR)files.o $(BUILDDIR)settings.o $(BUILDDIR)lines.o \
$(BUILDDIR)help.o $(BUILDDIR)blogentry.o $(BUILDDIR)id.o $(BUILDDIR)page.o             \
$(BUILDDIR)sites.o $(BUILDDIR)config.o $(BUILDDIR)date.o $(BUILDDIR)os_commands.o
TARGETNAME=easyblogger
TARGET= $(BUILDDIR)$(TARGETNAME)
BINDIR=/usr/bin/


$(TARGET):$(OBJECTS)
	@if test ! -d $(BUILDDIR) ; then mkdir $(BUILDDIR); echo "created $(BUILDDIR)" ; fi
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILDDIR)%.o:%.cpp
	@if test ! -d $(BUILDDIR) ; then mkdir $(BUILDDIR); echo "created $(BUILDDIR)" ; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(BUILDDIR)*.o

install:
	cp $(TARGET) $(BINDIR)

uninstall: 
	rm $(BINDIR)$(TARGETNAME)

$(BUILDDIR)files.o:files.hpp lines.hpp

$(BUILDDIR)main.o:settings.hpp help.hpp sites.hpp

$(BUILDDIR)settings.o:settings.hpp files.hpp

$(BUILDDIR)lines.o:lines.hpp

$(BUILDDIR)help.o:help.hpp

$(BUILDDIR)blogentry.o:blogentry.hpp id.hpp lines.hpp files.hpp date.hpp

$(BUILDDIR)id.o:id.hpp files.hpp

$(BUILDDIR)page.o:page.hpp blogentry.hpp files.hpp settings.hpp lines.o

$(BUILDDIR)sites.o:sites.hpp page.hpp settings.hpp blogentry.hpp id.hpp files.hpp lines.hpp date.hpp os_commands.hpp

$(BUILDDIR)config.o:config.hpp settings.hpp sites.hpp

$(BUILDDIR)date.o:date.hpp lines.hpp settings.hpp

$(BUILDDIR)os_commands.o: os_commands.hpp
