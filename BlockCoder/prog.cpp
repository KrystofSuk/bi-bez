#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class Convertor{
    private:
        vector<unsigned char> _bin;
        vector<string> _hex;
        bool _valid = true;
        bool CheckValidity(){
            return true;
        }
        bool ConvertBytesToHex(string s){
                        
            return true;
        }
        bool ConvertHexToBytes(string s){

            return true;
        }


    public:
        Convertor(string val, bool hex){

            if(!hex){
                cout << "Converting: " << val << endl;
                for (auto it = val.cbegin() ; it != val.cend(); ++it) {
                    stringstream ss;
                    ss<< std::hex << (int)(*it);
                    string res = (ss.str());
                    cout << *it << " - " << res << endl;
                    _bin.push_back((unsigned char)(*it));
                    _hex.push_back(res);
                }
            }
            if(hex){
                
                if(val.length() < 2)
                {
                    cout << "Too short!" << endl;
                    return;
                }
                
                if(val.length() % 2 != 0){
                    cout << "Wrong lenght!" << endl;
                    return;
                }
                
                for(auto it = val.cbegin() ; it != val.cend(); ++it){
                    cout << *it << " " << (int)(*it) << endl;
                    if(!((int)*it <= 102 && (int)*it >= 97)){
                        if(!((int)*it <= 57 && (int)*it >= 48)){
                            if(!((int)*it <= 70 && (int)*it >= 65)){
                                cout << "Wrong hex value!" << endl;
                                return;
                            }
                        }
                    }
                };


                cout << "Converting: " << val << endl;
                for (auto it = val.cbegin() ; it != val.cend(); ++it) {
                    string hx = "";
                    hx += *it;
                    it++;
                    hx += *it;
                    unsigned char res = (unsigned char)std::stoul(hx, nullptr, 16);
                    cout << hx << " - " << res << endl;
                    _hex.push_back(hx);
                    _bin.push_back(res);
                }
            }

        }
        const bool IsValid() const{
            return _valid;
        }
};

int main ( int argc, char* argv[] ) {
    /*
    string s = "Test string";
    Convertor c = Convertor(s, false);
    */
    string s2 = "fc57c9cfdac7202694e8c2712d1f0e8e21b8c6f6d612d6c96847e42e6257b3f9ea98466cfc8761ed5e0308311deb15";
    Convertor c2 = Convertor(s2, true);
    return 0;
}