#include<bits/stdc++.h>
using namespace std;

vector < vector <string> > result;

int n=6,m=891;

#define ifile "train_input_4.csv"
#define ifile2 "train_titanic.csv"
#define ofile "text_input_4.txt"



void read_csv()
{
	ifstream str(ifile);
	ofstream myfile;
	myfile.open (ofile,ios::out);


	// vector < vector <string> > result;
    string line;
    
	int i=0,j;
    while(str)
    {	string line;
    	getline(str,line);
    	//myfile<<"line:"<<line;
    	stringstream lineStream(line);
    	string cell;
    	vector <string> r;
	    while(getline(lineStream,cell,','))
	    {	
	    	
	        r.push_back(cell);

	        //myfile<<result[0][i]<<" ";
	        //i++;
	    }
	    //myfile<<r[0]<<endl;
	    result.push_back(r);
	    
	    i++;
	}
	str.close();
	//n=result[0].size()-1;//number of features
	//m=result.size()-1;//number of samples
	 myfile<<n<<endl;
	myfile<<m<<endl;
	myfile.close();

	// ifstream str2(ifile2);
	
 //    while(str2)
 //    {	string line;
 //    	getline(str2,line);
 //    	//myfile<<"line:"<<line;
 //    	stringstream lineStream(line);
 //    	string cell;
 //    	vector <string> r;
	//     while(getline(lineStream,cell,','))
	//     {	
	    	
	//         r.push_back(cell);

	//         //myfile<<result[0][i]<<" ";
	//         //i++;
	//     }
	//     //myfile<<r[0]<<endl;
	//     result.push_back(r);
	    
	//     i++;
	// }
	// str2.close();
	

	
}
	map < string, int > mapx[10];
void process_column(int k)
{
   ofstream myfile;
  myfile.open (ofile,ios::app);
  	

	// myfile<<n<<endl<<m<<endl;
	//cout<<mapx.size()<<endl;
	for(int i=0;i<m;++i)
	{
		
		//cout<<"hii"<<endl;
		
		map< string,int >::iterator it = mapx[k].find(result[i][k]);
	
		if(it == mapx[k].end())
		{
			//cout<<"hi"<<endl;
			int digit=mapx[k].size();
		
		   mapx[k].insert(make_pair(result[i][k],digit));
		}
	}

	if(k!=n)
	myfile<<mapx[k].size()<<endl;//cardinality

	for(int i=0;i<m;++i)
		myfile<<mapx[k][result[i][k]]<<" ";
	myfile<<endl;

	myfile.close();


}

void process_testData()
{
	 ofstream myfile;
  myfile.open (ofile,ios::app);
  cout<<result.size()<<endl;
  myfile<<result.size()-1-m<<endl;
	for(int i=m;i<result.size()-1;++i)
	{
		for(int j=0;j<result[m].size()-1;++j)
		{
			//cout<<"hi"<<endl;
			myfile<<mapx[j][result[i][j]]<<" ";
		}
		myfile<<endl;
	}
	myfile.close();

}

int main()
{	
	

	read_csv();
	//read_csv();
	for(int i=0;i<n;++i)
		process_column(i);

	process_column(n);

	process_testData();

}
