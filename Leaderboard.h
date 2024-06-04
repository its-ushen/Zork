#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <algorithm>
#include <QString>
#include <QDebug> // If you want to use qDebug()

template<typename T>
class Leaderboard {
private:
    struct Entry {
        QString playerName;
        T score;

        Entry(const QString& name, T score) : playerName(name), score(score) {}

        // Comparison operator for sorting
        bool operator<(const Entry& other) const {
            return score > other.score; // Assuming you want a descending order
        }
    };

    std::vector<Entry> entries;

public:
    void addEntry(const QString& playerName, T score) {
        entries.emplace_back(playerName, score);
        std::sort(entries.begin(), entries.end());  // Keep entries sorted on each insertion
    }

    void display() const {
        for (const auto& entry : entries) {
            qDebug() << entry.playerName << ": " << entry.score;
        }
    }

    const std::vector<Entry>& getEntries() const {
        return entries;
    }
};

#endif // LEADERBOARD_H
