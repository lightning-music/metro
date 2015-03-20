.PHONY: all clean install test

MAC_DIR=macosx
POSIX_DIR=posix

OS := $(shell uname -s)

LIBMETRO_AR=libmetro.a

# Get the list of object files to compile,
# some are platform-agnostic and some are not.

OBJS_GENERIC := event.o mem.o ringbuffer.o time.o
OBJS_PLATFORM := metro.o thread.o

ifeq ($(OS),Darwin)
PLATFORM_DIR := $(MAC_DIR)
else
PLATFORM_DIR := $(POSIX_DIR)
endif
OBJS_PLATFORM := $(addprefix $(PLATFORM_DIR)/,$(OBJS_PLATFORM))

OBJS := $(OBJS_GENERIC) $(OBJS_PLATFORM)

TEST_PROGS := $(wildcard test/*.c)
TEST_PROGS := $(subst .c,,$(TEST_PROGS))

EXAMPLE_PROGS := $(wildcard examples/*.c)
EXAMPLE_PROGS := $(subst .c,,$(EXAMPLE_PROGS))

# gcc flags

CPPFLAGS=-I.
CFLAGS=-Wall -g -O2 -pthread
LDFLAGS=-L.
LDLIBS=-lcheck -lmetro

all: $(LIBMETRO_AR)

$(LIBMETRO_AR): $(OBJS)
	ar rcs $(LIBMETRO_AR) $^

clean:
	rm -rf $(LIBMETRO_AR) $(OBJS) *~ $(MAC_DIR)/*~ $(POSIX_DIR)/*~ \
        $(TEST_PROGS) $(EXAMPLE_PROGS) examples/*~ test/*~
	find . -name '*.dSYM' -type d -exec rm -rf '{}' \;

test: $(LIBMETRO_AR) $(TEST_PROGS)
	@for test in $(TEST_PROGS); do $$test; done

examples: $(LIBMETRO_AR) $(EXAMPLE_PROGS)
