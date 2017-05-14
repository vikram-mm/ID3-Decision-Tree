#include<bits/stdc++.h>
using namespace std;

map < int, vector<int> > input;
int n,m;//n- number of attributes, m - number of data points
int selected[100000];
vector < int > cardinality;
vector < int > binary; // 0 for no 1 for yes - contains the result of all m data points

float entropy(int x,int y)
{
	if(x==0||y==0)
		return 0;
	return -(((float)x/(x+y))*(log((float)x/x+y)/log(2))+((float)y/(x+y))*(log((float)y/x+y)/log(2)));
}

struct node{

	int ans;
	int attribute;
	node* next[10000];
};

node* create()
{
	node* n=new node;
	n->attribute=-1;
	n->ans=-1;
	return n;
}


float info_gain(int att,vector<int> data)
{	
	//cout<<"entering info_gain"<<endl;
	int count=0;//Number of positive examples
	for(int i=0;i<binary.size();i++)
		if(binary[i]==1)
			count++;
	float initial=entropy(count,binary.size()-count);//initial entropy of original set
	//cout<<"initial "<<initial<<endl;
	float final=0.0;
	

	for(int j=0;j<cardinality[att];j++)
	{
		int count1=0;// Number of positive examples with attribute value j
		int count0=0;//Number of negative examples with attribute value j
		for(int i=0;i<data.size();i++)
			if(input[att][data[i]]==j && binary[data[i]]==1)
				count1++;
			else if(input[att][data[i]]==j)
				count0++;

		//cout<<"count0 : "<<count0<<"count1 : "<<count1<<endl;
		final+=(float(count1+count0)/data.size())*entropy(count1,count0);
		//cout<<"final "<<j<<final<<endl;
	}
	return (initial+final);
}	


int select(vector<int> data)
{	

	cout<<"entering select function"<<endl;
	float maxx=INT_MIN;
	int max_att;
	for(int i=0;i<n;i++)
	{
		//cout<<"hi"<<endl;
		if(selected[i]==0)
		{
			//cout<<"hi2"<<endl;
			float ig=info_gain(i,data);
			//cout<<ig;
			if(ig>maxx)
			{	maxx=ig;
				max_att=i;
			}
	    }
	}
	if(maxx==INT_MIN)
		return -1;
	//cout<<"here"<<endl;
	//cout<<"min_att : "<<max_att<<endl;
	selected[max_att]=1;

	return max_att;
}
int popular_ans;

int popular_vote(vector<int> data)
{
	cout<<"using popular vote"<<endl;
	int yes=0,no=0;

		for(int i=0;i<data.size();++i)
			if(binary[data[i]]==0)
				no++;
			else
				yes++;

		if(yes>no)
			{cout<<"returning 1"<<endl;
						return 1;}
		else
			{cout<<"returning 0"<<endl;
						return 0;}
}

void decision(vector<int> data, node* node_passed)
{
	int flag=1;
	if(data.size()==0)
		return;
	for(int i=1;i<data.size();++i)
		if(binary[data[i]]!=binary[data[i-1]])
		{

			flag=0;
			break;
		}
	if(flag)//indicates all data elements give same output (i.e. yes or no)
	{	
		node_passed->ans=binary[data[0]];
		cout<<binary[data[0]];
		return;	//return the yes or no whichever is present
	}
	
	int selected_attribute=select(data);
	cout<<"Selected attribute is:"<<selected_attribute<<" "<<endl;
	if(selected_attribute!=-1)
	node_passed->attribute=selected_attribute;

	ofstream myfile;
		  myfile.open ("example.txt",ios::app);
		  myfile << selected_attribute<<" "<<endl;
    myfile.close();
	
	//exit(0);
	if(selected_attribute==-1)//run out of attributes
	{
		//going for popular choice
		cout<<"going for popular choice"<<endl;
		node_passed->ans=popular_vote(data);
		cout<<node_passed->ans<<endl;
		//cout<<popular_vote(data);
		//return;
	}

	else
	{

		vector <int> split_data[cardinality[selected_attribute]];//an array of vectors where each vector 
		//represents the smaller data set after splitting

		for(int i=0;i<data.size();++i)
		{
			split_data[input[selected_attribute][data[i]]].push_back(data[i]);
		}

		for(int i=0;i<cardinality[selected_attribute];++i)
			{
				node* child_node=create();
				node_passed->next[i]=child_node;
				decision(split_data[i],child_node);
			}
	}


}

void input_func()
{
	cout<<"enter number of atributes"<<endl;
	cin>>n;
	cout<<"enter number of data elements"<<endl;
	cin>>m;
	for(int i=0;i<n;++i)
	{
		cout<<"attribute "<<i<<endl;
		cout<<"number of possible values (cardinality) : ";
		int cardi;
		cin>>cardi;
		cardinality.push_back(cardi);
		cout<<endl<<"enter the m values for the attribute :"<<endl;
		vector < int > v;
		int a;
		for(int j=0;j<m;++j)
		{	
			l:
			cin>>a;
			if(a<cardinality[i])
			v.push_back(a);
			else
			{	cout<<"not a possible value, enter a value from 0 to "<<cardinality[i]<<endl;
							goto l;}


		}
		input.insert(make_pair(i,v));

	}//input map done


	//creating vector binary
	cout<<"enter yes(1) or no(0) for the m values"<<endl;
	for(int j=0;j<m;++j)
		{	
			ll:
			int a;
			cin>>a;
			if(a<2)
			binary.push_back(a);
			else
			{	cout<<"not a possible value, enter a value from 0 or 1"<<endl;
							goto ll;}


		}
		
}

int predict(node* node_passed,vector<int> test)
{
	while(node_passed->ans==-1)
	{	

		node_passed=node_passed->next[test[node_passed->attribute]];
	}
	return node_passed->ans;
}

int correct=0;
int wrong=0;

int correct0=0;
int wrong0=0;

int correct1=0;
int wrong1=0;

int num1=0;

void predict_interactive(node* root,int x)
{
	//cout<<endl<<"enter the values of the "<<n<<" different attributes for the test example"<<endl;
	vector <int> test_data;
	int a;
	for(int i=0;i<n;++i)
	{
		cin>>a;
		test_data.push_back(a);
	}

	int answer=predict(root,test_data);

	cout<<answer<<" "<<binary[x]<<endl;

	if(binary[x]==1)
		num1++;

	if(answer==binary[x])
		{
			correct++;
			if(binary[x]==0)
				correct0++;
			else
				correct1++;
		}
	else
	{
		wrong++;

		if(answer==0)
				wrong0++;
			else
				wrong1++;
	}

	//cout<<answer<<endl;

	// if(answer)
	// {
	// 	cout<<"he will play tennis :-) "<<endl;
	// }
	// else
	// {
	// 	cout<<"he will not play tennis :-( "<<endl;
	// }
}

int main()
{	
	
	input_func();
	vector <int> v;

	for(int i=0;i<m;++i)
		v.push_back(i);

	node* root=create();



	decision(v,root);

	//cin>>n;
	int num_test;
	cin>>num_test;

	for(int i=0;i<num_test;++i)
	predict_interactive(root,i);

	cout<<"correct "<<correct<<endl;
	cout<<"wrong "<<wrong<<endl;

	cout<<"accuracy : "<<float(correct)/(wrong+correct)*100<<"%"<<endl;

	cout<<"precision for survived : "<<float(correct1)/(correct1+wrong1)*100<<"%"<<endl;
	cout<<"recall for survived : "<<float(correct1)/(num1)*100<<"%"<<endl;

}