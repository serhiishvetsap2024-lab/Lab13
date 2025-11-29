#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>


class MobileOS {
protected:
    std::string name;        
    double version{};        
    double marketShare{};    

    struct SecurityInfo {
        std::string encryptionModel; 
        std::string authMethod;      
    } security;

public:
    MobileOS(const std::string& n = "Unknown OS",
        double v = 0.0,
        double share = 0.0,
        const std::string& enc = "none",
        const std::string& auth = "none");

    virtual ~MobileOS();

    
    virtual void input();
    virtual void print() const;
    virtual void saveToFile(std::ofstream& fout) const;
    virtual void readFromFile(std::ifstream& fin);

    
    double getMarketShare() const { return marketShare; }

    
    bool operator>(const MobileOS& other) const;
};



class AndroidOS : public MobileOS {
private:
    int apiLevel{};             
    bool hasGoogleServices{};   

public:
    AndroidOS(const std::string& n = "Android",
        double v = 0.0,
        double share = 0.0,
        const std::string& enc = "File-based",
        const std::string& auth = "Fingerprint",
        int api = 1,
        bool gms = true);

    void input() override;
    void print() const override;
    void saveToFile(std::ofstream& fout) const override;
    void readFromFile(std::ifstream& fin) override;
};



class IOS : public MobileOS {
private:
    std::string deviceFamily; 
    bool hasAppStore{};       

public:
    IOS(const std::string& n = "iOS",
        double v = 0.0,
        double share = 0.0,
        const std::string& enc = "Full-disk",
        const std::string& auth = "FaceID",
        const std::string& family = "iPhone",
        bool store = true);

    void input() override;
    void print() const override;
    void saveToFile(std::ofstream& fout) const override;
    void readFromFile(std::ifstream& fin) override;
};

#endif 
