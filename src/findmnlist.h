#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
//#include <conio.h>

using namespace std;

static const int LBLOCK=3;
static const unsigned int SIGNALON=10286;
static const unsigned int SIGNALOFF=20219;
static const unsigned int LOCKFROM=2095091600; //  1595091600 = 07/18/2020T17:00:00// - time to lock from in historical list 
static const unsigned int STARTCHECKTX2=24000; // 30k for bull
static const unsigned int STARTHISTORYMN=10; 
static const unsigned int NVACCEPTABLESHIFT=1000000; // 

string short0string = "0000000000000000000000000000000000";
string long0string = "0000000000000000000000000000000000000000000000000000000000000000";

int LDebug = GetArg("-ldebug", 0); 


class Char35Adr
{
public:
    char sca[35];
    Char35Adr(string scamadr){
        strcpy (sca, scamadr.c_str());
    }

    void f()
    {
        //cout << "Char35Adr::f - " << sca << endl;
        LogPrintf("Address:  %s \n", sca); 

    }

    string toString()
    {
        return sca;
    }

    int elemsize(){
        return sizeof(sca);
    }
};


class MnTxHash
{
public:
    char txha[65];
    MnTxHash(string txhash){
        strcpy (txha, txhash.c_str());
    }

    void f()
    {
        //cout << "MnTxHash::f - " << txha << endl;
        LogPrintf("MnTxHash::f -  %s \n", txha); 
    }

    string toString()
    {
        return txha;
    }

    int elemsize(){
        return sizeof(txha);
    }
};


class FindMnList
{
private:
    bool erasefirstisdone;
    int lastcollateral;
 
public:
    vector<Char35Adr> arr;
    vector<MnTxHash> txhash;
    vector<int> outInd;
    FindMnList(){
        erasefirstisdone = false;
        lastcollateral = 0;
        arr.push_back( Char35Adr(short0string) );
        outInd.push_back(0);
        txhash.push_back( MnTxHash(long0string) );
    }

    void reInitialyze(){
        if(erasefirstisdone){
            erasefirstisdone = false;
        }
        for(int k=0; k<this->sizeMn(); k++){
            outInd[k] = 0;
            arr[k] = Char35Adr(short0string);
            txhash[k] = MnTxHash(long0string);
        }
        for(int k=(this->sizeMn()-1); k>0; k--){
            this->erase(k);
            LogPrintf("reInitialyze(): ERASE k=%d \n", k);
        }
    }

    void checkCollateral(int currentColl){
        if(!lastcollateral) lastcollateral = currentColl;  // if this is first collateral we only initialyze lastcollateral value 
        else if(currentColl != lastcollateral) {
            lastcollateral = currentColl;
            this->reInitialyze();
        }
    }

    void vinit(string adr, string hash, int outputIndex){
        outInd.push_back( outputIndex ); 
        arr.push_back( Char35Adr(adr) ); 
        txhash.push_back( MnTxHash(hash) ); 
    }

    void eraseFirst(){
        if(!erasefirstisdone){
            outInd.erase(outInd.begin());
            arr.erase(arr.begin());
            txhash.erase(txhash.begin());
            erasefirstisdone = true;
        }
        else {
            if(fDebug) LogPrintf("   ___eraseFirst()___  HAS BEEN ERASED ALREADY \n");
        }

        return;
    }


    void erase(int k){
        outInd.erase(outInd.begin()+k);
        arr.erase(arr.begin()+k);
        txhash.erase(txhash.begin()+k);
        LogPrintf("   ___erase()___  done\n");
        return;
    }


    void print()
    {
        for(unsigned i = 0; i < arr.size(); ++i)
        {
            arr[i].f();
            txhash[i].f();
            LogPrintf("outInd = %d\n", outInd[i]);
        }
    }

    string getValueMn(int i)
    {
        return arr[i].toString();
    }

    int getValueOI(int i)
    {
        return outInd[i];
    }

    string getValueHash(int i)
    {
        return txhash[i].toString();
    }

    int sizeMn(){
        return arr.size()/* * sizeof(Char35Adr)*/;
    }

