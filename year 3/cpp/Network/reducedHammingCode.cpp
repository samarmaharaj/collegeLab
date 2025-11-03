#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> encode(vector<int> d){
    vector<int> c(7);
    c[2]=d[0]; c[4]=d[1]; c[5]=d[2]; c[6]=d[3];
    c[0]=c[2]^c[4]^c[6]; c[1]=c[2]^c[5]^c[6]; c[3]=c[4]^c[5]^c[6];
    return c;
}
vector<int> decode(vector<int> c){
    int s1=c[0]^c[2]^c[4]^c[6], s2=c[1]^c[2]^c[5]^c[6], s3=c[3]^c[4]^c[5]^c[6];
    int err=s1+(s2<<1)+(s3<<2);
    if(err){ cout<<"  -> Correcting error at bit "<<err<<"\n"; c[err-1]^=1; }
    return {c[2],c[4],c[5],c[6]};
}
vector<int> byteToBits(unsigned char c){
    vector<int> b(8);
    for(int i=7;i>=0;i--) b[7-i]=(c>>i)&1;
    return b;
}
unsigned char bitsToByte(const vector<int>& b){
    unsigned char c=0;
    for(int x:b) c=(c<<1)|x;
    return c;
}
int main(){
    while(true){
        cout<<"\nEnter text (or 'exit'): ";
        string msg; getline(cin, msg);
        if(msg=="exit") break;
        cout<<"[Sender] Original: "<<msg<<"\n";
        vector<vector<int>> tx;
        for(unsigned char c:msg){
            vector<int> b=byteToBits(c);
            tx.push_back(encode({b[0],b[1],b[2],b[3]}));
            tx.push_back(encode({b[4],b[5],b[6],b[7]}));
        }
        cout<<"[Sender] Encoded: ";
        for(auto& blk:tx) for(int b:blk) cout<<b;
        cout<<"\n";
        cout<<"Inject error? (y/n): ";
        char choice; cin>>choice;
        if(choice=='y'||choice=='Y'){
            int bytePos, bitPos, map[4]={2,4,5,6};
            cout<<"Byte num (1-"<<msg.size()<<"): "; cin>>bytePos;
            cout<<"Bit num (1-8): "; cin>>bitPos;
            int blkIdx=(bytePos-1)*2+(bitPos>4), bitIdx=(bitPos-1)%4;
            if(blkIdx<tx.size()) tx[blkIdx][map[bitIdx]]^=1;
        }
        cin.ignore(); string recovered;
        for(int i=0;i<tx.size();i+=2){
            vector<int> d1=decode(tx[i]), d2=decode(tx[i+1]);
            d1.insert(d1.end(),d2.begin(),d2.end());
            recovered.push_back(bitsToByte(d1));
        }
        cout<<"[Receiver] Recovered: "<<recovered<<"\n";
    }
    cout<<"Exiting.\n"; return 0;
}

