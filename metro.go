// golang wrapper for github.com/lightning/metro
package metro

// #cgo CPPFLAGS: -I.
// #cgo LDFLAGS: -L. -lmetro
// #include "metro/metro.h"
import "C"

type Metro interface {
	Start() error
	Stop() error
	SetTempo(bpm float32) float32
	Ticks() chan uint64
}
// do we need to cover Metro_free? [bps]

type metro struct {
	C         chan uint64
	handle    C.Metro
	counter   uint64
}

func NewMetro(bpm float32) {
	m := new(metro)
	m.C = make(chan uint64)
	m.handle = C.Metro_create(C.Bpm(bpm))
	e := C.Metro_tick(m.handle)
	go metroTick(m, e)
}

func metroTick(m *metro, e C.Event) {
	for {
		C.Event_wait(e)
		m.C <- m.counter
		m.counter++
	}
}
