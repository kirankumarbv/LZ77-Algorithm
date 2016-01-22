//lz77 coding and decoding program
#include<stdio.h>
#include<string.h>
#define sblen 50
#define null 0
struct triplet
{
	int offset;
	int matchlength;
	char code;
	struct triplet *link;
};
typedef struct triplet* node;
node getnode()
{
	node temp;
	temp=(node)malloc(sizeof(struct triplet));
	temp->offset=0;
	temp->matchlength=0;
	temp->code='\0';
	temp->link=null;
	return temp;
}
node getlength(char *sb,char *lb,node list)
{
	int i=0,j=0,k,l,offset=0,max=0;
	char *maxpos=null,*temppos;
	node temp,cur; 
	while(i<sblen)
	{
		k=0;
		j=0;
		l=i;	
		while(sb[l++]==lb[k++] && k<sblen)
		{
			j++;
		}
		if(j>max)
		{
			maxpos=sb+i;
			max=j;
			offset=50-i;
		}
		i++;
	}
	temp=getnode();
	temp->matchlength=max;
	if(max==0)
	{
		temp->offset=0;
		temp->code=lb[k-1];
	}
	else
	{
		temp->offset=offset;
		temp->code=lb[max];
	}
	cur=list;
	if(list==null)
		list=temp;
	else
	{
		while(cur->link!=null)
			cur=cur->link;
		cur->link=temp;
	}	
	return (temp);			
}
int main()
{
	node list=null,cur;
	char *sbst,*lkst,*lkend,sb[50],*txt,ch,*op;
	FILE *fp,*out;
	int i=0,shift=0,j,k;
	fp=fopen("text.txt","r");
	while(getc(fp)!=EOF)i++;
	txt=(char*)calloc(i,sizeof(char));
	op=(char*)calloc(i,sizeof(char));
	fclose(fp);
	i=0;
	fp=fopen("text.txt","r");
	while((ch=getc(fp))!=EOF)
	{
		txt[i++]=ch;
	}		
	txt[i]='\0';
	fclose(fp);//coding starts from here
	for(i=0;i<50;i++)
	{
		sb[i]=txt[i];
	}
	sb[i]='\0';
	sbst=txt;
	lkst=txt+50;
	while(lkst[1]!='\0')
	{
		sbst+=shift;
		lkst+=shift;
		cur=getlength(sbst,lkst,list);
		if(list==null)
			list=cur;
		shift=cur->matchlength+1;
			
	}
	out=fopen("outpt.txt","w");
	cur=list;
	while(cur->link!=null)
	{
		fprintf(out,"<%d,%d,%c>\t",cur->offset,cur->matchlength,cur->code);
		cur=cur->link;	
	}
	fclose(out);
	cur=list;//decoding starts from here.
	fp=fopen("op.txt","w");	
	for(i=0;i<50;i++)
	{
		op[i]=sb[i];
	}
	sbst=op;
	lkst=op+50;
	while(cur!=null)
	{
		j=0;
		k=50-cur->offset;
		while(j<cur->matchlength)
		{
			op[i++]=sbst[k++];
			j++;		
		}
		op[i++]=cur->code;
		sbst+=cur->matchlength+1;
		lkst+=cur->matchlength+1;
		cur=cur->link;
	}
	op[i]='\0';
	fprintf(fp,"%s",op);	
	fclose(fp);	
	return 0;
}
