
EXCEC = game

SRCDIR  = Sources 
OBJDIR  = Objects
CC = gcc

SRCS    := $(shell find $(SRCDIR) -name '*.c')
HDRS    := $(shell find $(SRCDIR) -name '*.h')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

CFLAGS := -Wall 

LDFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_ttf -lm


all: $(EXCEC)

$(EXCEC) : buildrepo $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

distclean: clen
	$(RM) $(EXCEC)
	
buildrepo:
	@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef
