#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int a, b, c, t, i, flag;
long int e[50], d[50], temp[50], j, m[50], enc[50];
char msg[100];
int prime(long int);
void encrypt_key();
long int cd(long int);
void encrypt();
void decrypt();
void primeval();
void intstage();

int main()
{
  primeval();
  intstage();
  encrypt_key();
  encrypt();
  decrypt();
  return 0;
}

void primeval()
{
  printf("\nENTER FIRST PRIME NUMBER\n");
  scanf("%d", &a);
  flag = prime(a);
  if(flag == 0)
  {
    printf("\nINVALID INPUT\n");
    exit(0);
  }
  printf("\nENTER SECOND PRIME NUMBER\n");
  scanf("%d", &b);
  flag = prime(b);
  if(flag == 0 || a == b)
  {
    printf("\nINVALID INPUT\n");
    exit(0);
  }
}

void intstage()
{
  printf("\nENTER MESSAGE TO ENCRYPT\n");
  scanf("%s",msg);
  for(i = 0; msg[i] != NULL; i++)
    m[i] = msg[i];
  c = a * b;
  t = (a-1) * (b-1);
}
int prime(long int pr)
{
  int i;
  j = sqrt(pr);
  for(i = 2; i <= j; i++)
  {
   if(pr % i == 0)
     return 0;
  }
  return 1;
 }

void encrypt_key()
{
  int k;
  k = 0;
  for(i = 2; i < t; i++)
  {
    if(t % i == 0)
     continue;
    flag = prime(i);
    if(flag == 1 && i != a && i != b)
    {
     e[k] = i;
     flag = cd(e[k]);
    if(flag > 0)
    {
     d[k] = flag;
     k++;
    }
   if(k == 99)
    break;
   }
 }
}
long int cd(long int u)
{
  long int k = 1;
  while(1)
  {
    k = k + t;
    if(k % u == 0)
     return(k / u);
  }
}

void encrypt()
{
  long int pt, ct, key = e[0], k, len;
  i = 0;
  len = strlen(msg);
  while(i != len)
  {
    pt = m[i];
    pt = pt - 96;
    k = 1;
    for(j = 0; j < key; j++)
    {
     k = k * pt;
     k = k % c;
    }
   temp[i] = k;
   ct = k + 96;
   enc[i] = ct;
   i++;
  }
  enc[i] = -1;
  printf("\n\nTHE ENCRYPTED MESSAGE IS\n");
  for(i = 0; enc[i] != -1; i++)
    printf("%d ", enc[i]);
}

void decrypt()
{
  long int pt, ct, key = d[0], k;
  i = 0;
  while(enc[i] != -1)
  {
    ct = temp[i];
    k = 1;
    for(j = 0; j < key; j++)
    {
      k = k * ct;
      k = k % c;
    }
   pt = k + 96;
   m[i] = pt;
   i++;
  }
  m[i] = -1;
  printf("\n\nTHE DECRYPTED MESSAGE IS\n");
  for(i = 0; m[i] != -1; i++)
   printf("%c", m[i]);
  printf("\n");
}
