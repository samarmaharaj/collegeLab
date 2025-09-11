// Sender/Receiver demo: Even/Odd Parity, 16-bit checksum, CRC-16-CCITT (compact)
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>

using namespace std;

// Helpers
vector<uint8_t> toBytes(const string& s) { return {s.begin(), s.end()}; }
void printHex(const vector<uint8_t>& a){ ios::fmtflags f(cout.flags()); for(size_t i=0;i<a.size();++i) cout<<hex<<uppercase<<setw(2)<<setfill('0')<<(unsigned)a[i]<<(i+1!=a.size()?" ":""); cout.flags(f);} 

// Trailers
uint8_t parityBit(const vector<uint8_t>& d,bool even){ unsigned ones=0; for(uint8_t b:d) ones+=__builtin_popcount(b); return even?(ones&1u):((ones&1u)^1u);} 
uint16_t checksum16(const vector<uint8_t>& d){ uint32_t s=0; size_t i=0; for(;i+1<d.size();i+=2){ s+= (d[i]<<8)|d[i+1]; if(s>0xFFFF) s=(s&0xFFFF)+1; } if(i<d.size()){ s+= (d[i]<<8); if(s>0xFFFF) s=(s&0xFFFF)+1; } return (uint16_t)(~s & 0xFFFF);} 
uint16_t crc16(const vector<uint8_t>& d,uint16_t poly=0x1021,uint16_t init=0xFFFF){ uint16_t c=init; for(uint8_t b:d){ c^=(b<<8); for(int i=0;i<8;++i) c=(c&0x8000)?(uint16_t)((c<<1)^poly):(uint16_t)(c<<1);} return c; }

enum class Method{ParityEven=1,ParityOdd,Checksum16,CRC16};
static const char* MName[]{"","Even Parity","Odd Parity","16-bit Checksum","CRC-16-CCITT"};

// Frame build/verify
vector<uint8_t> build(const vector<uint8_t>& p,Method m){
    vector<uint8_t> f=p; 
    if(m==Method::ParityEven||m==Method::ParityOdd){ f.push_back(parityBit(p,m==Method::ParityEven)); }
    else if(m==Method::Checksum16){ uint16_t s=checksum16(p); f.push_back(s>>8); f.push_back(s&0xFF);} 
    else { uint16_t c=crc16(p); f.push_back(c>>8); f.push_back(c&0xFF);} 
    return f;
}

bool verify(const vector<uint8_t>& f,Method m,vector<uint8_t>& out){ if(f.empty()) return out.clear(),false; 
    if(m==Method::ParityEven||m==Method::ParityOdd){ if(f.size()<1) return false; out.assign(f.begin(),f.end()-1); return (uint8_t)(f.back()&1u)==parityBit(out,m==Method::ParityEven);} 
    if(f.size()<2) return false; uint16_t recv=(uint16_t)((f[f.size()-2]<<8)|f.back()); out.assign(f.begin(),f.end()-2); uint16_t calc=(m==Method::Checksum16)?checksum16(out):crc16(out); return recv==calc; }

inline void flip(vector<uint8_t>& b,size_t i,int k){ if(i<b.size()&&k>=0&&k<8) b[i]^=(1u<<k); }

int main(){
    for(;;){
        cout<<"Enter data (text line): "; string line; if(!getline(cin>>ws,line)) break; vector<uint8_t> payload=toBytes(line);
        cout<<"\nChoose method: 1) Even Parity  2) Odd Parity  3) 16-bit Checksum  4) CRC-16-CCITT  0) Exit\nEnter choice: ";
        int c=0; if(!(cin>>c) || c<0 || c>4){ cout<<"Exiting...\n"; break;} if(c==0){ cout<<"Exiting...\n"; break; }
        Method m=(Method)c;

        cout<<"\nSender: payload (hex): "; printHex(payload); cout<<"\nSender: method = "<<MName[c]<<'\n';
        vector<uint8_t> frame=build(payload,m);

        if(m==Method::ParityEven||m==Method::ParityOdd) cout<<"Sender: parity bit = "<<(unsigned)frame.back()<<'\n';
        else { uint16_t t=(uint16_t)((frame[frame.size()-2]<<8)|frame.back()); ios::fmtflags f(cout.flags()); cout<<"Sender: trailer = 0x"<<hex<<uppercase<<setw(4)<<setfill('0')<<t<<dec<<'\n'; cout.flags(f);} 

        cout<<"Sender -> Frame (hex): "; printHex(frame); cout<<'\n';

        cout<<"\nInject error? (y/n): "; char yn='n'; cin>>yn; if(yn=='y'||yn=='Y'){ cout<<"Enter byte index [0.."<<(frame.size()-1)<<"] and bit [0..7]: "; size_t bi=0; int bk=0; cin>>bi>>bk; flip(frame,bi,bk); cout<<"Channel: flipped bit "<<bk<<" of byte "<<bi<<'\n'; }

        cout<<"Channel -> Received frame (hex): "; printHex(frame); cout<<'\n';
        vector<uint8_t> recv; bool ok=verify(frame,m,recv);
        cout<<"Receiver: payload (hex): "; printHex(recv); cout<<"\nReceiver: error detected? "<<(ok?"No (OK)":"Yes (CORRUPTED)")<<"\n\n---\n";
    }
    return 0;
}
