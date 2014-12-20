// This project is an experimental project developed by Vahid_Sheigani(Mr.)
// Dated is 2014.09.13
//hello
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

bool checkrows(){
int a,b,c;
bool correct=true;
for (a = 0; a < 9; a++) {
	for (b = 0; b < 8; b++) {
	for (c = b+1; c < 9; c++) {
		if (nums[c][a] != 0 && nums[b][a] != 0 && nums[c][a]==nums[b][a]) {
			correct=false;
		}
	}
	}
}
return correct;
}

bool checkcols(){
int a1,b1,c1;
bool correct1=true;
for (a1 = 0; a1 < 9; a1++) {
	for (b1 = 0; b1 < 8; b1++) {
	for (c1 = b1+1; c1 < 9; c1++) {
		if (nums[a1][c1] != 0 && nums[a1][b1] != 0 && nums[a1][c1]==nums[a1][b1]) {
			correct1=false;
		}
	}
	}
}
return correct1;
}

bool checkboxes(){
int s,d2,a2,b2,c2;
bool correct2=true;
//for (s = 0; i <= 2; i++) {
for (a2 = 0; a2 < 3; a2++) {
	for (b2 = 0 ; b2 < 3; b2++) {
	if((b2+1)%3==1){
		if ((a2+1)%3==1) {
	for (d2 = a2+1; d2 < 3; d2++) {
	for (c2 = b2+1; c2 < 3; c2++) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		if ((a2+1)%3==2) {
	for (d2 = a2-1; d2 < 3; d2++) {
	for (c2 = b2+1; c2 < 3; c2++) {
			if (d2 != a2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}
		
		if ((a2+1)%3==0) {
	for (d2 = a2-2; d2 < 3; d2++) {
	for (c2 = b2+1; c2 < 3; c2++) {
			if (d2 != a2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}		
}
		
	if((b2+1)%3==2){
		if ((a2+1)%3==1) {
	for (d2 = a2+1; d2 < 3; d2++) {
	for (c2 = b2-1; c2 < 3; c2++) {
		if (c2 != b2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}

		if ((a2+1)%3==2) {
	for (d2 = a2-1; d2 < 3; d2++) {
	for (c2 = b2-1; c2 < 3; c2++) {
			if (d2 != a2) {
			if (c2 != b2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}
		}
		if ((a2+1)%3==0) {
	for (d2 = a2-2; d2 < 3; d2++) {
	for (c2 = b2-1; c2 < 3; c2++) {
			if (d2 != a2) {
			if (c2 != b2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}
		}				
		
}
}	
	
	if((b2+1)%3==0){
		if ((a2+1)%3==1) {
	for (d2 = a2+1; d2 < 3; d2++) {
	for (c2 = b2-2; c2 < 3; c2++) {
		if (c2 != b2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}


		if ((a2+1)%3==2) {
	for (d2 = a2-1; d2 < 3; d2++) {
	for (c2 = b2-2; c2 < 3; c2++) {
			if (d2 != a2) {
			if (c2 != b2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		
		}
		}
		}
		}
		}
		}
		if ((a2+1)%3==0) {
	for (d2 = a2-2; d2 < 3; d2++) {
	for (c2 = b2-2; c2 < 3; c2++) {
			if (d2 != a2) {
			if (c2 != b2) {
		if (nums[c2][d2] != 0 && nums[b2][a2] != 0 && nums[c2][d2]==nums[b2][a2]) {
			correct2=false;
		}
		}
		}
		}
		}				
		}	
}	
	}
	}
return correct2;
}

int main(int argc, const char *argv[])
{
int xup,yup,xdown,ydown,xright,yright,xleft,yleft,xnum,ynum,xtable=0,ytable=0,xdel,ydel;
int gen;
bool checkrow,checkcol,checkbox;
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
	printf("\033[2;40H%-20s","Hints:");
	printf("\033[3;40H%-20s","Use Arrow Keys For Moving Between Cells");
	printf("\033[4;40H%-20s","Press P for Print Sudoku Puzzle");
	printf("\033[5;40H%-20s","Press T for Testing Sudoku Puzzle");
	printf("\033[6;40H%-20s","Press S for Solve");
	printf("\033[7;40H%-20s","Press Q for Quit");

      printf("\033[1;2H");
      setBufferedInput(false);
      while(1){
      // getting arrow keys from user repeatedly 
	getkey= getchar();
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
      if (yright<27) {
      printf("\033[1C");
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
      printf("\033[1D");
      }
      break;
	
      case 49:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
	
      case 50:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 51:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 52:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 53:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 54:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 55:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 56:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
      case 57:
      printf("\033[6n");
      scanf("%7s",s);
      xnum= rowcount(s);
      ynum= colcount(s);	
	if (ynum != 1) {
  	 if (ynum%3==2) {
         num1= getkey - '0';
    	 nums[(ynum/3)][xnum-1]=num1;
	 ischanged[ynum/3][xnum-1]=true;	
         printf("\033[%d;%dH%d",xnum,ynum,num1);	
	}
}
      break;
	
	case 127:
      printf("\033[6n");
      scanf("%7s",s);
      xdel= rowcount(s);
      ydel= colcount(s);	
	if (ydel%3==0) {
      nums[(ydel/3)-1][xdel-1]=0;
//	ischanged[ydel/3][xdel-1]=true;	
      printf("\033[%d;%dH%1s",xdel,ydel-1," ");	
         printf("\033[1D");	
	}
	break;
/*	
	case 27:
      printf("\033[6n");
      scanf("%7s",s);
      xdel= rowcount(s);
      ydel = colcount(s);	
	if (ydel != 1) {
	if (ydel%3==0) {
      nums[ydel/3][xdel-1]=0;	
	ischanged[ydel/3][xdel-1]=true;	
      printf("\033[%d;%dH%-2s",xdel,ydel,"D");	
	}
}
	break;
*/
	case 112:	
	  for (m = 0; m < 9; m++) {
   	  for (n = 0; n < 9; n++) {
	xtable= 1+ (n*2);
	ytable= 13+ m;
	printf("\033[%d;%dH%s",ytable+1,xtable-1,"|");
		printf("\033[%d;%dH%-3d",ytable+1,xtable, nums[n][m]);
     	  }
	puts("");
    }
      printf("\033[1;2H");
	break;
	
	
	case 116:
	checkrow= checkrows();
	checkcol= checkcols();
	checkbox= checkboxes();

	if (checkrow==false) {
	printf("\033[11;5H%15s","                                   ");
	printf("\033[11;5H%15s","Same numbers inserteed in few Rows");
   	printf("\033[1;2H");
	}
	
	else if (checkcol==false) {
	printf("\033[11;5H%15s","                                   ");
	printf("\033[11;5H%15s","Same numbers inserted in few Coloumns");
   	printf("\033[1;2H");
	}
	
	else if (checkbox==false) {
	printf("\033[11;5H%15s","                                   ");
	printf("\033[11;5H%15s","Same numbers inserted in few Boxes");
   	printf("\033[1;2H");
	}
	else{	
	printf("\033[11;5H%15s","                                   ");
	printf("\033[11;5H%15s","Correct Puzzle");
   	printf("\033[1;2H");
	}

	break;

/*
      default :	
      //printf("\033[6n");
      //scanf("%7s",s);
      //xnum= rowcount(s);
     // ynum= colcount(s);	
	num1= getkey;
//	printf("\033[12;10H%-99s",err);
	printf("\033[40;10H%d",num1);
break;

*/
  }   
  }
  
  return 0;

  }
