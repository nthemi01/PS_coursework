#include "../include/landscape.h"



landscape::landscape(const Params &pars, const std::string kMapPath, const std::string kPumasPath = "", const std::string kHaresPath = "")
{
	//Extract size of the landscape
    std::ifstream map_file;
	map_file.open(kMapPath.c_str());
    if (!map_file.is_open())
    {
        std::cout<< "Failed to open map file. Given kPath: " <<  kMapPath << std::endl;
		throw std::invalid_argument("Invalid map file kPath");
    }
	else{
	map_file >> grid_size_x >> grid_size_y;
	
	//Add space for a ring of water. Note vector initializes to 0 so the ring will be added automatically
	grid_size_x += 2; grid_size_y += 2;
	
	map.resize(grid_size_x, std::vector<bool>(grid_size_y,0)); // Initialize the map matrix, whicht contains the morphology(true: land, false:water)
	hares.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the hare density matrix
	pumas.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the puma density matrix
	pumas_old.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the pumas_old matrix (used by the progress function)
	hares_old.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the hares_old  matrix (used by the progress function)
	N.resize(grid_size_x, std::vector<int>(grid_size_y,0)); // Initialize the N  matrix (for counting "dry" neighbors, used by the progress function)
	map_file.close();
	}
	
	if(!ReadInFile(kMapPath, map)){
		std::cout<< "Failed to read in map file. Given kPath: " <<  kMapPath << std::endl;		
	}
	
	std::srand(std::time(NULL)); //Seed random number generator
	
	if(kPumasPath != ""){
		if(!ReadInFile(kPumasPath, pumas)){
		std::cout << "Failed to read in puma density file. Given kPath: " <<  kPumasPath << std::endl<< "Have Generated a random initial density." << std::endl;;
		GenerateRandomDensity(pumas,map);}  //Handle failed density reading
	}
	else
		GenerateRandomDensity(pumas,map);
	if(kHaresPath != ""){
		if(!ReadInFile(kHaresPath, hares)){
		std::cout << "Failed to read in hare density file. Given kPath: " <<  kHaresPath << std::endl << "Have Generated a random initial density." << std::endl;
		GenerateRandomDensity(hares,map);}
	}
	else
		GenerateRandomDensity(hares,map);
						
	
	r = pars.r; a = pars.a; b = pars.b; m = pars.m; k = pars.k; l = pars.l; dt = pars.dt; 

	// filling the N matrix that represents the number of dry neighbors
	for(int i=1;i<grid_size_x-1;i++)
		for(int j=1;j<grid_size_y-1;j++)
			N[i][j]=map[i+1][j]+map[i][j+1]+map[i-1][j]+map[i][j-1];
		
		
		
	//Console output - To see the map and params
	
	// for(int x=0; x<grid_size_x; x++){
		// for(int y=0; y<grid_size_y; y++){			
			// std::cout << map[x][y];
		// }
		// std::cout << std::endl;
	// }	
	
	// std::cout << "r=" << r << " a=" << a << " b=" << b<< " m=" << m<< " k=" << k<< " l=" << l << std::endl;	
	// std::cout << "size of map: " << map.size() << " by " << map[0].size() << std::endl;

}


/*
	Progress function does the actual computation for both Pumas and Hares
 	and calculates the densities for for the next time step.
*/
void landscape::progress()
{
	pumas_old=pumas;
	hares_old=hares;


	for(int i=1;i<grid_size_x-1;i++)
		for(int j=1;j<grid_size_y-1;j++)
			if(map[i][j])
			{
				double part1,part2;

				part1 = hares_old[i-1][j]+hares_old[i+1][j]+hares_old[i][j-1]+hares_old[i][j+1];	
				part2 = k*(part1 - N[i][j]*hares_old[i][j]);
				hares[i][j] = hares_old[i][j] + dt*( r*hares_old[i][j] - a*hares_old[i][j]*pumas_old[i][j] + part2);
				hares[i][j] = abs(hares[i][j]); // In case the value gets negative, we make it positive so it will be physical
	
				part1 = pumas_old[i-1][j]+pumas_old[i+1][j]+pumas_old[i][j-1]+pumas_old[i][j+1];	
				part2 = l*(part1 - N[i][j]*pumas_old[i][j]);			
				pumas[i][j] = pumas_old[i][j] + dt*( b*hares_old[i][j]*pumas_old[i][j] - m*pumas_old[i][j] + part2);
				pumas[i][j] = abs(pumas[i][j]); // In case the value gets negative, we make it positive so it will be physical
			}	

}

