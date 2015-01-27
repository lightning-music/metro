.PHONY: all clean install

MAC_DIR=macosx
POSIX_DIR=posix

OS := $(shell uname -s)

LIBMETRO_AR=libmetro.a

OBJS := mem.o                  \
        metro.o

ifeq ($(OS),Darwin)
OBJS := $(addprefix $(MAC_DIR)/,$(OBJS))
else
OBJS := $(addprefix $(POSIX_DIR)/,$(OBJS))
endif

CPPFLAGS=-I.
CFLAGS=-Wall -g -O2

all: $(LIBMETRO_AR)

$(LIBMETRO_AR): $(OBJS)
	ar rcs $(LIBMETRO_AR) $^

clean:
	rm -rf $(LIBMETRO_AR) $(OBJS) *~ $(MAC_DIR)/*~ $(POSIX_DIR)/*~
