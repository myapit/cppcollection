#include<iostream>
#include<cmath>
using namespace std;

 
int main(){
int l;
int q=0;
int pr1,pr2;
int phifactors[20];
int encryptiky[20];
cout<<"ENTER FIRST PRIME NO::";
cin>>pr1;
cout<<"ENTER SECOND PRIME NO::";
cin>>pr2;
int phi=(pr1-1)*(pr2-1);
int i,j,f=0,h=0,d,g;

int arrayprime[100];
cout<<"THE PRIMES FACTORS FOR PHI ARE\n";
int temp=phi;
////start
	int z=2;

       
	while(z*z<=phi){
			
		if(phi%z==0){
		
			phifactors[h]=z;
				cout<<phifactors[h]<<" ";
			//	cout<<endl<<"THIS INDEX::"<<h<<endl;
				h++;
		//	cout<<phifactors[h]<<" ";
			
			phi=(phi/z);
	
	}
		else{
			z++;
		
			}
	
	}
	
	if(phi>1){
		
		//cout<<endl<<"CHECKED"<<h<<endl;
	phifactors[h]=phi;	
	cout<<phifactors[h]<<" ";
      h++;
	
	}
	
	//cout<<store[h]<<" ";

	
	

	///end
		
	
//cout<<"Enter upper bound of primes"<<endl;
//cin>>*number;
//for(int s=0;s<20;s++){
//	cout<<store[s]<<endl;
	
//}
cout<<"\nTHE PRIMES BTN  2 AND PHI ARE:"<<endl;

	for(int i=1;i<=temp;i++){
		int a=0;
		 d=0;
		g=0;
			for(int j=1;j<=i;j++){
				if(i%j==0){
				
				d=d+1;
				
				}
	}
	
	if(d==2 && i!=pr1 && i!=pr2){

	arrayprime[f]=i;
		 cout<<f<<"-->"<<arrayprime[f]<<endl;
        f++;
		
		 
		}
	g++;
	
	
	}
	int w;
  for ( w=0; w<f; w++)
    {
        int x;
        
        for (x=0; x<h; x++)

           
  
            if (arrayprime[w] == phifactors[x])
                break;
 
        if (x == h)
	encryptiky[q]= arrayprime[w];q++;
            
            	
            	
            
            
	}
    for(int y=2;y<q;y++){
    //	encryptiky[y];
    	for(int derk=1;derk<200;derk++){
    	//	cout<<"phi is"<<temp<<endl;
    		if(derk*encryptiky[y]%temp==1){
    		cout<<"ENCRYPTIONKEY:: "<<encryptiky[y]<<" DECRYPTIONS:: "<<derk<<" \n ";	
    		}
    	
		
		}
    }
}