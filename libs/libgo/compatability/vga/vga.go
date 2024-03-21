//Modified from OS dev.org
package vga

import "unsafe"

/*
 * Map the text mode video memory into a multi-dimensional array that can be safely
 * used from Go.
 */

func get_vidMem(addr uint32) *[25][80][2]byte {
	buff := (*[25][80][2]byte)(unsafe.Pointer(uintptr(addr)))
	return buff	
}

/*
 * This isn't a tutorial on the language itself so the rest should make sense to you.
 */

const (
	Black        = 0
	Blue         = 1
	Green        = 2
	Cyan         = 3
	Red          = 4
	Magenta      = 5
	Brown        = 6
	LightGrey    = 7
	DarkGrey     = 8
	LightBlue    = 9
	LightGreen   = 10
	LightCyan    = 11
	LightRed     = 12
	LightMagenta = 13
	LightBrown   = 14
	White        = 15
)

var Column, Row int
var Color byte
var vidMem *[25][80][2]byte

func Init() {
	vidMem = get_vidMem(0xB8000)
	Color = MakeColor(LightGrey, Black)
	Column = 0
	Row = 0
}

func MakeColor(fg, bg byte) byte {
	return fg | bg<<4
}

func ScrollUp() {
	for x := 1; x < 25; x++ {
		vidMem[x-1] = vidMem[x]
	}
	Row = 24
}

func Clear() {
	for r := 0; r < 25; r++ {
		for c := 0; c < 80; c++ {
			vidMem[r][c][0] = 32
			vidMem[r][c][1] = Color
		}
	}
}

func Poke(c rune) {
	if c == '\n' {
		Column = 0
		Row++
		if Row > 24 {
			ScrollUp()
		}
	} else {
		vidMem[Row][Column][0] = byte(c)
		vidMem[Row][Column][1] = Color
		Column++
		if Column > 79 {
			Column = 0
			Row++
			if Row > 24 {
				ScrollUp()
			}
		}
	}
}

func Print(s string) {
	for c := 0; c < len(s); c++ {
		Poke(rune(s[c]))
	}
}

func Println() {
	Print("\n");
}