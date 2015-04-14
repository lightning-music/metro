// metronome suitable for applications that require
// the smallest amount of clock jitter possible
package metro

// #include "metro.h"
// #cgo linux LDFLAGS: -lrt
import "C"
import "fmt"

type Pos uint64

type Metro interface {
	Start() error
	Stop() error
	SetTempo(bpm float32) float32
	Ticks() chan Pos
}

// do we need to cover Metro_free? [bps]

type metro struct {
	c       chan Pos
	handle  C.Metro
	counter Pos
}

func (self *metro) Start() error {
	if rc := C.Metro_start(self.handle); rc != 0 {
		return fmt.Errorf("Could not start metro %d", rc)
	}
	return nil
}

func (self *metro) Stop() error {
	if rc := C.Metro_stop(self.handle); rc != 0 {
		return fmt.Errorf("Could not stop metro %d", rc)
	}
	return nil
}

func (self *metro) SetTempo(bpm float32) float32 {
	return float32(C.Metro_set_bpm(self.handle, C.Bpm(bpm)))
}

func (self *metro) Ticks() chan Pos {
	return self.c
}

func New(bpm float32) Metro {
	m := new(metro)
	m.c = make(chan Pos)
	m.handle = C.Metro_create(C.Bpm(bpm))
	m.counter = 0
	e := C.Metro_tick(m.handle)
	go metroTick(m, e)
	return m
}

func metroTick(m *metro, e C.Event) {
	for {
		C.Event_wait(e)
		m.c <- m.counter
		m.counter++
	}
}
