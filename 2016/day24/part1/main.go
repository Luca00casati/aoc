package main

import (
	"bufio"
	"container/list"
	"fmt"
	"math"
	"os"
)

type Point struct {
	x, y int
}

var directions = []Point{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}

func parseMap(input []string) (map[int]Point, [][]bool) {
	points := make(map[int]Point)
	grid := make([][]bool, len(input))
	for y, line := range input {
		grid[y] = make([]bool, len(line))
		for x, char := range line {
			if char >= '0' && char <= '9' {
				points[int(char-'0')] = Point{x, y}
			}
			grid[y][x] = (char != '#')
		}
	}
	return points, grid
}

func bfs(grid [][]bool, start Point) map[Point]int {
	queue := list.New()
	queue.PushBack(start)
	distances := map[Point]int{start: 0}
	rows, cols := len(grid), len(grid[0])

	for queue.Len() > 0 {
		current := queue.Remove(queue.Front()).(Point)
		currentDistance := distances[current]

		for _, dir := range directions {
			next := Point{current.x + dir.x, current.y + dir.y}
			if next.x >= 0 && next.x < cols && next.y >= 0 && next.y < rows && grid[next.y][next.x] {
				if _, visited := distances[next]; !visited {
					distances[next] = currentDistance + 1
					queue.PushBack(next)
				}
			}
		}
	}
	return distances
}

func computeAllShortestPaths(points map[int]Point, grid [][]bool) map[int]map[int]int {
	shortestPaths := make(map[int]map[int]int)
	for i, point := range points {
		distances := bfs(grid, point)
		shortestPaths[i] = make(map[int]int)
		for j, otherPoint := range points {
			if i != j {
				shortestPaths[i][j] = distances[otherPoint]
			}
		}
	}
	return shortestPaths
}

func tsp(dp map[int]map[int]int, distances map[int]map[int]int, pos int, visited int) int {
	if visited == (1<<len(distances))-1 {
		return 0
	}
	if v, ok := dp[pos][visited]; ok {
		return v
	}

	minDist := math.MaxInt32
	for next := 1; next < len(distances); next++ {
		if visited&(1<<next) == 0 {
			newVisited := visited | (1 << next)
			dist := distances[pos][next] + tsp(dp, distances, next, newVisited)
			if dist < minDist {
				minDist = dist
			}
		}
	}
	dp[pos][visited] = minDist
	return minDist
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	var input []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		input = append(input, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	points, grid := parseMap(input)
	distances := computeAllShortestPaths(points, grid)
	dp := make(map[int]map[int]int)
	for i := range distances {
		dp[i] = make(map[int]int)
	}
	shortestPathLength := tsp(dp, distances, 0, 1)
	fmt.Println("Shortest Path Length:", shortestPathLength)
}
