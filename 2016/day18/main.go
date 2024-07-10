package main

import (
	"fmt"
)

func isTrap(left, center, right byte) bool {
	return (left == '^' && center == '^' && right == '.') ||
		(center == '^' && right == '^' && left == '.') ||
		(left == '^' && center == '.' && right == '.') ||
		(right == '^' && center == '.' && left == '.')
}

func generateNextRow(currentRow string) string {
	rowLength := len(currentRow)
	nextRow := make([]byte, rowLength)

	for i := 0; i < rowLength; i++ {
		left := byte('.')
		center := currentRow[i]
		right := byte('.')

		if i > 0 {
			left = currentRow[i-1]
		}
		if i < rowLength-1 {
			right = currentRow[i+1]
		}

		if isTrap(left, center, right) {
			nextRow[i] = '^'
		} else {
			nextRow[i] = '.'
		}
	}

	return string(nextRow)
}

func countSafeTiles(row string) int {
	count := 0
	for _, tile := range row {
		if tile == '.' {
			count++
		}
	}
	return count
}

func main() {
	//initialRow := "..^^."
	initialRow := ".^^^^^.^^^..^^^^^...^.^..^^^.^^....^.^...^^^...^^^^..^...^...^^.^.^.......^..^^...^.^.^^..^^^^^...^."
	//numRows := 40
	numRows := 400000

	totalSafeTiles := 0
	currentRow := initialRow

	for i := 0; i < numRows; i++ {
		totalSafeTiles += countSafeTiles(currentRow)
		currentRow = generateNextRow(currentRow)
	}

	fmt.Printf("Total number of safe tiles: %d\n", totalSafeTiles)
}
