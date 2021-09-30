
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<windows.h>
#include<stdlib.h>

void display();

int gotoxy(int, int);

void presence_of_file();

void choose_level();

void word_by_word();
void sentence();

void add_new_words();
void add_new_words_wbw();
void add_new_words_sen();

int gotoxy(int x,int y)
{
	COORD c;
	c.X=x,
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);	
}

int i;
char choice;

int main()
{
	loop1:
	system("cls");
	
	presence_of_file();
	
	display();

	gotoxy(50,14);	printf("Start Tutor            [1]");
	gotoxy(50,15);	printf("Add new words          [2]");
	gotoxy(50,16);  printf("Exit Tutor             [3]");
	gotoxy(50,18);	printf("Enter your choice : ");
	
	choice=getche();

	switch(choice)
	{
		case '1':
			choose_level();
			break;
					
		case '2':
			add_new_words();
			main();
			break;
			
		case '3':
			exit(1);
			break;
					
		default:
			gotoxy(50,19);
			printf("Invalid choice!");
			getch();
			main();
	}
	getch();
	return 0;	
}

void presence_of_file()
{
	FILE *fp1,*fp2;
	
	int presence_of_wbw=0,presence_of_sen=0;
	
	char word_one[50][15],word_two[50][15];
	
	system("cls");
	
	fp1=fopen("wordbyword.txt","r");
	fp2=fopen("sentence.txt","r");
	
	display();
	if(fp1==NULL || fp2==NULL)
	{
		if(fp1==NULL && fp2==NULL)
		{
			gotoxy(46,19);
				printf("File not found for word by word mode.");
			
			gotoxy(46,20);
				printf("File not found for sentence mode.");
			
			gotoxy(49,26);
				printf("Press any key to add files.");
			
			presence_of_wbw++;
			presence_of_sen++;
			
			getch();
		}
		else
		{
			if(fp1==NULL)
			{
				presence_of_wbw++;
				
				gotoxy(46,19);
					printf("File not found for word by word mode.");
					
				gotoxy(49,26);
					printf("Press any key to add file.");
			}
			else
			{
				presence_of_sen++;
				
				gotoxy(46,20);
					printf("File not found for sentence mode.");
					
				gotoxy(49,26);
					printf("Press any key to add file.");
			}
			getch();
		}
		
	}
	
	fclose(fp1);
	fclose(fp2);
	
	if(presence_of_wbw!=0)
	{
		system("cls");
		
		display();
		
		fp1=fopen("wordbyword.txt","w");
			
		gotoxy(46,20);
		    printf("Enter 50 words for word by word mode :");
		
		getch();
		
		for(i=0;i<50;i++)
		{
			system("cls");
			display();
				
			gotoxy(54,20);
				printf("Word %d : ",i+1);
				scanf("%s",word_one[i]);				
				fflush(stdin);
		}
			
		for(i=0;i<50;i++)
			fprintf(fp1,"%s ",word_one[i]);
			
		fclose(fp1);
		
		system("cls");
		display();
		
		gotoxy(47,20);
			printf("Words added to file successfully.");
		
		getch();
	}
	
	if(presence_of_sen!=0)
	{
		system("cls");
		
		display();
		
		fp2=fopen("sentence.txt","w");
			
		gotoxy(49,20);
			printf("Enter 50 words for sentence mode :");
		
		getch();
		
		for(i=0;i<50;i++)
		{
			system("cls");
			display();
			
			gotoxy(54,20);
				printf("Word %d : ",i+1);
				scanf("%s",word_two[i]);				
				fflush(stdin);
		}
		
		for(i=0;i<50;i++)
			fprintf(fp1,"%s ",word_two[i]);
			fclose(fp2);
			
		system("cls");
		display();
		
		gotoxy(47,20);
			printf("Words added to file successfully.");
		
		getch();
		fclose(fp2);
			
	}
	
	system("cls");
}


void display()
{
	gotoxy(46,10);	printf("***********************************");
	gotoxy(46,11);	printf("*          Typing Tutor           *");
	gotoxy(46,12);	printf("***********************************");
}


