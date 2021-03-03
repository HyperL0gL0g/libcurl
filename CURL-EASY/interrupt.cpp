//this program shows you how to interrupt a file download to stop it in between 
#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curl/curl.h>
using namespace std;
FILE* fp;
bool ex =false;
size_t func(char* buffer , size_t itemsize, size_t n  ,void* userp)
 {
 	
 	sleep(1);
 	if(ex)
 	{
 	cout << "exiting download thread from l17" << endl;
 	fclose(fp);
 	pthread_exit(0);
	}
 
 for(int i=0;i<strlen(buffer);i++){
 	if(ex){
 	cout << "exiting download thread from l23" << endl;
 	pthread_exit(0);
 	}
  	fputc(buffer[i],fp);
  }
 size_t bytes = itemsize*n;
 cout << bytes << " bytes received" << endl;
 return bytes;
 }
//TODO create one thread - trigger the download in that thread and stop that thread in 
//string  url = "https://raw.githubusercontent.com/logicinfinite/sample_video/master/ufc.mp4
 //thread function
void* download_file(void* args)
{
	if(ex){
		cout << "exiting download thread from l38" << endl;
		fclose(fp);
	pthread_exit(0);
}

	cout << "second thread working...." << endl;

	CURL* curl;
	curl = curl_easy_init();
	CURLcode res;
	if(!curl)
  {
  fprintf(stderr,"error initialised%s\n" ,curl_easy_strerror(res));   
  } 
  else if(curl) {
  	fp = fopen("t.txt","w+");
    curl_easy_setopt(curl, CURLOPT_URL, "http://itsabhinav.me"); //setting the url flag
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func);
  //  curl_easy_setopt(curl, CURLOPT_WRITEDATA,fp); // fp is the file pointer

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
	//sleep(3);
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
			// simulation 
			sleep(2);
			ex=true;

			cout << "Main thread DONE ......." << endl;
			pthread_join(download, NULL);
			cout << "thread joined" << endl;
	return 0;

}