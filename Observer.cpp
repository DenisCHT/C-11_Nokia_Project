#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Subject{
private:
    std::vector<class Observer *> observers;
    int state;

public:
    int getState(){
        return state;
    }

    void setState(int state){
        this->state = state;
        notifyAllObservers();
    }

    void attach(Observer *observer){
        observers.push_back(observer);
    }

    void notifyAllObservers();

};


class Notifier{
public:
    void notifierAnnounced(const std::string caller) {
        cout << "I was annouced about modifications by << " + caller << " >>\n\n";
    }
};
Notifier *notifierObj;
std::function<void(const std::string)> notifierMethodAddr = std::bind(&Notifier::notifierAnnounced, notifierObj,_1);


class Observer{
protected:
    Subject *subject;

public:
    Observer(Subject *subject){
        this->subject = subject;
        this->subject->attach(this);
    }

    virtual void update()=0;

    Subject *getSubject(){
        return subject;
    }
};


void Subject::notifyAllObservers(){
    for (int i = 0; i < observers.size(); i++)
        observers[i]->update();
}


class BinaryObserver : public Observer{
public:
    BinaryObserver(Subject *subject) : Observer(subject){}

    void update(){
        cout << "BinaryString for integer: " << getSubject()->getState() << endl;
        notifierMethodAddr("BinaryObserver");
    }
};

class OctalObserver : public Observer{
public:
    OctalObserver(Subject *subject) : Observer(subject){}

    void update(){
        cout << "OctalString for integer: " << getSubject()->getState() << endl;
        notifierMethodAddr("OctalObserver");
    }
};


class HexaObserver : public Observer{
public:
    HexaObserver(Subject *subject) : Observer(subject){}

    void update(){
        cout << "HexaString for integer: " << getSubject()->getState() << endl;
        notifierMethodAddr("HexaObserver");
    }
};




int main()
{
    Subject subject;

    BinaryObserver binObs(&subject);
    OctalObserver octObs(&subject);
    HexaObserver hexObs(&subject);

    subject.setState(15);

    return 0;
}








