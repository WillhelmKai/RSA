/*
A simple RSA encrapting program in C
In order to handle a socket programming where the Send() fucntion deal with Char* only
In this program, it support keys over 300+ or more and IO will be done in Char*


If u r a student of Ricky, u r lucky
*/
#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

// secrateKey<n, e>, publicKey<n,d>
int  n;
long int e, d;
char cipherFromEn[100];
//the encrpted message

//function to check an int is a prime or not
int prime(long int pr)
{
	int i;
	int j = sqrt(pr);
	for (i = 2; i <= j; i++)
	{
		if (pr % i == 0)
			return 0;
	}
	return 1;
}

long int cd(long int a, int t)
{
	long int k = 1;
	while (1)
	{
		k = k + t;
		if (k % a == 0)
			return(k / a);
	}
}

//function to generate encryption key
void encryption_key()
{
	srand((unsigned)time(NULL));
	int x, y, t;
	//randomly generate two prime number
	do {
		x = rand() % 50 + 2;
	} while (!prime(x));

	do {
		y = rand() % 50 + 2;
	} while (!prime(y));

	n = x * y;
	t = (x - 1) * (y - 1);

	int k;
	k = 0;
	//generate the publicKey and secretKey
	for (int i = 2; i < t; i++)
	{
		if (t % i == 0)
			continue;
		int flag = prime(i);
		if (flag == 1 && i != x && i != y)
		{
			//e[k] = i;
			if (k == 0)
			{
				e = i;
			}
			flag = cd(e, t);
			if (flag > 0)
			{
				//d[k] = flag;
				if (k == 0)
				{
					d = flag;
				}
				k++;
			}
			if (k == 99)
				break;
		}
	}
}

//function to encrypt the message, <e,n> combined the secrateKey
void encrypt(char msg[100], long int e, int n)
{
	long int  en[100];
	long int pt, ct, key = e, k, len;
	int i = 0;
	len = strlen(msg);
	while (i != len)
	{
		pt = msg[i];
		pt = pt - 96;
		k = 1;
		for (int j = 0; j < key; j++)
		{
			k = k * pt;
			k = k % n;
		}
		//temp[i] = k;
		ct = k + 96;
		en[i] = ct;
		i++;
	}
	en[i] = -1;
	printf("\n\nTHE ENCRYPTED MESSAGE IS\n");
	for (i = 0; en[i] != -1; i++)
		printf("%c", en[i]);

	//converting the long int to String contained by the char[400] cipher
	memset(cipherFromEn, '\0', sizeof(cipherFromEn));
	memcpy(cipherFromEn, en, sizeof(en));
}

// function to decrypt the message, <d,n> combined the publicKey
void decrypt(char ci[100], long int d, int n)
{
	//converting the char to long int contained by the ciphermsg[100]
	long int ciphermsg[100];
	//printf("/n/n/nsize of the cipherFromEn is %d, ci is %d, ciphermes is %d/n/n/n", sizeof(cipherFromEn), sizeof(ci), sizeof(ciphermsg));

	memset(ciphermsg, '\0', sizeof(ciphermsg));
	memcpy(ciphermsg, ci, sizeof(ciphermsg));


	long int pt, ct, key = d, k, m[100];
	int i = 0;
	while (ciphermsg[i] != -1)
	{
		ct = ciphermsg[i] - 96;
		k = 1;
		for (int j = 0; j < key; j++)
		{
			k = k * ct;
			k = k % n;
		}
		pt = k + 96;
		m[i] = pt;
		i++;
	}
	m[i] = -1;

	char deOut[100];
	memset(deOut, '\0', sizeof(deOut));
	//memcpy(deOut, m, sizeof(deOut));

	printf("\n\nTHE DECRYPTED MESSAGE IS\n");
	for (i = 0; m[i] != -1; i++) {
		printf("%c", m[i]);
		deOut[i] = (char)m[i];
	}
	printf("\n");

	//output a String 
	printf("\n %d, %d \n\The char de is:%s \n\n", sizeof(deOut), sizeof(m), deOut);

}



int main()
{
	while (1) {
		char msg[100];

		encryption_key();
		printf("Public keys are: %d and %d Secret keys are %d and %d \n", e, n, d, n);

		printf("\nENTER MESSAGE OR STRING TO ENCRYPT\n");

		gets_s(msg, 100);
		encrypt(msg, e, n);

		decrypt(cipherFromEn, d, n);
	}
	return 0;

}

