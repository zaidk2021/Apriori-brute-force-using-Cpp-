#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>

struct Example {
    std::map<std::string, std::string> attributes;
    std::string target;
};


double entropy(const std::vector<std::string>& outcomes) {
    std::map<std::string, int> frequency;
    for (const auto& outcome : outcomes) {
        frequency[outcome]++;
    }
    double entropy = 0.0;
    for (const auto& pair : frequency) {
        double prob = static_cast<double>(pair.second) / outcomes.size();
        entropy -= prob * log2(prob);
    }
    return entropy;
}

double informationGain(const std::vector<Example>& examples, const std::string& attribute, const std::string& target) {
    std::map<std::string, std::vector<std::string>> partitions;
    for (const auto& example : examples) {
        partitions[example.attributes.at(attribute)].push_back(example.target);
    }

    std::vector<std::string> targets;
    for (const auto& example : examples) {
        targets.push_back(example.target);
    }
    double totalEntropy = entropy(targets);

    double weightedEntropy = 0.0;
    for (const auto& pair : partitions) {
        double subsetEntropy = entropy(pair.second);
        weightedEntropy += static_cast<double>(pair.second.size()) / examples.size() * subsetEntropy;
    }

    return totalEntropy - weightedEntropy;
}

int main() {
    
   std::vector<Example> dataset = {
        { {{"Outlook", "Sunny"}, {"Temperature", "Hot"}, {"Humidity", "High"}, {"Wind", "Weak"}}, "No"},
        { {{"Outlook", "Sunny"}, {"Temperature", "Hot"}, {"Humidity", "High"}, {"Wind", "Strong"}}, "No"},
        { {{"Outlook", "Overcast"}, {"Temperature", "Hot"}, {"Humidity", "High"}, {"Wind", "Weak"}}, "Yes"},
        { {{"Outlook", "Rain"}, {"Temperature", "Mild"}, {"Humidity", "High"}, {"Wind", "Weak"}}, "Yes"},
        { {{"Outlook", "Rain"}, {"Temperature", "Cool"}, {"Humidity", "Normal"}, {"Wind", "Strong"}}, "No"},
        { {{"Outlook", "Rain"}, {"Temperature", "Cool"}, {"Humidity", "Normal"}, {"Wind", "Strong"}}, "No"},
        { {{"Outlook", "Overcast"}, {"Temperature", "Cool"}, {"Humidity", "Normal"}, {"Wind", "Strong"}}, "Yes"},
        { {{"Outlook", "Sunny"}, {"Temperature", "Mild"}, {"Humidity", "High"}, {"Wind", "Weak"}}, "No"},
        { {{"Outlook", "Sunny"}, {"Temperature", "Cool"}, {"Humidity", "Normal"}, {"Wind", "Weak"}}, "Yes"},
        { {{"Outlook", "Rain"}, {"Temperature", "Mild"}, {"Humidity", "Normal"}, {"Wind", "Weak"}}, "Yes"},
        { {{"Outlook", "Sunny"}, {"Temperature", "Mild"}, {"Humidity", "Normal"}, {"Wind", "Strong"}}, "Yes"},
        { {{"Outlook", "Overcast"}, {"Temperature", "Mild"}, {"Humidity", "High"}, {"Wind", "Strong"}}, "Yes"},
        { {{"Outlook", "Overcast"}, {"Temperature", "Hot"}, {"Humidity", "Normal"}, {"Wind", "Weak"}}, "Yes"},
        { {{"Outlook", "Rain"}, {"Temperature", "Mild"}, {"Humidity", "High"}, {"Wind", "Strong"}}, "No"}
    };

    std::vector<std::string> attributes = {"Outlook", "Temperature", "Humidity", "Wind"};
    std::string target = "Play ball";
    double maxGain = 0.0;
    std::string bestAttribute;

    for (const auto& attribute : attributes) {
        double gain = informationGain(dataset, attribute, target);
        if (gain > maxGain) {
            maxGain = gain;
            bestAttribute = attribute;
        }
    }

    std::cout << "Best attribute to split on using Information Gain: " << bestAttribute
              << " with an Information Gain of: " << maxGain << std::endl;

    return 0;
}
