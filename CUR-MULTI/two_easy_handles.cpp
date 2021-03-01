#include <iostream>
#include <curl/curl.h>
#include <iterator> 
#include <map>
#include<string>


using namespace std;
long long c=0;
//response handling function

size_t func(char* buffer , size_t itemsize, size_t n  , void* data)
 {
   cout << "func called"<< endl;
 size_t bytes = itemsize*n;
 //for(int i=0;i<strlen(buffer);i++)
 	//printf("%c",buffer[i]) 
 cout << "chunk size received in buffer "<<  bytes << endl;

 return bytes;
 }

int main(void)
{
CURLM *multi;  //curl multi handle
CURL *curl; // simple curl handle
CURL *curl2; //second simple curl handle
CURLcode res; // res for error codes 
int still_running = 1; //running processes 
curl_global_init(CURL_GLOBAL_ALL); // global init

curl2 = curl_easy_init();  //init easy handle
curl = curl_easy_init(); //init the easy handle
// setting flags to the easy handles
	curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &func); //func will handle the request
	curl_easy_setopt(curl2, CURLOPT_URL, "http://itsabhinav.me");
	curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, &func);
//populating the map  
    map<void*,string> maps;
    maps[curl]="https://example.com";
    maps[curl2]="http://itsabhinav.me";

multi = curl_multi_init(); //init the multi handle
curl_multi_add_handle(multi, curl);
curl_multi_add_handle(multi, curl2); //adding the easy handle to the multi 

  while(still_running) {
    c++;
    CURLMcode mc; /* curl_multi_poll() return code */
    /* we start some action by calling perform right away */
   // printf("before%d\n",still_running);
   // cout<< "MULTI PERFORM STARTED....." << endl;
    mc = curl_multi_perform(multi, &still_running);
    
   // cout<< ".......MULTI PERFORM FINISHED....." << endl;
   
   
    
   
    if(mc != CURLM_OK) {
      cout<< "curl_multi_wait() failed, code "<< mc;
      break;
    }
    
  }
cout << "count = " << c << endl;
//cleanups
		curl_multi_remove_handle(multi, curl);
		curl_multi_remove_handle(multi, curl2); //remove the easy handle from the multi one
		curl_easy_cleanup(curl); // cleanup easy
		curl_easy_cleanup(curl2); // cleanup easy
		curl_multi_cleanup(multi); // clean up multi
		curl_global_cleanup(); // global cleanup
  return 0;
}