//this function allows user to choose tutor mode i.e word by word or sentence
void choose_level()
{
	system("cls");
	
	display();
	
	gotoxy(47,14);	printf("Choose the mode of tutor : ");
	gotoxy(47,16);	printf("Word by word                   [1]");
	gotoxy(47,17);	printf("Sentence                       [2]");
	gotoxy(47,18);	printf("Goto home screen               [3]");
 
	gotoxy(47,20);	printf("Choose the mode : ");
					choice=getch();

	switch(choice)
	{
		case '1':
			word_by_word();
			break;
	
		case '2':
			sentence();
			break;
		
		case '3':
			main();
			break;
	
		default:
			gotoxy(47,22);
			printf("Invalid Choice");
			getch();
			choose_level();
	}
	choose_level();
}


//This function allows user to type one word at a time
//If the word is emtered correctly,new word is provided to enter again
//otherwise beep sound is produced and if word is incorredly typed for 3 times, the program shows number of word entered correctly
void word_by_word()
{
	FILE *fp1;
	
	int i,j,k,m=0;
	int choose=1,number;
	int count=0,count_correct=0,count_wrong=0;
	
	int num[50];
	
	char words[50][15],string[15];
	
	char wrong_word[50][15];
	char wrong_list[50][15];
	
	system("cls");

	for(i=0;i<50;i++)
		num[i]=-1;

	fp1=fopen("wordbyword.txt","r");

	for(i=0;i<50;i++)
		fscanf(fp1,"%s",words[i]);

	fclose(fp1);

	display();
	
	gotoxy(57,18);	
		printf("Be ready in");
	
	sleep(1);
	gotoxy(62,19);	
		printf("3 ");

	sleep(1);
	gotoxy(62,19);	
		printf("2 ");

	sleep(1);
	gotoxy(62,19);	
		printf("1 ");

	system("cls");

	//generating random number from 0 to 50 for choosing wordsy
	for(i=0;i<50;i++)
	{
		loop:
		number=rand()%50;
		//checking if the number is repeated in an array
		for(j=0;j<50;j++)
		{
			if(number==num[j])
				count++;
		}
		if(count==0)
			num[i]=number;
		else
		{
			count=0;
			goto loop;
		}
		count=0;
	}

	//word by word mode
	for(i=0;i<50;i++)
	{
		number=num[i];

		system("cls");

		display();
		
		gotoxy(47,15);	
			printf("Correct    : %d",count_correct);
		
		gotoxy(47,16);	
			printf("Incorrect  : %d",count_wrong);
		
		gotoxy(47,20);	
			printf("Enter the word => %s",words[number]);

		gotoxy(47,21);
			printf("Your word      => ");
			
		gotoxy(65,21);	
			scanf("%s",string);
			fflush(stdin);

		if(strcmp(string,words[number])==0)
		{
			count_correct++;
			printf("\n");
			if(count_correct==50 && count_wrong==0)
			{
				gotoxy(37,26);
				printf("Congratulations!!! You entered all words correctly.");
				
				getch();
				goto loop2;
			}
		}
		else
		{
			strcpy(wrong_list[m],string);
			strcpy(wrong_word[m],words[number]);
			count_wrong++;
			m++;
	
			gotoxy(57,24);	
				printf("Wrong :(");
			getch();
		}
		if(count_wrong==3)
		{
			system("cls");
			
			display();
			
			//determine whether the user is novice, intermediate, advanced or superior
			gotoxy(47,20);
				printf("Your proficience level : ");
			
			if(count_correct==0)
			{
				sleep(1);	
				
				printf("Novice  ");
				
				sleep(1);
				
				printf(":|");
			}
			else if(count_correct>0 && count_correct<=20)
			{
				sleep(1);	
				
				printf("Intermediate  ");
				
				sleep(1);
				
				printf(":(");
			}
			else if(count_correct>20 && count_correct<=49)
			{
				sleep(1);	
				
				printf("Advanced  ");
				
				sleep(1);
				
				printf(" :|");
			}
			else
			{
				sleep(1);
				
				printf("Superior  ");
				
				sleep(1);
				
				printf(":)");
			}
			
			sleep(1);
			gotoxy(47,25);
				printf("Enter any key to continue....");
			
			getch();
			
			system("cls");
			
			display();

			gotoxy(55,15);	
				printf("Incorrect words ");
			
			gotoxy(43,16);	
				printf("------------------------------------------\n\n");

			for(k=0;k<count_wrong;k++)
			{
				printf("\t\t\t\t\t    ");
				printf("You entered '%-10s' as '%-10s'.\n",wrong_word[k],wrong_list[k]);
			}

			printf("\n\t\t\t\t\t    ");
			printf("Total correct   words   : %d\n",count_correct);

			printf("\t\t\t\t\t    ");
			printf("Total incorrect words   : %d\n",count_wrong);
			
			gotoxy(43,25);	
				printf("------------------------------------------\n\n");
			
			getch();
			
			break;
		}
	}
	
	if(i>49 && count_wrong<3)
	{
		system("cls");
		
		display();
		
		gotoxy(47,20);
				printf("Your level : ");
			
		if(count_wrong==0)
		{
			sleep(1);	
				
			printf("Superior ");
				
			sleep(1);
				
			printf(":)");
		}
		else
		{
			sleep(1);	
				
			printf("Advanced ");
				
			sleep(1);
				
			printf(":|");
		}
			
		getch();
		
		system("cls");
		display();
		
		gotoxy(55,15);	
			printf("Incorrect words ");
		gotoxy(43,16);	
			printf("------------------------------------------\n\n");

		for(k=0;k<count_wrong;k++)
		{
			printf("\t\t\t\t\t    ");
			printf("You entered '%-10s' as '%-10s'.\n",wrong_word[k],wrong_list[k]);
		}

		printf("\n\t\t\t\t\t    ");
		printf("Total correct   words   : %d\n",count_correct);

		printf("\t\t\t\t\t    ");
		printf("Total incorrect words   : %d\n",count_wrong);
			
		gotoxy(45,25);	printf("------------------------------------------\n\n");
		
		getch();
	}

	loop2:
	fclose(fp1);
	
	main();
}


