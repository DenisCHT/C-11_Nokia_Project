//version: 05.06.18

/*
App is capable to add 1 client to a specific SubNetwork and StateMachine. If SM already has max number of clients,app will search for another
SM from the same SN wich can receive 1 client, if in the same SN no longer exists available SM,app will search in other SN's.
In case that there is no SN and also SM available,clients can not be added anymore.

P.S.:app is not finished 100% ,yet,but till this point is runnable.
*/


#include <iostream>
#include <list>
#include <vector>
#include <memory> //for smart pointers
#include <functional> //for std::function
#include <algorithm>  // for std::for_each----std::find(_if)

#define MaxClients 5

using namespace std;

template<typename T>
ostream& operator << (ostream& os,const std::vector<T>& vect){
    os << "[\n";
        for(unsigned int i=0; i < vect.size() ; i++){
            os <<'\t' << vect[i].subNetwork << "<---->";
            os << vect[i].ipRangeStart << " <---> ";
            os << vect[i].ipRangeStop << " --- ";
            os<<"[";
            os << vect[i].clients;
            os<<"]";
        if(i != vect.size()-1)
                os << endl;
        }
    os << "\n]\n";
    return os;
}

//SM----------------------------------------------------------------------------------------->>
typedef struct SM{
    int subNetwork;
    std::string ipRangeStart;
    std::string ipRangeStop;
    int clients;
    friend bool operator== ( const SM &n1, const SM &n2);
}SM;

bool operator== ( const SM &n1, const SM &n2)
{
        return ((n1.ipRangeStart == n2.ipRangeStart) && (n1.subNetwork == n2.subNetwork));
}
//END_SM------------------------------------------------------------------------------------<<

//NOTIFIER----------------------------------------------------------------------------------------------------------->>
template<class T,class U, class Z>
class Notifier{
private:
    //std::vector<std::shared_ptr<const Watcher<T,U,Z>>> _subscribers;
public:
    //Notifier(){cout << "Notifier object was created.\n";}
    //virtual ~Notifier(){cout << "Notifier object was destroyed.\n";}

    void update() {
        cout << "Notifier was announced by Watcher.From here,it's my job (^_^),Notifier said!\n";
    }
};
template<class T,class U,class Z>
std::shared_ptr<Notifier<T,U,Z>> _nPtr;

template<class T,class U,class Z>
std::shared_ptr<const Notifier<T,U,Z>> _nCPtr;
//END_NOTIFIER--------------------------------------------------------------------------------------------------------<<


//WATCHER----------------------------------------------------------------------------->>
template<class T,class U,class Z>
class Watcher{
private:
   // std::list<std::shared_ptr<StateMachine<T>>> _StateMachinesPtr;
    std::vector<Notifier<T,U,Z>*> _notifiers;
    U _message;
    Z _relevance;
public:
    //Watcher(){cout << "Watcher object was created.\n";}
    //virtual ~Watcher(){cout << "Watcher object was destroyed.\n";}
    void announcedAllNotifiers();

    void verify_SMs_State(){
        cout << "\nWatcher was announced by StateMachine about it's change!\n";
        announcedAllNotifiers();
    }

    void attachNotifier(Notifier<T,U,Z>* n){
        _notifiers.push_back(n);
    }
};
template<class T,class U,class Z>
std::shared_ptr<Watcher<T,U,Z>> _watcherPtr;

template<class T,class U,class Z>
std::shared_ptr<const Watcher<T,U,Z>> _watcherCPtr;
//END_WATCHER--------------------------------------------------------------------------<<


//STATE_MACHINE------------------------------------------------------------------------------------------>>
template<class T,class U,class Z>
class StateMachine{
private:
    std::vector<SM> _container;
    std::vector<Watcher<T,U,Z>*> _watchers;
public:
    //StateMachine(){cout << "StateMachine object was created.\n";}
    //virtual ~StateMachine(){cout << "StateMachine object was destroyed.\n";}

    void announcedAllWatchers();//body of this method is declared below

    void display() const{
        cout << _container;
    }

