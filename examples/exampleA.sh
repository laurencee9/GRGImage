# Glasses example

# Create the dataset
../build/GRGImage -i ./images/glasses.jpg -o ./data/glasses -N 1000 -d 3 --contrast 3.7 --transform --CSV --GNU

# Plot with Gnuplot
gnuplot -e "dat='./data/glasses_width1200_height748.dat'; o='./networks/glasses';w=1200;h=748;r=1;png=1;lw=1.8" ../src/GNU_plot.gpi

