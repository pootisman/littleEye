#include <stdlib.h>
#include <memory.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/videodev2.h>
#define VALID_ARGS "C:M:h"

int main(int argc, char *argv[]){
  void *frame = NULL;
  int dCam = 0, i = 0, j = 1;
  FILE *pFLog = NULL;
  struct v4l2_capability capCheck;

  while((i = getopt(argc, argv, VALID_ARGS)) != -1){
    switch(i){
      case('C'):{
        if(argv[j + 1]){
          dCam = open(argv[j + 1], O_RDWR);
	  if(dCam < 0){
            (void)perror("ARGUMENTS");
	    return EXIT_FAILURE;
	  }
	  j++;
	}
	break;
      }
      case('M'):{
        if(argv[j + 1]){
          pFLog = fopen(argv[j + 1], "wa");
	  if(!pFLog){
	    (void)perror("ARGUMENTS:");
            return EXIT_FAILURE;
	  }
	  j++;
	}
	break;
      }
      default:{
        break;
      }
    }
    j++;
  }

  if(dCam <= 0){
    (void)puts("No input was specfied, closing...");
    return EXIT_FAILURE;
  }

  if(ioctl(dCam, VIDIOC_QUERYCAP, &capCheck) < 0){
    (void)perror("HARDWARE:");
    close(dCam);
    return EXIT_FAILURE;
  }else if(pFLog){
    (void)fputs("Looks like specified device is ok.", pFLog);
  }

  if(close(dCam) < 0){
    (void)fputs(strerror(errno), pFLog);
  }

  if(pFLog){
    (void)fclose(pFLog);
  }
  return EXIT_SUCCESS;
}
