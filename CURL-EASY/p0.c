// program to redirect the general behavior of curl to print in console  and print in a new way with line number
#include <stdio.h>
#include <curl/curl.h>
 size_t func(char* buffer , size_t itemsize, size_t n  ,void* ignore)
 {
 
 CURL *curl = curl_easy_init();
 
 size_t bytes = itemsize*n;
 printf("chunk size received = %zu\n", bytes);
 int line=1;
 //printf("%d",line);
 for(int i=0;i<bytes;i++)
 {
 //printf("%c", buffer[i]);
 if(buffer[i]=='\n')
 {
 line++;
 //printf("%d",line);
 }
 
 }
 char* raw = "www. ggs. vom";
 char* encoded = curl_easy_escape(curl,raw, 13);
 if(encoded){
 printf("Raw url  : %s , Encoded Url : %s",raw,encoded);
 curl_free(encoded);
 //printf("void ignore   :%s" ,ignore); 
 }
 return  bytes;
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
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com"); //setting the url flag
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &func); // setting the writefunction to print data using out custom function 
    
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
  
    /* Check for errors */ 
    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
      }
 		
    /* always cleanup */ 
    curl_easy_cleanup(curl); 
  }
  return 0;
}
