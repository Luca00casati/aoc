package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Node struct {
	x, y  int
	size  int
	used  int
	avail int
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	var nodes []Node
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		if strings.HasPrefix(line, "/dev/grid/") {
			var x, y, size, used, avail int
			fmt.Sscanf(line, "/dev/grid/node-x%d-y%d %dT %dT %dT", &x, &y, &size, &used, &avail)
			nodes = append(nodes, Node{x, y, size, used, avail})
		}
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	viablePairs := 0
	for i := 0; i < len(nodes); i++ {
		for j := 0; j < len(nodes); j++ {
			if i != j && nodes[i].used > 0 && nodes[i].used <= nodes[j].avail {
				viablePairs++
			}
		}
	}

	fmt.Println("Number of viable pairs:", viablePairs)
}