//average_hares returns the average value of hares along the whole grid when called.
double landscape::average_hares()
{
double sum=0;

for (row = hares.begin(); row != hares.end(); row++) 
{
	for (col = row->begin(); col != row->end(); col++) 
	{
     	sum +=*col;
	}
}

return sum/((grid_size_x-2)*(grid_size_y-2));

}


//average_pumas returns the average value of pumas along the whole grid when  called.
double landscape::average_pumas()
{
double sum=0;

for (row = pumas.begin(); row != pumas.end(); row++) 
{
	for (col = row->begin(); col != row->end(); col++) 
	{
     	sum +=*col;
	}
}

return sum/((grid_size_x-2)*(grid_size_y-2));
}

/*
void landscape::printhares()
{
std::cout<<"hares:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
         std::cout << hares[i][j];				 
      }
      std::cout << std::endl;
   }
}
*/
/*
void landscape::printpumas()
{
std::cout<<"\npumas:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
          std::cout << pumas[i][j];				 

      }
      std::cout << std::endl;
   }
}
*/

//returns a vector of vectors corresponding to the hares density along the grid
std::vector<std::vector<double> > landscape::get_hares()
{
return hares;
}


//returns a vector of vectors corresponding to the pumas density along the grid
std::vector<std::vector<double> > landscape::get_pumas()
{
return pumas;
}


//returns a vector of vectors corresponding to the morphology of the landscape (true:earth, false:water)
std::vector<std::vector<bool> > landscape::get_map()
{
return map;
}





//helper functions for constructor

int landscape::ReadInFile(const std::string &kPath, std::vector<std::vector<double> >& matrix)
{
	int x_size = matrix.size(); int y_size = matrix[0].size();
	std::ifstream file;
    file.open(kPath.c_str());
    if (!file.is_open())
    {
        std::cout<< "Failed to open file " << kPath << std::endl;
		return 0;
    }
	else{	
	int tmp;
	file >> tmp >> tmp; // Ignore size values
	
	for(int x=1; x<(x_size-1); x++){        // Ingnore the first and last entries as they are the water ring
		for(int y=1; y<(y_size-1); y++){
			file >> tmp;
			matrix[x][y] = tmp;
		}
	}
	file.close();
	return 1;
    }
}


// Reads into "matrix" the .dat file fouond in "kPath"
// Returns 0 if it fails to open the file otherwise returns 1
int landscape::ReadInFile(const std::string &kPath, std::vector<std::vector<bool> >& matrix)
{
	int x_size = matrix.size(); int y_size = matrix[0].size();
	std::ifstream file;
    file.open(kPath.c_str());
    if (!file.is_open())
    {
        std::cout<< "Failed to open file " << kPath << std::endl;
		return 0;
    }
	else{	
	int tmp;
	file >> tmp >> tmp; // Ignore size values
	
	for(int x=1; x<(x_size-1); x++){        // Ingnore the first and last entries as they are the water ring
		for(int y=1; y<(y_size-1); y++){
			file >> tmp;
			matrix[x][y] = tmp;
		}
	}
	file.close();
	return 1;
    }
}


// Initializes "matrix" with a random animal density on all land points. The density is an number between 0 and 5.
void landscape::GenerateRandomDensity(std::vector<std::vector<double> > &matrix, std::vector<std::vector<bool> > const &map)
{
	int x_size = matrix.size(); int y_size = matrix[0].size();
	for(int x=0; x<x_size; x++){        
		for(int y=0; y<y_size; y++){
			if(map[x][y]==1)
			    matrix[x][y] = std::rand()%6;  //assign random density between 0 and 5
		}
	}
}

