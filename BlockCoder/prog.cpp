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
        void ConvertBytesToHex(string val){
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
        
        void ConvertHexToBytes(string val){
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


    public:
        Convertor(string val, bool hex){

            if(!hex){
                ConvertBytesToHex(val);
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

                ConvertHexToBytes(val);
                
            }

        }

        const vector<string> GetHex() const{
            return _hex;
        }

        const vector<unsigned char> GetBin() const{
            return _bin;
        }
};

int main ( int argc, char* argv[] ) {
    string s = "70443";
    Convertor c = Convertor(s, false);
    vector<unsigned char> b1 = c.GetBin();
    string res;
    for (auto it = b1.cbegin() ; it != b1.cend(); ++it) {
        res += (char)(*it);
    }
    cout << res << endl;
    /*
    string s2 = "fc57c9cfdac7202694e8c2712d1f0e8e21b8c6f6d612d6c96847e42e6257b3f9ea98466cfc8761ed5e0308311deb15";
    Convertor c2 = Convertor(s2, true);
    string s3 = "a83fa0bcfaae5306f5c8b1144e6d6bfa01cca38ea23cf68707258b4a1b77c09185ed2a08dcf5048c3a237c5974983b";
    Convertor c3 = Convertor(s3, true);
    vector<unsigned char> b1 = c2.GetBin();
    vector<unsigned char> b2 = c3.GetBin();
    int i = 0;
    string res;
    for (auto it = b1.cbegin() ; it != b1.cend(); ++it) {
        res += (char)(*it ^ b2[i]);
        i++;
    }
    cout << "XOR: " << res << endl;
    */

    return 0;
}