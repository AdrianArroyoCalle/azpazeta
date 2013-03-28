#ifndef WIN32
#define SOCKET int
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/un.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#define AZP_SOCK_TYPE "Berkely Sockets"
#else
#include <winsock2.h>
#include <windows.h>
#pragma comment (lib, "Ws2_32.lib")
#define AZP_SOCK_TYPE "WinSockets"
#endif

void blueprintf(const char* message);
void redprintf(const char* message);
void yellowprintf(const char* message);
void greenprintf(const char* message);
void StartBerkely();
void StartWinSock();
void MainLoop(int);
void *RegisterUser (void *); 

