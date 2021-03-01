#include <pthread.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
using namespace std;
size_t func(char* buffer , size_t itemsize, size_t n  ,void* ignore)
 {
 //cout << "func called" << endl;
  
 size_t bytes = itemsize*n;
 return bytes;
 }
//TODO create one thread - trigger the download in that thread and stop that thread in 
//string  url = "https://raw.githubusercontent.com/logicinfinite/libcurl/master/ufc.mp4";
void* download_file(void* args)
{
	cout << "second thread working...." << endl;
	//terminate();
	CURL* curl;
	curl = curl_easy_init();
	CURLcode res;
	if(!curl)
  {
  fprintf(stderr,"error initialised%s\n" ,curl_easy_strerror(res));   
  } 
  else if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://mediamelon.com/"); //setting the url flag
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &func); 
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