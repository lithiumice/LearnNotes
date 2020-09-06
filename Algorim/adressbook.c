
void create()
{
	FILE* fp;
	if((fp=fopen("adressbook.txt","wb"))==NULL)
	{
		printf("can not files!\n");
		return;
	}
	fclose(fp);
	printf("\n\nsuccess to create files!");
	getchar();
	return;
}
void append()
{
	struct record temp,info[M];
	FILE *fp;
	char ask;
	int i;
	if((fp=fopen("adressbook.txt","wb")==NULL))
	{
		printf("can open\n");
		return;
	 } 
	 printf("\n姓名 生日 电话 家庭地址 单位 备注\n");
	 while(1)
	 {
	 	scanf("%s%s%s%s%s%s",tempname,&temp.birth,temp.tele,temp.addr,temp.units,temp.note);
	 	info[i++]=temp;
	 	printf("continue?(y/n)");
	 	ask=getchar();
	 	getchar();
	 	if(ask=='y'||(ask=='Y'))
	 	{
	 		continue;
		 }
		 else if(ask=='n'||(ask=='N'))
		 {
		 	break;
		 }
		 fclose(fp);
		 return;
	  } 
}
void display()
{
	struct record info[M];
	FILE *fp;
	char ask;
	int i=0;
	if((fp=fopen("adressbook.txt","rb"))==NULL)
	{
		printf("can not\n");
		return;
	}
	while(1)
	{
		printf("\n\n");
		disp_str(' ',10);
		printf("显示通讯录信息（共有%d条记录）\n",i);
		disp_str('*',50);
		putchar('\n');
		disp_str(' ',17);
		printf("1.按自然顺序显示\n");
		disp_str(' ',17);
		printf("2.按排列顺序显示\n");
		disp_str(' ',17);
		printf("3.退出显示程序\n");
		disp_str('*',50);
		putchar('\n');
		ask=getchar();
		if(ask=='3')
		{
			fclose(fp);
			return;
			}
		else if(ask=='1')
			disp_arr(info,i);
		else if(ask=='2')
			sort(info,i);	
	}
}
void locate()
{
	printf("vv");
}
void modify()
{
	printf("vv");
}
void dele()
{
	printf("vv");
}
void disp_arr(struct record *info, int n)
{
	char press;
	int i;
	for(i=0;i<n;i++)
	{
		if(i%20==0)
		{
			printf("\n\n");
			disp_str(' ',25);
			printf("我的通讯录\n");
			disp_str('*',60);
			printf("\n");
			printf("序号");
			disp_table(); 
		}
		printf("%3d",i+1);
	}
}
void disp_row(struct record)
{
	printf("vv");
}
void disp_table()
{
	printf("vv");
}
void modi_seq(struct record[], int)
{
	printf("vv");
}


void disp_str(char ch, int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%c",ch);
	}
	return;
}


void sort(struct record[], int)
{
	printf("vv");
}
void sort_name(struct record[], int)
{
	printf("vv");
}
void sort_city(struct record[], int)
{
	printf("vv");
}
void dele_sequ(struct record[], int*)
{
	printf("vv");
}
void dele_name(struct record[], int*)
{
	printf("vv");
}
