package main

import (
	"fmt"
)

type Disc struct {
	positions int
	startPos  int
}

func CapsuleFallsThrough(discs []Disc, dropTime int) bool {
	for i, disc := range discs {
		positionAtTime := (disc.startPos + dropTime + i + 1) % disc.positions
		if positionAtTime != 0 {
			return false
		}
	}
	return true
}

func FindFirstTime(discs []Disc) int {
	time := 0
	for {
		if CapsuleFallsThrough(discs, time) {
			return time
		}
		time++
	}
}

func main() {
	discs := []Disc{
		//Disc #1 has 13 positions; at time=0, it is at position 11.
		//Disc #2 has 5 positions; at time=0, it is at position 0.
		//Disc #3 has 17 positions; at time=0, it is at position 11.
		//Disc #4 has 3 positions; at time=0, it is at position 0.
		//Disc #5 has 7 positions; at time=0, it is at position 2.
		//Disc #6 has 19 positions; at time=0, it is at position 17.
		{positions: 13, startPos: 11},
		{positions: 5, startPos: 0},
		{positions: 17, startPos: 11},
		{positions: 3, startPos: 0},
		{positions: 7, startPos: 2},
		{positions: 19, startPos: 17},
		// part2
		{positions: 11, startPos: 0},
		// test
		//{positions: 5, startPos: 4},
		//{positions: 2, startPos: 1},
	}

	result := FindFirstTime(discs)
	fmt.Printf("The first time to press the button is at t=%d\n", result)
}
