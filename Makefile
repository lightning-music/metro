.PHONY: all clean install

OS := $(shell uname -s)

LIBMETRO_AR=libmetro.a

OBJS := mem.o                  \
        metro.o

ifeq ($(OS),Darwin)
OBJS := $(addprefix macosx/,$(OBJS))
else
OBJS := $(addprefix posix/,$(OBJS))
endif

CPPFLAGS=-I.
CFLAGS=-Wall -g -O2

all: $(LIBMETRO_AR)

$(LIBMETRO_AR): $(OBJS)
	ar rcs $(LIBMETRO_AR) $^

clean:
	rm -rf $(LIBMETRO_AR) $(OBJS) *~
