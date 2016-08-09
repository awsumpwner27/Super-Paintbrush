EXENAME = superpaintbrush.exe
INCDIR = include
RESDIR = resources/
SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/
SOURCES = $(wildcard $(SRCDIR)*.c)
OBJECTS = $(SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.o)
DEPENDS = $(SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.d)

#	Genereated dependency files are placed in the object directory.
#	Apparently it's more fitting that a list of all potential object files should be used as a dependency than to simply put a pattern as a dependency for the exe.

CC = gcc
CFLAGS = -std=c89 -pedantic-errors -Wall -c -g -I $(INCDIR) -MMD
LDFLAGS = 

.PHONY: all clean
.SECONDARY: $(BINDIR)$(EXENAME)

all : $(BINDIR)$(EXENAME)
ifeq ($(BUILD_THEN_RUN),1)
	@start $(BINDIR)$(EXENAME)
endif

clean :
	@rm -f $(OBJDIR)*
	@rm -f $(BINDIR)$(EXENAME)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $< $(CFLAGS) -o $@
$(BINDIR)$(EXENAME) : $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

-include $(DEPENDS)