    int sizeHash(){
        return txhash.size()/* * sizeof(Char35Adr)*/;
    }
 /*
    void txtWrite(string path){
        ofstream fout;
        fout.open(path, ios::out | ios::trunc );  
        if(!fout.is_open()){
            cout << "txtWrite(): open out-file error" << endl;
        }
        else {
            if ( (fout.rdstate() & std::ofstream::failbit ) != 0 ) 
                cout << "txtWrite(): Error opening 'myfile.txt'\n";

            cout << "txtWrite(): out-file " << path << " was opened" << endl;
            //fout << "txtWrite(): Writing this to a file.\n";
            for(unsigned i=0; i<arr.size(); i++) fout << arr[i].toString() << "\n";
        }
        fout.close();
        return;
    }

    void binWrite(string path){
        ofstream fout;
        //    fout.open(path, ofstream::app);   //   ios::out | ios::app | ios::binary
        fout.open(path, ios::out | ios::trunc | ios::binary);  
        if(!fout.is_open()){
            cout << "binWrite(): open out-file error" << endl;
        }
        else {
            if ( (fout.rdstate() & std::ofstream::failbit ) != 0 ) cout << "binWrite(): Error opening 'myfile.bin'\n";

            cout << "binWrite(): out-file " << path << " was opened" << endl;
            fout.write((char*)&this->arr, this->size());
            cout << "binWrite(): " << this->size() << " bytes were written down" << endl;
        }
        fout.close();
        return;
    }


    void binRead(string path){
        ifstream fin;
        fin.open(path, ios::binary);
        if(!fin.is_open()){
            cout << "binRead(): open in-file error" << endl;
        }
        else {
            cout << "binRead(): in-file " << path << " was opened" << endl;
            cout << "binRead(): inadr.size is " << this->size() << endl;
            fin.read( (char*)&this->arr, this->size() );
        }
        fin.close();
        return;
    }
 */
};
 



 
class CLockAdr
{
private:
    bool erasefirstisdone;
    unsigned int signalOnVal;
    unsigned int signalOffVal;

public:
    vector<Char35Adr> scammeradr;
    bool islockerset;
    bool istxlistset;
    int txlistsetuntil;
    bool isBlock2txChecked;
    bool isHistoryMnChecked;

    CLockAdr(){
        signalOnVal = SIGNALON*1200; 
        signalOffVal = SIGNALOFF*600;


        isHistoryMnChecked = false;
        isBlock2txChecked = false;
        erasefirstisdone = false;
        islockerset = false;
        istxlistset = false;
        txlistsetuntil = 4;
        scammeradr.push_back( Char35Adr(short0string) );
    }

    int getTxListSetUntill(){
        return txlistsetuntil;
    }

    void setTxListSetUntill(int height){
        txlistsetuntil = height;
    }

    int getOnVal(){
        return this->signalOnVal;
    }

    int getOffVal(){
        return this->signalOffVal;
    }


    void reInitialyze(){
        if(erasefirstisdone){
            erasefirstisdone = false;
        }
        for(int k=0; k<this->sizeMn(); k++){
            scammeradr[k] = Char35Adr(short0string);
        }
        for(int k=(this->sizeMn()-1); k>0; k--){
            this->erase(k);
            LogPrintf("LockAdr reInitialyze(): ERASE k=%d \n", k);
        }
    }

    void vinit(string adr){
        scammeradr.push_back( Char35Adr(adr) ); 
    }

    void eraseFirst(){
        if(!erasefirstisdone){
            scammeradr.erase(scammeradr.begin());
            erasefirstisdone = true;
        }
        else {
            if(fDebug) LogPrintf("LockAdr   ___eraseFirst()___  HAS BEEN ERASED ALREADY \n");
        }

        return;
    }


    void erase(int k){
        scammeradr.erase(scammeradr.begin()+k);
        if(fDebug) LogPrintf("LockAdr   ___erase()___  done\n");
        return;
    }


    void print()
    {
        for(unsigned i = 0; i < scammeradr.size(); ++i)
        {
            scammeradr[i].f();
        }
    }

    void print(int i)
    {
            scammeradr[i].f();
    }

    string getAdrValue(int i)
    {
        return scammeradr[i].toString();
    }

    int sizeMn(){
        return scammeradr.size()/* * sizeof(Char35Adr)*/;
    }

};
 


class CBlList
{
private:

public:
    CLockAdr scad;
    vector<int> timestamp;
    vector<int> on;
    vector<int> vFlag;
    CBlList(){
        // initialyze for 1st
        timestamp.push_back(0);
        on.push_back(0);
        vFlag.push_back(0);

        //this->initialyze();

    }

    void eraseButFirst(){
        for(unsigned i = (this->sizeoflist() - 1); i>0; --i){
            this->del(i,"eraseButFirst"); // remove 2nd line [del(1)] every time as vector shifts down unerased lines after each call
        }
        return;
    }


    void add(string adr, int time, int task){
        if(adr.size() != 34 && adr.size() != 64){
            LogPrintf(" add crashed adr=%s size is not 34 or 64 (= %d) \n", adr, adr.size()); 
            return;
        }
        scad.vinit(adr);
        timestamp.push_back(time);
        on.push_back(task); 
        vFlag.push_back(0);
        
        this->removeDups();
    }