    void attachWatcher(Watcher<T,U,Z> *w){
        _watchers.push_back(w);
    }

    void attachSM(SM sm){
        _container.push_back(sm);
    }

    bool addSMClient(T nrOfSN,T nrOfSM){
        try {
                auto src = std::find(_container.begin(),_container.end(),_container.at(nrOfSM));
                if((src != _container.end()) && (src->subNetwork == nrOfSN) && (src->clients < MaxClients)){
                    _container.at(nrOfSM).clients += 1;
                    cout << "Client SUCCESSFULLY added to SM >> " << nrOfSM << " << from SUB_NETWORK >> " << nrOfSN << " << !\n";
                }
                else{
                    cout << "SM >> " << nrOfSM << " << from SUB_NETWORK >> " << nrOfSN << " already has maximum number of clients.\n";
                    cout << "Search for closer available one...\n";
                    auto searchCA_SM = searchCloserAvailableSM(nrOfSN);
                    if(searchCA_SM != -1){
                        cout << "Client was SUCCESSFULLY added to another available SM,which is >> "<<searchCA_SM<<" << from SUB_NETWORK >> " << nrOfSN << " << !\n";
                        return true;
                    }else{
                        cout << "There is NO available SM on >> " << nrOfSN << " << sub_network level!\n";
                        return false;
                    }
                }
                announcedAllWatchers();
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
        }
    }

    auto searchCloserAvailableSM(T nrOfSN) -> int{
        auto src = std::find_if(_container.begin(),_container.end(),[&nrOfSN](SM &s){
                            if ((s.subNetwork == nrOfSN) && (s.clients < MaxClients)){
                                return true;
                            }else{
                                return false;
                            }
                          });

        if(src != _container.end()){
            src->clients +=1;
            return (std::find(_container.begin(),_container.end(),*src)) - _container.begin();
        }else{
            return -1;
        }
    }


    int getSN(){
        try{
            auto src = std::find_if(_container.begin(),_container.end(),[this](SM &sm){
                                        if(sm.subNetwork != _container.at(0).subNetwork){
                                            return true;
                                        }else{
                                            return false;
                                        }
                                     });
            if(src != _container.end()){
                return -1; /*If function return -1 means that on same SN entity exist at least 2 different SN codes(SM->subNetwork member) which is not good.
                            Look like i have 2 subnetwork in the same subnetwork which does not make sense.
                            */
            }
            else{
                return _container.at(0).subNetwork;
            }

        }
        catch(const std::out_of_range& oor){
            std::cerr << "Out of Range error: " << oor.what() << endl;
        }
    }
};
template<class T,class U,class Z>
std::shared_ptr<StateMachine<T,U,Z>> _SMPtr;

template<class T,class U, class Z>
std::shared_ptr<const StateMachine<T,U,Z>> _SMCPtr;
//END_STATE_MACHINE-------------------------------------------------------------------------------------------<<



//MASTER_NETWORK--------------------------------------------------------------------->>
template<class T,class U,class Z>
class MasterNetwork{
private:
    std::vector<StateMachine<T,U,Z>*> _subNetworks ;
public:
    //MasterNetwork(){cout << "MasterNetwork was created!\n";}
    //virtual ~MasterNetwork(){cout << "MasterNetwork was destroyed!\n"}

    void attachSubNetwork(StateMachine<T,U,Z>* sn){
        _subNetworks.push_back(sn);
    }

