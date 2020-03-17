#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <openssl/evp.h>

using namespace std;


int main(int argc, char *argv[]){

  int i, res;
	char text[5];
  char hashFunction[] = "sha256";  // zvolena hashovaci funkce ("sha1", "md5" ...)

  EVP_MD_CTX *ctx;  // struktura kontextu
  const EVP_MD *type; // typ pouzite hashovaci funkce
  unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
  int length;  // vysledna delka hashe

  /* Inicializace OpenSSL hash funkci */
  OpenSSL_add_all_digests();
  /* Zjisteni, jaka hashovaci funkce ma byt pouzita */
  type = EVP_get_digestbyname(hashFunction);

  /* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
  if(!type) {
    printf("Hash %s neexistuje.\n", hashFunction);
    exit(1);
  }

  int l = 2;
  int a = 97;
  int b = 97;
  int c = 97; 
  int d = 97;
  int e = 0;

  while(e != 27){
    ctx = EVP_MD_CTX_create(); // create context for hashing
    if(ctx == NULL) exit(2);

    /* Hash the text */
    res = EVP_DigestInit_ex(ctx, type, NULL); // context setup for our hash type
    if(res != 1) exit(3);
    res = EVP_DigestUpdate(ctx, text, strlen(text)); // feed the message in
    if(res != 1) exit(4);
    res = EVP_DigestFinal_ex(ctx, hash, (unsigned int *) &length); // get the hash
    if(res != 1) exit(5);

    EVP_MD_CTX_destroy(ctx); // destroy the context

    if(hash[0] == 0xFF && hash[1] == 0xCC){
      cout << endl << endl << "Uloha 1:" << endl;
      cout << "Text: " << text << endl;
      stringstream ss;
      for (int i = 0; i < 5; i++) {
        ss<< std::hex << (int)(text[i]);
      }
      cout << "Hex: " << ss.str() << endl << "Hash: ";

      for(i = 0; i < length; i++){
        printf("%02x", hash[i]);
      }
      cout << endl << "---------------" << endl << endl;
      return 0;
    }
    
    a++;
    if(a == 122){
      a = 97;
      b++;
      if(l == 2){
        l++;
      }
    }
    if(b == 122){
      b = 97;
      c++;
      if(l == 3){
        l++;
      }
    }
    if(c == 122){
      c = 97;
      d++;
      if(l == 4){
        l++;
      }
    }
    if(d == 122){
      d = 97;
      e++;
    }
    text[0] = a;
    text[1] = b;
    text[2] = c;
    text[3] = d;
    text[l] = '\0';
  }
  return 0;
}