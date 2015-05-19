APP     = emu

SRCDIR  = src
OBJDIR  = bin

SRCS    := $(shell find $(SRCDIR) -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

CFLAGS  = -Wall
LDFLAGS =


all: $(APP)

$(APP) : buildrepo $(OBJS)
		$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

distclean: clean
		$(RM) $(APP)

buildrepo:
		@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
	      do \
		  	mkdir -p $(OBJDIR)/$$dir; \
			   done
   endef
