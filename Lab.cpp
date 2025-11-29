#include "lab.h"
#include <limits>

using namespace std;


MobileOS::MobileOS(const string& n, double v, double share,
    const string& enc, const string& auth)
    : name(n), version(v), marketShare(share) {
    security.encryptionModel = enc;
    security.authMethod = auth;
}

MobileOS::~MobileOS() = default;

void MobileOS::input() {
    cout << "Enter OS name (Android / iOS): ";
    getline(cin >> ws, name);

    cout << "Enter version (e.g. 14.0): ";
    cin >> version;
    if (version <= 0.0)
        throw invalid_argument("Version must be greater than 0.");

    cout << "Enter market share (%) : ";
    cin >> marketShare;
    if (marketShare < 0.0 || marketShare > 100.0)
        throw invalid_argument("Market share must be in [0, 100].");

    cout << "Enter encryption model (no spaces, e.g. FullDisk): ";
    cin >> security.encryptionModel;

    cout << "Enter authentication method (no spaces, e.g. PIN, FaceID): ";
    cin >> security.authMethod;
}

void MobileOS::print() const {
    cout << "OS: " << name
        << ", version: " << version
        << ", market share: " << marketShare << "%"
        << ", encryption: " << security.encryptionModel
        << ", auth: " << security.authMethod << "\n";
}

void MobileOS::saveToFile(ofstream& fout) const {
    if (!fout)
        throw runtime_error("Failed to open file for writing (base).");

   
    fout << name << " "
        << version << " "
        << marketShare << " "
        << security.encryptionModel << " "
        << security.authMethod << "\n";
}

void MobileOS::readFromFile(ifstream& fin) {
    if (!fin)
        throw runtime_error("Failed to open file for reading (base).");

    fin >> name >> version >> marketShare
        >> security.encryptionModel >> security.authMethod;
}

bool MobileOS::operator>(const MobileOS& other) const {
    return marketShare > other.marketShare;
}




AndroidOS::AndroidOS(const string& n, double v, double share,
    const string& enc, const string& auth,
    int api, bool gms)
    : MobileOS(n, v, share, enc, auth),
    apiLevel(api), hasGoogleServices(gms) {
}

void AndroidOS::input() {
    cout << "\n--- Android data input ---\n";
    MobileOS::input();

    cout << "Enter API level (integer, e.g. 34): ";
    cin >> apiLevel;
    if (apiLevel <= 0)
        throw invalid_argument("API level must be greater than 0.");

    int gms{};
    cout << "Has Google Play Services? (1 - yes, 0 - no): ";
    cin >> gms;
    if (gms != 0 && gms != 1)
        throw invalid_argument("Google Services flag must be 0 or 1.");
    hasGoogleServices = (gms == 1);
}

void AndroidOS::print() const {
    cout << "AndroidOS: ";
    MobileOS::print();
    cout << "   API level: " << apiLevel
        << ", Google Services: " << (hasGoogleServices ? "yes" : "no") << "\n";
}

void AndroidOS::saveToFile(ofstream& fout) const {
    if (!fout)
        throw runtime_error("Failed to write AndroidOS to file.");

    
    fout << "ANDROID" << "\n";
   
    MobileOS::saveToFile(fout);
    
    fout << apiLevel << " " << (hasGoogleServices ? 1 : 0) << "\n";
}

void AndroidOS::readFromFile(ifstream& fin) {
    MobileOS::readFromFile(fin);
    int gms{};
    fin >> apiLevel >> gms;
    hasGoogleServices = (gms == 1);
}




IOS::IOS(const string& n, double v, double share,
    const string& enc, const string& auth,
    const string& family, bool store)
    : MobileOS(n, v, share, enc, auth),
    deviceFamily(family), hasAppStore(store) {
}

void IOS::input() {
    cout << "\n--- iOS data input ---\n";
    MobileOS::input();

    cout << "Enter device family (e.g. iPhone, iPad): ";
    getline(cin >> ws, deviceFamily);

    int store{};
    cout << "Has full App Store? (1 - yes, 0 - no): ";
    cin >> store;
    if (store != 0 && store != 1)
        throw invalid_argument("App Store flag must be 0 or 1.");
    hasAppStore = (store == 1);
}

void IOS::print() const {
    cout << "iOS: ";
    MobileOS::print();
    cout << "   Device family: " << deviceFamily
        << ", App Store: " << (hasAppStore ? "yes" : "no") << "\n";
}

void IOS::saveToFile(ofstream& fout) const {
    if (!fout)
        throw runtime_error("Failed to write IOS to file.");

    
    fout << "IOS" << "\n";
   
    MobileOS::saveToFile(fout);
   
    fout << deviceFamily << " " << (hasAppStore ? 1 : 0) << "\n";
}

void IOS::readFromFile(ifstream& fin) {
    MobileOS::readFromFile(fin);
    int store{};
    fin >> deviceFamily >> store;
    hasAppStore = (store == 1);
}
