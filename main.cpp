#include <iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
struct HuffmanTree{
    double weight = 0;
    HuffmanTree* LChild = nullptr;
    HuffmanTree* RChild = nullptr;
    HuffmanTree* Parent = nullptr;
    HuffmanTree* next = nullptr;
};
struct ASCII_Code{
    int cde = 0;
    char chr = ' ';
    int frequency = 0;
    ASCII_Code *next = nullptr;
    HuffmanTree *tree = new HuffmanTree;
};
int nxx = 0;
double WPL =0;
ASCII_Code* search(ASCII_Code* head, int code){
    ASCII_Code *p;
    p=head->next;
    while(p != nullptr){
        if(p->cde==code){
            return p;
        }
        else p=p->next;
    }
    return nullptr;
}
HuffmanTree* sort(ASCII_Code * head){
    ASCII_Code * p;
    ASCII_Code * q;
    HuffmanTree* h;
    int temp_1;
    char temp_2;
    int temp_3;
    p=head;
    while(p->next){
        q=head->next;
        while(q->next){
            if(q->next->frequency>q->frequency){
                temp_1=q->cde;q->cde=q->next->cde;q->next->cde=temp_1;
                temp_2=q->chr;q->chr=q->next->chr;q->next->chr=temp_2;
                temp_3=q->frequency;q->frequency=q->next->frequency;q->next->frequency=temp_3;
            }
            q=q->next;
        }
        p=p->next;
    }
    p=head;
    h=p->next->tree;
    while(p!= nullptr){
        if(p->next!=nullptr)p->tree->next=p->next->tree;
        p->tree->weight=double(p->frequency)/double(nxx);
        p=p->next;
    }return h;
}
void create(HuffmanTree* h){
    HuffmanTree* lt;
    HuffmanTree* rt;
    stack<HuffmanTree*> stk;
    bool tag = true;
    while(h){
        stk.push(h);
        h=h->next;
    }
    lt=stk.top();stk.pop();
    while(!stk.empty()){
        lt->Parent=new HuffmanTree;
        lt->Parent->LChild=lt;
        lt->Parent->RChild=stk.top();stk.pop();
        lt->Parent->RChild->Parent=lt->Parent;
        lt=lt->Parent;
        if(!stk.empty()) {
            if(tag){rt=stk.top();stk.pop();tag=false;}
            rt->Parent = new HuffmanTree;
            rt->Parent->LChild = rt;
            rt->Parent->RChild=stk.top();stk.pop();
            rt->Parent->RChild->Parent=rt->Parent;
            rt=rt->Parent;
        }
    }
    lt->Parent=new HuffmanTree;
    lt->Parent->LChild=lt;
    lt->Parent->RChild=rt;
    rt->Parent=lt->Parent;
}
string codec(ASCII_Code &byte){
    stack<char> find;
    string code;
    HuffmanTree *p;
    code="";
    p=byte.tree;
    while(p->Parent){
        if(p->Parent->LChild==p){
            find.push('0');
        }else if(p->Parent->RChild==p){
            find.push('1');
        }
        p=p->Parent;
    }
    WPL=WPL+(byte.tree->weight*double(find.size()));
    while(!find.empty()){
        code+=find.top();
        find.pop();
    }
    return code;
}
void show(ASCII_Code *head){
    cout<<"ASCII\tChar\tWeight\t\tHuffmanCode"<<endl;head=head->next;
    while(head!=nullptr){
        cout<<head->cde<<"\t "<<head->chr<<"\t "<<head->tree->weight<<"\t\t"<<codec(*head)<<endl;
        head=head->next;
    }
    cout<<"WPL:"<<WPL;
}
void load(ASCII_Code *head){
    fstream file;
    string filename;
    int temp_code;
    ASCII_Code *p;
    ASCII_Code *q;
    head->frequency=0;
    p=head;
    cout<<"Input Filename:";
    cin>>filename;
    file.open("../"+filename+".txt",ios::in);
    if(file.is_open())
    {
        while(!file.eof()){
            file>>temp_code;
            q= search(head,temp_code);
            if(!q){
                p->next=new ASCII_Code;
                p=p->next;
                p->frequency=1;
                p->cde=temp_code;
                p->chr=char(temp_code);
                nxx++;
            }else{
                q->frequency++;
                nxx++;
            }
        }
    }
}
int main() {
    ASCII_Code *head;
    HuffmanTree* h;
    head=new ASCII_Code;
    load(head);
    h=sort(head);
    //build(h);
    create(h);
    show(head);
    return 0x1BF52;
}