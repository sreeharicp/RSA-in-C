#include<stdio.h>
#include<string.h>
#define maxlen 10000
long prime(long);
long gcd(long p, long q);
int publickey(long p, long q, long * exp, long * mod);
int privatekey(long p, long q, long pubexp, long * exp, long * mod);
int encrypt(long * inmsg, long , long , long * outmsg, size_t len);
int decrypt(long * inmsg, long , long , long * outmsg, size_t len);
int char2long(char* in, long * out);
int long2char(long* in, char* out);

int main(void)
{
   int i,k;	
   long p,q, pube, pubmod, prive, privmod;
   char inmsg[maxlen];
   long inmsg_l[maxlen];
   char outmsg[maxlen];
   long outmsg_l[maxlen];
   char decrmsg[maxlen];
   long decrmsg_l[maxlen];
   size_t len;

   printf("ENTER A PRIME NUMBER\n ");
   scanf("%ld", &p);
   if (prime(p)) 
   {
      printf("%ld is not prime.", p);
      return 1;
   }
   printf("ENTER ANOTHER PRIME NUMBER\n ");
   scanf("%ld", &q);
  
   if (prime(q)) 
   {
      printf("%ld is not prime.", q);
      return 1;
   }
   printf( "ENTER A MESSAGE \n" );
   scanf("%s", &inmsg);
   len = strlen(inmsg);
   
   
   publickey(p,q,&pube,&pubmod);
   privatekey(p,q,pube,&prive,&privmod);
   
   char2long(inmsg, inmsg_l);
   

   encrypt(inmsg_l, pube, pubmod, outmsg_l, len);
   long2char(outmsg_l, outmsg);
   k=strlen(outmsg);
   printf("Encrypted text : ");	
   for(i=0;i<k;i++)
   {
   	printf("%ld ",outmsg[i]);
   }
   
   decrypt(outmsg_l, prive, privmod, decrmsg_l, len);
   long2char(decrmsg_l, decrmsg);
   printf("\nDecrypted text: %s \n", decrmsg);
}


long prime(long a) 
{
  int flag = 0;
  for (long j = 2; j <= a/ 2; j++)
    {
     if ((a % j) == 0)
       {
           flag = 1;
           break;
        }
     }

    if (flag == 0)
	{ return 0;}
    else
 	{return 1;}
}

int publickey(long p, long q, long *exp, long *mod)
{
   long sqt,temp;
   *mod = (p-1)*(q-1);
   sqt=(*mod)/2;
   temp=0;
   while(sqt!=temp)
   {
        temp=sqt;
	sqt=((*mod)/temp+temp)/2;
   }
   *exp = (int)sqt;
   while (1!=gcd(*exp,*mod))  
   {
      (*exp)++;
   }
   *mod = p*q;
   return 0;
}

int privatekey(long  p, long q, long pubexp, long *exp, long *mod)
{
   *mod = (p-1)*(q-1);
   *exp = 1;
   long tmp=pubexp;
   while(1!=tmp%*mod)
   {
      tmp+=pubexp;
      tmp%=*mod; 
      (*exp)++;
   }
   *mod = p*q;
   return 0;
}


int encrypt(long * in, long exp, long mod, long * out, size_t len)
{
   #pragma omp parallel for
   for (int i=0; i < len; i++)
   {
      long c = in[i];
      for (int z=1;z<exp;z++)
      {
         c *= in[i];
         c %= mod; 
      }
      out[i] = c; 
   }
   out[len]='\0'; 
   return 0;
}

int decrypt(long * in, long exp, long mod, long * out, size_t len)

{
   #pragma omp parallel for
   for (int i=0; i < len; i++)
   {
      long int c = in[i];
      for (int z=1;z<exp;z++)
      {
         c *= in[i];
         c %= mod;
      }
      out[i] = c; 
   }
   out[len]='\0'; 
   return 0;
}

long gcd(long p, long q) 

{
   if (p<q) {long tmp=p;p=q;q=tmp;}
   while (q!=0)
   {
      long tmp = q;
      q = p%q;
      p = tmp;
   }

   return p;
}

int long2char(long* in, char* out)
{
   while(*in != 0) 
   *out++ = (char)(*in++);
   *out = '\0';
   return 0;
}


int char2long(char* in, long * out)
{
   while(*in != '\0') 
   *out++ = (long )(*in++);
   *out = 0;
   return 0;
}











