#ifndef GRG_CPP
#define GRG_CPP

#include "grg.hpp"
#include "main.hpp"

int getIntensity(const CImg<unsigned char> &image, matrix<int> &grayScale,
				 double contrast, bool displayGray){

	/*
		Get the grayScale of each pixel
	*/

	int total_intensity = 0;

	CImg<unsigned char> imgR(image.width(), image.height(), 1, 3, 0),
          imgG(image.width(), image.height(), 1, 3, 0),
          imgB(image.width(), image.height(), 1, 3, 0),
          imgGray(image.width(), image.height(), 1, 1, 0);

   cimg_forXY(image,x,y) {
    imgR(x,y,0,0) = image(x,y,0,0),    
    imgG(x,y,0,1) = image(x,y,0,1),    
    imgB(x,y,0,2) = image(x,y,0,2); 

  	int R = (int)image(x,y,0,0);
    int G = (int)image(x,y,0,1);
    int B = (int)image(x,y,0,2);

    // std::clog<<R<<"\t"<<G<<"\t"<<B<<std::endl;

    double u = (255-(int)(0.299*R + 0.587*G + 0.114*B))/255.0;
    double grayValue;
    if (contrast<0){
    	grayValue = pow(1.0-u, -1*contrast);
    }
    else {
    	grayValue = pow(u, contrast);
    }
    grayScale(x,y) = (int) (grayValue*255.0);
    imgGray(x,y,0,0) = (int) (grayValue*255.0);

    total_intensity +=  grayScale(x,y);
   }

  /* Uncomment if cmake works with display
  if (displayGray){

  	CImgDisplay main_disp(imgGray,"Gray");
	while (!main_disp.is_closed()){
		main_disp.wait();
	}
  }
  */
  

   return total_intensity;
}

int placeTheNodes(matrix<int> &grayScale, 
				 matrix<int> &nodes, 
				 double total_intensity,
				  double number_nodes){

	int total_number_nodes = 0;
	
	for (int i = 0; i < grayScale.size1(); ++i)
	{
		for (int j = 0; j < grayScale.size2(); ++j)
		{
			double p = grayScale(i,j)*(number_nodes/total_intensity);
			// std::clog<<p<<"\t"<<1.0-exp(-p)<<std::endl;
			if (uni()< 1.0-exp(-p)){
				nodes(i,j) = 1;
				total_number_nodes += 1;
				// imgNode(i,j,0,0) = 255;
			}
			else {
				nodes(i,j) = 0;
				// imgNode(i,j,0,0) = 0;
			}
		}
	}

	return total_number_nodes;
}

int min(int a, int b) {
	if (a<b){
		return a;
	}
	return b;
}
int max(int a, int b) {
	if (a>b){
		return a;
	}
	return b;
}

int addLinks(matrix<int> &nodes, matrix<int> &edges, int degree, int neigh){


	int total_number_edges = 0;
	
	for (int i = 0; i < nodes.size1(); ++i)
	{
		for (int j = 0; j < nodes.size2(); ++j)
		{
			if (nodes(i,j)==1){

			
				std::vector<std::tuple<double, int, int>> possible_edges;
				// Check its neighbors
				for (int inear = max(0,i-neigh); inear < min(nodes.size1(),i+neigh); ++inear)
				{
					for (int jnear = max(0,j-neigh); jnear < min(nodes.size2(),j+neigh); ++jnear)
					{	
						if ((i==inear) && (j==jnear)){

						}
						else {
							if (nodes(inear, jnear)==1 ){
								double distance = sqrt(pow(i-inear,2)+pow(j-jnear,2));
								possible_edges.push_back(std::make_tuple (distance, inear, jnear));
							}
						}						
					}
				}
				if (possible_edges.size()>degree){
					std::sort(possible_edges.begin(), possible_edges.end());
				}
				for (int k = 0; k < min(possible_edges.size(),degree); ++k)
				{
					edges(total_number_edges,0) = i;
					edges(total_number_edges,1) = j;
					edges(total_number_edges,2) = std::get<1>(possible_edges[k]);
					edges(total_number_edges,3) = std::get<2>(possible_edges[k]);
					total_number_edges += 1;
				}
				

			}
	
		}
	}

	return total_number_edges;
}

void saveNetworkCSV(CImg<unsigned char> &src, matrix<int> &edges, int number_edges, std::string filename){

	std::ofstream outfile (filename, std::ios::out);
	outfile<<"i1,j1,i2,j2,r,g,b"<<std::endl;
	for (int i = 0; i < number_edges; i++){

    	int x = edges(i,0);
    	int y = edges(i,1);
		outfile<< edges(i,0)<<","<<edges(i,1)<<","<<edges(i,2)<<","<<edges(i,3)<<","
			<<(int)src(x,y,0,0)<<","<<(int)src(x,y,0,1)<<","<<(int)src(x,y,0,2)<<std::endl;
	}
	outfile.close();
}

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}


void saveNetworkGNU(CImg<unsigned char> &src, matrix<int> &edges, int number_edges, std::string filename){

	std::ofstream outfile (filename, std::ios::out);
	outfile<<"#i,j,r,g,b"<<std::endl;
	for (int i = 0; i < number_edges; i++){
		

  //   	// HEX
		// int x = edges(i,0);
    	// int y = edges(i,1);
 		//  const unsigned red = (int)src(x,y,0,0), green = (int)src(x,y,0,1), blue = (int)src(x,y,0,2);
		// char hexcol[16];
		// snprintf(hexcol, sizeof hexcol, "%02x%02x%02x", red, green, blue);
		// outfile<< edges(i,0)<<" "<<src.height()-edges(i,1)<<","<<hexcol<<std::endl;
		// outfile<< edges(i,2)<<" "<<src.height()-edges(i,3)<<",'#"<<hexcol<<"'\n"<<std::endl;

		// RGB
		int x = edges(i,0);
  		int y = edges(i,1);
		outfile<< edges(i,0)<<","<<src.height()-edges(i,1)<<","<<(int)src(x,y,0,0)<<","<<(int)src(x,y,0,1)<<","<<(int)src(x,y,0,2)<<std::endl;
		outfile<< edges(i,2)<<","<<src.height()-edges(i,3)<<","<<(int)src(x,y,0,0)<<","<<(int)src(x,y,0,1)<<","<<(int)src(x,y,0,2)<<"\n"<<std::endl;


	}
	outfile.close();
}



#endif






