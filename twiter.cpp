#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
using namespace std;

class Message {
public:
   string msg;
    int id;
    set<string> likes;
    string username;
    Message(int id, :string msg, string username) : id(id), msg(msg), username(username) {}

    void like(string username) {
        likes.insert(username);
    }

    string toString() {
        stringstream ss;
        ss << "Message " << this->id << ": " << this->msg << "\n - " << username;
        ss << " - likes: " << likes.size();
        return ss.str();
    }

    int getId() {
        return id;
    }
};

class Inbox {
public:
    map<int, Message*> messages;
    map<int, Message*> unread;

    Inbox() {};

    vector<Message*> getAll() {
    vector<Message*> all;
        for (auto const& x : this->messages) {
            all.insert(all.begin(), x.second);
        }
        return all;
    }

    Message* getTweet(int id) {
        return messages[id];
    }

    vector<Message*> getUnread() {
    vector<Message*> all;
        for (auto const& x : this->unread) {
            all.insert(all.begin(), x.second);
        }
        return all;
    }

    void storeMessage(Message* tweet) {
        messages[tweet->getId()] = tweet;
        unread[tweet->getId()] = tweet;
    }

    void storeUnread(Message* tweet) {
        unread[tweet->getId()] = tweet;
    }

    string toString() {
        stringstream ss;
        ss << "Inbox: \n";
        for (auto x : this->messages) {
            ss << x.second->toString() << "\n";
        }
        return ss.str();
    }
};

class User {
    Inbox inbox;

public:
    string name;
    map<string, User*> followers;
    map<string, User*> following;

    User(string name) : name(name) {};

    // Função de seguir novos usuários
    void follow(User* user) {
        following[user->name] = user;
        user->followers[name] = this;
    }

    Inbox getInbox() {
        return this->inbox;
    }

    // Like nos tweets
    void like(int tweetId) {
        inbox.messages[tweetId]->like(name);
    }

    //Adicionando Mensagens no Tweet
    void sendTweet(Message* tweet) {
        this->inbox.storeMessage(tweet);
        for (auto const& x : followers) {
            x.second->inbox.storeUnread(tweet);
        }
    }
    // Deixando de Seguir Usuários
    void unfollow(User* user) {
        following.erase(user->name);
        user->followers.erase(name);
    }

    string toString() {
       stringstream ss;
        ss << "User " << name << "\nFollowers: \n";
        for (auto const& x : followers) {
            ss << x.second->name << " \n";
        }
        ss << "\nFollowing: \n";
        for (auto const& x : following) {
            ss << x.second->name << " \n";
        }
        return ss.str();
    }
};

class Twitter {
    map<string, User*> users;
    map<int, Message*> messages;
    int nxtId = 0;
public:
    Twitter() {};

    // Adicionando usuários
    void addUser(User* user) {
        users[user->name] = user;
    }

    User* getUser(string name) {
        return users[name];
    }
    // Enviar tweet
    void sendTweet(string username, string tweet) {
        messages[nxtId] = new Message(nxtId, tweet, username);
        users[username]->sendTweet(messages[nxtId]);
        nxtId++;
    }

    string toString() {
        stringstream ss;
        ss << "Twitter: \n";
        for (auto const& x : users) {
            ss << x.second->name << "\n";
        }
        return ss.str();
    }
};

int main() {
    cout << "Hello, World!\n";
    Twitter twitter;
    // Adicionando o usuário
    twitter.addUser(new User("diogo"));
    twitter.addUser(new User("dennis"));
    //Enviando um tweet ou uma mensagem para determinado usuário
    twitter.sendTweet("diogo", "Hello");
    cout << twitter.toString();
    // Seguindo o usuário
    twitter.getUser("diogo")->follow(twitter.getUser("dennis"));
    cout << twitter.getUser("diogo")->toString();
    cout << twitter.getUser("diogo")->getInbox().toString();

    // Diogo Ryan Pereira de Souza - 510737
}