    void addSNClient(T nrOfSN, T nrOfSM){ //SN = sub network, SM = state machine
        auto searchForSN_onMN = searchForSubNetwork_onMasterNetwork(nrOfSN);
        if(searchForSN_onMN != nullptr){
            bool addSNC = searchForSN_onMN->addSMClient(nrOfSN,nrOfSM);
            if(!addSNC){
                cout << "SubNetwork >> " << nrOfSN <<" << could not receive clients anymore !!!\n";
                cout << "Search for closer available SubNetwork...\n";
                int searchCA_SN = -1;
                for(int i=0; i<_subNetworks.size();i++){
                    auto searchCA_SN_aux = searchCloserAvailableSN(i);
                    if((searchCA_SN_aux != -1) && (i != nrOfSN)){
                        searchCA_SN = searchCA_SN_aux;
                        break;
                    }
                }
                if(searchCA_SN != -1){
                        cout << "Client was SUCCESSFULLY added to another available SubNetwork,who has the code >> "<<searchCA_SN<< " << !!!\n";
                    }else{
                        cout << "There is NO available SubNetwork on MASTER NETWORK !!!\n";
                    }
            }
        }else{
            auto src = std::find_if(_subNetworks.begin(),_subNetworks.end(),[](StateMachine<T,U,Z>* &sm){
                                        if(sm->getSN() == -1){
                                            return true;
                                        }else{
                                            return false;
                                        }
                                     });
             if(src != _subNetworks.end()){
                cout << "Was found at least 2 SN CODES on same SN unity of Master Network !!!\n";
             }else{
                cout << "The SubNetwork >> " <<nrOfSN<< " << was not found on Master Network !!!\n";
             }
        }
    }

    auto searchForSubNetwork_onMasterNetwork(T nrOfSN) -> StateMachine<T,U,Z>*{
         auto src = std::find_if(_subNetworks.begin(),_subNetworks.end(),[&nrOfSN](StateMachine<T,U,Z>* &sm){
                                        if(sm->getSN() == nrOfSN){
                                            return true;
                                        }else{
                                            return false;
                                        }
                                     });
         if(src != _subNetworks.end()){
            return *src;
         }else{
            return nullptr;
         }
    }


    auto searchCloserAvailableSN(T nrOfSN) -> int{
        auto src = std::find_if(_subNetworks.begin(),_subNetworks.end(),[&nrOfSN](StateMachine<T,U,Z>* &sm){
                                        if(sm->searchCloserAvailableSM(nrOfSN) != -1){
                                            return true;
                                        }else{
                                            return false;
                                        }
                                     });

        if(src != _subNetworks.end()){
            return (std::find(_subNetworks.begin(),_subNetworks.end(),*src)) - _subNetworks.begin();//true;
        }else{
            return -1; //false;
        }
    }

    void displaySN(){
        for(StateMachine<T,U,Z>* sm : _subNetworks){
            sm->display();
        }
    }

};
template<class T,class U,class Z>
std::shared_ptr<MasterNetwork<T,U,Z>> _MNPtr;
//END_MASTER_NETWORK-----------------------------------------------------------------<<



//------------------------------------------------------------------------------------------>>
MasterNetwork<int,std::string,int> *masterNetwork = new MasterNetwork<int,std::string,int>();
StateMachine<int,std::string,int> *stateMachine = new StateMachine<int,std::string,int>();
StateMachine<int,std::string,int> *stateMachine_2 = new StateMachine<int,std::string,int>();
Watcher<int,std::string,int> *watcher = new Watcher<int,std::string,int>();
Notifier<int,std::string,int> *notifier = new Notifier<int,std::string,int>();
//------------------------------------------------------------------------------------------<<



template<class T,class U,class Z>
std::function<void(StateMachine<T,U,Z>*)> SMClass_display = &StateMachine<T,U,Z>::display;

template<class T,class U,class Z>
std::function<void(Watcher<T,U,Z>*)> watcher_VSMS = &Watcher<T,U,Z>::verify_SMs_State;

template<class T,class U,class Z>
std::function<void(Notifier<T,U,Z>*)> notifierUupdate = &Notifier<T,U,Z>::update;

template<class T,class U,class Z>
void StateMachine<T,U,Z>::announcedAllWatchers(){
    std::for_each(_watchers.begin(),_watchers.end(),[](Watcher<T,U,Z> *w){
                    watcher_VSMS<T,U,Z>(w);
                  });
}

template<class T,class U,class Z>
void Watcher<T,U,Z>::announcedAllNotifiers(){
    std::for_each(_notifiers.begin(),_notifiers.end(),[](Notifier<T,U,Z> *n){
                    notifierUupdate<T,U,Z>(n);
                  });
}


