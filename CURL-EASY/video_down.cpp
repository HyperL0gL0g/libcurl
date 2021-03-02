//single threaded video downloader using libcurl
#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curl/curl.h>
using namespace std;
FILE* fp;

int main()
{
CURL* curl;
curl = curl_easy_init();
CURLcode res;
	if(!curl)
  {
  fprintf(stderr,"error initialised%s\n" ,curl_easy_strerror(res));   
  } 
  else if(curl) {
  	fp = fopen("vid.mp4","wb");
    curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/logicinfinite/sample_video/master/ufc.mp4"); //setting the url flag
   // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,fp); // fp is the file pointer
    cout << "downloading " << endl ;
    res = curl_easy_perform(curl);
	
     if(res == CURLE_OK){
      cout << "download success"  << endl;
      }    

     if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      }
      /*
      curl_off_t dl;
    res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &dl);
    if(!res) {
      printf("Downloaded %" CURL_FORMAT_CURL_OFF_T " bytes\n", dl);
    }*/
 		
    /* always cleanup */ 
  }
    curl_easy_cleanup(curl); 
			
	return 0;

}