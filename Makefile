.PHONY: all clean install

LIBMETRO_AR=libmetro.a

OBJS=mem.o              \
	 metro.o

CPPFLAGS=-I.
CFLAGS=-Wall -g -O2

all: $(LIBMETRO_AR)

$(LIBMETRO_AR): $(OBJS)
	ar rcs $(LIBMETRO_AR) $^

clean:
	rm -rf $(LIBMETRO_AR) $(OBJS) *~
