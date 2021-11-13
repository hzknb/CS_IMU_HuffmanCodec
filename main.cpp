#include <iostream>
#include<fstream>
#include<string>
using namespace std;
struct HuffmanTree{
    int weight = 0;
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
    HuffmanTree * tree = new HuffmanTree;
};
int num = 0;
double WPL =0;
void load(ASCII_Code * head);
bool search(ASCII_Code * head, int code);
HuffmanTree* sort(ASCII_Code * head);
void create(HuffmanTree* h);
string codec(ASCII_Code &byte);
int main() {
    ASCII_Code *head;
    HuffmanTree* h;
    head=new ASCII_Code;
    load(head);
    h=sort(head);
    create(h);
    cout<<"ASCII\tChar\tWeight\tHuffmanCode"<<endl;head=head->next;
    while(head!=nullptr){
        cout<<head->cde<<"\t\t"<<head->chr<<"\t\t"<<head->tree->weight<<"\t\t"<<codec(*head)<<endl;
        head=head->next;
    }
    cout<<"WPL:"<<WPL;
    return 0x1BF52;
}
void load(ASCII_Code *head){
    fstream file;
    string filename;
    int temp_code;
    ASCII_Code *p;
    head->frequency=0;
    p=head;
    cout<<"Input Filename:";
    cin>>filename;
    file.open("../"+filename+".txt",ios::in);
    if(file.is_open())
    {
        while(!file.eof()){
            file>>temp_code;
            if(!search(head,temp_code)){
                p->next=new ASCII_Code;
                p=p->next;
                p->frequency=1;
                p->cde=temp_code;
                p->chr=char(temp_code);
                num++;
            }
        }
    }
}
bool search(ASCII_Code* head, int code){
    ASCII_Code *p;
    p=head->next;
    while(p != nullptr){
        if(p->cde==code){
            p->frequency++;
            return true;
        }
        else p=p->next;
    }
    return false;
}
HuffmanTree* sort(ASCII_Code * head){
    ASCII_Code * p;
    ASCII_Code * q;
    HuffmanTree* h;
    HuffmanTree* r;
    int temp_1;
    char temp_2;
    int temp_3;
    p=head;
    while(p->next){
        q=p->next;
        while(q->next){
            if(q->next->frequency<q->frequency){
                temp_1=q->cde;q->cde=q->next->cde;q->next->cde=temp_1;
                temp_2=q->chr;q->chr=q->next->chr;q->next->chr=temp_2;
                temp_3=q->frequency;q->frequency=q->next->frequency;q->next->frequency=temp_3;
            }
            q=q->next;
        }
        p=p->next;
    }p=head;h=new HuffmanTree;r=h;p=p->next;
    while(p!= nullptr){
        r->next=new HuffmanTree;
        r=r->next;
        r->weight=p->frequency/num;
        p->tree=r;p=p->next;
    }
    return h;
}
void create(HuffmanTree* h){
    HuffmanTree *p;
    HuffmanTree *q;
    q=h->next;
    while(q->Parent!=nullptr) {
        p=q;
        while (p != nullptr) {
            p->Parent = new HuffmanTree;
            p->Parent->LChild = p;
            if (p->next != nullptr) {
                p->next->Parent = p->Parent;
                p->Parent->weight = p->weight + p->next->weight;
                p->Parent->RChild = p->next;
            } else p->Parent->weight = p->weight;
            p = p->next->next;
        }
        q=q->Parent;
    }
}
string codec(ASCII_Code &byte){
    string code;
    HuffmanTree *p;
    int i=0;
    code="";
    p=byte.tree;
    while(p->Parent){
        if(p->Parent->RChild==nullptr){
            continue;
        }else if(p->Parent->LChild==p){
            code+='0';i++;
        }else if(p->Parent->RChild==p){
            code+='1';i++;
        }
    }
    WPL+=(i*byte.tree->weight);
    return code;
}