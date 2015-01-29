.PHONY: all clean install

MAC_DIR=macosx
POSIX_DIR=posix

OS := $(shell uname -s)

LIBMETRO_AR=libmetro.a

# Get the list of object files to compile,
# some are platform-agnostic and some are not.

OBJS_GENERIC := mem.o
OBJS_PLATFORM := metro.o

ifeq ($(OS),Darwin)
PLATFORM_DIR := $(MAC_DIR)
else
PLATFORM_DIR := $(POSIX_DIR)
endif
OBJS_PLATFORM := $(addprefix $(PLATFORM_DIR)/,$(OBJS_PLATFORM))

OBJS := $(OBJS_GENERIC) $(OBJS_PLATFORM)

CPPFLAGS=-I.
CFLAGS=-Wall -g -O2

all: $(LIBMETRO_AR)

$(LIBMETRO_AR): $(OBJS)
	ar rcs $(LIBMETRO_AR) $^

clean:
	rm -rf $(LIBMETRO_AR) $(OBJS) *~ $(MAC_DIR)/*~ $(POSIX_DIR)/*~
