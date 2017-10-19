#include "../include/landscape.h"



landscape::landscape(const Params &pars, const std::string mapPath, const std::string pumaspath = "", const std::string harespath = "")
{
	//Still To-Do:
	// Add try, catch blocks for file reading
	// Tidy code with c in mind - i.e. maybe use more pass by reference, add const etc.


	//Extract size of the landscape
    std::ifstream mapfile;
    mapfile.open(mapPath.c_str());
    if (!mapfile.is_open())
    {
        std::cout<< "Failed to open file: " <<  mapPath << std::endl;
    }
	else{
    mapfile >> grid_size_x >> grid_size_y;
	//Add space for a ring of water. Note vector initializes to 0 so the ring will be added automatically
	grid_size_x += 2; grid_size_y += 2;
	map.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the map matrix
	hares.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the hare density matrix
	pumas.resize(grid_size_x, std::vector<double>(grid_size_y,0)); // Initialize the puma density matrix
	mapfile.close();
	}
	
	if(!readinfile(mapPath, map))
		std::cout<< "Failed to open file: " <<  mapPath << std::endl;
		
	
	
	std::srand(std::time(NULL)); //Seed random number generator
	
	if(pumaspath != "")
		readinfile(pumaspath, pumas);
	else
		generateRandomDensity(pumas,map);
	if(harespath != "")
		readinfile(harespath, hares);
	else
		generateRandomDensity(hares,map);
						
	
	//Console output - To see the map
	
	// for(int x=0; x<grid_size_x; x++){
		// for(int y=0; y<grid_size_y; y++){			
			// std::cout << map[x][y];
		// }
		// std::cout << std::endl;
	// }	
	// r = pars.r; a = pars.a; b = pars.b; m = pars.m; k = pars.k; l = pars.l; 

	// std::cout << "r=" << r << " a=" << a << " b=" << b<< " m=" << m<< " k=" << k<< " l=" << l << std::endl;
	
	// std::cout << "size of map: " << map.size() << " by " << map[0].size() << std::endl;
}

void landscape::progress()
{
	pumas_old.swap(pumas);
	hares_old.swap(hares);

	for(int i=1;i!=grid_size_x-1;i++)
		for(int j=1;j!=grid_size_y-1;j++)
			if(grid[i][j])
			{
				double part1,part2;

				part1 = hares_old[i-1][j]+hares_old[i+1][j]+hares_old[i][j-1]+hares_old[i][j+1];	
				part2 = k*(part1 - N[i][j]*hares_old[i][j]);
				hares[i][j] = hares_old[i][j] + dt*( r*hares_old[i][j] - a*hares_old[i][j]*pumas_old[i][j] + part2);
			 
				part1 = pumas_old[i-1][j]+pumas_old[i+1][j]+pumas_old[i][j-1]+pumas_old[i][j+1];	
				part2 = l*(part1 - N[i][j]*pumas_old[i][j]);			
				pumas[i][j] = pumas_old[i][j] + dt*( b*hares_old[i][j]*pumas_old[i][j] - m*pumas_old[i][j] + part2);
		}	

	// progress function will be the one doing the actual computation for both Pumas and Hares
	// and calculating the densities for for the next time step.
}

double landscape::average_hares()
{
	// when average function is called it will return the average value of Hares at that time.
}


double landscape::average_pumas()
{
	// when average function is called it will return the average value of Pumas at that time.
}

void landscape::printPPM()
{
	//export a PPM file when called
}

void landscape::printx()
{
	int x=5;
	for(int i=0;i!=10;i++)	
		progress();
	//printhares();
	//printpumas();
}
void landscape::resizeVec( std::vector<std::vector<double> > &vec , const unsigned short ROWS , const unsigned short COLUMNS )
{
    vec.resize( ROWS );
    for( std::vector<std::vector<double> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->resize( COLUMNS );
    }
}



void landscape::resizeVec( std::vector<std::vector<bool> > &vec , const unsigned short ROWS , const unsigned short COLUMNS )
{
    vec.resize( ROWS );
    for( std::vector<std::vector<bool> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->resize( COLUMNS );
    }
}


void landscape::resizeVec( std::vector<std::vector<int> > &vec , const unsigned short ROWS , const unsigned short COLUMNS )
{
    vec.resize( ROWS );
    for( std::vector<std::vector<int> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->resize( COLUMNS );
    }
}

void landscape::printhares()
{
std::cout<<"hares:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
         std::cout << hares[i][j] << "\t\t\t";
      }
      std::cout << std::endl;
   }
}


void landscape::printpumas()
{
std::cout<<"\npumas:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
         std::cout << pumas[i][j] << "\t\t\t";
      }
      std::cout << std::endl;
   }
}

std::vector<std::vector<double> > landscape::get_hares()
{
return hares;
}


std::vector<std::vector<double> > landscape::get_pumas()
{
return pumas;
}

//helper functions for constructor

int landscape::readinfile(const std::string path, std::vector<std::vector<double> >& matrix)
{
	int xs = matrix.size(); int ys = matrix[0].size();
	std::ifstream file;
    file.open(path.c_str());
    if (!file.is_open())
    {
        std::cout<< "Failed to open file " << path << std::endl;
		return 0;
    }
	else{	
	int tmp;
	file >> tmp >> tmp; // Ignore size values
	
	for(int x=1; x<(xs-1); x++){        // Ingnore the first and last entries as they are the water ring
		for(int y=1; y<(ys-1); y++){
			file >> tmp;
			matrix[x][y] = tmp;
		}
	}
	file.close();
	return 1;
    }
}

void landscape::generateRandomDensity(std::vector<std::vector<double> > &matrix, std::vector<std::vector<double> > const &map)
{
	int xs = matrix.size(); int ys = matrix[0].size();
	for(int x=0; x<xs; x++){        
		for(int y=0; y<ys; y++){
			if(map[x][y]==1)
			    matrix[x][y] = std::rand()%6;  //assign random density between 0 and 5
		}
	}
}
