#include"iostream"
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<fstream>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<queue>
#include<vector>
#include<cstdio>
#define MAX 75000
#define VERTEX_MAX 56984
#define MAX_SQ 10000
#define INFINITE 1000
#define UNDEFINED -1
#define pp pair<int,double>
clock_t begin,end;
using namespace std;

struct pri
{
  double operator() (const pair<int, double>&p1, const pair <int,double>&p2)
    {
        return p1.second>p2.second;
    }
};


struct Landmark
{
	long double x;
  long double y;
  double dist[20];
  double dist1[20];
	int preced[20];
	double sum[20];
  int val;
};


struct Point
{
    int id;
  char *City;
  char *Street_name;
   int To_vertex;
   int From_vertex;
  char *From_addr;
  char *To_addr;
   int Speed_KPH;
  char* Class;
};

struct vertex
{
 int ID;
 long double x;
 long double y;
};



struct coordinates
{
  int x;
  int y;
  int num;
  int degree;
};


struct min_array
{
  int edge_length;
  int initial;
  int end;
};

struct link_hash
 {
    int ID;
    long double distance;
    int speed;
    int degree;
    link_hash* next;
 }; 

struct hash
 {
    int ID;
   link_hash* next;
 }; 


struct node
{
  int x;
  int y;
  int degree;
  int num_nodes;
  int traverse;
  int label;
  struct node *parent;
  struct node *child;
  struct node *siblings;
};

struct node_binary
{
  int data[MAX];
  int size;
  int range;
  struct node_binary *left;
  struct node_binary*right;
};

struct solution_structure
{
  double distance;
  int result[MAX];
  int size_result;
};


typedef struct solution_structure solution;
typedef struct node_binary binary;
typedef struct min_array  min;
typedef struct coordinates coord;
typedef struct Landmark lm;
typedef struct node Node;
long double eucledian(long double , long double, long double, long double);
double Krushkal(struct hash [MAX],struct hash [MAX],vertex V[MAX]);
int allselected(int [MAX]);
int find_equivalent_array(binary *root,int array[],int [MAX][4]);                        // A NODE IS A CENTRAL NODE IF ITS ECCENTRICITY IN A GRAPH IS LOWEST
int find(int [MAX],int);
int uni(int [MAX],int,int,int,int);
int graph_to_tree(double [MAX][20], coord [MAX]);
int create_matrix(double [MAX+2][20],coord cd[MAX+2],int [MAX+2][4]);
binary* create_tree(double[MAX+2][20],coord[MAX+2],int,int[MAX][20],int[MAX][2],lm[],double [MAX][20],int [MAX][4]);
Node* create(int, int);
int landmark_selection(lm[],vertex [MAX+2],struct hash [MAX+2]);
double dijkstra (struct hash dist_mat[MAX+2],struct vertex [MAX+2],double dis[MAX+2],int preced[MAX+2],int,int);
int allselected(int selected[MAX],int);
double compute_lowerbound(lm[],struct hash [MAX+2],long int,int);
solution  modified_dijkstra(lm [MAX],struct hash [MAX],struct vertex [MAX],double dist[MAX],int preced[MAX],long int,long int,int[MAX],int);
binary* create_binary_node();
binary* split_tree(Node**,binary*, int[MAX][2],int,coord[MAX]);
int Max_hash(int [MAX][2]);
int check_cycle(double [MAX][20],int,int);
binary* tree_const(double[MAX+2][20],coord[MAX+2],lm[],double [MAX+2][20],int [MAX][4]);
int create_hashtable(double min_span[MAX+2][20],int [MAX][2]);
solution max_dist(binary*root,lm[MAX/5],double[MAX+2][20],coord[MAX+2],int [MAX][4],int);
int hash_max(int[MAX][2],int);
int subnode_assign(Node*,coord [MAX]);
int check_wellsep(binary* root_left,binary*root_right,int [MAX][4],lm[MAX/5],double[MAX+2][20],coord[MAX+2]);
int check_selected(int,int,coord[MAX]);
void insert_in_hashtable(int,int,double,double);
binary* create_binary_node(int [MAX],int);
double compute_wellsepdist_secopt(int,int[MAX],int [MAX][4],lm landm[MAX/5],double[MAX+2][20],coord [MAX+2],binary*,binary*);
void create_dummy_matrix(int ,int ,double dummy[MAX+2][20],double [MAX+2][20],int[MAX],int [MAX]);
int tree_traversal(Node*, int[MAX][2],int [MAX]);
int counter=0;
int mainhash_table[MAX][4],hash_index=0;
void inorder(Node*,int [MAX][4]);
int level1=0,level2=0;
using namespace std;




