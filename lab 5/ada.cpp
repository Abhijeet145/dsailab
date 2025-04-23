#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

class DecisionStump
{
public:
    int feature_index;
    double threshold;
    int polarity;

    void train(const vector<vector<double>> &data, const vector<int> &labels, const vector<double> &weights)
    {
        int num_features = data[0].size();
        double min_error = numeric_limits<double>::infinity();

        for (int feature = 0; feature < num_features; ++feature)
        {
            vector<pair<double, int>> feature_data;
            for (size_t i = 0; i < data.size(); ++i)
            {
                feature_data.push_back({data[i][feature], labels[i]});
            }

            sort(feature_data.begin(), feature_data.end());

            for (size_t i = 0; i < feature_data.size(); ++i)
            {
                double threshold = feature_data[i].first;
                int current_polarity = 1;

                double error = 0.0;
                for (size_t j = 0; j < data.size(); ++j)
                {
                    int predicted = (data[j][feature] <= threshold) ? 1 : -1;
                    if (predicted != feature_data[j].second)
                    {
                        error += weights[j];
                    }
                }

                if (error > 0.5)
                {
                    current_polarity = -1;
                    error = 1.0 - error;
                }

                if (error < min_error)
                {
                    min_error = error;
                    this->feature_index = feature;
                    this->threshold = threshold;
                    this->polarity = current_polarity;
                }
            }
        }
    }

    int predict(const vector<double> &sample)
    {
        if (sample[feature_index] <= threshold)
            return polarity;
        else
            return -polarity;
    }
};

class AdaBoost
{
public:
    vector<DecisionStump> stumps;
    vector<double> alphas;
    vector<double> weights;

    void train(const vector<vector<double>> &data, const vector<int> &labels, int T)
    {
        int n = data.size();
        weights.assign(n, 1.0 / n);

        for (int t = 0; t < T; ++t)
        {
            DecisionStump stump;
            stump.train(data, labels, weights);

            double error = 0.0;
            for (size_t i = 0; i < data.size(); ++i)
            {
                if (stump.predict(data[i]) != labels[i])
                {
                    error += weights[i];
                }
            }

            double alpha = 0.5 * log((1.0 - error) / (error + 1e-10));

            for (size_t i = 0; i < data.size(); ++i)
            {
                if (stump.predict(data[i]) != labels[i])
                {
                    weights[i] *= exp(alpha);
                }
                else
                {
                    weights[i] *= exp(-alpha);
                }
            }

            double sum_weights = 0.0;
            for (double weight : weights)
            {
                sum_weights += weight;
            }

            for (size_t i = 0; i < weights.size(); ++i)
            {
                weights[i] /= sum_weights;
            }

            stumps.push_back(stump);
            alphas.push_back(alpha);
        }
    }

    int predict(const vector<double> &sample)
    {
        double final_score = 0.0;
        for (size_t i = 0; i < stumps.size(); ++i)
        {
            final_score += alphas[i] * stumps[i].predict(sample);
        }
        return final_score > 0 ? 1 : -1;
    }
};

double accuracy(const vector<int> &predictions, const vector<int> &labels)
{
    int correct = 0;
    for (size_t i = 0; i < predictions.size(); ++i)
    {
        if (predictions[i] == labels[i])
        {
            ++correct;
        }
    }
    return (double)correct / predictions.size();
}

int main()
{
    vector<vector<double>> data = {
        {1.0, 2.0},
        {2.0, 3.0},
        {3.0, 3.0},
        {4.0, 5.0},
        {5.0, 6.0}};

    vector<int> labels = {1, -1, -1, 1, 1};

    AdaBoost adaBoost;
    adaBoost.train(data, labels, 10);

    vector<int> predictions;
    for (size_t i = 0; i < data.size(); ++i)
    {
        predictions.push_back(adaBoost.predict(data[i]));
    }

    double acc = accuracy(predictions, labels);
    cout << "Accuracy: " << acc << endl;

    return 0;
}
