#ifndef __THREAD_LOCAL_H__
#define __THREAD_LOCAL_H__ 1

#ifdef WITH_TLS
# include <openssl/ssl.h>
#else
typedef void *SSL_CTX;
typedef void *SSL;
#endif

#define THREAD_LOCAL(LOCAL_VAR) \
        (((ThreadLocal *) pthread_getspecific(thread_key))->_ ## LOCAL_VAR)

typedef struct ThreadLocal_ {
#define LOCAL_passive THREAD_LOCAL(passive)
    signed char _passive;

#define LOCAL_clientfd THREAD_LOCAL(clientfd)
    int _clientfd;
    
#define LOCAL_datafd THREAD_LOCAL(datafd)
    int _datafd;
    
#define LOCAL_cmd THREAD_LOCAL(cmd)
    char _cmd[MAXPATHLEN + 32U];
    
#define LOCAL_wd THREAD_LOCAL(wd)
    char _wd[MAXPATHLEN + 1U];
    
#define LOCAL_account THREAD_LOCAL(account)
    char _account[MAX_USER_LENGTH + 1U];
    
#define LOCAL_root_directory THREAD_LOCAL(root_directory)
    char *_root_directory;
    
#define LOCAL_loggedin THREAD_LOCAL(loggedin)
    signed char _loggedin;
    
#define LOCAL_guest THREAD_LOCAL(guest)
    signed char _guest;

#define LOCAL_chrooted THREAD_LOCAL(chrooted)
    signed char _chrooted;

#define LOCAL_ctrlconn THREAD_LOCAL(ctrlconn)
    struct sockaddr_storage _ctrlconn;
    
#define LOCAL_xferfd THREAD_LOCAL(xferfd)
    int _xferfd;
    
#define LOCAL_tls_ctx THREAD_LOCAL(tls_ctx)
    SSL_CTX *_tls_ctx;
    
#define LOCAL_tls_cnx THREAD_LOCAL(tls_cnx)
    SSL *_tls_cnx;
    
#define LOCAL_tls_cnx_handshaked THREAD_LOCAL(tls_cnx_handshaked)
    int _tls_cnx_handshaked;
    
#define LOCAL_tls_data_cnx THREAD_LOCAL(tls_data_cnx)
    SSL *_tls_data_cnx;
    
#define LOCAL_tls_data_cnx_handshaked THREAD_LOCAL(tls_data_cnx_handshaked)
    int _tls_data_cnx_handshaked;    
} ThreadLocal;

#include <pthread.h>
#ifdef DEFINE_GLOBALS
pthread_key_t thread_key;
ThreadLocal thread_local;
# define TGLOBAL0(A) A ## _LOCAL_INIT
# define TGLOBAL(A, B) A ## _LOCAL_INIT = B
# define TAGLOBAL0(A, S) A ## _LOCAL_INIT[S]
#else
extern pthread_key_t thread_key;
extern ThreadLocal thread_local;
# define TGLOBAL0(A) extern A ## _LOCAL_INIT
# define TGLOBAL(A, B) extern A ## _LOCAL_INIT
# define TAGLOBAL0(A, S) extern A ## _LOCAL_INIT[S]
#endif

#define LOCAL_INIT(A) LOCAL_ ## A = A ## _LOCAL_INIT
#define LOCAL_AINIT(A) *(LOCAL_ ## A) = 0

int init_thread_local_storage(void);

#endif