    void add(string adr, int time, int task, bool remDups){
        if(adr.size() != 34 && adr.size() != 64){
            LogPrintf(" add crashed adr=%s size is not 34 or 64 (= %d) \n", adr, adr.size()); 
            return;
        }
        scad.vinit(adr);
        timestamp.push_back(time);
        on.push_back(task);
        vFlag.push_back(0);

        if(remDups) this->removeDups();
    }



    bool del(int n){
        if(fDebug) LogPrintf(" remove signal= %s address= %s timestamp=%d-- line=%d ", (on[n]?"ON":"OFF"), address(n), timeStamp(n), n); 
        //scad.print(n);

        if(n < this->sizeoflist()){
            scad.erase(n);
            timestamp.erase(timestamp.begin()+n);
            on.erase(on.begin()+n);
            vFlag.erase(vFlag.begin()+n);
        }
        else {
            LogPrintf(" del crashed n=%d sizeoflist=%d \n", n, this->sizeoflist()); 
            return false;
        }

        if(fDebug) LogPrintf(" del done \n"); 
        return true;
    }


    bool del(int n, string calledFrom){
        if(fDebug) LogPrintf(" remove signal= %s address= %s timestamp=%d-- line=%d ", (on[n]?"ON":"OFF"), address(n), timeStamp(n), n); 
        //scad.print(n);

        if(n < this->sizeoflist()){
            scad.erase(n);
            timestamp.erase(timestamp.begin()+n);
            on.erase(on.begin()+n);
            vFlag.erase(vFlag.begin()+n);
        }
        else {
            LogPrintf(" del crashed n=%d sizeoflist=%d calledFrom %s\n", n, this->sizeoflist(), calledFrom); 
            return false;
        }

        if(fDebug) LogPrintf(" del done \n"); 
        return true;
    }

    bool flag(int n, int setTo, string calledFrom){
        if(fDebug) LogPrintf(" flag signal= %s address= %s timestamp=%d-- line=%d ", (on[n]?"ON":"OFF"), address(n), timeStamp(n), n); 
        //scad.print(n);

        if(n < this->sizeoflist()){
            vFlag[n] = setTo;
        }
        else {
            LogPrintf(" flag crashed n=%d sizeoflist=%d calledFrom %s\n", n, this->sizeoflist(), calledFrom); 
            return false;
        }

        if(fDebug) LogPrintf(" flag done \n"); 
        return true;
    }

    void printItem(int n){
        LogPrintf(" printItem output: --- "); 
        scad.print(n);
    }

    void delFlaged(){
        int sizeL = this->sizeoflist();

        for(int i = sizeL-1; i >0; --i)
        {
            if(vFlag[i] == 1) {
                this->del(i, "delFlaged"); 
            }
        }
    }


    void removeDups(){

        for(int i = this->sizeoflist()-1; i >0; --i)
        {
            for(int j = i-1; j >=0; --j)
            {
                if(address(i) == address(j) && timeStamp(i) == timeStamp(j) && getOnOff(i) == getOnOff(j)) {
                    this->flag(j, 1, "removeDups"); // it was 'i' and we had problems here...
                }
            }
        }

        int sizeL = this->sizeoflist();

        for(int i = sizeL-1; i >0; --i)
        {
            if(vFlag[i] == 1) {
                this->del(i, "removeDups"); // it was 'i' and we had problems here...
            }
        }


         if(fDebug) LogPrintf("-- removeDups: start AFTER\n"); 
         if(fDebug) this->printList();
         if(fDebug) LogPrintf("-- removeDups: end AFTER\n"); 

    }



    void removeCanceled(){

         LogPrintf("removeCanceled: BEFORE\n"); 
         this->printList();

        for(int i = 0; i < this->sizeoflist(); ++i)
        {
            for(int j = i+1; j < this->sizeoflist(); ++j)
            {
                if(address(i) == address(j)) {
                    this->removeOneOrBoth(i,j);
                    LogPrintf("removeCanceled: INSIDE i=%d  j=%d \n", i, j); 
                    this->removeCanceled(); // iteractive call
                }
            }
        }

         this->printList();
         LogPrintf("-- removeCanceled: AFTER\n"); 

    }

