#include <string>
#include <fstream>
#include "../include/landscape.h"
#include <vector>
#include <iostream>
#include "disdensity.h"


using namespace std;
using std::vector;
using cimg_library::CImg;


struct CmdParam {
  int loops,isshow,interval;
  string sMapfile, sCfgfile, sPumafile, sHarefile; 
  Params para;
};

int ReadConfigfile(const string sCfgfile, CmdParam &para, int &vector);

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
    string slist[] = {"-cfgfile","-mapfile","-pumafile","-harefile","-loops","-show","-interval","-r","-a","-m","-b","-k","-l","-dt"};
    string slist_cfg[] = {"cfgfile","mapfile","pumafile","harefile","loops","show","interval","r","a","m","b","k","l","dt"};
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
                param.sMapfile = value;
                break;
            case 2 :
                param.sPumafile = value;
                break;
             case 3 :
                param.sHarefile = value; 
                break;
             case 4 :
                param.loops = atoi(value.c_str());
                break;
             case 5 :
                param.isshow = atoi(value.c_str());
                break;
             case 6 :
                param.interval = atoi(value.c_str());
                break;
             case 7 :
                param.para.r = atof(value.c_str());
                break;
             case 8 :
                 param.para.a = atof(value.c_str());
                 break;
             case 9 :
                 param.para.m = atof(value.c_str());
                 break;
             case 10 : 
                 param.para.b = atof(value.c_str());
                 break;             
			 case 11 :
                 param.para.k = atof(value.c_str());
                 break;
             case 12 :
                 param.para.l = atof(value.c_str());
                 break;
             case 13 :
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


int ReadConfigfile(const string sCfgfile, CmdParam &para, int &vector) {
    ifstream file;
#ifdef DEBUG_OUT
	printf("\tReadconfigfile:\t %s\n",sCfgfile.c_str());
#endif
    file.open(sCfgfile.c_str());
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

    string usage = ""; 
    usage = usage + "Usage: caldensity -cfgfile <filename> -mapfile <filename> -loops <looptimes> -show <0/1> -interval <intervaltimes> \\\n"+
                    "       -r <value> -a <value> -m <value>  -k <value>  -l <value>  -dt <value>\n\n" +
                  "The detailed parameter description:\n" + 
                  "File path and name:\n" +
                  "  -mapfile The name of the land map file\n" +
                  "  -cfgfile The name of the config file\n" +
                  "  -pumafile The name of the file of puma's initialize density\n" +
                  "  -harefile The name of the file of hare's initialize density\n" +
                  "Key parameters and switches:\n" +
                  "  -loops total_loop_times\n" +
                  "  -show 0/1 1-display_changes_of_density 0-don't display\n" +
                  "  -interval interval_times_for_output_information\n" +
                  "  -r birth_rate_of_hares\n" +
                  "  -a predation_rate_of_pumas\n" +
                  "  -b birth_rate_of_pumas\n" +
                  "  -m puma_mortality_rate\n" +
                  "  -k diffusion_rate_for_hares\n" +
                  "  -l diffusion_rate_for_pumas\n" +
                  "  -dt interval\n\n" +
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
	
    if ((vector & 0x3FF2) != 0x3FF2) err_msg = err_msg + "Not all the required parameters are configued.";
#ifdef DEBUG_OUT
    string sinfo = "************************************************************************\n";  
    sinfo = sinfo +
                    "  -mapfile=%s The name of the land map file\n" +
                    "  -pumafile =%sThe name of the file of puma's initialize density\n" +
                    "  -harefile=%s The name of the file of hare's initialize density\n" +
                    "  -loops=%d total_loop_times\n" +
                    "  -show=%d 0/1 1-display_changes_of_density 0-don't display\n" +
                    "  -interval=%d interval_times_for_output_information\n" +
                    "  -r=%f birth_rate_of_hares\n" +
                    "  -a=%f predation_rate_of_pumas\n" +
                    "  -b =%f birth_rate_of_pumas\n" +
                    "  -m=%f puma_mortality_rate\n" +
                    "  -k=%f diffusion_rate_for_hares\n" +
                    "  -l=%f diffusion_rate_for_pumas\n" +
                    "  -dt=%f interval\n\n" +
					"***********************************************************************\n";
    printf (sinfo.c_str(),cmdPara.sMapfile.c_str(), cmdPara.sPumafile.c_str(),
			cmdPara.sHarefile.c_str(),cmdPara.loops,cmdPara.isshow,cmdPara.interval,cmdPara.para.r,cmdPara.para.a,
			cmdPara.para.b,cmdPara.para.m,cmdPara.para.k,cmdPara.para.l,cmdPara.para.dt);
#endif
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
        landscape land(cmdPara.para, cmdPara.sMapfile, cmdPara.sPumafile, cmdPara.sHarefile);
        int win_size_x,win_size_y;
            
        char *size_x = getenv("DENSITY_WIN_SIZE_X");
        char *size_y = getenv("DENSITY_WIN_SIZE_Y");
        win_size_x = (size_x == NULL) ? 400:atoi(size_x);
        win_size_y = (size_y == NULL) ? 400:atoi(size_y);
        output::screen windows(win_size_x, win_size_y, "Density of Pumas","Density of Hares");

        for (int index = 0;index < cmdPara.loops; index++) {
            land.progress();
           
            if (cmdPara.isshow) {
                auto img_pumas = output::get_img(land.get_pumas());
                auto img_hares = output::get_img(land.get_pumas());

               // get_img(density, map, savefig_toggle, filename) // last two are optional
               // get_img(density, savefig_toggle, filename)
               windows.assign(img_pumas, img_hares);
                // assign()
               windows.show(index);
           }
        }
	return 1;
}

