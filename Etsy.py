#etsy function to print popularity sorted shops
#only other thing I forgot to do was update the JS at the top to add .top


ShopsToPopularity = {
					"hello": 9,
					"othue": 10,
					"dubstep": 69,
					"gig": 5,
					"goodbye":0,
					"whynot": 48,
					"c":699,
					"wtf":1000
					}

def main():

	for key in sorted(ShopsToPopularity, key=ShopsToPopularity.get, reverse=True):
		print(key)

#can use del to truncate the list 

main()
a = 9