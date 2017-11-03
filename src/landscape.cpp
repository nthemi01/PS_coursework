#include "../include/landscape.h"


// landscape constructor - Initialises the class landscape
// INPUTS:  @pars Constant Stucture Params that contains the problem parameters - r,a,b,m,k,l,dt
//          @kMapPath Constant String contianing the path to the Map data file
//          @kPumasPath Constant String contianing the path to the Map data file
//          @kHaresPath Constant String contianing the path to the Map data file
// OUTPUTS: N/A
          
landscape::landscape(const Params &pars, const std::string kMapPath, const std::string kPumasPath, const std::string kHaresPath)
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
                        
    // Check for bad parameter inputs and handle by setting to default params
    if(pars.r < 0)
    {
        std::cout << "The birth rate of Hares, r, should be non-negative." << std::endl;
        std::cout << "Value of r gievn was: " << pars.r << std::endl;
        std::cout << "Have set r to the default value of 0.08" << std::endl;
        r = 0.08;
        throw  std::invalid_argument("The birth rate of Hares, r, should be non-negative.");
    }
    else
        r = pars.r;
    if(pars.a < 0)
    {
        std::cout << "The predation rate, a, should be non-negative." << std::endl;
        std::cout << "Value of a gievn was: " << pars.a << std::endl;
        std::cout << "Have set a to the default value of 0.04" << std::endl;
        a = 0.04;
        throw  std::invalid_argument("The predation rate, a, should be non-negative.");
    }
    else
        a = pars.a;
    if(pars.b < 0)
    {
        std::cout << "The birth rate of Pumas, b, should be non-negative." << std::endl;
        std::cout << "Value of b gievn was: " << pars.b << std::endl;
        std::cout << "Have set b to the default value of 0.02" << std::endl;
        b = 0.02;
        throw  std::invalid_argument("The birth rate of Pumas, b, should be non-negative.");
    }
    else
        b = pars.b;
    if(pars.m < 0)
    {
        std::cout << "The mortality rate of pumas, m, should be non-negative." << std::endl;
        std::cout << "Value of m gievn was: " << pars.m << std::endl;
        std::cout << "Have set m to the default value of 0.06" << std::endl;
        m = 0.06;
        throw  std::invalid_argument("The mortality rate of pumas, m, should be non-negative.");
    }
    else
        m = pars.m;
    if(pars.k < 0)
    {
        std::cout << "The diffusion rate for hares, k, should be non-negative." << std::endl;
        std::cout << "Value of k gievn was: " << pars.k << std::endl;
        std::cout << "Have set k to the default value of 0.2" << std::endl;
        k = 0.2;
        throw  std::invalid_argument("The diffusion rate for hares, k, should be non-negative.");
    }
    else
        k = pars.k;
    if(pars.l < 0)
    {
        std::cout << "The diffusion rate for pumas, l, should be non-negative." << std::endl;
        std::cout << "Value of l gievn was: " << pars.l << std::endl;
        std::cout << "Have set l to the default value of 0.2" << std::endl;
        l = 0.2;
        throw  std::invalid_argument("The diffusion rate for pumas, l, should be non-negative.");
    }
    else
        l = pars.l;
    if(pars.dt <= 0)
    {
        std::cout << "The time step, dt, should be positive." << std::endl;
        std::cout << "Value of dt gievn was: " << pars.dt << std::endl;
        std::cout << "Have set dt to the default value of 0.4" << std::endl;
        dt = 0.4;
        throw  std::invalid_argument("The time step, dt, should be positive.");
    }
    else
        dt = pars.dt; 

    // filling the N matrix that represents the number of dry neighbors
    for(int i=1;i<grid_size_x-1;i++)
        for(int j=1;j<grid_size_y-1;j++)
		if(1==map[i][j])
            		N[i][j]=map[i+1][j]+map[i][j+1]+map[i-1][j]+map[i][j-1];
    
    // Check that densities on the water are zero
    for(int i=0;i<grid_size_x;i++){
        for(int j=0;j<grid_size_y;j++)
        {
            if(!map[i][j])
            {
                if(pumas[i][j]!=0)
                {
                    std::cout << "Warning: puma density was non-zero on a water point. Reset to 0." << std::endl;
                    pumas[i][j]=0;
                }
                if(hares[i][j]!=0)
                {    
                    std::cout << "Warning: puma density was non-zero on a water point. Reset to 0." << std::endl;
                    hares[i][j]=0;
                }
            }
        }
    }
            
    // Console output - To see the map and params    
    #ifdef DEBUG
    for(int x=0; x<grid_size_x; x++){
        for(int y=0; y<grid_size_y; y++){            
            std::cout << map[x][y];
        }
        std::cout << std::endl;
    }    
    
    std::cout << "r=" << r << " a=" << a << " b=" << b<< " m=" << m<< " k=" << k<< " l=" << l << std::endl;  
    std::cout << "size of map: " << map.size() << " by " << map[0].size() << std::endl;
    #endif
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
				hares[i][j] = fabs(hares[i][j]); 
				// By taking the absolute value we make sure we never have negative density.
	
				part1 = pumas_old[i-1][j]+pumas_old[i+1][j]+pumas_old[i][j-1]+pumas_old[i][j+1];	
				part2 = l*(part1 - N[i][j]*pumas_old[i][j]);			
				pumas[i][j] = pumas_old[i][j] + dt*( b*hares_old[i][j]*pumas_old[i][j] - m*pumas_old[i][j] + part2);
				pumas[i][j] = fabs(pumas[i][j]);
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
double average= sum/((grid_size_x-2)*(grid_size_y-2));
if (average < 0.0001) average=0;
return average;
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

