// golang wrapper for github.com/lightning/metro
package metro

// #cgo CPPFLAGS: -I.
// #cgo LDFLAGS: -L. -lmetro
// #include "metro/metro.h"
import "C"

type Metro struct {
	C         chan uint64
	handle    C.Metro
	counter   uint64
}

func NewMetro(bpm float32) {
	m := new(Metro)
	m.C = make(chan uint64)
	m.handle = C.Metro_create(C.Bpm(bpm))
	e := C.Metro_tick(m.handle)
	go metroTick(m, e)
}

func metroTick(metro *Metro, tick C.Event) {
	for {
		C.Event_wait(tick)
		metro.C <- metro.counter
		metro.counter++
	}
}
