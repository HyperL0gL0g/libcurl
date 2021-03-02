//this program shows you how to write to a file using libcurl
// the i variable shows how many individual chunks were downloaded
#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curl/curl.h>
using namespace std;
FILE* fp;
int i=0;

size_t func(char* buffer , size_t itemsize, size_t n  ,FILE* fp)
 {
 //cout << "func called" << endl;
 	cout << "downloading chunk " << i << endl;
 for(int i=0;i<strlen(buffer);i++)
  	fputc(buffer[i],fp);
 size_t bytes = itemsize*n;
 cout << "downloaded chunk " << i << endl;
 i++;
 return bytes;
 }
//TODO create one thread - trigger the download in that thread and stop that thread in 
//string  url = "https://raw.githubusercontent.com/logicinfinite/libcurl/master/ufc.mp4";

 //thread function
void* download_file(void* args)
{
	cout << "second thread working...." << endl;
	
	CURL* curl;
	curl = curl_easy_init();
	CURLcode res;
	if(!curl)
  {
  fprintf(stderr,"error initialised%s\n" ,curl_easy_strerror(res));   
  } 
  else if(curl) {
  	fp = fopen("new.txt","w+");
    curl_easy_setopt(curl, CURLOPT_URL, "http://itsabhinav.me"); //setting the url flag
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,fp); // fp is the file pointer

    res = curl_easy_perform(curl);
     if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      }
      curl_off_t dl;
    res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &dl);
    if(!res) {
      printf("Downloaded %" CURL_FORMAT_CURL_OFF_T " bytes\n", dl);
    }
 		
    /* always cleanup */ 
    curl_easy_cleanup(curl); 

}
	cout << "second thread DONE...." << endl;
	fclose(fp);
	pthread_exit(0);
}
int main()
{

			pthread_t download;
			pthread_attr_t attr;
			pthread_attr_init(&attr);

			pthread_create(&download, &attr, download_file, NULL);
			//thread started
			cout << "Main thread working....."<< endl;
			for(long i=0;i<1000000000;i++)
			{
							// just boiler plate to simulate real life  multithreading
			}
			cout << "Main thread DONE ......." << endl;
			pthread_join(download, NULL);
			cout << "thread joined" << endl;
	return 0;

}