//In this function, users are provided a sentence to enter
//This function also calculates accuracy level and time taken to enter proveded sentence
void sentence()
{
	FILE *fp;

	int i,correct,wrong,time_taken;
	int start,end;
	char choice;
	char user[10][15],word[10][15];

	system("cls");

	fp=fopen("sentence.txt","r");

	if(fp==NULL)
		printf("No file found");
	else
	{
		loop:
		start=0,end=0,
		correct=0,wrong=0,time_taken=0;
		system("cls");
			
		display();

		gotoxy(40,14);
			printf("Enter the following sentence as fast as you can :\n");
		
		gotoxy(40,16);
		for(i=0;i<10;i++)
		{
			fscanf(fp,"%s",word[i]);
			printf("%s ",word[i]);
		}
		
		gotoxy(40,17);
			printf("---------------------------------------------------");
			
		start = clock();

		gotoxy(40,18);
			scanf("%s %s %s %s %s",user[0],user[1],user[2],user[3],user[4]);
			scanf("%s %s %s %s %s",user[5],user[6],user[7],user[8],user[9]);

		fflush(stdin);

		end = clock();

		time_taken=(end-start)/CLOCKS_PER_SEC;

		for(i=0;i<10;i++)
		{
			if(strcmp(word[i],user[i])==0)
				correct++;
			else
				wrong++;
		}

		gotoxy(49,20);	printf("Total correct words : %d\n",correct);

		gotoxy(49,21);	printf("Total wrong   words : %d\n",wrong);

		gotoxy(49,22);	printf("Total time taken    : %d second\n",time_taken);

		gotoxy(49,23);	printf("Accuracy            : %d percent \n\n",(100*correct)/(correct+wrong));
		
		getch();
		system("cls");
		display();
		
		//determining the proficiency of the user
		gotoxy(47,18);
			printf("Your profiency level : ");
		
		if((100*correct)/(correct+wrong)==0)
		{
			sleep(1);
				printf("Novice ");
			
			sleep(1);
				printf(":(");
		}
		
		else if((100*correct)/(correct+wrong)>0 && (100*correct)/(correct+wrong)<=50)
		{
			sleep(1);	
				
			printf("Intermediate ");
				
			sleep(1);
				
			printf(":|");
		}
		
		else if((100*correct)/(correct+wrong)>50 && (100*correct)/(correct+wrong)<99)
		{
			sleep(1);	
				
			printf("Advanced ");
				
			sleep(1);
				
			printf(":(");
		}

		else
		{
			sleep(1);
				
			printf("Superior  ");
				
			sleep(1);
		
			printf(":)");
		}
	
		getch();	

		gotoxy(47,25);	
			printf("Do you want to test again ? [y|n] : ");
			choice=getch();

		if(choice=='y' || choice=='Y')
			goto loop;
	}

	fclose(fp);
	getch();
}


