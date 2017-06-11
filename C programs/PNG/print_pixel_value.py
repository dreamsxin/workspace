from scipy import misc

img = misc.imread("/Users/vianneyyao/Documents/img.png")

i, j , k = img.shape
for x in range(i):
	for y in range(j):
		print(img[x][y])