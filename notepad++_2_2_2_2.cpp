/*********************Coded by: Matiur Rahman Minar*********************/

# include "iGraphics.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void screen();
void status_bar();
void options();
void input(unsigned char key);
void file();
void print();
void cursor();
void cursorcolor();
void fnameprint();

char str[42][120]={0};
int len,line;
int tx,ty,totalrow=0;
int cx,cy,col[40]={0};
int r,g,b;
int index,curtimer;
int open,save,newf;
char fname[50][50]={0};
int insert=0,fileLen=0,fileline=0;
int savefile=0,saveask=0,openfile=0;
int help=0,about=0;
int loaderr=0,saveerr=0;

void screen()
{
	iShowBMP(0,0,"back2.bmp");
	iSetColor(0, 0, 0);
	iText(15,664,"File",GLUT_BITMAP_HELVETICA_12);
	iText(50,664,"Edit",GLUT_BITMAP_HELVETICA_12);
	iText(86,664,"Language",GLUT_BITMAP_HELVETICA_12);
	iText(155,664,"Properties",GLUT_BITMAP_HELVETICA_12);
	iText(225,664,"Help",GLUT_BITMAP_HELVETICA_12);
}
void status_bar()
{	
	if((cx>=5 && cx<=977) && (cy>=40 && cy<=640))
	{
		char p[50];
		char b[10];
		char c[10];
		p[0]=NULL;
		strcat(p,"Ln:");
		strcat(p,itoa(line+1,b,10));
		strcat(p,", Col:");
		strcat(p,itoa(len+1,c,10));
		iSetColor(0, 0, 0);
		iText(760,6,p,GLUT_BITMAP_HELVETICA_12);
	}

	if(insert)
		iText(500,7,"Insert mode: OFF");
	else
		iText(500,7,"Insert mode: ON");
}

void options()
{
	if(index==1)
		iShowBMP(3,530,"save.bmp");
	else if(savefile)
		iShowBMP(310,280,"savefile.bmp");
	else if(saveask)
		iShowBMP(320,280,"save10.bmp");
	else if(help)
		iShowBMP(220,593,"help3.bmp");
	else if(about)
		iShowBMP(330,180,"about.bmp");
	else if(openfile)
		iShowBMP(310,280,"open.bmp");
	else if(loaderr)
		iShowBMP(310,280,"error-load.bmp");
	else if(saveerr)
		iShowBMP(310,280,"error-save.bmp");
}
void backspace()
{
	int flagx,flagy;
		if(len)
		{
			for(int i=len;;i++)
			{
				if(i && i<107)
				{
					str[line][i-1]=str[line][i];
					if(!str[line][i-1])
						break;
				}
				if(i== 107)
				{
					i=0;
					line++;
					str[line-1][107]=str[line][i];
					if(!str[line-1][107])
						break;
				}
			}
			cx-=9;
		}
		if(!len && line)
		{

			char backstr[110];
			strcpy(backstr,str[line]);
			for(int i=line;i<40;i++)
			{
				for(int j=0;j<107;j++)
				str[i][j]='\0';
				strcpy(str[i],str[i+1]);
			}
			cy+=15;
			cx=9*(strlen(str[line-1]))+5;
			if(strlen(str[line-1])==107)
			{
				cx-=9;
				str[line-1][106]='\0';
			}
			flagx=cx;
			flagy=cy;
			for(i=0;backstr[i];i++)
			{
				input(backstr[i]);
				backstr[i]='\0';
			}
		
			cx=flagx;
			cy=flagy;
			
		}
		len=(cx-5)/9;
		line=(640-cy)/15;
		if(!strlen(str[line+1]) && strlen(str[line])==107 )
		{
			{
				for(int i=line+1;i<39;i++)
					strcpy(str[i],str[i+1]);
			}
				strcpy(str[39],"");
		}
}
void newline()
{
	int flagy,enter;
	char entertemp[110];
	str[line][len]='\0';
	cx=5;
	cy-=15;
	totalrow++;

	if(str[line][len+1])
	{
		flagy=cy;
		for(enter=len+1;str[line][enter];enter++)
		{
			entertemp[enter-len-1]=str[line][enter];
			str[line][enter]='\0';
		}
		enter--;

		for(int i=0;i<=enter;i++)
		{
			input(entertemp[i]);
			entertemp[i]='\0';
		}
		if(!str[line][len])
			str[line][len]='\0';

		cx=5;
		cy=flagy;
	}
}