//menu for adding new words
void add_new_words()
{
	system("cls");
	
	display();
	

	gotoxy(52,15);	
		printf("Word by word       [1]");

	gotoxy(52,16);
		printf("Sentence mode      [2]");
		
	gotoxy(52,17);
		printf("Goto main menu     [3]");
	
	gotoxy(52,19);
		printf("Your choice : ");
		
	choice=getch();
	
	switch(choice)
	{
		case '1':
			add_new_words_wbw();
			break;
		case '2':
			add_new_words_sen();	
			break;
		case '3':
			main();
		
		default:
			gotoxy(52,22);
			printf("Invalid choice");
			getch();
	}
	
	add_new_words();
	
	getch();
}


//this function : add new words to the wfile related to word by word mode
void add_new_words_wbw()
{
	FILE *fp,*fp_dup;
	
	int num;
	
	char add_words[50][15];
	char words_file[50][15];
	
	system("cls");

	display();
	
	gotoxy(44,14);
		printf("How many words do you want to add ? : ");
		scanf("%d",&num);
	
	system("cls");
	
	gotoxy(51,8);
		printf("Enter %d words :",num);
		
	gotoxy(47,25);
		printf("Press 'Enter' to continue");
		getch();
		
	for(i=0;i<num;i++)
	{
		system("cls");
		
		display();
		
		gotoxy(53,20);
			printf("Word %d : ",i+1);
			scanf("%s",add_words[i]);
			fflush(stdin);
	}
	
	fp=fopen("wordbyword.txt","r");
	fp_dup=fopen("try.txt","w");
	
	for(i=0;i<50;i++)
	{
		if(i<num)
		{
			fprintf(fp_dup,"%s ",add_words[i]);
		}
		else
		{
			fscanf(fp,"%s",words_file[i]);
			fprintf(fp_dup,"%s ",words_file[i]);
		}
	}
	
	fclose(fp);
	fclose(fp_dup);
	
	remove("wordbyword.txt");
	rename("try.txt","wordbyword.txt");
	
	system("cls");
	display();
	
	gotoxy(56,25);
	printf("Words added :)");
	
	getch();
}


//this function : add new words to the wfile related to word by word mode
void add_new_words_sen()
{
	FILE *fp,*fp_dup;
	
	int num;
	
	char add_words[50][15];
	char words_file[50][15];
	
	system("cls");

	display();
	
	gotoxy(47,16);
		printf("How many sentence do you want to add ?");
	
	gotoxy(47,17);	
		printf("choose less than five) :");
		scanf("%d",&num);
		
		
	if(num>5)
	{
		gotoxy(47,19);
			printf("Invalid number !");
		
		gotoxy(47,24);
		sleep(1);
			printf("Press any key to continue....");
		
		getch();
		
		add_new_words_sen();
	}
	else
	{
		system("cls");
	
		gotoxy(51,15);
			printf("Enter %d sentence : ",num);
		
		gotoxy(47,25);
			printf("Press 'Enter' to continue");
			getch();
		
		for(i=0;i<10*num;i++)
		{
			system("cls");
		
			display();
		
			gotoxy(53,20);
				printf("Word %d : ",i+1);
				scanf("%s",add_words[i]);
				fflush(stdin);
		}
	
		fp=fopen("sentence.txt","r");
		fp_dup=fopen("try.txt","w");
	
		for(i=0;i<50;i++)
		{
			if(i<num*10)
			{
				fprintf(fp_dup,"%s ",add_words[i]);
			}
			else
			{
				fscanf(fp,"%s",words_file[i]);
				fprintf(fp_dup,"%s ",words_file[i]);
			}
		}
	
		fclose(fp);
		fclose(fp_dup);
	
		remove("sentence.txt");
		rename("try.txt","sentence.txt");
	
		system("cls");
		display();
	
		gotoxy(56,25);
			printf("sentence added :)");
	
		getch();
	}
}
