  #define cimg_display 0
#include "CImg.h"
#include "main.hpp"
#include "grg.cpp"

using namespace cimg_library;

namespace po = boost::program_options;




int main(int argc, char const *argv[]) {
  
    // Parameters
  int number_nodes, degree, neigh;
  double contrast;
  std::string imagePath, outputPath;
  bool transform=false;
  bool displayGray=false;
  bool GNU = false;
  bool CSV = false;

  po::options_description description("Options");
  description.add_options()

  ("imagePath,i", po::value<std::string>(&imagePath),"Path to the image")
  ("outputPath,o", po::value<std::string>(&outputPath),"Path to the output file")
  ("number_nodes,N", po::value<int>(&number_nodes)->default_value(1000),"Number of nodes that will populate the image")
  ("degree,d", po::value<int>(&degree)->default_value(3),"Maximum degree of a node")
  ("contrast", po::value<double>(&contrast)->default_value(1.0),"Contrast parameter")
  ("neigh,n", po::value<int>(&neigh)->default_value(50),"Paramter controlling the maximum number of neighbor pixel that a node can connect to")
  ("help", "Get help")
  ("transform", "Transform the image to a network")
  ("displayGray", "Display the gray image used for geometry")
  ("CSV", "Save in csv format for d3.js")
  ("GNU", "Save in Gnuplot format");


  po::variables_map var_map;
  po::store(po::parse_command_line(argc,argv,description), var_map);
  po::notify(var_map);


  if (var_map.count("help")>0 ) {
      std::clog << description;
      return EXIT_SUCCESS;
  }
  if (var_map.count("transform")>0){
    transform = true;
  }
  if (var_map.count("displayGray")>0){
    displayGray = true;
  }

  if (var_map.count("CSV")>0){
    CSV = true;
  }
  if (var_map.count("GNU")>0){
    GNU = true;
  }


  if (transform){
    // Load the image
    const char *const imagePathChar = imagePath.c_str();
    CImg<unsigned char> src(imagePathChar);
    matrix<int> nodes(src.width(), src.height());
    matrix<int> grayScale(src.width(), src.height());

    // Get the matrix of intensity
    int total_intensity = getIntensity(src, grayScale, contrast, displayGray);

    // Place nodes on spot
    int total_number_nodes = placeTheNodes(grayScale, nodes, (double)total_intensity, (double)number_nodes);
    std::clog<<"total_number_nodes: "<<total_number_nodes<<std::endl;

    // Add links
    matrix<int> edges(total_number_nodes*degree,4);
    int total_number_edges =  addLinks(nodes, edges,  degree, neigh);


    // Save network
    if (GNU){
      saveNetworkGNU(src, edges, total_number_edges, outputPath+"_width"+std::to_string(src.width())+"_height"+std::to_string(src.height())+".dat");
    }
    if (CSV){
      saveNetworkCSV(src, edges, total_number_edges, outputPath+"_width"+std::to_string(src.width())+"_height"+std::to_string(src.height())+".csv");
    }
    
    std::clog<<"total_number_edges: "<<total_number_edges<<std::endl;
    
  }
  
  return 0;
}