void input(unsigned char key)
{
	register int swapsen,arrsen;
	int arrline,foundline,foundsen,swapline,enter,flagy;
	char enterstr[110];
	len=cx/9;
	line=(640-cy)/15;
	if(str[line][len] && key!='\b')
		{
			for(arrline=line,arrsen=len;;arrsen++)
			{
				if(arrsen>107)
				{
					arrsen=0;
					arrline++;
				}
				if(!(str[arrline][arrsen]))
				{
					foundline=arrline;
					foundsen=arrsen;
					break;
				}
			}
	
			for(swapline=foundline,swapsen=foundsen;!(len!=106 && swapline==line && swapsen==len)&& !(len==106 && (!swapsen) && swapline==line);swapsen--)
			{
				if(!swapsen)
				{
					str[swapline][swapsen]=str[swapline-1][106];
					swapline--;
					swapsen=107;
					continue;
				}
				else
					str[swapline][swapsen]=str[swapline][swapsen-1];
			}
		}

	if(key!='\b')
	{
		str[line][len]=key;
		cx+=9;
	}
	if(key=='\b')
		backspace();
	

	if(cx>972)
	{
		cx=5;
		cy-=15;
	}
	if(key=='\r')
		key='\0';

	if(key == '\0')
		newline();	

}		


	/*else
	{
		if(insert)
		{
			str[line][len] = key;
			len++;
			cx+=9;
			if(len==107)
			{
				col[line]=len;
				cx=5;
				cy-=15;
				tx=cx;
				ty=cy;
				line++;
				len=0;
				totalrow++;
			}
			else if((line>=40 && len>107) || line>40)
			{
				cx=981;
				cy=40;
			}
		}
		else
		{
			int flagx,flagy;
			char insertstr[110];
			if(!str[line][len])
				{
					str[line][len] = key;
					len++;
					cx+=9;
				}
			else if(str[line][len])
			{
				for(int m=len,n=0;m<=col[line];m++)
				{
					insertstr[n] = str[line][m];
					str[line][m]='\0';
				}
				str[line][len]=key;
				cx+=9;
				flagx=cx;
				flagy=cy;
				for(int a=0;a<=strlen(enterstr);a++)
					input(enterstr[a]);
				cx=flagx;
				cy=flagy;
			}
			if(len==107)
			{
				col[line]=len;
				cx=5;
				cy-=15;
				tx=cx;
				ty=cy;
				line++;
				len=0;
				totalrow++;
			}
			else if((line>=40 && len>107) || line>40)
			{
				cx=981;
				cy=40;
			}
		}
	}*/


void file()
{
	FILE *fp;

	if(save)
	{
		if((fp=(fopen(fname[fileline],"w"))) == NULL)
		{
			saveerr=1;
			index=5;
		}
		for(int i=0;i<=totalrow+1;i++)
		{
			fputs(str[i],fp);
			fputc('\n',fp);
		}
		fclose(fp);
		save=0;
	}

	if(open)
	{
		if((fp=(fopen(fname[fileline],"r+"))) == NULL)
		{
			loaderr=1;
			index=5;
		}
		for(int i=0;i<=40;i++)
		{
			fgets(str[i],107,fp);
			str[i][strlen(str[i])-1]='\0';
		}
		fclose(fp);
		open=0;
	}

	if(newf)
	{

		for(int i=0;i<40;i++)
			{
				for(int j=0;j<107;j++)
					str[i][j]='\0';
			}
		newf=0;
		cx=5;
		cy=640;
		strcpy(fname[fileline],"");
	}
}

void print()
{
	iSetColor(0, 0, 0);
		for(int i=0;i<40;i++)
		{
			tx=5,ty=640-(15*i);
			iText(tx,ty,str[i],GLUT_BITMAP_9_BY_15);
			if(tx>977)
			{
				tx=5;
				ty-=15;
				i++;
			}
		}
}
void fnameprint()
{
	if(savefile)
	{
		tx=360,ty=377;
		iText(tx,ty,fname[fileline],GLUT_BITMAP_9_BY_15);
		tx+=5;
	}
	else if(openfile)
	{
		tx=360,ty=377;
		iText(tx,ty,fname[fileline],GLUT_BITMAP_9_BY_15);
		tx+=5;
	}
}
void cursor()
{
	if(index==0)
	{
		if((cx>=5 && cx<=977) && (cy>=40 && cy<=640))
		{
			iSetColor(r,g,b);
			iLine(cx,cy,cx,cy+15);
			if(cx>=977)
			{
				cx=5;
				cy-=15;
			}
		}
	}
}
void cursorcolor()
{
	r=255-r;
	g=255-g;
	b=255-b;
}
void filecursor()
{
	if(fname[fileline][fileLen] != '_')
		fname[fileline][fileLen]='_';
	else
		fname[fileline][fileLen]='\0';
}

void iDraw()
{
	iClear();
	screen();
	cursor();
	status_bar();
	print();
	options();
	fnameprint();
}

