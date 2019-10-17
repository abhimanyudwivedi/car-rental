#include<my_global.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<mysql.h>
#include<sys/types.h>

static char *host = "localhost";
static char *user = "root";
static char *pass = "";
static char *dbname = "first_project";
unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

void finish_with_error(MYSQL *conn)
{
//The function is used for updating mysql
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);    
}
int main()
{	system("clear");
	FILE *fp;
	int n,ch,b,det[10],dcost,bcost,tcost;
	double deta[10];
	char temp[40],passwordd[40],l[2];
	char details[10][40];
	char query[1024];
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int i,num_fields;
	MYSQL_FIELD *field;
	conn = mysql_init(NULL);
	if(!(mysql_real_connect(conn,host,user,pass,dbname,port,unix_socket,flag)))
	{
		fprintf(stderr,"\n error: %s\t [%d]",mysql_error(conn),mysql_errno(conn));
		exit(1);
	}
	
	fp = fopen("goodpass","r");
	fscanf(fp,"%s",temp);
	fclose(fp);
	
	printf("\t\t    connected to database \n");
	printf("\t\t    type 1 for admin access any other key for guest access\n\n ");
	scanf("%d",&n);
	if(n==1)
	{
		printf("enter the admin password \n");
		scanf("%s",passwordd);
		if(strcmp(passwordd,temp)!=0)
		{
			printf("access denied. bye!");
		}
	do{
		printf("\n\t\t    Hey! Admin what are you upto?\n\t\t    enter your choice");
		printf("\n\t\t    1. add a car\n\t\t    2. delete a car\n\t\t    3. delete a customer detail\n\t\t    4. delete a trip\n\t\t    5. show customer details\n\t\t    6. show trip details\n\t\t    7. show car details\n\t\t    8. to change password\n\t\t    999. to exit");
		scanf("%d",&ch);
		int c;
						
		if(ch==1)
		{	printf("\npress 999 to exit,any other key to continue");
			scanf("%d",&bcost);
			if(bcost==999)
			{
				continue;
			}
			printf("\nmake an entry for car no");
			scanf("%d",&det[0]);
			printf("\nmake an entry for car model");
			scanf("%s",details[1]);
			printf("\nmake an entry for capacity of the car");
			scanf("%d",&det[2]);
			printf("\nmake an entry for base cost");
			scanf("%d",&det[3]);
			printf("\nmake an entry for car type");
			scanf("%s",details[4]);
			printf("\nmake an entry for pickup point");
			scanf("%s",details[5]);
			printf("\nEnter availability ");
			scanf("%s",details[6]);
			sprintf(query,"INSERT INTO car_details(car_no,car_model,limit_car,cost_base,car_type,pickup_point,availability) VALUES('%d','%s','%d','%d','%s','%s','%s')",det[0],details[1],det[2],det[3],details[4],details[5],details[6]);
			if(mysql_query(conn,query))
			{
				finish_with_error(conn);
			}			
			printf("the table after the new entry is:\n");
			if(mysql_query(conn,"SELECT * FROM car_details"))
					{
						finish_with_error(conn);
					}
			result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ 
							if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s ", field->name);
             }
             
             printf("\n");           
          }
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result); 
		}
		if(ch==2)
		{	printf("\npress 999 to exit,any other key to continue");
			scanf("%d",&bcost);
			if(bcost==999)
			{
				continue;
			}
			next2:
			printf("\nthe table already is:\n");
			if(mysql_query(conn,"SELECT * FROM car_details"))
					{
						finish_with_error(conn);
					}
					result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ if (i == 0) 
          					{              
             					while(field = mysql_fetch_field(result)) 
             					{
                					printf("%s ", field->name);
             					}
             
            			 printf("\n");           
          			}
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result); 
			printf("delete according to?\n\n 1. car_no\n\n2. car_model\n\n 3. car_type\n\n 4. pickup point\n\n");
			scanf("%d",&c);
			switch(c)
			{		
				case 1 : printf("enter the car no");
						 scanf("%d",&det[0]);
						 sprintf(query,"DELETE FROM car_details WHERE car_no = '%d'",det[0]);
						 break;		
				case 2 : printf("enter the car model");
						 scanf("%s",details[0]);
						 sprintf(query,"DELETE FROM car_details WHERE car_model = '%s'",details[0]);
						 break;
				case 3 : printf("enter the car type");
						 scanf("%s",details[0]);
						 sprintf(query,"DELETE FROM car_details WHERE car_type = '%s'",details[0]);
						 break;
				case 4 : printf("enter the pickup point");
						 scanf("%s",details[0]);
						 sprintf(query,"DELETE FROM car_details WHERE pickup_point = '%s'",details[0]);
						 break;
				default : printf("wrong option"); goto next2;
			}
			if(mysql_query(conn,query))
			{
				finish_with_error(conn);
			}
		}			
			if(ch==3)
			{	printf("\npress 999 to exit right now");
			scanf("%d",&bcost);
			if(bcost==999)
			{
				continue;
			}
				printf("\nenter the customer no");
				scanf("%d",&det[0]);
				sprintf(query,"DELETE FROM cust_det WHERE cno = '%d'",det[0]);
			}	

			if(ch==4)
			{	printf("\npress 999 to exit, any other key to continue");
			scanf("%d",&bcost);
			if(bcost==999)
			{
				continue;
			}
				next1: 
				printf("\nthe table already consists of:\n");
				printf("\nthe table consists of:\n");
			if(mysql_query(conn,"SELECT * FROM trip_details"))
					{
						finish_with_error(conn);
					}
					result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ if (i == 0) 
          					{              
             					while(field = mysql_fetch_field(result)) 
             					{
                					printf("%s ", field->name);
             					}
             
            				 printf("\n");           
          			}
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result); 
			printf("delete according to?\n\n 1. customer's license_no\n\n2. car number\n\n ");
			scanf("%d",&c);
			printf("enter value : ");
			scanf("%s",details[0]);
			switch(c)
			{
				case 1 : sprintf(query,"DELETE FROM trip_details WHERE dlno = '%s'",details[0]);
						 break;		
				case 2 : sprintf(query,"DELETE FROM trip_details WHERE car_no = '%s'",details[0]);
						 break;
				default : printf("wrong option"); 
						goto next1;
				}
				if(mysql_query(conn,query))
				{
					finish_with_error(conn);
				}
			}
			if(ch==5)
			{	printf("\npress 999 to exit,any other key to continue");
			scanf("%d",&bcost);
			if(bcost==999)
			{
				continue;
			}
			
				printf("\ncustomer details");
				if(mysql_query(conn,"SELECT * FROM cust_det"))
					{
						finish_with_error(conn);
					}
			result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ 
							if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s ", field->name);
             }
             
             printf("\n");           
          }
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result);
			}
			if(ch==6)
			{	printf("\ntrip details");
				if(mysql_query(conn,"SELECT * FROM trip_details"))
					{
						finish_with_error(conn);
					}
			result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ 
							if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s ", field->name);
             }
             
             printf("\n");           
          }
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result);
			}
			if(ch==7)
			{	printf("\ncar details");
				if(mysql_query(conn,"SELECT * FROM car_details"))
					{
						finish_with_error(conn);
					}
			result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ 
							if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s ", field->name);
             }
             
             printf("\n");           
          }
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result);
			}
			if(ch==8)
			{
						char a[2];
		printf("\nDo you really want to change the password? press y/n");
		scanf("%s",a);
		if(strcmp(a,"y")==0)
		{
			fp = fopen("goodpass","w");
			char temp1[40];
			printf("\nenter your old password");
			scanf("%s",temp1);
			if(strcmp(temp,temp1)==0)
			{
				printf("\nenter your new password");
				scanf("%s",passwordd);
				printf("\nconfirm your password");
				scanf("%s",temp1);
				if(strcmp(passwordd,temp1)==0)
				{	fprintf(fp,"%s",temp1);
					printf("password has been changed!");
				}
				else 
					printf("\nunauthorized access terminated,bye!");
			}
			fclose(fp);
		}
			}
		
		}while(ch!=999);
	}			
		
	else
	{	int pick;
	do{
		
		printf("\n\t\t    Welcome guest! How May I Help you?");
		printf("\n\t\t    1.Search among all the cars\n\t\t    2.Bill generation\n\t\t    999.to exit");
		scanf("%d",&pick);
		switch(pick)
		{
			case 1 :printf("\ncar details");
				if(mysql_query(conn,"SELECT * FROM car_details"))
					{
						finish_with_error(conn);
					}
			result = mysql_store_result(conn);
  					if (result == NULL) 
  					{
  					   printf("empty table");
  					}

  					 num_fields = mysql_num_fields(result);

  					
  
  					while ((row = mysql_fetch_row(result))) 
  					{   
      					for(i = 0; i < num_fields; i++) 
      					{ 
							if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s ", field->name);
             }
             
             printf("\n");           
          }
      					    printf("%s\t",row[i] ? row[i] : "NULL"); 
      					} 
          					printf("\n"); 
  					}
  
  					mysql_free_result(result);
					printf("\n\t\t    selecting a car?\n\t\t    choose a suitable option,\n\t\t    1.car model\n\t\t    2. pickup point\n  ");
					scanf("%d",&ch);
					if(ch==1)
					{
						printf("\nenter the car model");
						scanf("%s",details[0]);
						sprintf(query,"SELECT * FROM car_details c WHERE c.car_model = '%s' AND c.availability = 'y'",details[0]);
						mysql_query(conn,query);
						result = mysql_store_result(conn);
						if(result == NULL)
						{
							printf("\nwe don't have the car right now");
						}
						num_fields = mysql_num_fields(result);
						while(row = mysql_fetch_row(result))
						{
							for(i = 0; i< num_fields; i++)
							{   
								printf("%s\t", row[i] ? row[i] : "NULL");
							}
						} 
						printf("\nAre you sure you wanna take this car?(y/n)");
						scanf("%s",l);
						if(strcmp(l,"y")==0)
						{	
							printf("\nyour trip is being generated\n");
							printf("\nenter your customer number");
							scanf("%d",&det[0]);
							printf("\nenter your name");
							scanf("%s",details[1]);
							printf("\nenter your destination ");
							scanf("%s",details[2]);
							printf("\nenter your email id");
							scanf("%s",details[3]);
							printf("\nenter your contact no");
							scanf("%d",&det[4]);
							printf("\nenter your dlno");
							scanf("%s",details[5]);
							sprintf(query,"SELECT * FROM car_details c WHERE c.car_model = '%s' AND c.availability = 'y'",details[0]);
							mysql_query(conn,query);
							result = mysql_store_result(conn);
							row = mysql_fetch_row(result);
							sprintf(query,"INSERT INTO cust_det(cno,name,destination,email_id,contact_no,dlno,car_no) VALUES('%d','%s','%s','%s','%d','%s','%s')",det[0],details[1],details[2],details[3],det[4],details[5],row[0]);
							mysql_query(conn,query);
							sprintf(query,"UPDATE car_details SET availability = 'n' WHERE car_model = '%s' ",row[1]);
							mysql_query(conn,query);
							printf("\nenter the date of the start of your trip");
							scanf("%s",details[0]);
							printf("\nenter the date of the end of your trip");
							scanf("%s",details[1]);
							printf("\nenter the distance");
							scanf("%lf",&deta[2]);
							sprintf(query,"INSERT INTO trip_details(start_t,end_t,car_no,distance,dlno) VALUES('%s','%s','%s','%lf','%s')",details[0],details[1],row[0],deta[2],details[5]);
							mysql_query(conn,query);
							mysql_free_result(result);
							break;
						}
					}
						if(ch==2)
						{	printf("\nenter the pickup point ");
							scanf("%s",details[0]);	
							sprintf(query,"SELECT * FROM car_details WHERE pickup_point = '%s' AND availability = 'y'",details[0]);
							mysql_query(conn,query);
						result = mysql_store_result(conn);
						if(result == NULL)
						{
							printf("we don't have the car right now");
						}
						num_fields = mysql_num_fields(result);

						while(row = mysql_fetch_row(result))
						{
							for(i = 0; i< num_fields; i++)
							{   
								printf("%s\t", row[i] ? row[i] : "NULL");
							}
						} 
						  printf("\n are you sure you wanna take this car?(y/n)");
						  scanf("%s",l);
						  if(strcmp(l,"y")==0)
						  {	printf("\nyour trip is being generated\n");
							printf("\nenter your customer number");
							scanf("%d",&det[0]);
							printf("\nenter your name");
							scanf("%s",details[1]);
							printf("\nenter your destination ");
							scanf("%s",details[2]);
							printf("\nenter your email id");
							scanf("%s",details[3]);
							printf("\nenter your contact no");
							scanf("%d",&det[4]);
							printf("\nenter your dlno");
							scanf("%s",details[5]);
							sprintf(query,"SELECT * FROM car_details WHERE pickup_point = '%s' AND availability = 'y'",details[0]);
							mysql_query(conn,query);
							result = mysql_store_result(conn);
							row = mysql_fetch_row(result);							
							sprintf(query,"INSERT INTO cust_det() VALUES('%d','%s','%s','%s','%d','%s','%s')",det[0],details[1],details[2],details[3],det[4],details[5],row[0]);
							mysql_query(conn,query);
							sprintf(query,"UPDATE car_details SET availability = 'n' WHERE car_model = '%s'", row[1]);
							mysql_query(conn,query);
							printf("\nenter the date of the start of your trip");
							scanf("%s",details[0]);
							printf("\nenter the date of the end of your trip");
							scanf("%s",details[1]);
							printf("\nenter the distance");
							scanf("%lf",&deta[2]);
							sprintf(query,"INSERT INTO trip_details(start_t,end_t,car_no,distance,dlno) VALUES('%s','%s','%s','%lf','%s')",details[0],details[1],row[0],deta[2],details[5]);
							mysql_query(conn,query);
						}
					}
					
					mysql_free_result(result); 
					break;
				case 2: printf("\n\t\t    The Bill is being generated");
						 printf("\n\t\t    enter your dlno");
						 scanf("%s",details[0]);
						 sprintf(query,"SELECT * FROM trip_details WHERE dlno = '%s'",details[0]);
						 mysql_query(conn,query);
						 result = mysql_store_result(conn);
						 row = mysql_fetch_row(result);
						 int j=0;
						 int temp=0;
						 while(row[3][i] != '\0')
						 {
							//this function is to calculate actual numeral value of bill
						 	temp=temp*10;
						 	temp=temp+((int)row[3][i]-48);
						 	i++;
						 }
						 dcost = temp*10;
						 printf("\n\t\tcost as per the distance travelled(rs.10 per km)rs.%d",dcost);
						 strcpy(details[0],row[2]);
						 mysql_free_result(result);
						 sprintf(query,"SELECT * FROM car_details WHERE car_no = '%s'",details[0]);
						 mysql_query(conn,query);
						 result = mysql_store_result(conn);
						 row = mysql_fetch_row(result);
						 j=0;temp=0;	
						 while(row[3][i] != '\0')
						 {	
						 	printf("\n%d",temp);
						 	temp=temp*10;
						 	temp=temp+((int)row[3][i]-48);
						 	i++;
						 }
						 printf("\ntemp%d",temp); 
						 bcost = temp;
						 tcost = bcost + dcost;						 
						 printf("\nthe base cost is:rs.%d\n the total cost is: rs.%d ",bcost,tcost);
						 mysql_free_result(result);
			}
		}while(pick!=999);
	}


	mysql_close(conn);
	return 0;
}
