#include <RBKLib.h>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    const char* pInPath = ".";
    const char* pOutFile = "result.h";

    const char* p = "#include \".\"\n";
    const char* pp = "#include \"..\"\n";
    const char* pDir = "#include \"dir.bat\"\n";
    const char* pDirExe = "#include \"ReadDir.exe\"\n";
    const char* pFileExe = "#include \"RBKLib.h\"\n";

    const char** ignore[] = { &p, &pp, &pFileExe, &pDir, &pDirExe };
    int sizeIgnore = sizeof(ignore) / sizeof(ignore[0]);

    if(argc == 3) {
        pInPath = argv[1];
        pOutFile = argv[2];
    }

    if(argc == 2)
        pInPath = argv[1];

    std::vector<std::string> out = ReadDir(&*pInPath);

    if(out.empty() == false) {

        for(auto& p : out) {
            p.append("\"\n");
            p.insert(0, "#include \"");
        }

        std::ofstream outfile(&*pOutFile);
        for(auto& p : out) {

            bool resultCompare = false;
            for(int i = 0; i < sizeIgnore; i++) {
                resultCompare = CompareSymbol(&p.front(), *ignore[i]);
                if(resultCompare == true)
                    break;
            }

            if(resultCompare == false)
                outfile << p;
        }
        outfile.close();
    } else {
        std::cout << "Could not open directory" << std::endl;
        getchar();
    }
}
