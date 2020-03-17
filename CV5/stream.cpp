#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int main(void) {
  int res;

  //My cypher
  unsigned char ot[1024] = "Jiz nikdo nema marast nalepku!";  // open text
  unsigned char st[1024];  // sifrovany text
  unsigned char key[EVP_MAX_KEY_LENGTH] = "COVID-19 with love";  // klic pro sifrovani
  unsigned char iv[EVP_MAX_IV_LENGTH] = "iv";  // inicializacni vektor
  const char cipherName[] = "RC4";
  const EVP_CIPHER * cipher;

  OpenSSL_add_all_ciphers();
  /* sifry i hashe by se nahraly pomoci OpenSSL_add_all_algorithms() */
  cipher = EVP_get_cipherbyname(cipherName);
  if(!cipher) {
    printf("Sifra %s neexistuje.\n", cipherName);
    exit(1);
  }
  
  int otLength = strlen((const char*) ot);
  int stLength = 0;
  int tmpLength = 0;

  EVP_CIPHER_CTX *ctx; // context structure
  ctx = EVP_CIPHER_CTX_new();
  if (ctx == NULL) exit(2);

  
  /* Sifrovani meho */
  res = EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv);  // context init - set cipher, key, init vector
  if(res != 1) exit(3);
  res = EVP_EncryptUpdate(ctx,  st, &tmpLength, ot, otLength);  // encryption of pt
  if(res != 1) exit(4);
  stLength += tmpLength;
  res = EVP_EncryptFinal_ex(ctx, st + stLength, &tmpLength);  // get the remaining ct
  if(res != 1) exit(5);
  stLength += tmpLength;

   /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  

  unsigned char ot2[1024] = "abcdefghijklmnopqrstuvwxyz0123";  // open text
  unsigned char st2[1024];  // sifrovany text
  int ot2Length = strlen((const char*) ot2);
  int st2Length = 0;
  tmpLength = 0;

  EVP_CIPHER_CTX *ctx2; // context structure
  ctx2 = EVP_CIPHER_CTX_new();
  if (ctx2 == NULL) exit(2);


  /* Sifrovani standard */
  res = EVP_EncryptInit_ex(ctx2, cipher, NULL, key, iv);  // context init - set cipher, key, init vector
  if(res != 1) exit(3);
  res = EVP_EncryptUpdate(ctx2,  st2, &tmpLength, ot2, ot2Length);  // encryption of pt
  if(res != 1) exit(4);
  st2Length += tmpLength;
  res = EVP_EncryptFinal_ex(ctx2, st2 + st2Length, &tmpLength);  // get the remaining ct
  if(res != 1) exit(5);
  st2Length += tmpLength;

   /* Clean up */
  EVP_CIPHER_CTX_free(ctx2);




  /* Vypsani zasifrovaneho a rozsifrovaneho textu. */
  stringstream ss;
  for (int i = 0; i < stLength; i++) {
    ss<< std::hex << (int)(st[i]);
  }
  stringstream ss2;
  for (int i = 0; i < st2Length; i++) {
    ss2<< std::hex << (int)(st2[i]);
  }
  cout << endl << endl << "Uloha 2:" << endl;
  cout << "Na IV nezalezi, viz prednaska. RC4 by mela pri kazdem spojeni vygenerovat nahodny klic v tom je i to nebezpeci, viz desifrace" << endl << endl;

  cout << "Muj OT: \"" << ot << "\"" << endl;
  cout << "Muj Key: \"" << key << "\"" << endl;
  cout << "Zasifrovany OT hex: \"" << ss.str() << "\""<< endl;
  cout << "Zasifrovany znamy hex: \"" << ss2.str() << "\"" << endl;

  //Desifrace
  unsigned char stZname[1024];
  unsigned char st3[1024]; 
  unsigned char binZname[1024];
  unsigned char binst3[1024]; 
  unsigned char otZname[1024]; 
  unsigned char ot3[1024];  // sifrovany text

  cin >> st3;
  cin >> stZname;

  cout <<  endl;
  cout << "Souseda zasifrovany hex: \"" << st3 << "\"" << endl << "Souseda zasifrovany znamy hex: \"" <<  stZname << "\"" <<endl;

  
  int stZnameLength = strlen((const char*) stZname);
  int st3Length = strlen((const char*) st3);


  int t = 0;
  for (int i = 0; i < stZnameLength; i++) {
    string hx = ""; 
    hx += stZname[i];
    i++;
    hx += stZname[i];
    unsigned char res = (unsigned char)std::stoul(hx, nullptr, 16);
    binZname[t] = res;
    t++;
  }
  
  t = 0;
  for (int i = 0; i < st3Length; i++) {
    string hx = ""; 
    hx += st3[i];
    i++;
    hx += st3[i];
    unsigned char res = (unsigned char)std::stoul(hx, nullptr, 16);
    binst3[t] = res;
    t++;
  }
  stZnameLength = strlen((const char*) binZname);
  st3Length = strlen((const char*) binst3);


  char priv[30];

  //Xor for h
  for(int i = 0; i < stZnameLength; i++){
    priv[i] = (char)(binZname[i] ^ ot2[i]);
  }

  //Xor for ot
  for(int i = 0; i < stZnameLength; i++){
    ot3[i] = (char)(binst3[i] ^ priv[i]);
  }

  cout << endl << "Souseda puvodni text: \"" << ot3 << "\"" << endl;


  cout << "---------------" << endl << endl;





  

  exit(0);
}