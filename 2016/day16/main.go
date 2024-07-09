package main

import (
	"fmt"
	"strings"
)

func reverseAndInvert(s string) string {
	n := len(s)
	inverted := make([]byte, n)
	for i := 0; i < n; i++ {
		if s[n-1-i] == '0' {
			inverted[i] = '1'
		} else {
			inverted[i] = '0'
		}
	}
	return string(inverted)
}

func generateData(initialState string, desiredLength int) string {
	data := initialState
	for len(data) < desiredLength {
		reversedInverted := reverseAndInvert(data)
		var sb strings.Builder
		sb.Grow(len(data) + 1 + len(reversedInverted))
		sb.WriteString(data)
		sb.WriteByte('0')
		sb.WriteString(reversedInverted)
		data = sb.String()
	}
	return data[:desiredLength]
}

func calculateChecksum(data string) string {
	for {
		n := len(data)
		checksum := make([]byte, n/2)
		for i := 0; i < n; i += 2 {
			if data[i] == data[i+1] {
				checksum[i/2] = '1'
			} else {
				checksum[i/2] = '0'
			}
		}
		if len(checksum)%2 != 0 {
			return string(checksum)
		}
		data = string(checksum)
	}
}

func main() {
	initialState := "10001110011110000"
	diskLength := 35651584 // part1: 272

	data := generateData(initialState, diskLength)
	fmt.Println("Generated Data:", data)

	checksum := calculateChecksum(data)
	fmt.Println("Checksum:", checksum)
}