// MAIN FUNCTION

int main()
{
 coord cd[MAX+2];
 lm landm[16];
 double time_spent;
 solution result;
 struct vertex V[VERTEX_MAX+2];
 struct Point P[MAX];
 struct hash hash_table[VERTEX_MAX+2];
 char *pch,*pchar, str[100],strng[100];
 ifstream inFile1,inFile2;
  ofstream inFile3;
 inFile2.open("vertices.txt",ios::in);
 inFile3.open("example3.txt",ios::out);
 if(!inFile2)
 { 
  cerr<<"Cannot open vertices file";
  exit(1);
 }
 V[0].ID=0;
 V[0].x=3;
 V[0].y=6; 
 int count1=0;
 while(V[count1-1].ID!=VERTEX_MAX)
  {
    int i=0;
    pchar=strtok(strng,"|");
    inFile2>>strng;
    cout<<strng;
    i++;
    while(pchar!=NULL)
      {
        if(i==1)
          {
            V[count1].ID=atoi(pchar);
//            cout<<" ID=  V["<<count1<<"]= "<<V[count1].ID;
            i++;
          }
         else if(i==2)
         {
            V[count1].x=atof(pchar);
  //          cout<<" its x coordinate="<<V[count1].x;
            i++;
         }
        else if(i==3)
         {
            V[count1].y=atof(pchar);
    //        cout<<" its y coordinate="<<V[count1].y;
            i++;
         }  
       pchar=strtok(NULL,"|");
      }
       cout<<"\n";
       count1++;
    }
  inFile2.close();
  
/*for(int i=0;i<VERTEX_MAX;i++)
{
   cout<<" "<<V[i].x<<","<<V[i].y<<" "<<"\n";
  }
  */ 
 
 inFile1.open("edges.txt",ios::in);
 if(!inFile1)
 { 
  cerr<<"Cannot open vertices file";
  exit(1);
 }

  cout<<"\n The vertices saved!!";
 sleep(3);
 
for(int i=0;i<16;i++)
    {
      landm[i].val=rand()%VERTEX_MAX;
      cout<<" \n landm j val"<<landm[i].val;
      landm[i].x=V[landm[i].val].x;
      landm[i].y=V[landm[i].val].y;
      cout<<" ("<<landm[i].x<<","<<landm[i].y<<")";
    }
 sleep(3);
int count=1;
P[0].id=242;
P[0].From_vertex=13127;
P[0].To_vertex=13128;
P[0].Speed_KPH=50;  
// loop for tokenizing the file input and storing them in the structure

 while((P[count-1].id!=356229))                        
  {
    
    int i=0;
     {
       pch=strtok(str,"|");
     }
    inFile1>>str;
    cout<<str<<"\n"; 
    i++;
    cout<<count<<"\n";
    while(pch!=NULL)
    {
      if(i==1)
        {
          P[count].id=atoi(pch);
  //        cout<<"ID="<<P[count].id<<"\n";
          i++; 
        }
      else if(i==2)
       {
        P[count].City=pch;
    //    cout<<"City="<<P[count].City<<"\n";
        i++;
       }
      else if(i==3)
       {
        P[count].Street_name=pch;
      //  cout<<"Street="<<P[count].Street_name<<"\n";
        i++;
       }
     else  if(i==4)
      {
        P[count].From_vertex=atoi(pch);
        cout<<"From Vertex="<<P[count].From_vertex<<"\n";
        int indices=P[count].From_vertex; 
        hash_table[indices].ID=P[count].From_vertex; 
        cout<<"hash table at "<<indices<<"th entry is::"<<hash_table[indices].ID;
        hash_table[indices].next=NULL;
        i++;
      }
     else if(i==5)
      {
       P[count].To_vertex=atoi(pch);
       cout<<"To vertex"<<P[count].To_vertex<<"\n";
       int indices=P[count].To_vertex; 
       hash_table[indices].ID=P[count].To_vertex; 
       cout<<"hash table at "<<indices<<"th entry is::"<<hash_table[indices].ID;
       hash_table[indices].next=NULL; 
       i++;
      }
     else if(i==6)
      {
       P[count].To_addr=pch;
      // cout<<"Distance"<<P[count].To_addr<<"\n";
       i++;
      }
      else if(i==7)
      {
       P[count].From_addr=pch;
      // cout<<"To addr"<<P[count].From_addr<<"\n";
       i++;
      }
     else if(i==8)
      {
       P[count].Speed_KPH=atoi(pch);
      // cout<<"Speed "<<P[count].Speed_KPH<<"\n";
       i++;
      }
    else if(i==9)
      {
       P[count].Class=pch;
     //  cout<<"Class"<<P[count].Class<<"\n";
       i++;
      }
    pch=strtok(NULL,"|");
    }
   cout<<"\n";
   count++;
  }



//  sleep(3);
  long int size=count-1;
  cout<<"size="<<size;
  inFile1.close();
  int x1,x2;
  long int index=0;  
 // cout<<" "<<P[index].id<<","<<","<<P[index].To_vertex<<","<<P[index].dist<<"\n";
  index=0;

/*for(int i=0;i<VERTEX_MAX;i++)
{
   cout<<" "<<V[i].x<<"\n";
  }
*/

// sleep(3); 
 while(index<size)
    {     
    count=1;
    if(hash_table[P[index].From_vertex].next==NULL)                         // For insertion of the first linked list
      {
        x1=0;x2=0;
        struct link_hash *node;
   //     cout<<"\n Entering 1  "<<P[index].To_vertex<<"\n";
        long double dis=0,a1,a2,b1,b2;
        node=(struct link_hash*)malloc(sizeof(struct link_hash));
        node->ID=P[index].To_vertex;
        node->speed=P[index].Speed_KPH;
        node->next=NULL;    
        for(int i=0;i<VERTEX_MAX;i++)
          { 
            if(V[i].ID==P[index].From_vertex)
              {
                a1=V[i].x;
            //    cout<<"a1 ="<<a1;
                b1=V[i].y;
              //  cout<<"b1 ="<<b1;
                x1=1;
               if((x1==1)&&(x2==1))
                {
                  break;
                }
              }
            if(V[i].ID==P[index].To_vertex)
            {
               
                a2=V[i].x;
                //cout<<"a2 ="<<a2;
                b2=V[i].y;
               // cout<<"b2 ="<<b2;
                x2=1;
               if((x1==1)&&(x2==1))
               {
                 break;
               }
            }
          }
       dis=eucledian(a1,a2,b1,b2);
        if(P[index].From_vertex==56850)
        {
  //        sleep(2);
          cout<<"\n"<<P[index].To_vertex<<"\n dis="<<dis;
    //      sleep(2);
        }
        
   //    cout<<"\n dist="<<dis;
       node->distance=dis;
       hash_table[P[index].From_vertex].next=node;       
       if(hash_table[P[index].To_vertex].next==NULL)
          {
            struct link_hash *node1;
            node1=(struct link_hash*)malloc(sizeof(struct link_hash));
            node1->ID=P[index].From_vertex;
            node1->distance=dis;
            node1->speed=P[index].Speed_KPH;
            node1->next=NULL;
            hash_table[P[index].To_vertex].next=node1;
          }
        else
          {
            struct link_hash *node1,*node2;
            node1=(struct link_hash*)malloc(sizeof(struct link_hash));
            node2=(struct link_hash*)malloc(sizeof(struct link_hash));
            node2=hash_table[P[index].To_vertex].next;
            while(node2->next!=NULL)
             {
                node2=node2->next;
             }
            node1->ID=P[index].From_vertex;
            node1->distance=dis;
            node1->speed=P[index].Speed_KPH;
            node1->next=NULL;
            node2->next=node1;
          }
      }
    else
      {
       x1=0;x2=0;
      // cout<<"\n Entering 2"<<P[index].To_vertex;
       struct link_hash*node;                                                
       double dis,a1,a2,b1,b2;
       node=(struct link_hash*)malloc(sizeof(struct link_hash)); 
       node=hash_table[P[index].From_vertex].next;
      while(node->next!=NULL)
        {
          node=node->next;
        }
        struct link_hash *newnode;
        newnode=(struct link_hash*)malloc(sizeof(struct link_hash));
        newnode->ID=P[index].To_vertex;
        newnode->speed=(P[index].Speed_KPH);
        newnode->next=NULL; 
        for(int i=0;i<VERTEX_MAX;i++)
          {
            if(V[i].ID==P[index].To_vertex)
             {
                a1=V[i].x;
             //   cout<<"\n a1 ="<<a1;
                b1=V[i].y;
             //   cout<<"\n b1 ="<<b1;
                x1=1;
                if((x1==1)&&(x2==1))
                   {
                     break;
                   }
                
              }
            if(V[i].ID==P[index].From_vertex)
            {
                a2=V[i].x;
               // cout<<"\n a2="<<a2;
                b2=V[i].y;
               // cout<<"\n b2="<<b2;
                x2=1;
               if((x1==1)&&(x2==1))
               {
                 break;
               }
                
            }
       
          }
        dis=eucledian(a1,a2,b1,b2);
        if(P[index].From_vertex==56850)
        {
      //  sleep(2);
        cout<<"\n"<<P[index].To_vertex<<"\n dis="<<dis<<"for "<<a1<<" and "<<a2<<","<<b1<<"and"<<b2<<"\n";
      //  sleep(2);
        }
        newnode->distance=dis; 
        node->next=newnode;         
       if(hash_table[P[index].To_vertex].next==NULL)
          {
            struct link_hash *node1;
            node1=(struct link_hash*)malloc(sizeof(struct link_hash));
            node1->ID=P[index].From_vertex;
            node1->distance=dis;
            node1->speed=(P[index].Speed_KPH);
            node1->next=NULL;
            hash_table[P[index].To_vertex].next=node1;
          }
        else
          {
            struct link_hash *node1,*node2;
            node1=(struct link_hash*)malloc(sizeof(struct link_hash));
            node2=(struct link_hash*)malloc(sizeof(struct link_hash));
            node2=hash_table[P[index].To_vertex].next;
            while(node2->next!=NULL)
             {
                node2=node2->next;
             }
            node1->ID=P[index].From_vertex;
            node1->distance=dis;
            node1->speed=(P[index].Speed_KPH);
            node1->next=NULL;
            node2->next=node1;
          }
                        
       
      }
   //  cout<<"index incremented";
     index++;
     }
// sleep(2);
cout<<"\n Done with the distance computation";
cout<<" \n So the hash table is::";

 for(int i=0;i<=VERTEX_MAX;i++)
  {
    cout<<hash_table[i].ID<<" ";
    inFile3<<hash_table[i].ID<<" " ;
    if(hash_table[i].next!=NULL)
      {
       struct link_hash*node;                                                
       node=(struct link_hash*)malloc(sizeof(struct link_hash));
       node=hash_table[i].next;
        while(node!=NULL)
          {
            cout<<"  ("<<node->ID;
            inFile3<<"("<<node->ID;
          cout<<" , "<<node->distance<<" )   ";
          inFile3<<","<<node->distance<<" ) ";
            node=node->next;
          }
        cout<<" NULL \n ";
        inFile3<<" NULL \n";
      }
    else
      {
        cout<<" NULL  \n ";
        inFile3<<" NULL \n";
      }
    }
// sleep(5);
 inFile3.close();
 cout<<"**************************************************THE END*******************************************";
// sleep(3);
 landmark_selection(landm,V,hash_table); 
 double dist[VERTEX_MAX],result1;
 int preced[VERTEX_MAX];
 for(int i=0;i<VERTEX_MAX;i++)
    {    
      dist[i]=1000;
      preced[i]=UNDEFINED;
    }
 long int source,dest;
 cout<<"\n Enter source:";
 cin>>source;
 cout<<"\n Enter destination:";
 cin>>dest;
 begin=clock(); 
 result1=dijkstra(hash_table,V,dist,preced,source,dest);           // Needs correction
 cout<<"result1="<<result1;
 end=clock();
 time_spent=double(end-begin)/CLOCKS_PER_SEC;
 cout<<"\n So the time spent is::"<<time_spent;
 return 0;
}



