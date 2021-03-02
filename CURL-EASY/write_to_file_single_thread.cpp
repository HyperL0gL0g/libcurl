//this program shows you how to write to a file using libcurl

//#include <pthread.h>
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
  if(curl) {
  	fp = fopen("new.txt","w+");
    curl_easy_setopt(curl, CURLOPT_URL, "http://itsabhinav.me"); //setting the url flag
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,fp); // fp is the file pointer

    res = curl_easy_perform(curl);
     if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      }
      curl_off_t dl;
    res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &dl);
  
    curl_easy_cleanup(curl); 

}
	
	fclose(fp);

	return 0;
}

