#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sys/timeb.h>
#include "landscape.h"
#include "disdensity.h"

using namespace std;
using std::vector;
using cimg_library::CImg;

typedef long long TIME_T;

struct CmdParam {
  int loops,is_show,interval;
  string map_file, cfg_file, puma_file, hare_file, ppm_folder="./output/"; 
  Params para;
};

int ReadConfigfile(const string , CmdParam &, int &);

void TrimString (string &input) {
    int pos;
    while ((pos=input.find(" ")) == 0) input = input.substr(pos+1);
    while ((pos=input.find("\t")) == 0) input = input.substr(pos+1);
    while ((pos=input.find_last_of(" ")) == input.size()-1) input = input.substr(0,pos);
    while ((pos=input.find_last_of("\t")) == input.size()-1) input = input.substr(0,pos);
}

int SetVector(int &vector, int index) {
    if (index < 0 || index > 30)	return 0;
    vector = vector | (1 << index);
}

int SetParameter(CmdParam &param, int &vector, string key, string value) {
    int index;
    string slist[] = {"-cfgfile","-mapfile","-pumafile","-harefile","-loops","-show","-interval","-ppmfolder","-r","-a","-m","-b","-k","-l","-dt"};
    string slist_cfg[] = {"cfgfile","mapfile","pumafile","harefile","loops","show","interval","ppmfolder","r","a","m","b","k","l","dt"};
#ifdef DEBUG_OUT
    printf( "\tSetParameter:\t key=%s,", key.c_str());
	printf( "value=%s\n",value.c_str());
#endif	
   
    int length = sizeof(slist)/sizeof(string);
    for (index = 0;index < length; index++)
         if (key == slist[index] || key == slist_cfg[index]) break;
#ifdef DEBUG_OUT
    printf( "\tSetParameter:\t index=%d size=%d,key=%s, value=%s\n",index,length,key.c_str(),value.c_str());
#endif	
    if (index < length) {
        SetVector(vector , index);
#ifdef DEBUG_OUT
        printf("\tSetParameter:\t Set vector to %x \n",vector);
#endif
        switch (index) {
            case 0 :
                if (value != "")
                    if ( !ReadConfigfile(value , param, vector))	return 0;   
                break;
            case 1 :
                param.map_file = value;
                break;
            case 2 :
                param.puma_file = value;
                break;
             case 3 :
                param.hare_file = value; 
                break;
             case 4 :
                param.loops = atoi(value.c_str());
                break;
             case 5 :
                param.is_show = atoi(value.c_str());
                break;
             case 6 :
                param.interval = atoi(value.c_str());
                break;
             case 7 :
                param.ppm_folder = value;
                if (param.ppm_folder[param.ppm_folder.size()-1] != '/') 
                    param.ppm_folder = param.ppm_folder + "/";
                break;
             case 8 :
                param.para.r = atof(value.c_str());
                break;
             case 9 :
                 param.para.a = atof(value.c_str());
                 break;
             case 10 :
                 param.para.m = atof(value.c_str());
                 break;
             case 11 : 
                 param.para.b = atof(value.c_str());
                 break;             
             case 12 :
                 param.para.k = atof(value.c_str());
                 break;
             case 13 :
                 param.para.l = atof(value.c_str());
                 break;
             case 14 :
                 param.para.dt = atof(value.c_str());
                 break;
             default :
                 return 0;
        }
#ifdef DEBUG_OUT
		printf("\tSetParameter:\t After switch\n");
#endif
    }
}


int ReadConfigfile(const string cfg_file, CmdParam &para, int &vector) {
    ifstream file;
#ifdef DEBUG_OUT
	printf("\tReadconfigfile:\t %s\n",cfg_file.c_str());
#endif
    file.open(cfg_file.c_str());
    if (!file.is_open()) {
        return 0;
    }
    else{
        string sline, skey, svalue;
        int pos;
        while (getline(file,sline)) {
            if ((pos = sline.find("=")) > 0 && pos < sline.size()-1 ) {
                skey = sline.substr(0,pos);
                svalue = sline.substr(pos+1);
                TrimString(skey);
                TrimString(svalue);
                if (skey != "-cfgfile" && skey != "cfgfile") {
#ifdef DEBUG_OUT
		    printf("\t");
#endif              
                    if (!SetParameter(para, vector, skey, svalue)) return 0;
                }
            }
        }
        return 1;
    }
}          

