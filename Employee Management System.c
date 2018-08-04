#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
void enter();
void getpass(char *p);
void search();
struct employee{
	char name[80],gender[10];
	long int salary;
	int joinyear,age;
};
int main()
{
	int a;
	do{
        struct employee e[100];
        FILE *emp;
        char ch;
        int i,number=0;
        emp=fopen("empfile.txt","r");
        for(i=0;!feof(emp);i++){
            fgets(e[i].name,80,emp);
            if(!feof(emp)){
                e[i].name[strlen(e[i].name)-1]='\0';
                fgets(e[i].gender,10,emp);
                e[i].gender[strlen(e[i].gender)-1]='\0';
                fscanf(emp,"%d %ld %d",&e[i].age,&e[i].salary,&e[i].joinyear);
                if(!feof(emp)){
                    ch=fgetc(emp);
                }
                number++;
            }
        }
        fclose(emp);
		printf("\t\tPlease select an option.\n");
		printf("\t\t1) Enter new employee (Only for admin)\n\t\t2) Search for employee\n\t\t3) Show list of all employees\n\t\t4) List by gender\n\t\t5) Display highest paid employee\n\t\t6) About us\n\t\t7) Contact us\n");
		printf("\t\tAnything else to quit.\n");
		scanf("%d",&a);
		getchar();
		system("CLS");
		switch(a){
			case 1:
				enter();
				break;
			case 2:
				search();
				break;
			case 3:
				printf("\n");
				if(number){
					printf("\t\tFollowing is a list of all the employees in the database.\n\n");
					for(i=0;i<number;i++){
						printf("\t\t%d)\n\t\t Name: %s\n\t\t Gender: %s\n\t\t Age: %d\n\t\t Salary: %ld\n\t\t Join year: %d\n\n",i+1,e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
					}
				}
				else
					printf("\t\tDatabase empty.\n\n");
				break;
			case 4:
				printf("Please select an option\n1) Male\n2) Female\n\nAnything else to quit\n");
				char opt,f=0;
				scanf("%d",&opt);
				getchar();
				if(opt==1){
					for(i=0;i<number;i++){
						if(!strcmp(e[i].gender,"Male")){
                            f=1;
							printf("\t\t%d)\n\t\t Name: %s\n\t\t Gender: %s\n\t\t Age: %d\n\t\t Salary: %ld\n\t\t Join year: %d\n\n",i+1,e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
						}
					}
				}
				else if(opt==2){
						for(i=0;i<number;i++){
							if(!strcmp(e[i].gender,"Female")){
                                f=1;
								printf("\t\t%d)\n\t\t Name: %s\n\t\t Gender: %s\n\t\t Age: %d\n\t\t Salary: %ld\n\t\t Join year: %d\n\n",i+1,e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
							}
						}
				}
				if(opt>=1 && opt<=2 && !f)
                    printf("\t\tNo entry found in database.\n\n");
				a=3; // unknown error as a always gets assigned 0
				break;
			case 5:
				printf("\n");
				char highestpaid[100][80];
				long int max=0;
				int index[100]={0},num=0,j=0; // num = number of highest paid employees
				if(number){
					for(i=0;i<number;i++){
						if(max<e[i].salary){
							max=e[i].salary;
							strcpy(highestpaid[0],e[i].name);
							j=0;
							index[j]=i+1;
							j++;
						}
						else if(max==e[i].salary){
                            strcpy(highestpaid[j],e[i].name);
                            index[j]=i+1;
                            j++;
						}
					}
					if(j){
						printf("\t\tFollowing is the list of the highest paid employees:\n\n");
					}
					for(i=0;i<j;i++){
                        printf("\t\t%d) %s\n\t\t   Salary:- %ld\n",index[i],e[index[i]-1].name,e[index[i]-1].salary);
					}
				}
				else{
					printf("\t\tNo entry found in database.\n");
				}
				printf("\n");
				break;
			case 6:
				printf("This section contains all the information that people don\'t actually read.\n\n");
				break;
			case 7:
				printf("------------------\n\n");
				break;
		}
	}while(a>=1 && a<=7);
	return 0;
}
void enter()
{
	int number=0,i;
	FILE *pass;
	char prompt[20],password[20];
	printf("Please enter password: ");
	getpass(prompt);
	pass=fopen("emppass.txt","r");
	fgets(password,20,pass);
	fclose(pass);
	if(!strcmp(prompt,password)){
		printf("Access granted.\n");
		struct employee e[100];
		FILE *emp;
		char ch;
		emp=fopen("empfile.txt","r");
		for(i=0;!feof(emp);i++){
			fgets(e[i].name,80,emp);
			if(!feof(emp)){
				e[i].name[strlen(e[i].name)-1]='\0';
				fgets(e[i].gender,10,emp);
				e[i].gender[strlen(e[i].gender)-1]='\0';
				fscanf(emp,"%d %ld %d",&e[i].age,&e[i].salary,&e[i].joinyear);
				if(!feof(emp)){
					ch=fgetc(emp);
				}
				number++;
			}
		}
		fclose(emp);
		int num;
		printf("Please select the number of employees you want to enter.\n");
		scanf("%d",&num);
		getchar();
		emp=fopen("empfile.txt","a");
		for(i=number;i<num+number;i++){
			int j=0;
			if(i==number && i>0)
				fprintf(emp,"\n");
			printf("Employee number %d:\n",i+1);
			printf("Please enter name: ");
			gets(e[i].name);
			fputs(e[i].name,emp);
			fprintf(emp,"\n");
			printf("Please enter gender: ");
			gets(e[i].gender);
			fputs(e[i].gender,emp);
			fprintf(emp,"\n");
			printf("Please enter age, salary and join year: ");
			scanf("%d %ld %d",&e[i].age,&e[i].salary,&e[i].joinyear);
			getchar();
			fprintf(emp,"%d %ld %d",e[i].age,e[i].salary,e[i].joinyear);
			if(i<(number+num-1))
				fprintf(emp,"\n");
		}
		fclose(emp);
		number=i;
	}
	else
		printf("Wrong password.Access denied.\n");
	return;
}
void getpass(char *p)
{
	*p=getch();
	if(*p!='\r'){
		printf("*");
		p++;
		return getpass(p);
	}
	*p='\0';
	return;
}
void search()
{
	int number=0,i,count=0,a[100];
	char search[80],ch;
	struct employee e[100];
		FILE *emp;
		emp=fopen("empfile.txt","r");
		for(i=0;!feof(emp);i++){
			fgets(e[i].name,80,emp);
			if(!feof(emp)){
				e[i].name[strlen(e[i].name)-1]='\0';
				fgets(e[i].gender,10,emp);
				e[i].gender[strlen(e[i].gender)-1]='\0';
				fscanf(emp,"%d %ld %d",&e[i].age,&e[i].salary,&e[i].joinyear);
				if(!feof(emp)){
					ch=fgetc(emp);
				}
				number++;
			}
		}
		fclose(emp);
		printf("Please enter the name of the employee: ");
		gets(search);
		for(i=0;i<number;i++){
			if(!strcmp(search,e[i].name)){
				a[count]=i; // Saving the index where name and search match
				count++;
			}
		}
		if(!count){
			printf("No employee named %s is found in the database.\n",search);
		}
		else{
            int exist=0;
			printf("\t\tThe names of the following employees were found in the database.\n");
			for(i=0;i<count;i++){
				int j=a[i]; // The index of struct e where name and search match
				printf("\t\t%d)\n\t\t Name: %s\n\t\t Gender: %s\n\t\t Age: %d\n\t\t Salary: %ld\n\t\t Join year: %d\n\n",j+1,e[j].name,e[j].gender,e[j].age,e[j].salary,e[j].joinyear);
                exist++;
			}
			printf("\t\tEnter the assigned number of the employee you want to select.\n\t\tEnter anything else to return to the menu.\n");
			int k,choice,rightchoice=0;
			scanf("%d",&k);
			for(i=0;i<exist;i++){
                if((k-1)==a[i]){
                    rightchoice=1;
                }
			}
			if(k>=1 && k<=number && rightchoice){
				printf("\t\tPlease select an option.\n");
				printf("\t\t1) Edit name\n\t\t2) Edit gender\n\t\t3) Edit age\n\t\t4) Edit salary\n\t\t5) Edit join year\n\t\t6) Delete entry\n\t\tAnything else to quit\n");
				scanf("%d",&choice);
				getchar();
				if(choice==1){
					printf("Please enter password: ");
					FILE *pass;
					char prompt[20],password[20];
					getpass(prompt);
					pass=fopen("emppass.txt","r");
					fgets(password,20,pass);
					fclose(pass);
					if(!strcmp(password,prompt)){
						printf("\t\tAccess granted.\n");
						printf("Please enter name: ");
						gets(e[k-1].name);
						FILE *emp;
						emp=fopen("empfile.txt","w");
						for(i=0;i<number;i++){
							fprintf(emp,"%s\n%s\n%d %ld %d",e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
							if(i<number-1)
								fprintf(emp,"\n");
						}
						fclose(emp);
					}
					else{
						printf("\n");
						printf("\t\tIncorrect password. Operation not performed\n");
					}
				}
				else if(choice==2){
						printf("Please enter password: ");
						FILE *pass;
						char prompt[20],password[20];
						getpass(prompt);
						pass=fopen("emppass.txt","r");
						fgets(password,20,pass);
						fclose(pass);
						if(!strcmp(password,prompt)){
							printf("\t\tAccess granted.\n");
							printf("Please enter gender: ");
							gets(e[k-1].gender);
							FILE *emp;
							emp=fopen("empfile.txt","w");
							for(i=0;i<number;i++){
								fprintf(emp,"%s\n%s\n%d %ld %d",e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
								if(i<number-1)
									fprintf(emp,"\n");
							}
							fclose(emp);
						}
						else{
							printf("\n");
							printf("\t\tIncorrect password. Operation not performed\n");
						}
				}
					else if(choice==3){
							printf("Please enter password: ");
							FILE *pass;
							char prompt[20],password[20];
							getpass(prompt);
							pass=fopen("emppass.txt","r");
							fgets(password,20,pass);
							fclose(pass);
							if(!strcmp(password,prompt)){
								printf("\t\tAccess granted.\n");
								printf("Please enter age: ");
								scanf("%d",&e[k-1].age);
								FILE *emp;
								emp=fopen("empfile.txt","w");
								for(i=0;i<number;i++){
									fprintf(emp,"%s\n%s\n%d %ld %d",e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
									if(i<number-1)
										fprintf(emp,"\n");
								}
								fclose(emp);
							}
							else{
								printf("\n");
								printf("\t\tIncorrect password. Operation not performed\n");
							}
					}
						else if(choice==4){
								printf("Please enter password: ");
								FILE *pass;
								char prompt[20],password[20];
								getpass(prompt);
								pass=fopen("emppass.txt","r");
								fgets(password,20,pass);
								fclose(pass);
								if(!strcmp(password,prompt)){
									printf("\t\tAccess granted.\n");
									printf("Please enter salary: ");
									scanf("%ld",&e[k-1].salary);
									FILE *emp;
									emp=fopen("empfile.txt","w");
									for(i=0;i<number;i++){
										fprintf(emp,"%s\n%s\n%d %ld %d",e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
										if(i<number-1)
											fprintf(emp,"\n");
									}
									fclose(emp);
								}
								else{
									printf("\n");
									printf("\t\tIncorrect password. Operation not performed\n");
								}
						}
							else if(choice==5){
									printf("Please enter password: ");
									FILE *pass;
									char prompt[20],password[20];
									getpass(prompt);
									pass=fopen("emppass.txt","r");
									fgets(password,20,pass);
									fclose(pass);
									if(!strcmp(password,prompt)){
										printf("\t\tAccess granted.\n");
										printf("Please enter age: ");
										scanf("%d",&e[k-1].joinyear);
										FILE *emp;
										emp=fopen("empfile.txt","w");
										for(i=0;i<number;i++){
											fprintf(emp,"%s\n%s\n%d %ld %d",e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
											if(i<number-1)
												fprintf(emp,"\n");
										}
										fclose(emp);
									}
									else{
										printf("\n");
										printf("\t\tIncorrect password. Operation not performed\n");
									}
							}
								else if(choice==6){
										printf("Please enter password: ");
										FILE *pass;
										char prompt[20],password[20];
										getpass(prompt);
										pass=fopen("emppass.txt","r");
										fgets(password,20,pass);
										fclose(pass);
										if(!strcmp(password,prompt)){
											int i;
											for(i=k-1;i<number-1;i++){
												strcpy(e[i].name,e[i+1].name);
												strcpy(e[i].gender,e[i+1].gender);
												e[i].age=e[i+1].age;
												e[i].salary=e[i+1].salary;
												e[i].joinyear=e[i+1].joinyear;
											}
											number--;
											FILE *emp;
											emp=fopen("empfile.txt","w");
											for(i=0;i<number;i++){
												fprintf(emp,"%s\n%s\n%d %ld %d",e[i].name,e[i].gender,e[i].age,e[i].salary,e[i].joinyear);
												if(i<number-1)
													fprintf(emp,"\n");
											}
											fclose(emp);
											printf("\n");
											printf("\t\tEntry deleted!\n");
										}
										else{
											printf("\n");
											printf("\t\tIncorrect password. Operation not performed.\n");
										}
								}
			}
		}
	return;
}
