#ifndef MAIN_HPP
#define MAIN_HPP




#include <cstdlib>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tuple> 
#include <utility>
#include <algorithm> 
#include <set>
#include <iomanip> //std::setprecision
#include <map>  //Pour avoir des maps


// option parser
#include <boost/program_options.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
boost::mt19937 generator(static_cast<unsigned int>(time(0)));
boost::uniform_real<> uni_dist(0,1);
boost::variate_generator<boost::mt19937&, boost::uniform_real<> > uni(generator, uni_dist);


#define Ligne "_____________________________________________\n"

#define RESETCOLOR "\033[0m"
#define BLACK   "\033[30m"      		   /* Black */
#define RED     "\033[31m"      		   /* Red */
#define GREEN   "\033[32m"      		   /* Green */
#define YELLOW  "\033[33m"      		   /* Yellow */
#define BLUE    "\033[34m"      		   /* Blue */
#define MAGENTA "\033[35m"      		   /* Magenta */
#define CYAN    "\033[36m"      		   /* Cyan */
#define WHITE   "\033[37m"      		   /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */





#endif //TYPES_H