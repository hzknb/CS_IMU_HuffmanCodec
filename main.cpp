#include <iostream>
#include<fstream>
using namespace std;
struct ASCII_Code{
    int cde = 0;
    char chr = ' ';
    int frequency = 0;
    ASCII_Code *next = nullptr;
};
void load(ASCII_Code * head);
bool search(ASCII_Code * head, int code);
void sort(ASCII_Code * head);
int main() {
    ASCII_Code *head;
    head=new ASCII_Code;
    load(head);
    sort(head);
    while(head->next != nullptr){
        head=head->next;
        cout<<head->cde<<" "<<head->chr<<" "<<head->frequency<<endl;
    }
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
void sort(ASCII_Code * head){
    ASCII_Code * p;
    ASCII_Code * q;
    int temp_1;
    char temp_2;
    int temp_3;
    p=head;
    while(p->next){
        q=p->next;
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
}