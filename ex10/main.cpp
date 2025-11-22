/*
 * ============================================================================
 * ЗАДАЧА: Клас "Избирателен район"
 * ============================================================================
 *
 * Да се дефинира клас Избирателен район.
 *
 * Член-данни на класа:
 *   1) име на района (указател към символен низ)
 *   2) брой гласоподаватели за района
 *   3) брой партии, за които се гласува
 *   4) динамичен масив, съдържащ броят на гласувалите за всяка партия
 *   5) масив от символни низове, съдържащ имената на партиите (инициалите им)
 *
 * Съставете програма, която:
 *   - Създава файл от обекти - избирателни райони.
 *   - Извежда процента гласове за всяка партия по райони, подредени по
 *     азбучен ред на името на района.
 *   - Извежда имената на районите, в които няма победител в изборите.
 *   - Записва имената районите от т. 3, както и процента на негласували
 *     в тях в нов файл.
 * ============================================================================
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class ElectionRegion
{
private:
    char *name_;
    int totalVoters_;
    int partiesCount_;
    int *votesCount_;
    char **partyNames_;

public:
    ElectionRegion(const char *name, const int totalVoters, const int partiesCount = 1)
    {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);

        totalVoters_ = totalVoters;

        int validPartiesCount = partiesCount == 0 ? 1 : partiesCount;
        partiesCount_ = validPartiesCount;
        votesCount_ = new int[validPartiesCount];
        partyNames_ = new char *[validPartiesCount];

        for (int index = 0; index < validPartiesCount; index++)
        {
            partyNames_[index] = nullptr;
            votesCount_[index] = 0;
        }
    }

    ~ElectionRegion()
    {
        delete[] name_;

        for (int index = 0; index < partiesCount_; index++)
        {
            delete[] partyNames_[index];
        }

        delete[] partyNames_;
        delete[] votesCount_;
    }

    const char *getName() const { return name_; }

    void addParty(const char *name)
    {
        for (int index = 0; index < partiesCount_; index++)
        {
            if (partyNames_[index] == nullptr)
            {
                partyNames_[index] = new char[strlen(name) + 1];
                strcpy(partyNames_[index], name);
                return;
            }
        }

        cout << "There is no free space for new party" << endl;
    }

    void addVotes(const int votes, const char *name)
    {
        for (int index = 0; index < partiesCount_; index++)
        {
            if (strcmp(name, partyNames_[index]) != 0)
            {
                continue;
            }

            votesCount_[index] += votes;
            return;
        }

        cout << "There is no such party in order to add votes" << endl;
    }

    void printPartyPercentages() const
    {
        cout << "Region: " << name_ << endl;
        for (int i = 0; i < partiesCount_; i++)
        {
            if (partyNames_[i] != nullptr)
            {
                double percentage = (votesCount_[i] * 100.0) / totalVoters_;
                cout << "  " << partyNames_[i] << ": "
                     << percentage << "%" << endl;
            }
        }
        cout << "  Non-voters: " << getNonVotersCount() << "%" << endl;
    }

    bool hasWinner() const
    {
        for (int index = 0; index < partiesCount_; index++)
        {
            if ((double)votesCount_[index] / totalVoters_ > 0.5)
            {

                return true;
            }
        }

        return false;
    }

    double getNonVotersCount() const
    {
        int votedCount = 0;

        for (int index = 0; index < partiesCount_; index++)
        {
            votedCount += votesCount_[index];
        }

        return ((totalVoters_ - votedCount) * 100.0) / totalVoters_;
    }

    string print() const
    {
        stringstream ss;

        ss << "Name: " << name_ << endl;
        ss << "Total count: " << totalVoters_ << endl;
        ss << "Parties count " << partiesCount_ << endl;

        for (int index = 0; index < partiesCount_; index++)
        {
            ss << "Party: " << partyNames_[index] << " has " << votesCount_[index] << " votes" << endl;
        }

        return ss.str();
    }
};

class ElectionRegions
{
private:
    vector<ElectionRegion *> electionRegions_;

public:
    ElectionRegions() {}

    ~ElectionRegions()
    {
        for (auto region : electionRegions_)
        {
            delete region;
        }
    }

    void addElectionRegion(ElectionRegion *region)
    {
        electionRegions_.push_back(region);
    }

    void printDistrictsWithoutWinner()
    {
        cout << "=== Districts Without Winner ===" << endl;
        for (auto region : electionRegions_)
        {
            if (!region->hasWinner())
            {
                cout << "- " << region->getName() << endl;
            }
        }
    }

    void printVotePercentagesSorted()
    {
        for (int i = 0; i < electionRegions_.size() - 1; i++)
        {
            for (int j = 0; j < electionRegions_.size() - i - 1; j++)
            {
                if (strcmp(electionRegions_[j]->getName(),
                           electionRegions_[j + 1]->getName()) > 0)
                {
                    ElectionRegion *temp = electionRegions_[j];
                    electionRegions_[j] = electionRegions_[j + 1];
                    electionRegions_[j + 1] = temp;
                }
            }
        }

        cout << "=== Vote Percentages by District ===" << endl;
        for (int i = 0; i < electionRegions_.size(); i++)
        {
            electionRegions_[i]->printPartyPercentages();
            cout << endl;
        }
    }

    void saveRegionsToFile(const string &filename) const
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "File cannot be opened" << endl;
            return;
        }

        for (const auto &region : electionRegions_)
        {
            file << region->print();
        }

        file.close();
    }

    void saveDistrictsWithoutWinner(const string &filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << "Districts without winner and non-voter percentage:\n\n";

            for (auto region : electionRegions_)
            {
                if (!region->hasWinner())
                {
                    file << region->getName() << " - Non-voters: "
                         << region->getNonVotersCount() << "%\n";
                }
            }
            file.close();
        }
    }
};

int main()
{
    ElectionRegions system;

    ElectionRegion *sofia = new ElectionRegion("Sofia-Center", 50000, 4);
    sofia->addParty("GERB");
    sofia->addParty("BSP");
    sofia->addParty("DPS");
    sofia->addParty("PP");
    sofia->addVotes(15000, "GERB");
    sofia->addVotes(12000, "BSP");
    sofia->addVotes(8000, "DPS");
    sofia->addVotes(10000, "PP");
    system.addElectionRegion(sofia);

    ElectionRegion *plovdiv = new ElectionRegion("Plovdiv-East", 30000, 4);
    plovdiv->addParty("GERB");
    plovdiv->addParty("BSP");
    plovdiv->addParty("DPS");
    plovdiv->addParty("PP");
    plovdiv->addVotes(16000, "GERB");
    plovdiv->addVotes(5000, "BSP");
    plovdiv->addVotes(3000, "DPS");
    plovdiv->addVotes(4000, "PP");
    system.addElectionRegion(plovdiv);

    ElectionRegion *burgas = new ElectionRegion("Burgas-South", 40000, 4);
    burgas->addParty("GERB");
    burgas->addParty("BSP");
    burgas->addParty("DPS");
    burgas->addParty("PP");
    burgas->addVotes(10000, "GERB");
    burgas->addVotes(9000, "BSP");
    burgas->addVotes(8000, "DPS");
    burgas->addVotes(8000, "PP");
    system.addElectionRegion(burgas);

    ElectionRegion *varna = new ElectionRegion("Varna-Center", 35000, 3);
    varna->addParty("GERB");
    varna->addParty("BSP");
    varna->addParty("PP");
    varna->addVotes(18000, "GERB");
    varna->addVotes(8000, "BSP");
    varna->addVotes(6000, "PP");
    system.addElectionRegion(varna);

    ElectionRegion *staraZagora = new ElectionRegion("Stara-Zagora", 25000, 4);
    staraZagora->addParty("GERB");
    staraZagora->addParty("BSP");
    staraZagora->addParty("DPS");
    staraZagora->addParty("PP");
    staraZagora->addVotes(6000, "GERB");
    staraZagora->addVotes(5000, "BSP");
    staraZagora->addVotes(4000, "DPS");
    staraZagora->addVotes(3000, "PP");
    system.addElectionRegion(staraZagora);

    cout << "=== ELECTION RESULTS SYSTEM ===" << endl
         << endl;

    cout << "1. Saving all regions to file..." << endl;
    system.saveRegionsToFile("all_regions.txt");
    cout << "   Done! Check 'all_regions.txt'" << endl
         << endl;

    cout << "2. Vote percentages by district (alphabetically sorted):" << endl;
    cout << "   ================================================" << endl;
    system.printVotePercentagesSorted();

    cout << "\n3. Districts without winner (no party > 50%):" << endl;
    cout << "   ===========================================" << endl;
    system.printDistrictsWithoutWinner();

    cout << "\n4. Saving districts without winner to file..." << endl;
    system.saveDistrictsWithoutWinner("no_winner_districts.txt");
    cout << "   Done! Check 'no_winner_districts.txt'" << endl;

    cout << "\nProgram completed successfully!" << endl;

    return 0;
}