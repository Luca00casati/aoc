package main

import "fmt"

func josephus(n int) int {
    highestPowerOf2 := 1
    for highestPowerOf2 <= n {
        highestPowerOf2 <<= 1
    }
    highestPowerOf2 >>= 1

    l := n - highestPowerOf2
    return 2 * l + 1
}

func main() {
    n := 3014603
    result := josephus(n)
    fmt.Printf("The Elf that gets all the presents is at position: %d\n", result)
}
