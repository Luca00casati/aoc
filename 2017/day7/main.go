package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Program struct {
	Weight   int
	Children []string
}

func part1() {
	// Open and read the input file
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	// Maps to track the programs
	children := make(map[string][]string) // Maps a program to its children
	allPrograms := make(map[string]bool)  // Tracks all programs

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, " -> ")
		// Extract program name and mark it
		program := strings.Fields(parts[0])[0]
		allPrograms[program] = true

		// Extract children if present
		if len(parts) > 1 {
			childPrograms := strings.Split(parts[1], ", ")
			children[program] = childPrograms

			// Mark children
			for _, child := range childPrograms {
				allPrograms[child] = true
			}
		}
	}

	// Identify the bottom program
	for program := range children {
		isChild := false
		for _, childList := range children {
			for _, child := range childList {
				if child == program {
					isChild = true
					break
				}
			}
			if isChild {
				break
			}
		}
		if !isChild {
			fmt.Println("The bottom program is:", program)
			break
		}
	}
}

func part2() {
	// Open and read the input file
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	// Parse input into program map
	programs := make(map[string]*Program)
	parents := make(map[string]string)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, " -> ")
		programInfo := strings.Fields(parts[0])
		programName := programInfo[0]
		weight, _ := strconv.Atoi(strings.Trim(programInfo[1], "()"))

		// Create program node
		program := &Program{Weight: weight}
		programs[programName] = program

		// Parse children if present
		if len(parts) > 1 {
			children := strings.Split(parts[1], ", ")
			program.Children = children

			// Track parents
			for _, child := range children {
				parents[child] = programName
			}
		}
	}

	// Find the root program
	root := findRoot(programs, parents)

	// Find the unbalanced program and correct its weight
	_, correctWeight := findImbalance(root, programs)
	fmt.Println("The correct weight is:", correctWeight)
}

func findRoot(programs map[string]*Program, parents map[string]string) string {
	for program := range programs {
		if _, hasParent := parents[program]; !hasParent {
			return program
		}
	}
	return ""
}

func findImbalance(programName string, programs map[string]*Program) (int, int) {
	program := programs[programName]

	// Base case: no children
	if len(program.Children) == 0 {
		return program.Weight, 0
	}

	// Recursive case: calculate weights of children
	childWeights := make(map[int][]string)
	totalWeight := program.Weight

	for _, child := range program.Children {
		childWeight, correction := findImbalance(child, programs)
		if correction != 0 {
			return 0, correction // Pass imbalance correction up the tree
		}
		childWeights[childWeight] = append(childWeights[childWeight], child)
		totalWeight += childWeight
	}

	// Check if child weights are balanced
	if len(childWeights) > 1 {
		// Imbalance found: identify the problematic child
		var correctWeight, incorrectWeight int
		var incorrectChild string
		for weight, children := range childWeights {
			if len(children) == 1 {
				incorrectWeight = weight
				incorrectChild = children[0]
			} else {
				correctWeight = weight
			}
		}
		// Calculate correction
		diff := correctWeight - incorrectWeight
		return 0, programs[incorrectChild].Weight + diff
	}

	return totalWeight, 0
}

func main(){
	part1()
	part2()
}