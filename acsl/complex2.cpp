#include<iostream>
#include<cmath>
using namespace std;
double z,i,f2[505][2],f[505][2];
int e,c;
void find(int count){
    f[count+1][0]=(f[count][0]*f[count][0]-f[count][1]*f[count][1])/100+f[1][0];
    f[count+1][1]=f[count][0]*f[count][1]*2/100+f[1][1];

    //cout << f[count][0] << " " << f[count][1] << " " << f[count+1][0] << " " << f[count+1][1] << endl;

    f2[count+1][0]=(int)(f[count+1][0]);
    f2[count+1][1]=(int)(f[count+1][1]);

    if((f[count+1][0]-f2[count+1][0]) >= 0.5) f2[count+1][0]=(int)(f[count+1][0])+1;
        else if((f[count+1][0]-f2[count+1][0]) <= -0.5) f2[count+1][0]=(int)(f[count+1][0])-1;
    
    if((f[count+1][1]-f2[count+1][1]) >= 0.5) f2[count+1][1]=(int)(f[count+1][1])+1;
        else if((f[count+1][1]-f2[count+1][1]) <= -0.5) f2[count+1][1]=(int)(f[count+1][1])-1;

    if(f2[count+1][0] == f[1][0] && f2[count+1][1] == f[1][1]){
        c = count--;
        cout << c << endl;
        return;
    }
    
    if(sqrt(pow(double(f2[count+1][0]),2) + pow(double(f2[count+1][1]),2)) > 40000){
        e = count-1;
        cout << "ESCAPES " << e << endl;
        return;
    }
    
    //printf("%.f %.f\n",f2[count+1][0],f2[count+1][1]);
    //if (count > 5) return;
    find(count+1);
}
int main(){
    scanf("%lf%lf",&z,&i);
    f[1][0]=(int)(z*100);
    f[1][1]=(int)(i*100);
    //cout << f[1][0] <<  " " << f[1][1] << endl;
    f2[1][0]=z;
    f2[1][1]=i;
    //printf("%.2lf %.2lf\n",f2[1][0],f2[1][1]);
    e = 0;
    c = 0;
    find(1);
    return 0;
}