void iMouseMove(int mx, int my)
{

}
void iPassiveMouseMove(int mx,int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if((mx>5 && mx<981) && (my>40 && my<655))
			{
				if((str[(((640-(((my+40)/15)*15)))/15)][((mx+5)/9)-1]||mx<9))
				{
					cx=((mx-5)/9)*9+5;
					cy=((my-40)/15)*15+40;
				}
			}
		if((mx>=10 && mx<=38) && (my>=660 && my<=678) && index==0)
		{
			index=1;
		}
		if((mx>=3 && mx<=195) && (my>=636 && my<=662) && index==1)
		{
			newf=1;
			file();
			index=0;
		}
		if((mx>=3 && mx<=195) && (my>=610 && my<=636) && index==1)
		{
			openfile=1;
			index=5;
		}
		if((mx>=3 && mx<=195) && (my>=584 && my<=610) && index==1)
		{
			savefile=1;
			index=5;
		}
		if((mx>=3 && mx<=195) && (my>=530 && my<=558) && index==1)
		{
			if(!(str[0][0] && fname[0][0]))
				exit(0);
			else
			{
				saveask=1;
				index=5;
			}
		}
		if((mx>=350 && mx<=400) && (my>=300 && my<=320) && saveask==1)
		{
			saveask=0;
			savefile=1;
		}
		if((mx>=220 && mx<=260) && (my>=660 && my<=678) && index==0)
		{
			help=1;
			index=5;
		}
		if((mx>=220 && mx<=412) && (my>=625 && my<=657) && help==1)
		{
			help=0;
			about=1;
		}
		if(!((mx>=220 && mx<=412) && (my>=625 && my<=657)) && (mx>=5 && mx<=981) && (my>=40 && my<=655) && about==1)
		{
			about=0;
			index=0;
		}
		if((mx>=220 && mx<=412) && (my>=593 && my<=625) && help==1)
		{
			help=0;
			FILE *file;
			file=fopen("help.txt","r");
			for(int i=0;i<=40;i++)
			{
				fgets(str[i],107,file);
				str[i][strlen(str[i])-1]='\0';
			}
			fclose(file);
		}
		if((mx>5 && mx<981) && (my>40 && my<655) && loaderr==1)
		{
			loaderr=0;
			index=0;
		}
		if((mx>5 && mx<981) && (my>40 && my<655) && saveerr==1)
		{
			saveerr=0;
			index=0;
		}
		
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	} 
}

void iKeyboard(unsigned char key)
{
	if(index==0)
		input(key);
	else if(savefile)
	{
		if(key=='\b')
		{
			fileLen--;
			fname[fileline][fileLen]='\0';
		}
		else if(key=='\r')
		{
			savefile=0;
			fname[fileline][fileLen]='\0';
			strcat(fname[fileline],".txt");
			save=1;
			file();
			index=0;
			cx=5;
			cy=640;
			strcpy(fname[fileline],"");
			fileline++;
			fileLen=0;
		}
		else
		{
			fname[fileline][fileLen]=key;
			fileLen++;
		}
	}
	else if(openfile)
	{
		if(key=='\b')
		{
			fileLen--;
			fname[fileline][fileLen]='\0';
		}
		else if(key=='\r')
		{
			openfile=0;
			fname[fileline][fileLen]='\0';
			strcat(fname[fileline],".txt");
			open=1;
			file();
			index=0;
			cx=5;
			cy=640;
			strcpy(fname[fileline],"");
			fileline++;
			fileLen=0;
		}
		else
		{
			fname[fileline][fileLen]=key;
			fileLen++;
		}
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{
	len=cx/9;
	line=(640-cy)/15;

	if(key == GLUT_KEY_LEFT)
	{
		if(cx>5 && str[line][len-1])
			cx-=9;
		else if(cx==5 && cy<640)
		{
			cy+=15;
			cx=(strlen(str[line-1])*9+5);
		}
	}
	if(key == GLUT_KEY_UP && cy<640)
	{
		if((len && str[line-1][len-1]) || !len)
			cy+=15;
	}	
	if(key == GLUT_KEY_RIGHT )
	{
		if(cx<981 && str[line][len])
			cx+=9;
		else if(str[line][107])
		{
			cy-=15;
			cx=5;
		}
	}

	if(key == GLUT_KEY_DOWN && (str[(640+15-cy)/15][(cx/9)-1]) && cy>15)
		cy-=15;
	if(key == GLUT_KEY_INSERT)
	{
		if(insert)
			insert=0;
		else
			insert=1;
	}
}

int main()
{
	open=0,save=0,newf=0;
	index=0;
	len = 0;
	line=0;
	cx=5,cy=640;
	tx=(cx/9)*9,ty=(cy/15)*15;
	r=g=b=0;
	curtimer = iSetTimer(500,cursorcolor);
	iSetTimer(500,filecursor);
	iInitialize(1000, 680, "Notepad++");
	return 0;
}	