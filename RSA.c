#include <stdio.h>/*needed for printf and scanf */
#include <math.h>/*needed for pow and log (use -lm when compiling) */


int saunderson(int a, int b){
    /*function used in RSA encryption */
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


long int encrypt(int msg,int n,int k/*either "e" or "d"*/){
    /*notice the same function also decrypts*/
    int DIM = (int)(log((double)k)/log(2))+1,i;
    long int v[DIM],R = 1;/*remainder starts with the neutral value of multiplication */

    v[0]=msg;/*since n is bigger than msg, pow(msg,1)%n = msg */
    for(i = 1;i < DIM;++i)
        v[i] = (long int)(pow((double)v[i-1],2))%n;/*storing all remainders from pow(msg,2)%n to pow(msg,pow(2,DIM-1))%n */

    for(i = DIM-1;i >= 0;--i){
        /*calculates pow(msg,k)%n deconstructing k in powers of 2 */
        int two_to_i = (int)pow(2,i);
        if(k >= two_to_i){
            R *= v[i];
            R %= n;
            k -= two_to_i;
        }
    }
    return R;
}


int main(){
	int p = 61,q = 47;/*two primes and "e" smaller than lcm(p-1,q-1)*/
    int N = p*q, e = 17;/*public key */
	int d = (p-1)*(q-1)+saunderson((p-1)*(q-1),e);/*private key together with p and q */
    int MSG;/*message must be less than N-1 */

    printf("Introduce an integer:\n");
    scanf("%d",&MSG);

    MSG = encrypt(MSG,N,e);/*encryption */
    printf("message encrypted: %d\n",MSG);
    
    MSG = encrypt(MSG,N,d);/*decryption */
    printf("message decrypted: %d\n",MSG);
	return 0;
}
