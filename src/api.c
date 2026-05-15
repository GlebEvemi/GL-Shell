#include "functions.h"

// Functions requests server and gets all computers
int getAllComputers(char *server_url, char *username, char *password){
    char new_url[256];
    snprintf(new_url, sizeof(new_url), "%s/api/pc", server_url);
    CURL *curl = NULL;
    // Initialize curl
    curl = curl_easy_init();
    if(!curl) return -1;

    CURLcode result;
    char *header = ""; // Add header here if needed
    struct curl_slist *headers = NULL;


    curl_easy_setopt(curl, CURLOPT_URL, new_url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);


    result = curl_easy_perform(curl);
    if(result != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return -1;
    }
        

    curl_easy_cleanup(curl);
    return (int)result;
}



int getComputerByHostname(char *server_url,char *hostname, char *username, char *password){
    CURL *curl = NULL;
    // Initialize curl
    curl = curl_easy_init();
    if(!curl) return -1;
    CURLcode result;
    char *header = ""; // Add header here if needed
    struct curl_slist *headers = NULL;

    char new_url[128];
    char *encoded = curl_easy_escape(curl, hostname, 0);
    snprintf(new_url, sizeof(new_url), "%s/api/pc/%s", server_url, encoded);
    curl_free(encoded);


    curl_easy_setopt(curl, CURLOPT_URL, new_url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);

    result = curl_easy_perform(curl);

    if(result != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return -1;
    }
    
    curl_easy_cleanup(curl);
    return (int)result;


}