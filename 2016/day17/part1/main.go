package main

import (
    "crypto/md5"
    "encoding/hex"
    "fmt"
)

type Point struct {
    x, y int
}

type State struct {
    position Point
    path     string
}

func isOpenDoor(char byte) bool {
    return char >= 'b' && char <= 'f'
}

func getPossibleMoves(passcode, path string, position Point) []State {
    hash := md5.Sum([]byte(passcode + path))
    hashStr := hex.EncodeToString(hash[:])

    directions := []struct {
        move   string
        point  Point
        door   byte
        within func(Point) bool
    }{
        {"U", Point{position.x, position.y - 1}, hashStr[0], func(p Point) bool { return p.y >= 0 }},
        {"D", Point{position.x, position.y + 1}, hashStr[1], func(p Point) bool { return p.y < 4 }},
        {"L", Point{position.x - 1, position.y}, hashStr[2], func(p Point) bool { return p.x >= 0 }},
        {"R", Point{position.x + 1, position.y}, hashStr[3], func(p Point) bool { return p.x < 4 }},
    }

    var moves []State
    for _, d := range directions {
        if isOpenDoor(d.door) && d.within(d.point) {
            moves = append(moves, State{d.point, path + d.move})
        }
    }
    return moves
}

func findShortestPath(passcode string) string {
    start := Point{0, 0}
    end := Point{3, 3}

    queue := []State{{start, ""}}
    for len(queue) > 0 {
        current := queue[0]
        queue = queue[1:]

        if current.position == end {
            return current.path
        }

        moves := getPossibleMoves(passcode, current.path, current.position)
        queue = append(queue, moves...)
    }

    return ""
}

func main() {
    passcode := "vwbaicqe"
    shortestPath := findShortestPath(passcode)
    fmt.Println("Shortest path:", shortestPath)
}
