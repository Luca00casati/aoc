package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	// Open and read the input file
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	// Initialize a map to store registers
	registers := make(map[string]int)

	// Variable to track the highest value ever held
	highestEver := 0

	// Parse and process instructions
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		processInstruction(line, registers, &highestEver)
	}

	// Find the largest value in any register
	largest := findLargestValue(registers)
	fmt.Println("The largest value in any register is:", largest)
	fmt.Println("The highest value ever held in any register is:", highestEver)
}

func processInstruction(instruction string, registers map[string]int, highestEver *int) {
	// Split the instruction into parts
	parts := strings.Fields(instruction)

	// Extract relevant parts
	targetReg := parts[0]
	operation := parts[1]
	value, _ := strconv.Atoi(parts[2])
	conditionReg := parts[4]
	conditionOp := parts[5]
	conditionValue, _ := strconv.Atoi(parts[6])

	// Check the condition
	conditionRegValue := registers[conditionReg]
	condition := evaluateCondition(conditionRegValue, conditionOp, conditionValue)

	// If the condition is true, apply the operation
	if condition {
		if operation == "inc" {
			registers[targetReg] += value
		} else if operation == "dec" {
			registers[targetReg] -= value
		}

		// Update the highest value ever held
		if registers[targetReg] > *highestEver {
			*highestEver = registers[targetReg]
		}
	}
}

func evaluateCondition(regValue int, op string, condValue int) bool {
	switch op {
	case ">":
		return regValue > condValue
	case "<":
		return regValue < condValue
	case ">=":
		return regValue >= condValue
	case "<=":
		return regValue <= condValue
	case "==":
		return regValue == condValue
	case "!=":
		return regValue != condValue
	default:
		panic("Unknown operator: " + op)
	}
}

func findLargestValue(registers map[string]int) int {
	largest := 0
	for _, value := range registers {
		if value > largest {
			largest = value
		}
	}
	return largest
}