double average= sum/((grid_size_x-2)*(grid_size_y-2));
if (average < 0.0001) average=0;
return average;
}


void landscape::printhares()
{
std::cout<<"hares:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
	std::cout << hares[i][j]<<" ";				 
      }
      std::cout << std::endl;
   }
}




void landscape::printpumas()
{
std::cout<<"pumas:\n\n";
for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
	std::cout << pumas[i][j]<<" ";				 
      }
      std::cout << std::endl;
   }
}


// returns a vector of vectors corresponding to the hares density along the grid
std::vector<std::vector<double> > landscape::get_hares()
{
return hares;
}


// returns a vector of vectors corresponding to the pumas density along the grid
std::vector<std::vector<double> > landscape::get_pumas()
{
return pumas;
}


// returns a vector of vectors corresponding to the morphology of the landscape (true:earth, false:water)
// std::vector<std::vector<bool> > landscape::get_map()
// {
// return map;
// }



//returns a vector of vectors corresponding to the number of dry neighbors each square has. Only used for the gtest
 std::vector<std::vector<int> > landscape::get_neighbors()
 {
 return N;
 }

//prints on screen all the variables. Useful for debugging
void landscape::print_all_variables()
{
std::cout << "r=" << r << " a=" << a << " b=" << b<< " m=" << m<< " k=" << k<< " l=" << l<<"dt="<<dt << std::endl;	
std::cout << "size of map: " << map.size() << " by " << map[0].size() << std::endl;
}

// Helper function for the constructor
// INPUTS:  @kPath Constant String that contains the file path loactaing the file to be read in
//          @matrix Vecotor of Vectors representing the matrix to read the data into
// OUTPUTS: 0 or 1 depending on if the file was read in successuflly or not - 0 fail, 1 worked

int landscape::ReadInFile(const std::string &kPath, std::vector<std::vector<double> >& matrix)
{
    std::ifstream file;
    file.open(kPath.c_str());
    if (!file.is_open())
    {
        std::cout<< "Failed to open file " << kPath << std::endl;
        return 0;
    }
    else{   
    int xSize; int ySize;
    file >> xSize >> ySize;
    if(xSize != grid_size_x-2)
        throw std::invalid_argument("ReadInFile failed because the file was not the same size as the Map file");
    if(ySize != grid_size_y-2)
        throw std::invalid_argument("ReadInFile failed because the file was not the same size as the Map file");
    
    double tmp;
    for(int x=1; x<(grid_size_x-1); x++){        // Ingnore the first and last entries as they are the water ring
        for(int y=1; y<(grid_size_y-1); y++){
            file >> tmp;
            matrix[x][y] = tmp;
        }
    }
    file.close();
    return 1;
    }
}


// Helper function for the constructor
// INPUTS:  @kPath Constant String that contains the file path loactaing the file to be read in
//          @matrix Vecotor of Vectors representing the matrix to read the data into
// OUTPUTS: 0 or 1 depending on if the file was read in successuflly or not - 0 fail, 1 worked

int landscape::ReadInFile(const std::string &kPath, std::vector<std::vector<bool> >& matrix)
{
    std::ifstream file;
    file.open(kPath.c_str());
    if (!file.is_open())
    {
        std::cout<< "Failed to open file " << kPath << std::endl;
        return 0;
    }
    else{   
    int xSize; int ySize;
    file >> xSize >> ySize;
    if(xSize != grid_size_x-2)
        throw std::invalid_argument("ReadInFile failed because the file was not the same size as the Map file");
    if(ySize != grid_size_y-2)
        throw std::invalid_argument("ReadInFile failed because the file was not the same size as the Map file");
    
    bool tmp;
    for(int x=1; x<(grid_size_x-1); x++){        // Ingnore the first and last entries as they are the water ring
        for(int y=1; y<(grid_size_y-1); y++){
            file >> tmp;
            matrix[x][y] = tmp;
        }
    }
    file.close();
    return 1;
    }
}

void landscape::GenerateRandomDensity(std::vector<std::vector<double> > &matrix, std::vector<std::vector<bool> > const &map)
{
    int x_size = matrix.size(); int y_size = matrix[0].size(); int samples = 10;
    int yy = static_cast<int>(x_size/samples + 1);
    int xx = static_cast<int>(y_size/samples + 1);
    auto density = map_gen(xx,yy,1.7,samples,4) * 5;
    // remove superfluous edges
    int yyres = yy*samples - x_size;
    int xxres = xx*samples - y_size;
    for (int i = 0; i < yyres; ++i)
        density.pop_back();
    for (auto& yelem : density)
        for (int i = 0; i < xxres; ++i)
            yelem.pop_back();

    for (int i = 0; i < x_size; ++i)
        for (int j = 0; j < y_size; ++j)
            density[i][j] = map[i][j]?density[i][j]:0;

    matrix = density;
}

// Initializes "matrix" with a random animal density on all land points. The density is an number between 0 and 5.
// void landscape::GenerateRandomDensity(std::vector<std::vector<double> > &matrix, std::vector<std::vector<bool> > const &map)
// {
    // int grid_size_x = matrix.size(); int grid_size_y = matrix[0].size();
    // for(int x=0; x<grid_size_x; x++){        
        // for(int y=0; y<grid_size_y; y++){
            // if(map[x][y]==1)
                // matrix[x][y] = std::rand()%6;  //assign random density between 0 and 5
        // }
    // }
// }

