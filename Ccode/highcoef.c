#include <math.h>
#include "filt.h"
extern void bcoef (double, double *, double (*)[2], double (*)[2], int *, double *);

void highcoef()
{
	static double pai=3.14159265358979324;
	double  cos(),atan();
	double  th,wp,ar,ar1,b1,b2,cd,e;
        double  gg1[HiConst1],aa1[HiConst1][HiConst2],bb1[HiConst1][HiConst2],c;
	int    i,nn;
        e = highpass.decay / 2.0;
        bcoef(e, gg1, aa1, bb1, &nn, &c);
        wp = 2.0 * pai * highpass.cutoff / smpf;//Op
	th=2.0*atan(c/2.0);//vp
	ar=-cos((th+wp)/2.0)/cos((th-wp)/2.0);//alpha
	ar1=(1.0-ar)*(1.0-ar);
	for(i=0;i<nn;i++){
		b1=bb1[i][0];//basic["b1"](k)
		b2=bb1[i][1];//basic["b2"](k)
		cd=1.0-b1*ar+b2*ar*ar;//C(k)
		ggh[i]=gg1[i]*ar1/cd;//A
		bbh[i][0]=(2.0*ar*(1.0+b2)-(1.0+ar*ar)*b1)/cd;//b1
		bbh[i][1]=(ar*ar-b1*ar+b2)/cd;//b2
		aah[i][0]=-aa1[i][0];//a1
		aah[i][1]=aa1[i][1];//a2
	}
        highpass.pole=nn;
}
