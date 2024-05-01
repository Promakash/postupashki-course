#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_set>

class KeyValueStorage {
private:
    std::unordered_map<std::string, std::string> storage;
    std::unordered_set<std::string> adresses;
    using storage_iterator = typename std::unordered_map<std::string, std::string>::iterator;
public:
    //Iterator == storage iterator 
    class Iterator{
        private:
            storage_iterator it_;
        public:
            Iterator(storage_iterator it_of_storage){
                it_ = it_of_storage;
            }

            Iterator& operator++(){
                it_++;
                return *this;
            }

            auto& operator*(){
                return *it_;
            }
            
            bool operator!=(const Iterator& rhs){
                return it_ != rhs.it_;
            }
    };
public:
    //Returns result of insertion: false - key was already in storage, true - successful insertion
    bool AddEntry(std::string_view key, std::string_view entry) {
        auto status = storage.insert({(std::string)key, (std::string)entry});
        return status.second;
    }

    //Returns value by key. Throws invalid_argument if found nothing
    std::string GetValue(std::string_view key) {
        //it == storage.end() if found nothing
        auto it = storage.find(std::string(key));
        if (it == storage.end()){
            throw std::invalid_argument("Can't find this key");
        }
        std::string value (it->second);
        return value;
    }

    //Returns set of adresses of gRPC servers
    std::unordered_set<std::string> getAdresses(){
        return adresses;
    }

    //Adds new adress to set of gRPC servers
    void AddReplicaAdress(std::string_view adress){
        adresses.insert((std::string)adress);
    }

    //Removes adress from set of gRPC servers
    void DeleteReplicaAdress(const std::string& adress){
        adresses.erase(adress);
    }

    Iterator begin(){
        return Iterator(storage.begin());
    }

    Iterator end(){
        return Iterator(storage.end());
    }
};
