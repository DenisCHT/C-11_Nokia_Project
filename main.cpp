#include <iostream>
#include <vector>
#include <memory>
#include <list>
#define MaxClients 10

using namespace std;

template<typename T>
ostream& operator << (ostream& os,const std::vector<T>& vect){
    os << "[\n";
        for(unsigned int i=0; i < vect.size() ; i++){
            os <<'\t' << vect[i].ipRangeStart << " ";
            os << vect[i].ipRangeStop << " ";
            os << vect[i].clients;
        if(i != vect.size()-1)
                os << endl;
        }
    os << "\n]\n";
    return os;
}

typedef struct SM{
    std::string ipRangeStart;
    std::string ipRangeStop;
    int clients;
}SM;

ostream& operator << (ostream& os,const SM& sm){
    os << "[";
        os << sm.ipRangeStart << " ";
        os << sm.ipRangeStop << " ";
        os << sm.clients;
    os << "]\n";
    return os;
}


//----------------------------------------------------------------->>
template<class T>
class StateMachine{
private:
    std::vector<SM> container_;
public:
    //methods
    StateMachine(){
        cout << "StateMachine object created.\n";
    }
    virtual ~StateMachine(){
        cout << "StateMachine object destroyed.\n";
    }

    void attachSM(SM c){
        container_.push_back(c);
    }

    void updateOneOfSM(T nrOfSM,T clients){
        try{
            container_.at(nrOfSM).clients += clients;
            announceNotifier();
        }
        catch(const std::out_of_range& oor){
            cout << "Out of Range error occur during the program execution : " << oor.what() << endl;
            exit(EXIT_FAILURE);
        }
    }

    void announceNotifier();

    std::vector<SM> getVector() const{
        return container_;
    }

    void displayVectorContent() const{
        cout << container_;
    }
};

template<class T>
std::shared_ptr<StateMachine<T>> SMPtr_ ;

template<class T>
std::shared_ptr<const StateMachine<T>> SMCPtr_;

//---------------------------------------------------------------------<<


//---------------------------------------------------------------------->>
template<class T, class U, class Z>
class Watcher{
private:
    std::list<std::shared_ptr<StateMachine<T>>> StateMachinesPtr_;
    U message_;
    Z relevance_;
public:
    //methods
    Watcher(){
        cout << "Watcher object created.\n";
    }
    virtual ~Watcher(){
        cout << "Watcher object destroyed.\n";
    }

    void print() const{
        cout << "Watcher(s) was announced!\n";
    }
};

template<class T, class U, class Z>
std::shared_ptr<Watcher<T,U,Z>> watcherPtr_;

template<class T, class U, class Z>
std::shared_ptr<const Watcher<T,U,Z>> watcherCPtr_;
//--------------------------------------------------------------------------<<


//--------------------------------------------------------------------------->>
template<class T, class U, class Z>
class Notifier{
private:
    std::vector<std::shared_ptr<const Watcher<T,U,Z>>> subscribers_ ;

public:
    //methods

    void attachSubscriber(std::shared_ptr<const Watcher<T,U,Z>> subscriber){
        subscribers_.push_back(subscriber);
    }

    void notifyAllWatchers(){
        cout << "I was notified! I will notify watcher(s)\n";
        if(!subscribers_.empty()){
            for(int i=0; i<subscribers_.size();i++){
                subscribers_[i]->print();
            }
        }else{
            cout << "There is no watcher(s)!\n";
        }
    }
};

template<class T, class U, class Z>
std::shared_ptr<Notifier<T,U,Z>> nPtr_;

template<class T, class U, class Z>
std::shared_ptr<const Notifier<T,U,Z>> nCPtr_;
//---------------------------------------------------------------------------<<

template<class T>
void StateMachine<T>::announceNotifier(){
    nPtr_<T,char,char>->notifyAllWatchers();
}



int main(){

    SMCPtr_<int> = std::make_shared<const StateMachine<int>>();
    SMPtr_<int> = std::make_shared<StateMachine<int>>();

    nCPtr_<int,char,char> = std::make_shared<const Notifier<int,char,char>>();
    nPtr_<int,char,char> = std::make_shared<Notifier<int,char,char>>();

    watcherCPtr_<int,char,char> = std::make_shared<const Watcher<int,char,char>>();
    watcherPtr_<int,char,char> = std::make_shared<Watcher<int,char,char>>();

    SM s1 {.ipRangeStart = "0", .ipRangeStop = "10", .clients=7};
    SM s2 {.ipRangeStart = "11", .ipRangeStop = "21", .clients=9};

    cout << s1;
    cout << s2 << endl;




    SMPtr_<int>->attachSM(s1);
    SMPtr_<int>->attachSM(s2);
    cout << SMPtr_<int>->getVector() << endl;
    SMPtr_<int>->updateOneOfSM(0,2);
    nPtr_<int,char,char>->attachSubscriber(watcherCPtr_<int,char,char>);
    SMPtr_<int>->updateOneOfSM(1,-2);


    SMCPtr_<int> = SMPtr_<int>;
    cout << SMCPtr_<int>->getVector();



    return 0;
}







