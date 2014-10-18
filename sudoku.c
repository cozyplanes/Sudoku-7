// This project is an experimental project developed by Vahid_Sheigani(Mr.)
// Dated is 2014.09.13

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


int nums[9][9];
bool ischanged[9][9];
char getkey;
int status=0,m,n,i,j,z;
int row=0,col=0,col1=0,col10=1;
  // this function change application state to recieve arrow keys without buffering them and hitting enter key  
  void setBufferedInput(bool enable) {
    static bool enabled = true;
    static struct termios old;
    struct termios new;
    if (enable && !enabled) {
      tcsetattr(STDIN_FILENO,TCSANOW,&old);
      enabled = true;
    } else if (!enable && enabled) {
    tcgetattr(STDIN_FILENO,&new);
    old = new;
    new.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new);
    enabled = false;
    }
  }
  // below function print any changed number in nums array in specified loction
  int printchanges(){ 
  int ss2,ss1,ss3;
  int xposition;
  for (ss1 = 0; ss1 < 9; ss1++) {
    for (ss2 = 8; ss2 >= 0 ; ss2--) {
       if (ischanged[ss2][ss1]==true) {
       if (nums[ss2][ss1] != 0){
       xposition=((ss1)*5)+2;
       printf("\033[%d;%dH%-s",ss2+1,xposition,"    ");
       printf("\033[%d;%dH%-d",ss2+1,xposition,nums[ss2][ss1]);
      }
      else{   
       xposition=((ss1)*5)+2;
       printf("\033[%d;%dH%-s",ss2+1,xposition,"    ");
      }
      ischanged[ss2][ss1]=false;
     }
  }
  }
    return 0;
  }
int rowcount(char w[8]){
setBufferedInput(false);
int gen1;
	for (gen1=0; gen1<8 ; gen1++){
	if (w[gen1]== ';'){
	row= w[gen1-1]- '0';
	}
}
return row;
}


int colcount(char m[8]){
setBufferedInput(false);
int gen2;
	for (gen2=0; gen2<8 ; gen2++){
	if(m[gen2]=='R'){
	col1 = m[gen2-1]- '0';
	if (m[gen2-2]== ';') {
		col=col1;
		break;
	}
	else{
	col10= m[gen2-2]- '0';	
	col= col10*10+col1;
	}
	}
	}
return col;
}

int main(int argc, const char *argv[])
{
int xup,yup,xdown,ydown,xright,yright,xleft,yleft,xnum,ynum;
int gen;
int num1;
char s[8];
char err[100]="Wrong Key Inserted";
   // Clearing terminal screen using system function
   system("clear");
  
  // filling nums and changed arrays witn zero and false values in the application start
  for (m = 0; m < 9; m++) {
    for (n = 0; n < 9; n++) {
      nums[m][n]=0;
      ischanged[m][n]=false;
    }
  }
  

  // printing game table with nums array number in application start
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      printf("|");
      for (z = 0; z < 2; z++){
      printf(" ");
      }
}
    puts("");
  }

	
      printf("\033[1;2H");
      setBufferedInput(false);
      while(1){
      // getting arrow keys from user repeatedly 
      getkey=getchar(); 

      // check which arrow keys are pressed
      switch(getkey){

      // calling required functions when up key is pressed
      case 65:
      
      printf("\033[6n");
      scanf("%7s",s);
      xup= rowcount(s);
      yup= colcount(s);
      if (yup>1) {
      printf("\033[1A");
      }

      break;
      
      // calling required functions when down key is pressed
      case 66:
      
      printf("\033[6n");
      scanf("%7s",s);
      xdown= rowcount(s);
      ydown= colcount(s);
      if (xdown<9) {
      printf("\033[1B");
      }
      break;

      // calling required functions when right key is preesed
      case 67:
      printf("\033[6n");
      scanf("%7s",s);
      xright= rowcount(s);
      yright= colcount(s);
      if (yright<25) {
      printf("\033[3C");
      }
      break;

	case 113:
   	system("clear");
	setBufferedInput(true);
	exit(status);
	break;
	

      // calling required functions when left key is pressed
      case 68:
      printf("\033[6n");
      scanf("%7s",s);
      xleft= rowcount(s);
      yleft= colcount(s);
      if (yleft>2) {
      printf("\033[3D");
      }
      break;
	
      case 49:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
      num1= getkey - '0';
      printf("\033[%d;%dH%d",xnum,ynum,num1);
      break;
/*
      default :	
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	num1= getkey - '0';
	printf("\033[12;10H%-99s",err);
	printf("\033[%d;%dH",xnum,ynum);
	break;
*/
  }   
  }
  
  return 0;

  }
