#include <stdio.h>
#include <math.h>

const double PI = 3.1415926536; 

  
void bitReverse(float A[], int N) 
{ 
    int i=1;
    float temp;
    for(int n=1;n<N;n++)
    {
		if(n>i)
		{
			temp=A[n-1];
			A[n-1]=A[i-1];
			A[i-1]=temp;
		}
		int m=N/2;
		while(m>=2 && i>m)
		{
			i=i-m;
			m=m/2;
		}
		i=i+m;
    } 
} 

/*void fft( int A,int B, int N) 
{ 
    bitReverse()
  
    // j is iota 
    const complex<double> J(0, 1); 
    for (int s = 1; s <= log2n; ++s) { 
        int m = 1 << s; // 2 power s 
        int m2 = m >> 1; // m2 = m/2 -1 
        cd w(1, 0); 
  
        // principle root of nth complex  
        // root of unity. 
        cd wm = exp(J * (PI / m2));  
        for (int j = 0; j < m2; ++j) { 
            for (int k = j; k < n; k += m) { 
  
                // t = twiddle factor 
                cd t = w * A[k + m2];  
                cd u = A[k]; 
  
                // similar calculating y[k] 
                A[k] = u + t;  
  
                // similar calculating y[k+n/2] 
                A[k + m2] = u - t;  
            } 
            w *= wm; 
        } 
    } 
} */
  
  
void fft(float A[],int N)
{
	int M=1,Istep,j;
	while(N>M)
	{
		Istep = M<<1;
		for(int m=0;m<M;m++)
		{
			for(int i=m;i<N;i=i+Istep)
			{
				j=i+M;
				float re = cos(PI *2*m/N)*A[j];
				float im = sin(PI *2*(m)/N)*A[j];
				A[j]=A[i]-re;
				A[N-1+j]=A[N-1+i]-im;
				A[i]=A[i]+re;
				A[i+N-1]=A[i+N-1]+im;
			}
		}
		M=Istep;
	}
}
void ffta(double real[],double imaginary[],int N)
{
    double Wmk_re,Wmk_im;
    double u_re,u_im;
    double t_re,t_im;

    for (int r = 1; r <= log2(N); r++)
    {
        int m = 1 << r;
        int md2 = m >> 1;
        double theta = 2*PI / m;
        double Wm_re = cos(theta);
        double Wm_im = sin(theta);
        for (int n = 0; n < N; n += m)
        {
            Wmk_re = 1;
            Wmk_im = 0;
            for (int k = 0; k < md2; k++)
            {
                int i_e = n + k;
                int i_o = i_e + md2;
                u_re = real[i_e];
                u_im = imaginary[i_e];
                t_re = Wmk_re*real[i_o] - Wmk_im*imaginary[i_o];
                t_im = Wmk_re*imaginary[i_o] + Wmk_im*real[i_o];
                real[i_e] = u_re + t_re;
                imaginary[i_e] = u_im + t_im;
                real[i_o] = u_re - t_re;
                imaginary[i_o] = u_im - t_im;
                t_re = Wmk_re*Wm_re - Wmk_im*Wm_im;
                t_im = Wmk_re*Wm_im + Wmk_im*Wm_re;
                Wmk_re = t_re;
                Wmk_im=t_im;
            }
        }
    }
}

int main() 
{ 
	const int N=8;
	float A[N];
	for(int i=0;i<N;i++)
	{
		A[i]=i;
	}
	bitReverse(A,N);
	double real[8];
	double imaginary[8];
	
	for(int i=0;i<N;i++)
	{
		real[i]=A[i];
		imaginary[i]=0;
	}	

	ffta(real,imaginary,8);
	for(int i=0;i<N;i++)
	{
		printf("%lf ,%lf \n",real[i],imaginary[i]);
	}
} 
