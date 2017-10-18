#include "../include/landscape.h"


landscape::landscape()
{
	grid_size_x = 9;
	grid_size_y=9;

	resizeVec(grid,grid_size_x,grid_size_y);	// resize and initialize grid with some default values for now	
	for(int i=0;i!=grid_size_x;i++)
		for(int j=0;j!=grid_size_y;j++)
			if( i==0 || i==grid_size_x-1 || j==0 || j==grid_size_y-1)
				grid[i][j]=0;
			else if( (i==4 && j==4) || (i==3 && j==4))
				grid[i][j]=0;
			else
				grid[i][j]=1;

	resizeVec (N,grid_size_x,grid_size_y); // N counts the number of neighbors for each cell in order to be used from the progress function
	for(int i=1;i!=grid_size_x-1;i++)
		for(int j=1;j!=grid_size_y-1;j++)
			N[i][j]=grid[i+1][j]+grid[i][j+1]+grid[i-1][j]+grid[i][j-1];

	resizeVec(pumas,grid_size_x,grid_size_y);
	resizeVec(hares,grid_size_x,grid_size_y);

	resizeVec(pumas_old,grid_size_x,grid_size_y);
	resizeVec(hares_old,grid_size_x,grid_size_y);

	

	for(int i=0;i!=grid_size_x;i++)
		for(int j=0;j!=grid_size_y;j++)
		{
			if( grid[i][j]==1)
			{
				if( i==0 || i==grid_size_x-1 || j==0 || j==grid_size_y-1)
				{
					pumas[i][j]=0;
					hares[i][j]=0;
					continue;
				}
				hares[i][j]= i*1./2;
				pumas[i][j]= j*1./2;
			}
		}
			
			
	r= 0.08;a=0.04;b=0.02;m=0.06;k=0.2;l=0.2;dt=0.4; // where ...
	//onstractor will set the size of pumas & hares
	// fill them (if this will be a seperate class)
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
