package main

import (
	"fmt"
	"container/list"
	"strconv"
)

// Given favorite number
const favoriteNumber = 1352

// Function to determine if a cell is an open space or a wall
func isOpenSpace(x, y int) bool {
	value := x*x + 3*x + 2*x*y + y + y*y + favoriteNumber
	binaryRepresentation := strconv.FormatInt(int64(value), 2)
	oneBitsCount := 0
	for _, c := range binaryRepresentation {
		if c == '1' {
			oneBitsCount++
		}
	}
	return oneBitsCount%2 == 0
}

// Breadth-First Search function to find the shortest path
func bfs(start, goal [2]int) int {
	queue := list.New()
	queue.PushBack([3]int{start[0], start[1], 0})
	visited := make(map[[2]int]bool)
	visited[start] = true

	for queue.Len() > 0 {
		element := queue.Front()
		queue.Remove(element)
		current := element.Value.([3]int)
		x, y, distance := current[0], current[1], current[2]

		// If we reached the goal
		if x == goal[0] && y == goal[1] {
			return distance
		}

		// Explore neighbors
		directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
		for _, dir := range directions {
			nx, ny := x+dir[0], y+dir[1]
			if nx >= 0 && ny >= 0 {
				if _, ok := visited[[2]int{nx, ny}]; !ok && isOpenSpace(nx, ny) {
					visited[[2]int{nx, ny}] = true
					queue.PushBack([3]int{nx, ny, distance + 1})
				}
			}
		}
	}
	return -1 // If no path is found (should not happen in this problem)
}

func bfsMaxSteps(start [2]int, maxSteps int) int {
	queue := list.New()
	queue.PushBack([3]int{start[0], start[1], 0})
	visited := make(map[[2]int]bool)
	visited[start] = true

	for queue.Len() > 0 {
		element := queue.Front()
		queue.Remove(element)
		current := element.Value.([3]int)
		x, y, distance := current[0], current[1], current[2]

		// Stop if we've reached the maximum number of steps
		if distance >= maxSteps {
			continue
		}

		// Explore neighbors
		directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
		for _, dir := range directions {
			nx, ny := x+dir[0], y+dir[1]
			if nx >= 0 && ny >= 0 {
				if _, ok := visited[[2]int{nx, ny}]; !ok && isOpenSpace(nx, ny) {
					visited[[2]int{nx, ny}] = true
					queue.PushBack([3]int{nx, ny, distance + 1})
				}
			}
		}
	}
	return len(visited)
}

func part1() {
	// Start position and goal position
	start := [2]int{1, 1}
	goal := [2]int{31, 39}

	// Find the fewest number of steps required
	steps := bfs(start, goal)
	fmt.Println(steps)
}

func part2() {
	// Start position
	start := [2]int{1, 1}
	maxSteps := 50

	// Count the number of distinct locations that can be reached within 50 steps
	count := bfsMaxSteps(start, maxSteps)
	fmt.Println(count)
}

func main(){
	part2()
}