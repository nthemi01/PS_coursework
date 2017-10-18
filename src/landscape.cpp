#include "../include/landscape.h"


landscape::landscape()
{
	grid_size_x = 9;
	grid_size_y=9;


	resizeVec(grid,grid_size_x,grid_size_y);
	resizeVec (N,grid_size_x,grid_size_y);
	for(int i=0;i!=grid_size_x;i++)
		for(int j=0;j!=grid_size_y;j++)
		{
		}	

	resizeVec(pumas,grid_size_x,grid_size_y);
	resizeVec(hares,grid_size_x,grid_size_y);

	resizeVec(pumas_old,grid_size_x,grid_size_y);
	resizeVec(hares_old,grid_size_x,grid_size_y);

	for(int i=0;i!=grid_size_x;i++)
		for(int j=0;j!=grid_size_y;j++)
		{
			if( i==0 || i==grid_size_x-1 || j==0 || j==grid_size_y-1)
			{
				pumas[i][j]=0;
				hares[i][j]=0;
				continue;
			}
			hares[i][j]= i;
			pumas[i][j]= j;
		}
			
			
	r= 0.08;a=0.04;b=0.02;m=0.06;k=0.2;l=0.2;dt=0.4; // where ...
	//onstractor will set the size of pumas & hares
	// fill them (if this will be a seperate class)
}

void landscape::progress()
{
	pumas_old.swap(pumas);
	hares_old.swap(hares);

	for(int i=0;i!=grid_size_x;i++)
		for(int j=0;j!=grid_size_y;j++)
		{
			double part1,part2,part3,part4;

			part1= hares_old[i-1][j]+hares_old[i+1][j]+hares_old[i][j-1]+hares_old[i][j+1];	
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
	progress();
	printhares();
	printpumas();
	//std::cout<<"X: "<<x<<std::endl;
	//std::cout<<pumas.size()<<std::endl;
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
std::cout<<"Hares:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
         std::cout << hares_old[i][j] << " ";
      }
      std::cout << std::endl;
   }
}


void landscape::printpumas()
{
std::cout<<"\nPumas:\n\n";

for (int i = 0; i < grid_size_x; i++ ) {
      for (int j = 0; j < grid_size_y; j++ ) {
         std::cout << pumas_old[i][j] << " ";
      }
      std::cout << std::endl;
   }
}
