#include <iostream>
#include <curl/curl.h>
#include <iterator> 
#include <map>
#include<string>

using namespace std;
//response handling function

size_t func(char* buffer , size_t itemsize, size_t n  , void* data)
 {
 size_t bytes = itemsize*n;
 //for(int i=0;i<strlen(buffer);i++)
 	//printf("%c",buffer[i]) 
 //cout << "chunk size received in buffer "<<  bytes << endl;
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
	curl_easy_setopt(curl2, CURLOPT_URL, "http://itsabhinav.meow");
	curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, &func);
  
map<void*,string> maps;
maps[curl]="https://example.com";
maps[curl2]="http://itsabhinav.me";


//maps.insert((void*)curl,"https://example.com");
//maps.insert((void*)curl2,"http://itsabhincsaav.com");

multi = curl_multi_init(); //init the multi handle
curl_multi_add_handle(multi, curl);
curl_multi_add_handle(multi, curl2); //adding the easy handle to the multi 
struct CURLMsg *m;
  while(still_running) {

    CURLMcode mc; /* curl_multi_poll() return code */
   

    /* we start some action by calling perform right away */
   // printf("before%d\n",still_running);
    mc = curl_multi_perform(multi, &still_running);
    do {
  int msgq = 0;
  m = curl_multi_info_read(multi, &msgq);
  if(m && (m->msg == CURLMSG_DONE)) {
    CURL *e = m->easy_handle;  // individual handle returned

    CURLcode result;
    long http_code = 0;
     //get the http code returned by the server
        curl_easy_getinfo (e, CURLINFO_RESPONSE_CODE, &http_code);
      //cout<<"--------long http code : ----------"<< http_code<< endl;
       map<void*,string>::iterator it ; 
        it =maps.find((void*)e);
        if(it == maps.end()) 
        cout << "url  not present in map" ; 
    else
        cout<< "--------long http code : ----------: "<< http_code <<  " URL= " << it->second << endl; 
    
   // curl_multi_remove_handle(multi,e);
   // curl_easy_cleanup(e);
  }
} while(m);
   
    if(mc != CURLM_OK) {
      cout<< "curl_multi_wait() failed, code "<< mc;
      break;
    }
    
  }

//cleanups
		curl_multi_remove_handle(multi, curl);
		curl_multi_remove_handle(multi, curl2); //remove the easy handle from the multi one
		curl_easy_cleanup(curl); // cleanup easy
		curl_easy_cleanup(curl2); // cleanup easy
		curl_multi_cleanup(multi); // clean up multi
		curl_global_cleanup(); // global cleanup
  return 0;
}

