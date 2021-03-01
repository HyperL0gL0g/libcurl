// program to redirect the general behavior of curl to print in console  and print in a new way with line number
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
using namespace std;
 size_t func(char* buffer , size_t itemsize, size_t n  ,void* ignore)
 {
 cout << "func called" << endl;
  CURL *curl = curl_easy_init();
 
 size_t bytes = itemsize*n;
 printf("chunk size received = %zu\n", bytes);
 int line=1;
 return bytes;
 
 }
int main(void)
{
  CURL *curl; //curl pointer(handle)
  CURLcode res; //for return codes
  curl = curl_easy_init(); // initiaising the curl pointer
  if(!curl)
  {
  fprintf(stderr,"error initialised%s\n" ,curl_easy_strerror(res));   
  } 
  
 else if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://mediamelon.com/"); //setting the url flag
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &func); // setting the writefunction to print data using out custom function 
    
    /* Perform the request, res will get the return code */ 
    cout << "EASY PERFORM STARTED........." << endl;
    res = curl_easy_perform(curl);
    cout << "---EASY PERFORM FINISHED---" << endl;
    
    
     long http_code = 0;
     //get the http code returned by the server
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
  printf("--------long http code : ----------%ld\n",http_code );
    /* Check for errors */ 
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      }
      //get the bytes downloaded
    curl_off_t dl;
    res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &dl);
    if(!res) {
      printf("Downloaded %" CURL_FORMAT_CURL_OFF_T " bytes\n", dl);
    }
 		
    /* always cleanup */ 
    curl_easy_cleanup(curl); 
  }
  return 0;
}