int main(){
    _MNPtr<int,std::string,int>.reset(masterNetwork); //interface for master network object

    _SMPtr<int,std::string,int>.reset(stateMachine);
    _SMCPtr<int,std::string,int> = _SMPtr<int,std::string,int>;  //shared_ptr<T> is convertable to shared_ptr<const T> BUT NOT THE REVERSE

    _watcherPtr<int,std::string,int>.reset(watcher);
    _watcherCPtr<int,std::string,int> = _watcherPtr<int,std::string,int>;

    _nPtr<int,std::string,int>.reset(notifier);
    _nCPtr<int,std::string,int> = _nPtr<int,std::string,int>;

    SM sm1 {.subNetwork = 0, .ipRangeStart = "172.16.254.0", .ipRangeStop = "172.16.254.9", .clients = 1};
    SM sm2 {.subNetwork = 0, .ipRangeStart = "172.16.254.10", .ipRangeStop = "172.16.254.19", .clients = 4};
    SM sm3 {.subNetwork = 0, .ipRangeStart = "172.16.254.20", .ipRangeStop = "172.16.254.29", .clients = 5};

    SM sm4 {.subNetwork = 1, .ipRangeStart = "172.16.254.0", .ipRangeStop = "172.16.254.9", .clients = 1};
    SM sm5 {.subNetwork = 1, .ipRangeStart = "172.16.254.10", .ipRangeStop = "172.16.254.19", .clients = 4};
    SM sm6 {.subNetwork = 1, .ipRangeStart = "172.16.254.20", .ipRangeStop = "172.16.254.29", .clients = 5};


    //stateMachine->attachSM(sm1);
    _SMPtr<int,std::string,int>->attachSM(sm2);
    _SMPtr<int,std::string,int>->attachSM(sm3);

    stateMachine_2->attachSM(sm4);
    stateMachine_2->attachSM(sm5);
    stateMachine_2->attachSM(sm6);

    _SMPtr<int,std::string,int>->attachWatcher(watcher);

    _watcherPtr<int,std::string,int>->attachNotifier(notifier);

    /*
    SMClass_display<int,std::string,int>(stateMachine);
    _SMPtr<int,std::string,int>->addSMClient(0,1); //when call addClient() method all observers will be announced
    SMClass_display<int,std::string,int>(stateMachine);
    _SMPtr<int,std::string,int>->addSMClient(0,1); //when call addClient() method all observers will be announced
    SMClass_display<int,std::string,int>(stateMachine);
    */

    _MNPtr<int,std::string,int>->attachSubNetwork(stateMachine);
    _MNPtr<int,std::string,int>->attachSubNetwork(stateMachine_2);

    _MNPtr<int,std::string,int>->displaySN();
    _MNPtr<int,std::string,int>->addSNClient(0,1);
    _MNPtr<int,std::string,int>->displaySN();
    _MNPtr<int,std::string,int>->addSNClient(0,1);
    _MNPtr<int,std::string,int>->displaySN();
   // _MNPtr<int,std::string,int>->displaySN();

    while(1){
        cout << "\nMenu:\n";
        cout << "\t1.Add client for a specific SubNetwork and StateMachine.\n";
        cout << "\t2.Display all SubNetworks(Which belong to MasterNetwork.)\n";
        cout << "\t0.Exit.\n";
        int optiune,mainSN,mainSM;
        printf("Optiunea este:");
        scanf("%d",&optiune);

        switch(optiune){
            case 1: printf("SubNetwork is:");
                    scanf("%d",&mainSN);
                    printf("StateMachine is:");
                    scanf("%d",&mainSM);
                    _MNPtr<int,std::string,int>->addSNClient(mainSN,mainSM);
                    break;

            case 2:_MNPtr<int,std::string,int>->displaySN();
                    break;

            case 0: exit(EXIT_SUCCESS);
                    break;

            default: cout << "Undefine state!\n";
                    break;
        }
    }

    return 0;
}










