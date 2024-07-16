package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Instruction struct {
	op   string
	x    string
	y    string
}

func parseInstruction(line string) Instruction {
	parts := strings.Fields(line)
	if len(parts) == 2 {
		return Instruction{parts[0], parts[1], ""}
	}
	return Instruction{parts[0], parts[1], parts[2]}
}

func getValue(registers map[string]int, operand string) int {
	val, err := strconv.Atoi(operand)
	if err == nil {
		return val
	}
	return registers[operand]
}

func simulate(instructions []Instruction, initialA int) bool {
	registers := map[string]int{"a": initialA, "b": 0, "c": 0, "d": 0}
	ip := 0
	expected := 0
	count := 0

	for ip >= 0 && ip < len(instructions) {
		inst := instructions[ip]
		switch inst.op {
		case "cpy":
			val := getValue(registers, inst.x)
			registers[inst.y] = val
		case "inc":
			registers[inst.x]++
		case "dec":
			registers[inst.x]--
		case "jnz":
			val := getValue(registers, inst.x)
			if val != 0 {
				ip += getValue(registers, inst.y) - 1
			}
		case "out":
			val := getValue(registers, inst.x)
			if val != expected {
				return false
			}
			expected = 1 - expected
			count++
			if count >= 10 {
				return true
			}
		}
		ip++
	}
	return false
}

func findInitialValue(instructions []Instruction) int {
	for a := 1; ; a++ {
		if simulate(instructions, a) {
			return a
		}
	}
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	var instructions []Instruction
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		instructions = append(instructions, parseInstruction(line))
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	result := findInitialValue(instructions)
	fmt.Println("The lowest positive integer that generates the correct clock signal is:", result)
}
