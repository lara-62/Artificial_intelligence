#include<bits/stdc++.h>
using namespace std;
int k;
map<vector<vector<int>>,bool>m;



int absolute(int x)
{
    if(x>=0)
    {
        return x;
    }
    else
        return -x;
}

pair<int,int> get_zeroPos(vector<vector<int>>state)
{
    pair<int,int>zero_pos= {-1,-1};

    for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(state[i][j]==0)
            {
                zero_pos.first=i;
                zero_pos.second=j;
                return zero_pos;
            }
        }

    }
    return zero_pos;
}
vector<vector<int>>get_child(vector<vector<int>>state,int x1,int y1,int x2,int y2)
{
    vector<vector<int>> new_state(k,vector<int>(k)) ;
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<k;j++)
        {
            new_state[i][j]=state[i][j];
        }
    }
    int temp=new_state[x1][y1];
    new_state[x1][y1]=new_state[x2][y2];
    new_state[x2][y2]=temp;
    return new_state;
}
class Node
{
    vector<vector<int>>state;
    Node *parent;
    int   g;
public:
    Node()
    {
        //kuch nehi
    }
    Node(vector<vector<int>>board)
    {
        state=board;
        g=0;
        parent=nullptr;

    }
    void setParent(Node* parentState)
    {
        parent=parentState;
    }
    Node* getParent()
    {
        return parent;
    }
    void set_g(int value)
    {
        g=value;
    }
    int get_g()
    {
        return g;
    }
   vector<vector<int>> get_matrix()
    {
        return state;
    }
};
//heruistic
int hamming_distance(vector<vector<int>>board)
{
    int heruistic=0;
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(board[i][j]!=0)
            {
                if((i*k+j+1)!=board[i][j])
                {

                    heruistic++;
                }
            }


        }
    }
    return heruistic;


}
int manhattan(vector<vector<int>>board)
{
    int heruistic=0;
   /* for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(board[i][j]!=0)
            {
                int x=absolute(ceil(double(board[i][j])/double(k))-1-i);
                int y=absolute(((board[i][j])-((ceil(double(board[i][j])/ double(k))-1)*k)-1)-j);
               // cout<<x<<" "<<y<<endl;
                heruistic+=x+y;


            }


        }
    }
    return heruistic;
}

//inversion count


int inversionCount(vector<int>board)
{
    int inversion=0;

    for(int i=0;i<board.size();i++)
    {
        for(int j=i+1;j<board.size();j++)
        {
            if(board[i]>board[j])
             inversion++;
        }
       // cout<<inversion<<endl;
    }
    return inversion;
}

class Compare {
public:
    bool operator()(pair<int,Node*>a,pair<int,Node*>b)
    {
        if (a.first > b.first) {
            return true;
        }
        else if (a.first == b.first
                 && a.second->get_g()<b.second->get_g()) {
            return true;
        }

        return false;
    }
};


int main()
{

    cin>>k;
    vector<vector<int>>board(k, vector<int>(k));
    vector<int>board1D;
    Node* targetNode=nullptr;
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            int a;
            cin>>a;
            board[i][j]=a;
            if(a!=0){
            board1D.push_back(a);
            }
        }
    }

   /* for(int i=0;i<board1D.size();i++)
    {
        cout<<board1D[i]<<" ";
    }
    cout<<endl;
   // cout<<manhattan(board);
   cout<<inversionCount(board1D)<<endl;*/
   int zero_row_pos=get_zeroPos(board).first;
   //cout<<zero_row_pos<<endl;

    if(k%2 && inversionCount(board1D)%2)
    {
        cout<<"Not solveable"<<endl;
    }
    else if(k%2==0 && (((k-zero_row_pos)%2==0 &&inversionCount(board1D)%2==0)||((k-zero_row_pos)%2 &&inversionCount(board1D)%2)))
    {
      cout<<"Not solveable"<<endl;
    }
    else
    {


    priority_queue<pair<int,Node*>,vector<pair<int,Node*>>,Compare>minheap;
    Node* source;
    source=new Node(board);
    minheap.push(make_pair(manhattan(board),source));
    m[board]=true;
    while(!minheap.empty())
    {

        Node* u=minheap.top().second;
        int f=minheap.top().first;
        minheap.pop();
        vector<vector<int>>state=u->get_matrix();
        pair<int,int>zero_pos=get_zeroPos(state);

        //childnodes

        int i=zero_pos.first;
        int j=zero_pos.second;

        //up
        if(i-1>=0)
        {
           vector<vector<int>>child_matrix=get_child(state,i,j,i-1,j);

            if(m.find(child_matrix)==m.end()){
            int q=u->get_g()+1;
            int h=manhattan(child_matrix);
            int childf=q+h;
            Node *childnode=new Node(child_matrix);
            childnode->set_g(q);
            childnode->setParent(u);
            pair<int,Node*>v;
            v.first=childf;
            v.second=childnode;
            minheap.push(v);
            m[child_matrix]=true;
            if(h==0)
            {   //cout<<"cost "<<q<<endl;
                 targetNode=childnode;
                break;
            }
            }
        }
        //down

        if(i+1<k)
        {
            vector<vector<int>>child_matrix=get_child(state,i,j,i+1,j);

            if(m.find(child_matrix)==m.end()){
            int q=u->get_g()+1;
            int h=manhattan(child_matrix);
            int childf=q+h;
            Node *childnode=new Node(child_matrix);
            childnode->set_g(q);
            childnode->setParent(u);
            pair<int,Node*>v;
            v.first=childf;
            v.second=childnode;
            minheap.push(v);
            m[child_matrix]=true;
            if(h==0)
            {
                //cout<<"cost "<<q<<endl;
                targetNode=childnode;
                break;
            }
            }
        }
        // left

        if(j-1>=0)
        {
            vector<vector<int>>child_matrix=get_child(state,i,j,i,j-1);

            if(m.find(child_matrix)==m.end()){
            int q=u->get_g()+1;
            int h=manhattan(child_matrix);
            int childf=q+h;
            Node *childnode=new Node(child_matrix);
            childnode->set_g(q);
            childnode->setParent(u);
            pair<int,Node*>v;
            v.first=childf;
            v.second=childnode;
            minheap.push(v);
            m[child_matrix]=true;
            if(h==0)
            {
               // cout<<"cost "<<q<<endl;
               targetNode=childnode;
                break;
            }
            }
        }

        //right
        if(j+1<k)
        {

            vector<vector<int>>child_matrix=get_child(state,i,j,i,j+1);

            if(m.find(child_matrix)==m.end()){
            int q=u->get_g()+1;
            int h=manhattan(child_matrix);
            int childf=q+h;
            Node *childnode=new Node(child_matrix);
            childnode->set_g(q);
            childnode->setParent(u);
            pair<int,Node*>v;
            v.first=childf;
            v.second=childnode;
            minheap.push(v);
            m[child_matrix]=true;
            if(h==0)
            {
                //cout<<"cost "<<q<<endl;
                targetNode=childnode;
                break;
            }
            }
        }
    }
       cout<<"Minimum number of moves: "<<targetNode->get_g()<<endl<<endl;
       cout<<"All the steps:"<<endl<<endl;
       stack<Node *>parent;

       while(targetNode!=nullptr)
       {
           parent.push(targetNode);
           targetNode=targetNode->getParent();
       }
       while(!parent.empty())
       {
           vector<vector<int>>state=parent.top()->get_matrix();
           for(int i=0;i<k;i++)
           {
               for(int j=0;j<k;j++)
               {
                   cout<<state[i][j]<<" ";
               }
               cout<<endl;
           }
           cout<<endl;
           parent.pop();
       }

    }

}

