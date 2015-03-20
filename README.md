# metro
metronome suitable for music applications

# build

```shell
$ make
```

# install

```shell
$ sudo make install
```

# usage

### link flag

`-lmetro`

### API

```c

#include <metro.h>

static void *
tick(void *data)
{
        //...
}

// Initialize some data you want to use in your ticker function
Metro metro = Metro_create(120, tick, &data);

int fail = Metro_start(metro);
if (fail != 0) {
   // could not start
}

// ...

fail = Metro_stop(metro);
if (fail != 0) {
   // could not stop
}

Metro_free(&metro);
```