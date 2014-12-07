// This project is an experimental project developed by Vahid_Sheigani(Mr.)
// Dated is 2014.09.13

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

bool guessed[9][9];
int tempanswers[9][9];
bool solved=false;
bool wrong[9][9][9];
int answers[9][9];
int sug[9][9][9];
int nums[9][9];
bool ischanged[9][9];
char getkey;
int tempx=0,tempy=0,tempz=0;
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
int s,s2,d2,a2,b2,c2,h2,k2;
bool correct2=true;
for (s = 0; s <= 2; s++) {
for (a2 = 3*s ; a2 < (s+1)*3; a2++) {
	for (s2 = 0; s2 <= 2; s2++) {
	for (b2 = 3*s2 ; b2 < (s2+1)*3 ; b2++) {
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
	}
	}
return correct2;
}

void fillnums(){
nums[0][0]=0;nums[1][0]=4;nums[2][0]=0;
nums[3][0]=0;nums[4][0]=0;nums[5][0]=0;
nums[6][0]=0;nums[7][0]=0;nums[8][0]=7;

nums[0][1]=8;nums[1][1]=0;nums[2][1]=9;
nums[3][1]=0;nums[4][1]=0;nums[5][1]=6;
nums[6][1]=3;nums[7][1]=0;nums[8][1]=5;


nums[0][2]=0;nums[1][2]=3;nums[2][2]=0;
nums[3][2]=4;nums[4][2]=9;nums[5][2]=0;
nums[6][2]=2;nums[7][2]=8;nums[8][2]=0;


nums[0][3]=0;nums[1][3]=0;nums[2][3]=0;
nums[3][3]=0;nums[4][3]=0;nums[5][3]=0;
nums[6][3]=5;nums[7][3]=1;nums[8][3]=0;

nums[0][4]=0;nums[1][4]=9;nums[2][4]=4;
nums[3][4]=1;nums[4][4]=2;nums[5][4]=5;
nums[6][4]=6;nums[7][4]=3;nums[8][4]=0;

nums[0][5]=0;nums[1][5]=6;nums[2][5]=5;
nums[3][5]=0;nums[4][5]=0;nums[5][5]=0;
nums[6][5]=0;nums[7][5]=0;nums[8][5]=0;

nums[0][6]=0;nums[1][6]=2;nums[2][6]=7;
nums[3][6]=0;nums[4][6]=5;nums[5][6]=3;
nums[6][6]=0;nums[7][6]=9;nums[8][6]=0;

nums[0][7]=4;nums[1][7]=0;nums[2][7]=3;
nums[3][7]=9;nums[4][7]=0;nums[5][7]=0;
nums[6][7]=0;nums[7][7]=0;nums[8][7]=6;

nums[0][8]=9;nums[1][8]=0;nums[2][8]=0;
nums[3][8]=0;nums[4][8]=0;nums[5][8]=0;
nums[6][8]=0;nums[7][8]=5;nums[8][8]=0;
}

int checkforrem(){
int a,b,c;
int a1,b1,c1,c4,c3;
//bool correct1=true;
for (a1 = 0; a1 < 9; a1++) {
	for (b1 = 0; b1 < 9; b1++) {
	for (c1 = b1+1; c1 < 9; c1++) {
		if (answers[a1][b1] == 0 && answers[a1][c1] != 0 && sug[a1][b1][answers[a1][c1]-1]==answers[a1][c1]) {
			sug[a1][b1][answers[a1][c1]-1]=0;
		}

	}
	}
}


for (a1 = 0; a1 < 9; a1++) {
	for (b1 = 0; b1 < 9; b1++) {
	for (c4 = b1-1; c4 >= 0; c4--) {
		if (answers[a1][b1] == 0 && answers[a1][c4] != 0 && sug[a1][b1][answers[a1][c4]-1]==answers[a1][c4]) {
			sug[a1][b1][answers[a1][c4]-1]=0;
		}
  }
  }
}

for (a = 0; a < 9; a++) {
	for (b = 0; b < 9; b++) {
	for (c = b+1; c < 9; c++) {
		if (answers[b][a] == 0 && answers[c][a] != 0 && sug[b][a][answers[c][a]-1]==answers[c][a]) {
			sug[b][a][answers[c][a]-1]=0;
		}
	}

}
}

for (a = 0; a < 9; a++) {
	for (b = 0; b < 9; b++) {
	for (c3 = b-1; c3 >=0; c3--) {
		if (answers[b][a] == 0 && answers[c3][a] != 0 && sug[b][a][answers[c3][a]-1]==answers[c3][a]) {
			sug[b][a][answers[c3][a]-1]=0;
		}
}
}
}

int n2,m2,p,o,n,m,j3,k3,s,s2,d2,a2,b2,c2,h2,k2;

for (s = 0; s <= 2; s++) {
  n2=3*s;
  m2= (3*(s+1))-1;
for (n = 0; n <= 2; n++) {
  j3=3*n;
  k3= (3*(n+1))-1;
  
	for (b2 = n2; b2 <= m2; b2++) {
	for (a2 = j3; a2 <= k3; a2++) {
//	if((b2+1)%3==1){
//		if ((a2+1)%3==1) {
//	
	for (p= n2; p <= m2; p++) {
	for (o = j3; o <= k3; o++) {
		if (answers[b2][a2] == 0 && answers[p][o] != 0 && sug[b2][a2][answers[p][o]-1]==answers[p][o]) {		
			sug[b2][a2][answers[p][o]-1]=0;
		}
  }
		}
		}
  }	
  }
}
return 0;
}



bool checkforremtemp(){
int a,b,c;
bool done;
int a1,b1,c1,c4,c3;
//bool correct1=true;
for (a1 = 0; a1 < 9; a1++) {
	for (b1 = 0; b1 < 9; b1++) {
	for (c1 = b1+1; c1 < 9; c1++) {
		if (tempanswers[a1][b1] == 0 && tempanswers[a1][c1] != 0 && sug[a1][b1][tempanswers[a1][c1]-1]==tempanswers[a1][c1]) {
			sug[a1][b1][tempanswers[a1][c1]-1]=0;
      done= true;
		}

	}
	}
}




for (a1 = 0; a1 < 9; a1++) {
	for (b1 = 0; b1 < 9; b1++) {
	for (c4 = b1-1; c4 >= 0; c4--) {
		if (tempanswers[a1][b1] == 0 && tempanswers[a1][c4] != 0 && sug[a1][b1][tempanswers[a1][c4]-1]==tempanswers[a1][c4]) {
			sug[a1][b1][tempanswers[a1][c4]-1]=0;
      done= true;
		}
  }
  }
}

for (a = 0; a < 9; a++) {
	for (b = 0; b < 9; b++) {
	for (c = b+1; c < 9; c++) {
		if (tempanswers[b][a] == 0 && tempanswers[c][a] != 0 && sug[b][a][tempanswers[c][a]-1]==tempanswers[c][a]) {
			sug[b][a][tempanswers[c][a]-1]=0;
      done=true;
		}
	}

}
}

for (a = 0; a < 9; a++) {
	for (b = 0; b < 9; b++) {
	for (c3 = b-1; c3 >=0; c3--) {
		if (tempanswers[b][a] == 0 && tempanswers[c3][a] != 0 && sug[b][a][tempanswers[c3][a]-1]==tempanswers[c3][a]) {
			sug[b][a][tempanswers[c3][a]-1]=0;
      done=true;
		}
}
}
}

int n2,m2,p,o,n,m,j3,k3,s,s2,d2,a2,b2,c2,h2,k2;

for (s = 0; s <= 2; s++) {
  n2=3*s;
  m2= (3*(s+1))-1;
for (n = 0; n <= 2; n++) {
  j3=3*n;
  k3= (3*(n+1))-1;
  
	for (b2 = n2; b2 <= m2; b2++) {
	for (a2 = j3; a2 <= k3; a2++) {
//	if((b2+1)%3==1){
//		if ((a2+1)%3==1) {
//	
	for (p= n2; p <= m2; p++) {
	for (o = j3; o <= k3; o++) {
		if (tempanswers[b2][a2] == 0 && tempanswers[p][o] != 0 && sug[b2][a2][tempanswers[p][o]-1]==tempanswers[p][o]) {		
			sug[b2][a2][tempanswers[p][o]-1]=0;
      done=true;
		}
  }
		}
		}
  }	
  }
  
  }
	/*	if ((a2+1)%3==2) {
	for (d2 = a2-1; d2 < 3; d2++) {
	for (c2 = b2+1; c2 < 3; c2++) {
			if (d2 != a2) {
		
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
		}
		}
		}
		}
    }	
		if ((a2+1)%3==0) {
	for (d2 = a2-2; d2 < 3; d2++) {
	for (c2 = b2+1; c2 < 3; c2++) {
			if (d2 != a2) {    
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
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
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
		}
		}
		}
		}
		}

		if ((a2+1)%3==2) {
	for (d2 = a2-1; d2 < 3; d2++) {
	for (c2 = b2-1; c2 < 3; c2++) {
			if (d2 != a2 && c2 != b2) {	
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
		}
		}
		}
		}
		}

		if ((a2+1)%3==0) {
	for (d2 = a2-2; d2 < 3; d2++) {
	for (c2 = b2-1; c2 < 3; c2++) {
		 if (d2 != a2 && c2 != b2) {	
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
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
		
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
		}
		}
		}
		}
    }
		if ((a2+1)%3==2) {
	for (d2 = a2-1; d2 < 3; d2++) {
	for (c2 = b2-2; c2 < 3; c2++) {
			if (d2 != a2 && c2 != b2) {
	
		
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
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
		if (nums[c2][d2] == 0 && nums[b2][a2] != 0 && sug[c2][d2][nums[b2][a2]-1]==nums[b2][a2]) {		
      sug[c2][a2][nums[b2][a2]-1]=0;
		}
		}
		}
		}				
	
    }	
    }	
}
	}
*/
return done;
}

int checkifone(){
  int l,o,w,e,l1,o1,w1;
  int free[9][9];
 
 for (l1=0 ; l1<9; l1++){ 
 for (o1=0 ; o1<9; o1++){
 free[l1][o1]=0;
 }
 }


 for (l=0 ; l<9; l++){ 
 for (o=0 ; o<9; o++){
 for (w=0 ; w<9; w++){
 if(sug[l][o][w]==0){
 free[l][o]+=1;
 }
 }
 if(free[l][o]==8){
   for (e=0; e<9; e++){
     if(sug[l][o][e] != 0){
   answers[l][o]= sug[l][o][e];
     sug[l][o][e]=11;
   }
       else{
     sug[l][o][e]=11;
       }
 }
 }
 }
 }

 return 0;
}

void fillanswers(){

int q,qq;
for(q=0; q<9; q++){
  for(qq=0; qq<9 ; qq++){
  
      if(nums[q][qq] != 0){
      answers[q][qq]=nums[q][qq];
      }
   }
}
}


void printsug(){
int xxx,yyy,t,y,u;

	  for (t = 0; t < 9; t++) {
	  for (y = 0; y < 9; y++) {
   	  for (u = 0; u < 9; u++) {
//	xxx= 21+ (y*2);
//	yyy= 13+ t;
//	printf("\033[25;15H");
  printf("%3d", sug[y][t][u]);
     	  }
	puts("");
    }
}
}

int printtempanswers(){
int n1,m1,xx,yy;
	  for (m1 = 0; m1 < 9; m1++) {
   	  for (n1 = 0; n1 < 9; n1++) {
	xx= 21+ (n1*2);
	yy= 13+ m1;
	//printf("\033[%d;%dH%s",yy+1,xx-1,"|");
		printf("\033[%d;%dH%-3d",yy+1,xx-1,tempanswers[n1][m1]);
     	  }
	puts("");
    }
      printf("\033[1;2H");

return 0;
}

int printanswers(){
int n1,m1,xx,yy;
	  for (m1 = 0; m1 < 9; m1++) {
   	  for (n1 = 0; n1 < 9; n1++) {
	xx= 21+ (n1*2);
	yy= 13+ m1;
	//printf("\033[%d;%dH%s",yy+1,xx-1,"|");
		printf("\033[%d;%dH%-3d",yy+1,xx-1,answers[n1][m1]);
     	  }
	puts("");
    }
      printf("\033[1;2H");

return 0;
}

void fillsug(){
int q,qq,qqq;
for(q=0; q<9; q++){
  for(qq=0; qq<9 ; qq++){
    for (qqq=1 ; qqq<=9 ; qqq++){
    if(answers[q][qq] == 0){
    sug[q][qq][qqq-1]=qqq;
    }
    else{
    sug[q][qq][qqq-1]=11;
    }
  }  
}
}
}

int ifsolved(){
 int i,j,k;
for(i=0; i<9; i++){
  for(j=0; j<9 ; j++){
    if(tempanswers[i][j]==0){
    solved=false;
    }else{
    solved=true;
    }    
  }
}
return 0;
}

int filltemp(){
 for (n=0 ; n<9; n++){ 
   for (m=0 ; m<9; m++){
     tempanswers[n][m]=answers[n][m];
   }
 }
}


int solve(){
int jk;
for(jk=1 ; jk<=100; jk++){
checkforrem();
checkifone();
if(solved==true){
break;
}
}
return 0;
}

void ifwrong(l,o){
  int g,h,u,nm,fn,hh,kk;
  bool xx;
    checkforremtemp();
      for(u=0 ; u<9; u++){
       if(sug[l][o][u]!=0){
         nm+=1;
       }
      }
      if(l>0){
      for(hh=l ; hh>=0; hh--){
      if(guessed[hh][o]==true){
    tempx=hh;tempy=o;
      }
      }
      }else{
        l=8;o=o-1;
        for(kk=l; kk>=0; kk--){
          if(guessed[kk][o]==true){
        tempx=kk;tempy=o;
          }
         }
      }

  if(nm==0){
    wrong[tempx][tempy][tempz]=false;
  }
  else{
    wrong[tempx][tempy][tempz]=true;
  }
}

int solve_2(){
int n,m,l,o,w,con;
int q,y,e,mj;

for (con=1;con<1000; con++ ){
//  ifsolved();
//  if(solved==false){
 for (o=0 ; o<9; o++){ 
  for (l=0 ; l<9; l++){
   if (tempanswers[l][o]==0){
    for (w=0 ; w<9; w++){
      ifwrong(l,o);
    if(wrong[tempx][tempy][tempz]==true){
        if(sug[l][o][w]!=0){
      tempanswers[l][o]=sug[l][o][w];
      guessed[l][o]=true;
      tempz=w;
      if(l<8){
        l+=1;
      }else{
        l=0;o+=1;
      }
        }
      break;
      }else{
      tempanswers[tempx][tempy]=0;
      sug[tempx][tempy][tempz]=0;
      wrong[tempx][tempy][tempz]=true; 
      //guessed[tempx][tempy]=false;
      o=tempy;l=tempx;
      for (mj=0; mj<9; mj++){
        if(sug[l][o][mj]!=0){
      tempanswers[l][o]=sug[l][o][mj];
        }
       }
      if(l<8){
        l+=1;
      }else{
        l=0;o+=1;
      }
      break;
      
   }
 }
    ifwrong(l,o);
 /*   ifwrong(l,o);
   }else if(wrong[tempx][tempy][tempz]==false){
      tempanswers[tempx][tempy]=0;
      sug[tempx][tempy][tempz]=0;
      wrong[tempx][tempy][tempz]=true; 
      w=0;
      guessed[tempx][tempy]=false;
        o=tempy;l=tempx;
        break;break;
        
}
*/
}

}
}
ifsolved();
//}else{
//  break;
//}

}
return 0;
}

void fillwrong(){
int l,o,w;
 for (l=0 ; l<9; l++){ 
  for (o=0 ; o<9; o++){
    for (w=0 ; w<9; w++){
      wrong[l][o][w]=true;
    }
   }
  }
}

void fillguessed(){
int l,o,w;
 for (l=0 ; l<9; l++){ 
  for (o=0 ; o<9; o++){
      guessed[l][o]=false;
    }
   }
  }
/*
int a,b,c;
int a1,b1,c1;
//bool correct1=true;
for (a1 = 0; a1 < 9; a1++) {
	for (b1 = 0; b1 < 8; b1++) {
	for (c1 = b1+1; c1 < 9; c1++) {
		if (nums[a1][c1] == 0 && nums[a1][b1] != 0 && sug[a1][c1][nums[a1][b1]]==nums[a1][b1]) {
			sug[a1][c1][nums[a1][b1]]=0;
		}
	}
	}
}

for (a = 0; a < 9; a++) {
	for (b = 0; b < 8; b++) {
	for (c = b+1; c < 9; c++) {
		if (nums[c][a] == 0 && nums[b][a] != 0 && sug[c][a][nums[b][a]]==nums[b][a]) {
			sug[c][a][nums[b][a]]=0;
		}
	}
}
}
*/



int main(int argc, const char *argv[])
{
int xup,yup,xdown,ydown,xright,yright,xleft,yleft,xnum,ynum,xtable=0,ytable=0,xdel,ydel;
int gen;
bool checkrow,checkcol,checkbox;
int num1;
char ns[9][9];
int zz1,zz,zz2,ff=1,sss;

char s[8];
char err[100]="Wrong Key Inserted";
   // Clearing terminal screen using system function
   system("clear");
  
  // filling nums and changed arrays witn zero and false values in the application start
  for (m = 0; m < 9; m++) {
    for (n = 0; n < 9; n++) {
      nums[m][n]=0;
    //  ischanged[m][n]=false;
    }
  }
for(zz=0 ; zz <9; zz++ ){
scanf("%9s",ns[zz]);
  for(zz2=0 ; zz2<9; zz2++){
    nums[zz2][zz]=ns[zz][zz2]-'0';
  }
}

 // fillnums();
setBufferedInput(false);
while(1){

getkey=getchar();
switch(getkey){
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


  case 115:
  fillanswers();
  fillsug();
  //filltemp();
  fillwrong();
  fillguessed();
  
  //solve_2();
  solve();
  printanswers();
  //printtempanswers();
  break;

	case 113:
   	system("clear");
	setBufferedInput(true);
	exit(status);
  break;
}
}
return 0;
}
/*
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


  }   
  }
*/  
//  return 0;

  //}
