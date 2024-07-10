package main

import (
	"fmt"
)

func lastElfStanding(n int) int {
	largestPowerOf3 := 1
	for largestPowerOf3*3 <= n {
		largestPowerOf3 *= 3
	}
	
	if n == largestPowerOf3 {
		return n
	} else if n <= 2*largestPowerOf3 {
		return n - largestPowerOf3
	} else {
		return 2*n - 3*largestPowerOf3
	}
}

func main() {
	n := 3014603
	result := lastElfStanding(n)
	fmt.Printf("The Elf that gets all the presents is at position: %d\n", result)
}
