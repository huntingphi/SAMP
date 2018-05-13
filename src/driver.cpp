#include<iostream>
#include<sstream>
#include<cstdlib>

// #define STUB(method) void method(){\
//   std::cout<<"Todo: "<<#method<<"\n";\
// }

#define STUB(method) [](){std::cout<<"Todo: "<<#method<<"\n";};

struct audio_file{
    int channels;
    int sample_rate;
    int bitrate;
    char* file_name;
};

enum operation_code{
    none, add, cut, radd, cat, v_factor, rms, normalise, fadein, fadeout
};

int exitWithError(){
    std::cout << "Usage: samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>] soundFile1 [soundFile2]"<<std::endl;
    return 1;
}


//samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>] soundFile1 [soundFile2]
int main(int argc, char *argv[])
{
    // auto lam = [](){std::cout<<"sigh"<<std::endl;};
    // lam();
    std::cout<<argc<<"\n";
    if(argc<8){ //Invalid arguements given
        return exitWithError();
        }
    int r, b, c;
    float r1, r2, s1, s2;
    char* file_input_1;
    char* file_input_2;
    std::string file_output = "out";//set default
    operation_code op = none;
    float n;
    if(argv[1][1]=='r'){
        std::istringstream ss(argv[2]);
        if (!(ss >> r))
            std::cerr << "Invalid number " << argv[2] << '\n';
    }else{
        return exitWithError();
    }
    if(argv[3][1]=='b'){
        std::istringstream ss(argv[4]);
        if (!(ss >> b))
            std::cerr << "Invalid number " << argv[4] << '\n';
    }else{
        return exitWithError();
    }
    if(argv[5][1]=='c'){
        std::istringstream ss(argv[6]);
        if (!(ss >> c))
           std::cerr << "Invalid number " << argv[6] << '\n';
    }else{
        return exitWithError();
    }
    if(argc==8){ //Ie if the minimum arguements are given
    file_input_1 = argv[7];
    }else{
    if(argv[7][0]=='-'){
        int offset = 0; //Need to offset argv index by 2 if we're specifying an output file
        if(argv[7][1]=='o'){
            file_output = argv[8];
            offset = 2;
            //No operation done
        }
        if(argc>7+offset){
            int argi = 7+offset;
            std::istringstream ss(argv[argi]);
            std::string operation_code;
            ss>>operation_code;
            if (operation_code == "-add"){
                if(argc>argi+2){
                file_input_1 = argv[argi+1];
                file_input_2 = argv[argi+2];
                if(file_input_2==file_input_1)return exitWithError();
                op = add;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-cut"){
                if(argc>argi+3){
                    r1=std::atoi(argv[argi+1]);
                    r2=std::atoi(argv[argi+2]);
                    file_input_1 = argv[argi + 3];

                    op = cut;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-radd"){
                if(argc>argi+6){
                    r1=std::atoi(argv[argi+1]);
                    r2 = std::atoi(argv[argi + 2]);
                    s1 = std::atoi(argv[argi + 3]);
                    s2 = std::atoi(argv[argi + 4]);
                    file_input_1 = argv[argi + 5];
                    file_input_2 = argv[argi + 6];
                    op = radd;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-cat"){
                if(argc>argi+2){
                file_input_1 = argv[argi+1];
                file_input_2 = argv[argi+2];
                if(file_input_2==file_input_1)return exitWithError();
                op = cat;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-v"){
                if(argc>argi+3){
                    r1=std::atoi(argv[argi+1]);
                    r2=std::atoi(argv[argi+2]);
                    file_input_1 = argv[argi + 3];

                    op = v_factor;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-rms"){
                if(argc>argi+1){
                file_input_1 = argv[argi+1];
                 op = rms;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-norm"){
                if(argc>argi+3){
                    r1=std::atoi(argv[argi+1]);
                    r2=std::atoi(argv[argi+2]);
                    file_input_1 = argv[argi + 3];

                    op = normalise;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-fadein"){
                if(argc>argi+2){
                n = std::atof(argv[argi+1]);
                file_input_1 = argv[argi + 2];

                op = fadein;
                }else{
                    return exitWithError();
                }
            }
            if (operation_code == "-fadeout"){
                if(argc>argi+2){
                n = std::atof(argv[argi+1]);
                file_input_1 = argv[argi + 2];

                op = fadeout;
                }else{
                    return exitWithError();
                }
            }
            if(op == none){
                return exitWithError();
            }
        
            }else{
                return exitWithError();
            }
            
        }else{
            return exitWithError();
        }
    
    }

    // op = radd;
    switch(op){
        case add:
        {
            auto func_add = STUB(add);
            func_add();//Tested
        }
            break;
        case radd:
        {
            auto func_radd = STUB(radd);
            func_radd();//Tested
        }
            break;
        case cut:
        {
            auto func_cut = STUB(cut);
            func_cut();//Tested
        }
            break;
        case cat:
        {
            auto func_cat = STUB(cat);
            func_cat();//Tested
        }
            break;
        case v_factor:
        {
            auto func_v = STUB(v);
            func_v();//Tested
        }
            break;
        case rms:
        {
            auto func_rms = STUB(rms);
            func_rms();//Tested
        }
            break;
        case normalise:
        {
            auto func_normal = STUB(normalise);
            func_normal();//Tested
        }
            break;
        case fadein:
        {
            auto func_fin = STUB(fadein);
            func_fin();//Tested
        }
            break;
        case fadeout:
        {
            auto func_fout = STUB(fadeout);
            func_fout();//Tested
    }
            break;
    }
    std::cout<<"Operation: "<<op<<std::endl;
    std::cout << "File input1: " << file_input_1 << std::endl;
    std::cout << "File input2: " << file_input_2 << std::endl;
    std::cout << "File output: " << file_output << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "N: " << n << std::endl;

    return 0;
}

