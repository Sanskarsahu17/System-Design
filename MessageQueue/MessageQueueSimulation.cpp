#include<iostream>
#include<thread>
#include<condition_variable>
#include<vector>
#include<queue>

using namespace std;

struct MessageType{
    int id;
    string payload;
    MessageType(int id, string payload){
        this->id = id;
        this->payload = payload;
    }   
};

class MessageQueue{
    private:
    queue<MessageType> q_;
    mutex mt;
    condition_variable cv;

    public:

    void send(const MessageType &message){
        lock_guard<mutex> lock(mt);
        q_.push(message);
        cv.notify_one();
    }

    MessageType receive(){
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [this](){ return !q_.empty();});
        MessageType m = q_.front();
        q_.pop();
        return m;
    }


};

void producer(MessageQueue &mq, int messageId, string payload){
    cout<<"Producer: "<<messageId<<" Sending: "<<payload<<endl;
    MessageType m(messageId,payload);
    mq.send(m);
}

void consumer(MessageQueue &mq){
    MessageType m = mq.receive();
    cout<<"Consumer: messageType: "<<m.id<<" Payload: "<<m.payload<<endl;
}

int main(){
    MessageQueue messageQueue;
    thread producerThread(producer,ref(messageQueue), 1, "Email to karthik");
    thread consumerThread(consumer,ref(messageQueue));

    producerThread.join();
    consumerThread.join();


    return 0;
}