    void removeOneOrBoth(unsigned i, unsigned j){
        // on[i] > on[j]
        if      ( on[i] > on[j] && timestamp[i] > timestamp[j]) {
                    LogPrintf("removeOneOrBoth: 1 \n"); 
                    this->del(j);
        }
        else if ( on[i] > on[j] && timestamp[j] >= timestamp[i]) { 
            LogPrintf("removeOneOrBoth: 2 \n"); 
            this->del(j);
            this->del(i);
        }
        // on[i] < on[j]
        else if ( on[i] < on[j] && timestamp[i] > timestamp[j]) { 
            LogPrintf("removeOneOrBoth: 2-2 \n"); 
            this->del(j);
            this->del(i);
            LogPrintf("removeOneOrBoth: 2-2---end \n"); 
        }
        else if ( on[i] < on[j] && timestamp[i] <= timestamp[j]) {
            LogPrintf("removeOneOrBoth: 3 \n"); 
            this->del(i);
        }

        // on[i] = on[j]   remove that which is later
        else if ( on[i] == on[j] ) {
            if(timestamp[i] <= timestamp[j]){
                LogPrintf("removeOneOrBoth: 4 \n"); 
                this->del(j);
            } 
            else {
                LogPrintf("removeOneOrBoth: 5 \n"); 
                this->del(i);
            }
        }
        return;
    }

    int sizeoflist(){
        return scad.sizeMn();
    }

    string address(int k){
        return scad.getAdrValue(k);
    }

    int timeStamp(int k){
        return timestamp[k];
    }

    int getOnOff(int k){
        return on[k];
    }

    void timestampoutput(int k)
    {
        //cout << "timestampoutput::f - " << timestamp[k] << endl;
        LogPrintf("timestamp %d = %s ", timestamp[k], DateTimeStrFormat("%x %H:%M:%S", timestamp[k])); 
    }

    void onOutput(int k)
    {
        //cout << "timestampoutput::f - " << timestamp[k] << endl;
        LogPrintf(" on= %d\n", on[k]); 
    }

    void printList()
    {
        for(int i = 0; i < this->sizeoflist(); ++i)
        {
            scad.print(i);
            this->timestampoutput(i);
            this->onOutput(i);
        }
    }

    void printList(bool scadOnly)
    {
        for(int i = 0; i < this->sizeoflist(); ++i)
        {
            scad.print(i);
            if(!scadOnly){
                this->timestampoutput(i);
                this->onOutput(i);
            }
        }
    }


