package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
	"regexp"
)

const salt = "ahsbgdzn"

func generateMD5Hash(input string) string {
	hash := md5.Sum([]byte(input))
	return hex.EncodeToString(hash[:])
}

func containsTriplet(hash string) (bool, byte) {
	for i := 0; i < len(hash)-2; i++ {
		if hash[i] == hash[i+1] && hash[i] == hash[i+2] {
			return true, hash[i]
		}
	}
	return false, 0
}

func containsQuintuplet(hash string, char byte) bool {
	quintuplet := string([]byte{char, char, char, char, char})
	return regexp.MustCompile(quintuplet).MatchString(hash)
}

func main() {
	index := 0
	keysFound := 0
	hashes := make(map[int]string)

	for {
		hash, exists := hashes[index]
		if !exists {
			hash = generateMD5Hash(fmt.Sprintf("%s%d", salt, index))
			hashes[index] = hash
		}

		hasTriplet, tripletChar := containsTriplet(hash)
		if hasTriplet {
			for i := index + 1; i <= index+1000; i++ {
				nextHash, exists := hashes[i]
				if !exists {
					nextHash = generateMD5Hash(fmt.Sprintf("%s%d", salt, i))
					hashes[i] = nextHash
				}

				if containsQuintuplet(nextHash, tripletChar) {
					keysFound++
					fmt.Printf("Key %d found at index %d\n", keysFound, index)
					break
				}
			}
		}

		if keysFound == 64 {
			fmt.Printf("The 64th key is found at index %d\n", index)
			break
		}

		index++
	}
}
