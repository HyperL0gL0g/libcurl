#include <stdio.h>
#include <curl/curl.h>
#include<string.h>

//response handling function
struct D
{
	size_t bytes;
	char* resp;
};

size_t func(char* buffer , size_t itemsize, size_t n  , struct D* data)
 {
 size_t bytes = itemsize*n;
 for(int i=0;i<strlen(data);i++)
 	printf("%c",data[i]) ;

 printf("chunk size received = %zu\n", bytes);
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
	curl_easy_setopt(curl2, CURLOPT_URL, "http://itsabhincsaav.com");
	curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, &func);

multi = curl_multi_init(); //init the multi handle
curl_multi_add_handle(multi, curl); //adding the easy handle to the multi 
curl_multi_add_handle(multi, curl2); //adding second handle

  while(still_running) {

    CURLMcode mc; /* curl_multi_poll() return code */
    int numfds;

    /* we start some action by calling perform right away */
   // printf("before%d\n",still_running);
    mc = curl_multi_perform(multi, &still_running);
   //s  printf("after	%d\n",still_running);
    /*if(still_running){
      /* wait for activity, timeout or "nothing" */
      /* CURLMcode curl_multi_poll(CURLM *multi_handle,
                          struct curl_waitfd extra_fds[],
                          unsigned int extra_nfds,
                          int timeout_ms,
                          int *numfds);         
      	mc = curl_multi_poll(multi, NULL, 0, 1000, &numfds); // timeout in ms
      	 
      }*/

    if(mc != CURLM_OK) {
      fprintf(stderr, "curl_multi_wait() failed, code %d.\n", mc);
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