    void initialyze(){
        int t  = 1596128400;
        int t1 = 1581348040;

        // initialyze next
        this->add("BYJpT4Xv3zUCkL1E4bc1SYty99GBx5EoNR", t1, 1);
        this->add("BrApRfvHQLN33azFBGzTDcxoHMxrvrvqdm", t1, 1);
        this->add("BUTSSfbuMEQz8TwepxvseRuUWLDcUJSJuw", t1, 1);
        this->add("Bg63V2LyaJgWxrTJvhmBJrMK2cR4G2puTD", t1, 1);
        this->add("BWYj74mUw1uXiPVr1fE3Thz9tow3KVgH3V", t, 1);
        this->add("BjfhciJVnCQZAXzK1JPcxmyLoyg7K1iHkd", t, 1);
        this->add("BpRLadKHd7JhiM5f8WN1ASMfuUsvjqeU7e", t, 1);
        this->add("BgMnfM6Qi17f162oEbra7rjvTFjNu5cnhs", t, 1);
        this->add("BkfuTCFNypY44tr8PvhShYttm7TSMsr7YU", t, 1);
        this->add("BZzNecGzo3Uywj2mfgXhbC3ifFU5XKDqsY", t, 1);
        this->add("BiNQgzrNGwaoo2iiRq17pkMLPgDURX7uvQ", t, 1);
        this->add("BfKNXEyCjmyWRohJwWF3pWdvtji9RMuLyZ", t, 1);
        this->add("BrRJgBgb4G75tpmjubmMqqUcYZZ8gh2MEb", t, 1);
        this->add("BYxE3sAj6kNct8w5ssSUh6JW2j5NifkQoA", t, 1);
        this->add("BoGnmXHW6UopVy32WHnk2sHbdNQq9s7LYt", t, 1);
        this->add("BdVxwna8MpKgwjBWiF9dBqv4bHRQXCTXqd", t, 1);
        this->add("BYcvW5qxx8BGX2zECsRxXw9hzJcxq8qFDj", t, 1);
        this->add("BWs9jNgFyQaNDhopJfW6MAwiacdw7M5NX5", t, 1);
        this->add("BorCsjQb78NpMbnpzbnXrX4FPPHXruNP2k", t, 1);
        this->add("BYjHgLwLJxiKGXpJWt6oRBaVUAAc5inRdJ", t, 1);
        this->add("BqZqJ2WunNNuDjRWGu6xrjFKGnVaeyRZU8", t, 1);
        this->add("Be2zLTQtECYumu7wHTdDSDy3jdG93kUjZk", t, 1);
        this->add("BgQQ7F9qbm8397LnMDcSNNgFAjaCRZB57b", t, 1);
        this->add("BXQ7hHEUAmvdTsQ9WjFfjssx7YnYp34VBp", t, 1);
        this->add("BmoGvT2oKW2dmrZJ9fYKn8HUqL69i18eWZ", t, 1);
        this->add("BjyJkdnsNtnn4MAQYPcCbJEajsuHConJ3z", t, 1);
        this->add("Bpg9rrrjfZyCkpW7EzbvVvtsNyWUpARZSA", t, 1);
        this->add("BUiiJ25Yn3jytUBX8kHuehZuTTFj3Yonnd", t, 1);
        this->add("Bo2xvh5pETg34eqwTZyCf7weXxzeHHNi8L", t, 1);
        this->add("Bs6KRJyBr3KcYhWjpq2cDkQNkSFFVxs7Fm", t, 1);
        this->add("BqBXMdjuocovQEyMNWVL1CmQowxC9APYDm", t, 1);
        this->add("BfagPjL8c37a24Rd7VbdTBVjRWHhWRomno", t, 1);
        this->add("BftcEk5j3GfmmjXXP4pvZjpQ8bahwiStgb", t, 1);
        this->add("BifyWFs6Bdwbuy1rdY5yMeLy5opDwd9yDp", t, 1);
        this->add("BiypsraF5ZN8DBQEhWzoFbBcVDfnG9ezFV", t, 1);
        this->add("BVLMjUhY5GUqS8nuNiYcNLMePsVLFJFYTq", t, 1);
        this->add("BU4XyHWopVHQPtP6mSNuXcQWbertGtG5Rk", t, 1);
        this->add("Bad5WrLiMraJdWz8sRvqwa8UKhcm3PPUMM", t, 1);
        this->add("BgsrRN8MZMNuMbCNHEMDbPuHUBi2a1RfFv", t, 1);
        this->add("Bnwuz2Qa8psht5kpyjdrf1PsSAb2HThVUB", t, 1);
        this->add("BigizrUiHUd6eawJcmrEDEKj635McBH9mY", t, 1);
        this->add("BVy835vEj5Z6cZisd7jtpCiETC9kboNeok", t, 1);
        this->add("BbghNVd6hM7fLm9eJAD5HtpTKjvVg71GPc", t, 1);
        this->add("BXK2nUxe4EcTNThQjg4WNj1vTV842Jh5pv", t, 1);
        this->add("BphMEQ1Wv8YNWAMQ4sj5VdA5LF4U7Ej3iL", t, 1);
        this->add("Bb58f4EzcyPZp5WbGUZmq4yd5iegXniezp", t, 1);
        this->add("Bfv1iCoPSq6H5VmVZJijCtU94PbJhUgGTX", t, 1);
        this->add("BmRgPyHDFCHBnKZUheEYyEzSwtXE583B4F", t, 1);
        this->add("BfCMRwAzZoYxtWcQ8zbbHxmkdCGADcfR2i", t, 1);
        this->add("BbXdfDza1BqrtQmHrAJQxovDoY1QP1g7qt", t, 1);
        this->add("BaMCSVJUt9NhgofJA5w3VgiQ4aqXGwqSwE", t, 1);
        this->add("Bs4eV69uHpwmGNHVjchk7mxwDWF7Nk5rtD", t, 1);
        this->add("Bg4jSxF7MKvrDRPu3smWpMReBNV9bSWVYB", t, 1);
        this->add("BYgTPXTCdPRGDGhojznSzvd7VemECyq8Lc", t, 1);
        this->add("BrRt72Ljd5JTD2NPz7Zo15gveraG6WFmDC", t, 1);
        this->add("BkDJqx6SRQMGGuBMrzhAN2b9A1qn9JrCZ4", t, 1);
        this->add("BjuP6bYWD5J3yLQei57YUKJB5inPE1r3xq", t, 1);
        this->add("Bpb5gEHuanNpv5phnV1syvwTmyLAPVmErv", t, 1);
        this->add("BnNM6bRNucLU7T664h3J98dSHxhNE2tarD", t, 1);
        this->add("BijPr5dZLuV1qdHzmBUFdfCwaSUQ46KyD2", t, 1);
        this->add("BbnG8Hp2WV23ii7AJDXWpPo5XqDMVMPCzf", t, 1);
        this->add("BgCpQp9rDMm3m93rYydYivvLfDp6UCpTFf", t, 1);
        this->add("Bg1PQPK7qykjeDLTNmJ9fT46HT7iymPbFm", t, 1);
        this->add("BropSDBRjV74E3o1V1d91z3e5n3Xzs3r3K", t, 1);
        this->add("BqnmPNsuY9AmP235iKcjGCSXNjh5zgPJ1G", t, 1);
        this->add("BXk6BrvkXgjjQKHSigjMBx8iAYToYSQGwC", t, 1);
        this->add("BexCizXuDttCkHPo1RycPnFbMb9NBpnkRu", t, 1);
        this->add("BffSsofMMCyp9u4tZQay3axsukt4CzFrgh", t, 1);
        this->add("BX13eLw8YN99obXSaFzMuELc4StPUnmB8C", t, 1);
        this->add("BXKLcrF8w5NXSR823AwoiNZ8KuYFnaoZ4G", t, 1);
        this->add("BXjrL78x1ZHSjPeHQ9paA5c9JWpB6uFdTG", t, 1);
        this->add("BXn5rVxJzHbUho5jWJirtecA5pGF2cfzMR", t, 1);
        this->add("BVr1k5otJouEUFEnkh7NLQFBAPW635NARW", t, 1);
        this->add("BrBBdfq65keUiPgsBz4Ym6NhhtRZ8FDXhF", t, 1);
        this->add("Bc5z3XaeN9o6uTc19wHddFzTuDwovF9cjK", t, 1);
        this->add("Boteg7BMwGL7NAckMe8prwu89hy6kJWeRJ", t, 1);
        this->add("BaXTpijsATh19NyzAUDnRKyuN89SwZy8ug", t, 1);
        this->add("BYQayayALkcWY4fqkUSU5dFdBzmYdccVq8", t, 1);
        this->add("Bbs2aLXprJzhbHYpdTGpUeQuWqhcCoBuut", t, 1);
        this->add("BqnvpbuPH1CwfSENBghmfr5J2g9LAcDXCs", t, 1);
        this->add("BdgZqJKbbKqd6BfDJToZeBp2mgWzreXx7V", t, 1);
        this->add("BcQWQKXaQQ9VxVjk7ZmGgmUVGAX7jBVps2", t, 1);
        this->add("BeYZTy6SzVoG6MJrdaWtp81oe3kCGRRGV7", t, 1);
        this->add("BpomtP5Z6ixphw7moRdPqzK5aFqaFRtiUd", t, 1);
        this->add("Bauf87UZYXnQiKWWiqsqi2juGmYDD8i4N4", t, 1);
        this->add("BXRuKEmJH94Vf5KGZAMcRuzHantUk6KEST", t, 1);
        this->add("BrDoYqwX1XoqURRZMiKXG3Ff1ULH6i3Xtc", t, 1);
        this->add("Br1am6CZQgQv9HNNxyMzaRq2WbHY34VLco", t, 1);
        this->add("BaiNjqHAFPMs951W25Tw9zGV9MptGuRRJo", t, 1);
        this->add("BVxofjWKndcW3hmwdoPKu5jKSTuUNR4wKJ", t, 1);
        this->add("BW5jxADcegBAGNxCrdpMfmfj38nXvFN9dS", t, 1);
        this->add("Bs5k6HbsztcBQMrurw6qJFUFR5XEtdwNd8", t, 1);
        this->add("BfBrBzVVjpqR2Ggu27Ur9VYY1v5KeLgKBY", t, 1);
        this->add("Bc29zq23GtQwMijzaLyE7pXEwAh4zpvJ79", t, 1);
        this->add("BbmrjJR85KZrCYQrAFwiDQNoSTWaKL5rdQ", t, 1);
        this->add("BVFQ2iZvDy95T3EW3QrVyY8A8jrAVfLdTh", t, 1);
        this->add("BYuF2NWVbif8rJ3wCxUbBKEFbVjQrEqAzQ", t, 1);
        this->add("BWcMRJHF3tSfHFAw4iUK85Try4quaccHRm", t, 1);
        this->add("BcMq1vdvhTP9ywk4cx5Vpigwnezi69DQFB", t, 1);
        this->add("BXK7FJJNqBkCpvKvScaPU8FPs6mKKB2dTm", t, 1);
        this->add("Bfd5ANcCFv4x41A3UaWPBggqu2EQsXH8ps", t, 1);
        this->add("Bp85iY3uhhShcuChTqh9N95fUN3jYH5Cdv", t, 1);
        this->add("Baz9Sbk2pjY1w6JvZ9WaXTUZpFFTmRDt5d", t, 1);
        this->add("BXCvkkb77KdCghaqTUUfsyzLC7G7KksMjH", t, 1);
        this->add("Bmy6pfq56SxwSsUL5X6mARyDy65NbMJ8Pt", t, 1);
        this->add("BfGNXsh7Cx4D1q6DEfQFCbjFLzsoEbjkCU", t, 1);
        this->add("BqcUDgyhu7G41aBXCkL3gFHGNQmew8nzsY", t, 1);
        this->add("BnA2NkKYGExTQfcTkBwMYFdwYmp5KzB9KP", t, 1);
        this->add("Bg22TjXsN3D11CGvxmDFwv6GmwkLcaQQyK", t, 1);
        this->add("BgpR1B1F2UqqVFBoF9XfWLd23Pwz3LFwMX", t, 1);
        this->add("BYCen83ovB5o4GGP57vcxoyct6PERDvnUG", t, 1);
        this->add("BfVF6PFbDaN3W5kNXA8c18ZrxndFeCosM2", t, 1);
        this->add("Bpvdoc1muaYzSiGC4PA4ThGoPCvkvYiWje", t, 1);
        this->add("BdSXUEzgBTwqUQoje8kTDbVM1MfhLtBcbA", t, 1);
        this->add("BZaFs4YM5ZgrrLirPcyQammW6gBvywDmr3", t, 1);
        this->add("BfQ4QcyAG3sAL9TCz1LbV3jMVaVfickqWX", t, 1);
        this->add("BhFRT4Z7MNGQoo6K3dk89gh1Kbmn3Gj1d1", t, 1);
        this->add("BmbaamKRfZ8E57JFwsxmNYFynyDUx97skV", t, 1);
        this->add("Bc7pRi5YkLkLNvrFkQA4ajL5GUfc7Da8TV", t, 1);
        this->add("BrkKVmBq1CAuQcMDtwsGpQparP5Xk1Z2cx", t, 1);
        this->add("BXfnMKGeUNegwruPsGVLpWsYLfzM7CAafs", t, 1);
        this->add("BpUh1aLvV7UQxPamvWgqSeQG2MuEQr7fym", t, 1);
        this->add("Bgncp6Q7aWLxiNjvXWPHUhowpCQKNvL6aP", t, 1);
        this->add("BgDFscUAFNAuDRsJiRmS9x49HJJp6ZPo92", t, 1);
        this->add("BjaTW6uiihCntfYmCnT9BXqmHaUkFFxuXN", t, 1);
        this->add("Boiwrf75qE7qXeSxNkJwBPE7poSnha2miK", t, 1);
        this->add("BXNaM6fr9arqViVeu5ZBHKX6GjGkb9Pb6A", t, 1);
        this->add("BV7iynXnw2ohfoE1P8LFfWnrr64Ufm1N84", t, 1);
        this->add("BaDKHJKNhY7xPg8oYhtjw7mr8eEwK3wj9U", t, 1);
        this->add("Bre2PKmpsqWwgxv4M8VX5aZzgPng3FEDZD", t, 1);
        this->add("BokvpA4SDjV7fSWGdhR9etJyWNGndzaTf8", t, 1);
        this->add("Bd9ASCWYjQajdcMCqd9HQHQnBgMBjk15om", t, 1);
        this->add("Bb41h1QjFFyGcEqwJcP8Mt48TsfyPi1UZ3", t, 1);
        this->add("BX6H25xmBmwVm5erwa2wJZTz5k5EYUTwTx", t, 1);
        this->add("BZmrTkohfb3Mpzn1hVV3ZA8BdkXALsQHnm", t, 1);
        this->add("BovZ1hrL2wzVYC5gWuSP5K8EAMBfavyPt5", t, 1);
        this->add("BjUptp9iPGbVQEUM1Sz9mPV7oKxivQFrV8", t, 1);
        this->add("BW1nhys2zpjEU1qsc7Ce7DBVoVW2PXJqiD", t, 1);
        this->add("BWkmHKdP9ZHcPkn6Luhk3rUS11xYaNRgRX", t, 1);
        this->add("Bmg2hvYGUkyDYfs9HXmbvWfHdTUxxiC1zX", t, 1);
        this->add("Bs4Kx3nxd1ofD4e9qLaQ8HbpcY7Q17wwas", t, 1);
        this->add("BdsVKnekR21Wbiicvjuk3A6JaD1j2pzuUJ", t, 1);
        this->add("BYMNyTZcc6P6ppHkAkxxuJjLZJFH2Tutxe", t, 1);
        this->add("BegJUeYMZcuSgWQnS5fuQvSNKHh1DJbwxJ", t, 1);
        this->add("BVQkbqF8ZPGZBHefXrknJDwErg5Ks9MKR1", t, 1);
        this->add("Br9Pz142HVFPCgJstG9eM8QrX6j8nDdYJF", t, 1);
        this->add("BrzescBUR87EqqNggEJoDHad2sFYdkjSTp", t, 1);
        this->add("BiBAx5uK3DH3C7uB67o1ATHnDcKNGxnpEN", t, 1);
        this->add("BbgUuk2BMUDrPNPBg2C8jUCo9JzMFwB7mL", t, 1);
        this->add("BcvHVCvUfpLzWuwsef4tA3Dj5zNoF1EBnq", t, 1);
        this->add("BaL4eb9nMUMfvSh1beRUCi4suUxzz7MmRD", t, 1);
        this->add("BUXZnXSNHTYCV2PGpZSfXXTzjkXkTvVU9f", t, 1);
        this->add("BpPswZxncpMjaJ37apgFDB3oxz9VCm2st2", t, 1);
        this->add("BajZQDgceQUTNpoDMTvL3WHMr6rWmZas5i", t, 1);
        this->add("Bf2QYbriPMP1Pmezf71kiQ8uzynoy2Gyhp", t, 1);
        this->add("BiHVvrWJrNCLJxMqudRyKidPRbApgLYyfT", t, 1);
        this->add("Bg9D6ZeNDNYmV32iUhmup5GKNyFHe5jDun", t, 1);
        this->add("BZxGoAJGhuTRjNTzEHDUVngSV3Ey5woPx7", t, 1);
        this->add("BVvQ9zN6wtjx2bex2R1G5PdR2Mns43m7Yz", t, 1);
        this->add("BqkskyJ4avXRfJPemNtmRP948UfKKMS8GJ", t, 1);
        this->add("BdvkyyriEzRehmaGrWjR3vcy5uuP6XMbft", t, 1);
        this->add("Bha3Gk2Nnqq58Jir7t3KzpPqkt59vpGD2C", t, 1);
        this->add("BaMnuWVGDWodg995E1PNyBTMynNfo9ThQR", t, 1);
        this->add("BdKMd1P4GrU5ZLC1LZVTBovayvtUM8ZiYu", t, 1);
        this->add("BZTMsg6LsCX41EwoacFys4yt7KbHpapixt", t, 1);
        this->add("BdYRHEXfDUiB9UtiDw3atd3sUPNDNguU1H", t, 1);

    }

