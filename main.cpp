#include "lab.h"
#include <vector>
#include <memory>
#include <limits>

using namespace std;


unique_ptr<MobileOS> loadOS(ifstream& fin) {
    string type;
    if (!(fin >> type)) {
        return nullptr; 
    }

    if (type == "ANDROID") {
        auto os = make_unique<AndroidOS>();
        os->readFromFile(fin);
        return os;
    }
    else if (type == "IOS") {
        auto os = make_unique<IOS>();
        os->readFromFile(fin);
        return os;
    }
    else {
        throw runtime_error("Unknown OS type in file: " + type);
    }
}

int main() {
    vector<unique_ptr<MobileOS>> systems;

    try {
        cout << "=== Input mobile operating systems (Android, iOS) ===\n";

        AndroidOS android;
        android.input();

        IOS ios;
        ios.input();

       
        systems.emplace_back(make_unique<AndroidOS>(android));
        systems.emplace_back(make_unique<IOS>(ios));

        
        ofstream fout("os_data.txt");
        if (!fout)
            throw runtime_error("Failed to open os_data.txt for writing.");

        for (const auto& p : systems)
            p->saveToFile(fout);

        fout.close();
        cout << "\nData saved to file os_data.txt\n";

        
        cout << "\n=== Output from memory ===\n";
        for (const auto& p : systems)
            p->print();

        
        if (*systems[0] > *systems[1])
            cout << "\nFirst OS has a higher market share.\n";
        else
            cout << "\nSecond OS has greater or equal market share.\n";

       
        double totalShare = 0.0;
        double minShare = numeric_limits<double>::max();
        double maxShare = 0.0;

        for (const auto& p : systems) {
            double s = p->getMarketShare();
            totalShare += s;
            if (s < minShare) minShare = s;
            if (s > maxShare) maxShare = s;
        }

        double avgShare = systems.empty()
            ? 0.0
            : totalShare / systems.size();

        cout << "\n=== Market share summary ===\n";
        cout << "Total market share: " << totalShare << "%\n";
        cout << "Average market share: " << avgShare << "%\n";
        cout << "Min market share: " << minShare << "%\n";
        cout << "Max market share: " << maxShare << "%\n";

        
        ifstream fin("os_data.txt");
        if (!fin)
            throw runtime_error("Failed to open os_data.txt for reading.");

        vector<unique_ptr<MobileOS>> loaded;
        while (true) {
            auto os = loadOS(fin);
            if (!os) break;
            loaded.emplace_back(std::move(os));
        }
        fin.close();

        cout << "\n=== Objects loaded back from file ===\n";
        for (const auto& p : loaded)
            p->print();
    }
    catch (const exception& e) {
        cerr << "\nError: " << e.what() << '\n';
    }

    return 0;
}
