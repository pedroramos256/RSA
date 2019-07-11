#include <stdio.h>
#include <math.h>

int saunderson(int a, int b){
	int x0 = 1,y0 = 0,x1 = 0,y1 = 1,q,bubble;
	while(a != 0 && b != 0){
		q = a/b;
		bubble = b;
		b = a%b;
		a = bubble;
		bubble = x1;
		x1 = x0-(q*x1);
		x0 = bubble;
		bubble = y1;
		y1 = y0-(q*y1);
		y0 = bubble;
	}
	return y0;
}

long int encrypt(int num,int n,int k){
    /*notice the same function also decrypts*/
    int DIM = (int)(log((double)k)/log(2))+1,i;
    long int v[DIM],R=1;
    v[0]=num;
    for(i = 1;i < DIM;++i)
        v[i]=(long int)(pow((double)v[i-1],2))%n;
    for(i = DIM;i >= 0;--i)
        if(k >= (int)pow(2,i)){
            R*=v[i];
            R%=n;
            k-=(int)pow(2,i);
        }
    return R;
}

int main(){
	int p=61,q=47,N,e=17,d,NUM;
	N = p*q;
	d = (p-1)*(q-1)+saunderson((p-1)*(q-1),e);
    scanf("%d",&NUM);
    NUM = encrypt(NUM,N,e);
    printf("message encrypted: %d\n",NUM);
    NUM = encrypt(NUM,N,d);
    printf("message decrypted: %d\n",NUM);
	return 0;
}