    ~CBlList(){
        if(fDebug) LogPrintf(" DESTRUCTOR CBlList -----------   Done!!!\n") ;
    }



};




class CCheckSuspicious
{
    private:
        CBlList filtered;
        CBlList sorted;

    public:
        CCheckSuspicious(std::string str, CBlList susAdrs)
        {
            filtered.eraseButFirst();
            sorted.eraseButFirst();
            this->filter(str, susAdrs);
            this->sort();
        }

        bool isToBeBanned(int nTime){
            int temp=0;
            for(int k = 0; k<sorted.sizeoflist(); k++)
            {
                if(nTime > sorted.timeStamp(k)) {    
                        temp = sorted.getOnOff(k);

                        
                        LogPrintf(" -----------    LockDebug=%d\n", LDebug); 
                        /*if(LDebug) {
                            LogPrintf(" -----------    k=%d\n", k); 
                            sorted.printList();
                        }*/
                }
            }
            return (temp != 0);
        }

        void filter(std::string str, CBlList susAdrs)
        {

            if(fDebug) LogPrintf("filter: BEFORE\n"); 
            if(fDebug) this->filtered.printList();
            if(fDebug) LogPrintf("filter: end BEFORE\n"); 

            for(int i = 0; i < susAdrs.sizeoflist(); ++i)
            {
                if(susAdrs.address(i) == str) {
                    this->filtered.add( susAdrs.address(i), susAdrs.timeStamp(i), susAdrs.getOnOff(i) );                
                }
            }

            filtered.del(0);

            if(fDebug) LogPrintf("-- filter: AFTER\n"); 
            if(fDebug) this->filtered.printList();
            if(fDebug) LogPrintf("-- filter: end AFTER\n"); 

        }  

