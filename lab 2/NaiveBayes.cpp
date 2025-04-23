#include <bits/stdc++.h>
using namespace std;

class NaiveBayes {
private:
    vector<vector<string>> data;  
    vector<string> labels;             
    map<string, int> label_count;      
    map<string, map<string, int>> word_count_per_label;  
    int total_documents = 0;                     

public:
    
    void train(const vector<vector<string>>& data, const vector<string>& labels) {
        this->data = data;
        this->labels = labels;
        total_documents = data.size();

        for (int i = 0; i < data.size(); ++i) {
            const vector<string>& document = data[i];
            const string& label = labels[i];

            
            label_count[label]++;

            
            for (auto& word : document) {
                word_count_per_label[label][word]++;
            }
        }
    }

    
    double calculate_prior_probability(const string& label) {
        return label_count[label]*1.0/ total_documents;
    }

    
    double calculate_conditional_probability(const string& word, const string& label) {
        int word_count = word_count_per_label[label].count(word) ? word_count_per_label[label][word] : 0;
        int total_word_count_in_label = 0;

        
        for (const auto& pair : word_count_per_label[label]) {
            total_word_count_in_label += pair.second;
        }

        
        int vocabulary_size = 0;
        for (const auto& label_pair : word_count_per_label) {
            for (const auto& word_pair : label_pair.second) {
                vocabulary_size++;
            }
        }

        return (word_count + 1)*1.0 / (total_word_count_in_label + vocabulary_size);
    }

    
    string predict(const vector<string>& document) {
        map<string, double> class_probabilities;

        for (const auto& label_pair : label_count) {
            const string& label = label_pair.first;

            
            double class_prob = log(calculate_prior_probability(label));

            
            for (const string& word : document) {
                class_prob += log(calculate_conditional_probability(word, label));
            }

            
            class_probabilities[label] = class_prob;
        }

        
        string best_label;
        double max_prob = -INFINITY;
        for (const auto& pair : class_probabilities) {
            if (pair.second > max_prob) {
                max_prob = pair.second;
                best_label = pair.first;
            }
        }

        return best_label;
    }
};

int main() {
    
    vector<vector<string>> data = {
        {"buy", "car", "cheap"},
        {"buy", "phone", "expensive"},
        {"buy", "cheap", "phone"},
        {"cheap", "car"},
        {"expensive", "car"},
        {"expensive", "phone", "expensive"}
    };

    vector<string> labels = {
        "electronics", "electronics", "electronics", "automotive", "automotive", "electronics"
    };

    NaiveBayes nb;
    nb.train(data, labels);

    
    vector<string> test_data = {"buy", "expensive", "car"};
    string predicted_label = nb.predict(test_data);
    
    cout << "Predicted label: " << predicted_label << endl;

    return 0;
}
