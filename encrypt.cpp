#include <iostream>
#include <fstream>
using namespace std;
char upper(int c_int)
{
	if((c_int>=97)&&(c_int<=122))
	{
	c_int=c_int-32;
                  return((char)c_int);
	}
return((char)c_int);	
}
char lower(int c_int)
{
	if((c_int>=65)&&(c_int<=90))
	{
	c_int=c_int+32;
                  return((char)c_int);
	}
return((char)c_int);	
}
int main()
{
    char secret[10];//Secret key
    char keyword[2][10];//Assumption keyword is of length
    char passage[200];
    int sec,key1,key2,pass,t=0;
    ifstream secretfile("secret.txt");
    int i=0,j=0;
    char c;
    int sc=0;
    if (secretfile.is_open())
    {
        while (!secretfile.eof() ) {
        secretfile.get(c);
        secret[i]=c;
        i++;
        }
        secret[i-1]='\0';
        sec=i-1;
        //cout<<secret<<endl;
        secretfile.close();
    }
    else cout << "Unable to open file"<<endl; 
     
    i=0;
    j=0;
    ifstream keywordfile("keyword.txt");
    if (keywordfile.is_open())
    {
        while (!keywordfile.eof() ) {
            keywordfile.get(c);	
            if(c=='\n')
            {
                keyword[j][i]='\0';
                key1=i;
                //cout<<keyword[j]<<endl;
                keywordfile.get(c);
                i=0;
                j=j+1;
     
                keyword[j][i]=c;
                i++;
            }
            else
            {
 
                keyword[j][i]=c;
                i++;
 	
            }      
           
        }

        keyword[j][i-1]='\0';
        key2=i-1;
        //cout<<keyword[j]<<endl;
        keywordfile.close();
    }
    else cout << "Unable to open file"<<endl; 

    i=0;
    j=0;
    
    ifstream passagefile("passage.txt");
    if (passagefile.is_open())
    {
        while (!passagefile.eof() ) {
            passagefile.get(c);	
            passage[i]=c;
            i++;
        }
        passage[i-1]='\0';
        pass=i-1;
        //cout<<passage<<endl;
        passagefile.close();
    }
    else cout << "Unable to open file"<<endl; 

    for(int x=0;x<pass;)
    {
        int y=0;
        for(y=0;y<key1;)
        {
            if((passage[x+y]==keyword[0][y])||(passage[x+y]==upper(keyword[0][y]))||(passage[x+y]==lower(keyword[0][y])))
            {
                y++; 
            }
            else break;
        }
        t=(int)passage[x+y];
        if((y==key1)&&((t<65)||(t<96)||(t>90)||(t>122))&&(sc<sec))
        {

            if(secret[sc]=='0')
            passage[x]=lower(passage[x]);
            if(secret[sc]=='1')
            passage[x]=upper(passage[x]);
        x=x+key1;
        sc=sc+1;
        }

        for(y=0;y<key2;)
        {
             if((passage[x+y]==keyword[1][y])||(passage[x+y]==upper(keyword[1][y]))||(passage[x+y]==lower(keyword[1][y])))
            {
                y++; 
            }
            else break;

        }
        t=(int)passage[x+y];
        if((y==key2)&&((t<65)||(t<96)||(t>90)||(t>122))&&(sc<sec))
        {
            if(secret[sc]=='0')
            passage[x]=lower(passage[x]);
            if(secret[sc]=='1')
            passage[x]=upper(passage[x]);
        x=x+key2;
        sc=sc+1;
        }
    x=x+1; 
    if(sc==sec)break;
    }
	/*for(int x=0;x<pass;x++)
	{
	    cout<<passage[x];
	}*/
  ofstream encfile;
  encfile.open ("encoded.txt");
  for(int x=0;x<pass;x++)  
	encfile<<passage[x];
  encfile.close();
    
    return 1;
}
