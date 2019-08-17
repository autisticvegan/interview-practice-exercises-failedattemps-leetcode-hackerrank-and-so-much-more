package darts

import (
	"math"
)

func getDistance(x float64, y float64) float64 {
	return math.Sqrt(math.Pow(x, 2) + math.Pow(y, 2))
}

func Score(x float64, y float64) int {

dist := getDistance(x,y)
switch {
	case dist > 10:
		return 0
	case dist > 5:
		return 1
	case dist > 1:
		return 5
	default:
		return 10
}

}