package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	//generate all 3 things, needs to be biased as to be valid
	// 50 things in each
	// quantities is 10-2000
	// prices is 1 to 1000
	// meals is 0 to 10
	quantities := make([][]int, 50)
	costs := make([][]int, 50)
	meals := make([][]int, 50)

	for i, _ := range quantities {
			quantities[i] = append(quantities[i], 10 + rand.Intn(2000 - 9))
		}

	for i, _ := range costs {
		costs[i] = append(costs[i], 10 + rand.Intn(2000 - 9))
	}


	for i, _ := range meals {
		meals[i] = append(meals[i], 10 + rand.Intn(2000 - 9))
	}
	start := time.Now()
	_ = choosingShops(quantities, costs, meals)
	elapsed := time.Since(start)
	fmt.Println(elapsed)
}

type shopPair struct {
	shopX int
	shopY int
	totalQuantities []int
}

func choosingShops(quantities [][]int, costs [][]int, meals [][]int) []int {

	// every combination of shops (including x, blank)
	// some of those are valid
	// find the cheapest one between them
	results := []int{}
	totalPairsOfShops := []shopPair{}
	// first, add up all the quantities for each pair of shops
	for i, q := range quantities {
		// if we only visit 1 shop
		singleShopPair := shopPair{
			shopX: i,
			shopY: -1,
			totalQuantities: q,
		}
		totalPairsOfShops = append(totalPairsOfShops, singleShopPair)

		for j := i+1; j < len(quantities); j++ {

			quants := q
			for k, qq := range quantities[j] {
				quants[k] += qq
			}
			// if we visit 2 shops (i and j)
			dualShopPair := shopPair {
				shopX: i,
				shopY: j,
				totalQuantities: quants,
			}
			totalPairsOfShops = append(totalPairsOfShops, dualShopPair)
		}

	}

	// we can't calculate every possible set of ingredients because that would be 50 ^ 50
	// so as a solution we calculate 50^3 instead (shops * shops * meals)
	for _, meal := range meals {

		validPairsOfShops := []shopPair{}

		for _, shopPair := range totalPairsOfShops {
			// is this a valid pair, or not?
			valid := true
			for ingredient, amount := range meal {
				if shopPair.totalQuantities[ingredient] < amount {
					valid = false
					break
				}
			}

			if valid {
				validPairsOfShops = append(validPairsOfShops, shopPair)
			}
		}

		totalMinSoFar := 99999999999
		for _, currentShopPair := range validPairsOfShops {

			currentPrice := 0
				//possibility of cheapest of x and y
				//possibility of some of x and some of y
				//possibility of all x, all y
				// is x or y cheaper?
			firstShop := currentShopPair.shopX
			secondShop := currentShopPair.shopY

				for ingredient, amount := range meal {

					shopXIsCheaper := false
					if secondShop == -1 {
						shopXIsCheaper = true
					} else if costs[firstShop][ingredient] < costs[secondShop][ingredient] {
						shopXIsCheaper = true
					}

					//if shopx is cheaper, then use it first

					amountWeNeed := amount
					if shopXIsCheaper {
						if amountWeNeed > quantities[firstShop][ingredient] {
							amountWeGetFromShop1 := quantities[firstShop][ingredient]
							currentPrice += costs[firstShop][ingredient] * amountWeGetFromShop1
							amountWeNeed -= amountWeGetFromShop1
							currentPrice += costs[secondShop][ingredient] * amountWeNeed
						} else {
							// < or =
							currentPrice += costs[firstShop][ingredient] * amountWeNeed
						}
					} else {
						// shopYisCheaper
						if amountWeNeed > quantities[secondShop][ingredient] {
							amountWeGetFromShop2 := quantities[secondShop][ingredient]
							currentPrice += costs[secondShop][ingredient] * amountWeGetFromShop2
							amountWeNeed -= amountWeGetFromShop2
							currentPrice += costs[firstShop][ingredient] * amountWeNeed
						} else {
							// < or =
							currentPrice += costs[secondShop][ingredient] * amountWeNeed
						}
					}
				}

				if currentPrice < totalMinSoFar {
					totalMinSoFar = currentPrice
				}
		}

		results = append(results, totalMinSoFar)
	}

	return results
}