# Zebra example

# Create the dataset
../build/GRGImage -i ./images/zebra.jpg -o ./data/zebra -N 5000 -d 3 --contrast -2.0 --transform --CSV --GNU

# # Plot with Gnuplot
gnuplot -e "dat='./data/zebra_width800_height686.dat'; o='./networks/zebra';w=800;h=686;r=3;png=1;lw=3.0;bc='black'" ../src/GNU_plot.gpi

