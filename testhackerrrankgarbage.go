package main

import (
	"fmt"
)

func isPowerOfTwo(val uint32) bool {
	return (val & (val - 1)) == 0
}

func visuallyBalancedSections(colors [4]uint32) uint32 {
    // Write your code here
	var total uint32 
	total = 0
	
	for i, _ := range colors {

		var xorVal uint32 
		xorVal = 0
		
		for j := i; j < len(colors); j++ {

			leftShifted := xorVal << colors[j]
			xorVal ^= leftShifted
			if xorVal == 0 || isPowerOfTwo(xorVal) {
				total++
			}

		}


	}
	
	
	return total
}
func main() {
	t := [...]uint32{1,2,2,1}
	fmt.Println(visuallyBalancedSections(t))
}
