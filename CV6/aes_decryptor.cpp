//kryštof šuk

#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int convertInt(const char *c)
{
  int num = 0;
  for (int i = 0; i != 4; ++i)
  {
    num |= (int)(unsigned char)c[i] << (i * 8);
  }
  return num;
}

int main(int argc, char *argv[])
{

  int start = 0;
  int cypherL = 0;
  unsigned char *cypheredData;
  unsigned char *uncypheredData;
  char *memblock;
  char *header;

  ifstream streamImage;

  streamImage.open(string{argv[1]} + ".bmp", ios_base::binary);
  if (streamImage.is_open())
  {
    streamImage.seekg(0, streamImage.end);
    int size = streamImage.tellg();
    streamImage.seekg(0, streamImage.beg);

    memblock = new char[size];
    streamImage.read(memblock, size);
    streamImage.close();

    //Predpokladame, ze je to bitmapa

    char s[4] = {memblock[10], memblock[11], memblock[12], memblock[13]};
    start = convertInt(s);

    cypheredData = new unsigned char[size - start];
    uncypheredData = new unsigned char[size - start];

    
    header = new char[start];


    cypherL = size - start;
    for (int i = 0; i < start; i++){
      header[i] = (char)memblock[i];
    }
    for (int i = 0; i < size - start; i++)
      cypheredData[i] = memblock[i + start];
  }
  else
  {
    cerr << "Unable to open file!" << endl;
    return 0;
  }

  unsigned char key[EVP_MAX_KEY_LENGTH] = "COVID-19withlove"; // klic pro sifrovani
  unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor";    // inicializacni vektor
  const char cipherName[] = "aes128";
  const EVP_CIPHER *cipher;

  OpenSSL_add_all_ciphers();
  /* sifry i hashe by se nahraly pomoci OpenSSL_add_all_algorithms() */
  cipher = EVP_get_cipherbyname(cipherName);
  if (!cipher)
  {
    printf("Sifra %s neexistuje.\n", cipherName);
    exit(1);
  }

  
  /**
   * 
   * Decryption of images
   * 
  **/
  EVP_CIPHER_CTX *ctx; // context structure


  int len = 0;

  //cbc
  ctx = EVP_CIPHER_CTX_new();
  if(string{argv[2]} == "cbc"){
    if (ctx == NULL || 1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)){
      cout << "Errors occured" << endl;
      exit(2);
    }
  }else if(string{argv[2]} == "ecb"){
    if (ctx == NULL || 1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv)){
      cout << "Errors occured" << endl;
      exit(2);
    }
  }

  if(1 != EVP_DecryptUpdate(ctx, uncypheredData, &len, cypheredData, cypherL)){
    cout << "Errors occured" << endl;
    exit(2);
  }

  if(1 != EVP_DecryptFinal(ctx, uncypheredData, &len)){
    cout << "Errors occured" << endl;
    exit(2);
  }
  EVP_CIPHER_CTX_free(ctx);
  

  string o_cbc = string{argv[1]} + "_dec" + ".bmp";
  ofstream outcbc;
  outcbc.open(o_cbc, ios_base::binary);
  for (int i = 0; i < start; i++){
    outcbc << header[i];
  }
  for (int i = 0; i < cypherL; i++){
    outcbc << uncypheredData[i];
  }
  outcbc.close();

  /*
  //ecb
  ctx = EVP_CIPHER_CTX_new();
  if (ctx == NULL || 1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv)){
    cout << "Errors occured" << endl;
    exit(2);
  }

  if(1 != EVP_EncryptUpdate(ctx, cypheredData, &len, uncypheredData, cypherL)){
    cout << "Errors occured" << endl;
    exit(2);
  }

  EVP_EncryptFinal(ctx, cypheredData + len, &tmpLength);
  ciphertext_len = tmpLength;
  EVP_CIPHER_CTX_free(ctx);

  //printf("Ciphertext is:\n");
  //BIO_dump_fp (stdout, (const char *)cypheredData, ciphertext_len);
  string o_ecb = string{argv[1]} + "_ecb" + ".bmp";
  ofstream outecb;
  outecb.open(o_ecb, ios_base::binary);
  cout << len << endl;
  for (int i = 0; i < start; i++){
    outecb << header[i];
  }
  for (int i = 0; i < len+ciphertext_len; i++){
    outecb << cypheredData[i];
  }
  outecb.close();
*/

  delete[] cypheredData;
  delete[] memblock;
  delete[] header;

  exit(0);
}