// LANDMARK ALGORITHMS BEGIN HERE


int landmark_selection(lm landm[100],vertex V[VERTEX_MAX+2],struct hash hash_table[VERTEX_MAX+2])                                   // Function for selection of landmarks
{
 int m=0,i,size=0,j=0;
 int count=MAX/10;
 ofstream infile4;
 long double result;
 infile4.open("example4.txt",ios::out);
 if(!infile4)
  {
    cerr<<"cannot open file";
    sleep(4);
  }

 double dist[VERTEX_MAX];
 int preced[VERTEX_MAX];
 for(i=0;i<VERTEX_MAX;i++)
    {
     
      dist[i]=1000;
      preced[i]=UNDEFINED;
    }

  size=3000;
// sleep(3);
	cout<<"\n So the landmarks are::";
	for(int i=0;i<1;i++)
		{
			cout<<"("<<landm[i].x<<","<<landm[i].y<<") ,"<<landm[i].val<<"\n";
		}


 // sleep(3);
  for(int i=0;i<5;i++)                             // Needs correction from here
		{
		for(int j=0;j<VERTEX_MAX;j++)
				{
       		if((landm[i].val!=j))
						{
				   		cout<<"\n landmark = "<<landm[i].val<<"\n\n";
						  landm[i].dist1[j];
			        result =dijkstra(hash_table,V,dist,preced,landm[i].val,j);           // Needs correction
              infile4<<landm[i].val<<" "<<j<<" "<<result<<"\n";
							if(landm[i].dist1[j]==INFINITE)

								{
									cout<<"\n No path exists between node ("<<landm[i].val<<") and node ("<<V[j].ID<<")";
									
								}

							else
							{
    	          cout<<"\n The length of the path between node ("<<landm[i].val<<") and node  ("<<V[j].ID<<") is "<<result;		
								}
					}

					else
								{
								//	landm[i].dist1[j]=0;
    	      			cout<<"\n **************************************************************\n The distance is zero";
								}
			}	
				
		}
  infile4.close();
	return 0;
} 