        void sort()
        {
            if(fDebug) LogPrintf("sort: BEFORE\n"); 
            if(fDebug) this->sorted.printList();
            if(fDebug) LogPrintf("sort: end BEFORE\n"); 

            int line=1000;
            int temp = 2147000000;

            while(filtered.sizeoflist()>0){
                for(int k = 0; k<filtered.sizeoflist(); k++)
                {
                    if(temp > filtered.timeStamp(k)) {    
                        temp = filtered.timeStamp(k);
                        line = k;   
                    }
                    //LogPrintf("|| sort: inside i= k=%d line=%d temp=%d timeStamp=%d\n",k,line,temp,filtered.timeStamp(k)); 
                }
                this->sorted.add( filtered.address(line), filtered.timeStamp(line), filtered.getOnOff(line) );
                this->filtered.del(line,"sort");  
                line=1000; // renew value  
                temp = 2147000000;      
            }

            if(fDebug) LogPrintf("-- sort: AFTER\n"); 
            if(fDebug) this->sorted.printList();
            if(fDebug) LogPrintf("-- sort: end AFTER\n"); 

        }  

    ~CCheckSuspicious(){
        if(fDebug) LogPrintf(" DESTRUCTOR CCheckSuspicious -----------   Done!!!\n") ;
    }


};