int main(int argc , char **argv) {

    CmdParam cmdPara;
    int vector = 0;
    string err_msg ;
    string str_para,str_value;

    struct timeb t_start,t_end;

    string usage = ""; 
    usage = usage + "Usage: caldensity -cfgfile <filename> -mapfile <filename> -loops <looptimes> -show <0/1> -interval <intervaltimes> \\\n"+
                    "       -r <value> -a <value> -m <value>  -k <value>  -l <value>  -dt <value>\n\n" +
                  "The detailed parameter description:\n" + 
                  "  File path and name:\n" +
                  "  -mapfile\tthe name of the land map file\n" +
                  "  -cfgfile\tthe name of the config file\n" +
                  "  -pumafile\tthe name of the file of puma's initialize density\n" +
                  "  -harefile\tthe name of the file of hare's initialize density\n" +
                  "  Key parameters and switches:\n" +
                  "  -loops\tthe total loop times\n" +
                  "  -show\t 0/1 1-display_changes_of_density 0-don't display\n" +
                  "  -interval\tthe interval times for output\n" +
                  "  -r\tthe birth rate of hares\n" +
                  "  -a\tthe predation rate of pumas\n" +
                  "  -b\tthe birth rate of pumas\n" +
                  "  -m\tthe puma mortality rate\n" +
                  "  -k\tthe diffusion rate for hares\n" +
                  "  -l\tthe diffusion rates for pumas\n" +
                  "  -dt\tthe size of the time step \n\n" +
                  "Notice: 1.The -pumafile and -harefile is optional, system will randomly generate density if these parameters missed.\n"+
                  "        2.The parameters can be configed in file or inputed in command, command line have higher priority.\n";
    int index = 1;
    while (index < argc) {
        str_para = string(argv[index]);
        if ( (index+1) < argc ) {
            str_value = string(argv[++index]);
#ifdef DEBUG_OUT
            printf("Main : Key is %s,value is %s \n",str_para.c_str(),str_value.c_str());
#endif
#ifdef DEBUG_OUT
            printf("Main : Now vector is %x\n",vector);
#endif
            if (!SetParameter(cmdPara, vector, str_para, str_value)) { 
                err_msg = "Some of your parameter is incorrect!";
                break;
            }
            else index++;
        }
        else {
            err_msg = "Parameter is invalid!";
            break;
        }
    }

    if ((vector & 0x7F72) != 0x7F72) err_msg = err_msg + "Not all the required parameters are configued.";
#ifdef DEBUG_OUT
    printf("Main : err_msg is %s\nMain ：Vector is %x\n",err_msg.c_str(),vector); 
#endif
    if ( !err_msg.empty() ) {
	std::cout << err_msg << "\n\n" << usage << std::endl;
        return 0; 
    }
    else {
#ifdef DEBUG_OUT
	printf("Main : Calculate the density\n"); 
#endif
        landscape land(cmdPara.para, cmdPara.map_file, cmdPara.puma_file, cmdPara.hare_file);
        int win_size_x,win_size_y;
            
        char *size_x = getenv("DENSITY_WIN_SIZE_X");
        char *size_y = getenv("DENSITY_WIN_SIZE_Y");
        win_size_x = (size_x == NULL) ? 400:atoi(size_x);
        win_size_y = (size_y == NULL) ? 400:atoi(size_y);
        output::screen *pwindow;
        int out_count = 1;
        char out_name[512];
#ifdef DEBUG_OUT
	printf("Main : Windows displayed\n"); 
#endif
        if (cmdPara.is_show) pwindow = new output::screen(win_size_x, win_size_y, "Density of Pumas","Density of Hares");
        ftime (&t_start);
        for (int index = 0;index < cmdPara.loops; index++) {
            land.progress();
            if (index % cmdPara.interval == 0 || index == cmdPara.loops-1) {
                sprintf(out_name, "%sPumaDensity_%04d.ppm", cmdPara.ppm_folder.c_str(),out_count);
                auto dump = output::get_img(land.get_pumas(),true,string(out_name));
                sprintf(out_name, "%sHareDensity_%04d.ppm", cmdPara.ppm_folder.c_str(),out_count);
                dump = output::get_img(land.get_hares(),true,string(out_name));
                
                double average =  land.average_pumas();
                std::cout << "The average value of puma's density is " << average  << " at No." << index << " loop." << std::endl;
                average =  land.average_hares();
                std::cout << "The average value of hare's density is " << average << " at No." << index << " loop." << std::endl;

                out_count++;
            }
            if (cmdPara.is_show) {
                auto img_pumas = output::get_img(land.get_pumas(),land.get_map());
                auto img_hares = output::get_img(land.get_hares(),land.get_map());

               pwindow->assign(img_pumas, img_hares);
               pwindow->show(index);
           }
        }
        ftime (&t_end);
        TIME_T t1=(TIME_T)t_start.time*1000+t_start.millitm;
        TIME_T t2=(TIME_T)t_end.time*1000+t_end.millitm;
        int ti=t2-t1;
        std::cout << "The total time is " << ti << "ms" << std::endl;
	return 1;
  }
}