double dijkstra (struct hash hash_table[VERTEX_MAX+2],vertex V[VERTEX_MAX],double dis[VERTEX_MAX],int mpreced[VERTEX_MAX],int s, int f)         // p and q to be corrected
 {
  double smalldist=0,w;
  int v,u,visit[VERTEX_MAX+1]={0},flag;
  long int vertex_num;
  priority_queue<pp,vector<pp>,pri> q;
  double d[VERTEX_MAX+1];
  for(int i=0;i<VERTEX_MAX;i++)
    {
      d[i]=1000;
    }
  d[s]=0;
  q.push(pp(s,d[s]));
  cout<<" source inputed";
  while((u!=f)&&(!q.empty()))
    {
      flag=0;
      int size=0,flag=0;
      u=q.top().first;
  //    cout<<"\n step a";
      while(visit[u]==1)
        {
          if(visit[u]==1)
            {
              flag=1;
              break;
            }
        //  cout<<"\n step b";
          if(flag==1)
            {
              q.pop();
              u=q.top().first;
            }
         }
      smalldist=q.top().second;
      cout<<"\t\t  The distance so far is::"<<smalldist;
      q.pop();
      visit[u]=1;
      cout<<"\n step c";
      cout<<"\t The node visited is::"<<hash_table[u].ID;
      if(u==0)
        {
        //  sleep(5);
        }
      struct link_hash* node;
      node=(struct link_hash*)malloc(sizeof(struct link_hash));
      node=hash_table[u].next;
      cout<<"\n step d";
      while(node!=NULL)
        {
           v=node->ID;
           cout<<"\n step e";
           w=node->distance;
            if(d[v]>d[u]+w)
              {
                d[v]=d[u]+w;
                q.push(pp(v,d[v]));
                cout<<"\n Step f \n\n\n";
              }
            node=node->next;
         }
     }
 if(q.empty()==1)
   {
     smalldist=INFINITE;
  }

  /*int selected[VERTEX_MAX],x,new_node[VERTEX_MAX],new_size=0,k,d,j,X,visited[VERTEX_MAX];
	for(int i=0;i<(VERTEX_MAX);i++)
		{
			selected[i]=0;
			dis[i]=1000;
			mpreced[i]=UNDEFINED;

		}

  	int current;
    d=f;
    current=v;
    long double dc,newdist,smalldist;
  	selected[current]=1;
  	dis[current]=0;
	  dc=dis[current];
	  new_node[new_size]=current;

//    insert(Priority_Q,current,d);
	  cout<<"\n *****************************************************************************\n SOURCE "<<v<<" DESTINATION "<<d<<"\n";
	  while(!allselected(selected,d))
    	{
         smalldist=INFINITE;
	       x=0;
         for(j=0;j<=new_size;j++)                     // n=Pop(Priority_Q)    make n visited
		      	{                                         // for(i=0;i<degree;i++)       { insert(Priority_Q,,d+dist)
			      	current=new_node[j];                    
    	      	dc=dis[current];
              X=hash_table[current].ID;
              if(hash_table[current].next==NULL)
                {
                  cout<<"do nothing";
                }
              else
                {
                  struct link_hash* newnode;
                  newnode=(struct link_hash*)malloc(sizeof(struct link_hash));
                  newnode=hash_table[current].next;
    			       	while(newnode!=NULL)
    				        {      
				  	          if(selected[newnode->ID]==0)
    						         {                             
					    	     	     x++;         
    					   		       newdist=dc+newnode->distance;
                       //cout<<"\n newdist="<<newdist;
          						   if(newdist<dis[newnode->ID])
    		  						    {
    			  				    		dis[newnode->ID]=newdist;
						  	     	  	  mpreced[newnode->ID]=current;
    					 		   	    }  
    					      if(dis[newnode->ID]<smalldist)
  					       	  {
          						  smalldist=dis[newnode->ID];
				        			  k=newnode->ID;
           			   	  }
                    
                    }		
                    newnode=newnode->next;
                 }
                 cout<<"small dist="<<smalldist;
				     	}
            }
		if(x==0) 
			{
				return INFINITE;
			}
    		current=k;
		if((current !=f))             // Needs correction
			{
				new_size++;
				new_node[new_size]=current;
    		selected[current]=1;
       }
		else
			{	
				break; 
			}		
	
}
int  path=d;
//	cout<<"\n and their new size is::\n"<<new_size<<"\n"<<d<<"-------->";
 while(mpreced[path]!=v)
  {
    cout<<mpreced[path]<<"--->";
    path=mpreced[path];
    
  } */                                      // TO BE SEEN LATER
 //cout<<v;
	return smalldist;
  }



int allselected(int *selected,int d)
{
  int i;
  for(i=0;i<(VERTEX_MAX+2);i++)
    if(selected[d]==0)
      return 0;
  return 1;  
}
 


double compute_lowerbound(lm landm[MAX/5],struct hash hash_table[MAX+2],long int src,int dest )   
{
 double large=0,L[10];
 for(int i=0;i<4;i++)
	{
			
       if(landm[i].dist1[src]>landm[i].dist1[dest])
          {
			      	L[i]=(landm[i].dist1[src]-landm[i].dist1[dest]);
          }
      else
          {
              L[i]=(landm[i].dist1[dest]-landm[i].dist1[src]);
          }

		if(L[i]>100)
			{
				L[i]=0;
			}
		if(L[i]>large)
			{
				large=L[i];
			}
	}
 //cout<<"\n The lower bound between "<<src<<" and "<<dest<<" is ::"<<large<<"\n";

 return large;
}



solution modified_dijkstra(lm landm[MAX],struct hash hash_table[MAX], struct vertex V[MAX], double dist[MAX],int preced[MAX],long int mv,long int mf,int result[MAX],int count)               
{
  int dest,mx,mk,mcurrent,mnew_size=0,mnew_node[MAX+2],selected[MAX+2],point;
  long int MX;
  double M=0,msmalldist,mnewdist[MAX+2],mdc,mnewdistt=INFINITE,small,mnewdisttt[MAX+2];
  solution result_djk;
  for(int i=0;i<(MAX+2);i++)
	{
		selected[i]=0;
		dist[i]=INFINITE;
    preced[i]=UNDEFINED;
	}
  dest=mf;
   mcurrent=mv;
  selected[mcurrent]=1;
  dist[mcurrent]=0;
  mdc=dist[mcurrent];
  mnew_node[mnew_size]=mcurrent;
  //cout<<"\n ************************************\n SOURCE   "<<source<<" DESTINATION  "<<dest<<"\n";
  while(!allselected(selected,dest))
	{
		mx=0;
		msmalldist=INFINITE;
    small=INFINITE;
		for(int j=0;j<=mnew_size;j++)
			{	
				mcurrent=mnew_node[j];
				mdc=dist[mcurrent];
        MX=hash_table[mcurrent].ID;
        if(hash_table[mcurrent].next==NULL)
          {
            cout<<"\n Do nothing"; 
          }
        else
					{
            struct link_hash* newnode;
            newnode=(struct link_hash*)sizeof(struct link_hash);
            newnode=hash_table[mcurrent].next;
            while(newnode!=NULL)
              {
						    if(selected[newnode->ID]==0)
							{
								mx++;
								M=compute_lowerbound(landm,hash_table,newnode->ID,dest);
								mnewdist[newnode->ID]=mdc+newnode->distance+M;
                mnewdisttt[newnode->ID]=mdc+newnode->distance;
                /*if(mnewdist[i]<small)
                  {
                    small=mnewdist[i];
                    point=i;
						        msmalldist=mnewdisttt[i];
                  }*/
									if(mnewdisttt[newnode->ID]<dist[newnode->ID])
										{
											dist[newnode->ID]=mnewdisttt[newnode->ID];
											preced[newnode->ID]=mcurrent;
										}    
                if(mnewdist[newnode->ID]<small)
                  {
                    small=mnewdist[newnode->ID];
                    point=newnode->ID;
						        msmalldist=mnewdisttt[newnode->ID];
                  }             
							}
              newnode=newnode->next;		
				  	}
		  	 }
      }
		if(mx==0)
			{
  				result_djk.distance=INFINITE;
          return result_djk;                               //previously it was return Infinite
			}
		mcurrent=point;
  if((mcurrent !=mf))
    {
	  	mnew_size++;
	  	mnew_node[mnew_size]=mcurrent;
	  	selected[mcurrent]=1;
    }
	else         // Needs correction
		{
				break;
		}
	}
/*cout<<"\n the new node set is::\n";
for(int w=0;w<=mnew_size;w++)
  {
    cout<<mnew_node[w]<<" ";
  }*/
// cout<<"\n And the node size is "<<mnew_size<<"\n";	
 int path=mf;
 result_djk.size_result=0; 
 //cout<<"\n"<<path<<"------>";
 while(preced[path]!=mv)
  {
//    cout<<preced[path]<<"--->";
    path=preced[path];
    result_djk.result[result_djk.size_result]=preced[path];
    result_djk.size_result++;
  } 
 result_djk.distance=msmalldist;
 return result_djk;                                  // yet to be edited
}
			
       
long double eucledian(long double a1,long double a2,long double b1,long double b2)
{
  long double x_sq, y_sq,result;
  x_sq=pow((a1-a2),2.0);
  y_sq=pow((b1-b2),2.0);
  result=sqrt(x_sq+y_sq);

/*      cout<<"\n x_sq pow"<<x_sq;
      cout<<"\n y_sq pow"<<y_sq;
      cout<<"\n result="<<result<<"\n";*/
  return result;
}
