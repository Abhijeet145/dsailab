#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Sample {
    double feature;
    int label;
    double weight;
};

struct WeakClassifier {
    double threshold;
    int direction; // 1 if feature >= threshold => +1, else -1
    double alpha;  // classifier weight
};

double calculateError(const vector<Sample>& samples, double threshold, int direction) {
    double error = 0.0;
    for (const auto& sample : samples) {
        int prediction = (sample.feature >= threshold) ? 1 : -1;
        if (direction == -1) {
            prediction *= -1;
        }
        if (prediction != sample.label) {
            error += sample.weight;
        }
    }
    return error;
}

WeakClassifier trainWeakClassifier(vector<Sample>& samples) {
    double minError = numeric_limits<double>::max();
    WeakClassifier bestClassifier;

    for (const auto& sample : samples) {
        for (int direction : {1, -1}) {
            double error = calculateError(samples, sample.feature, direction);
            if (error < minError) {
                minError = error;
                bestClassifier.threshold = sample.feature;
                bestClassifier.direction = direction;
            }
        }
    }

    bestClassifier.alpha = 0.5 * log((1 - minError) / (minError + 1e-10));
    return bestClassifier;
}

void updateWeights(vector<Sample>& samples, const WeakClassifier& classifier) {
    double sumWeights = 0.0;
    for (auto& sample : samples) {
        int prediction = (sample.feature >= classifier.threshold) ? 1 : -1;
        if (classifier.direction == -1) {
            prediction *= -1;
        }
        sample.weight *= exp(-classifier.alpha * sample.label * prediction);
        sumWeights += sample.weight;
    }

    // Normalize weights
    for (auto& sample : samples) {
        sample.weight /= sumWeights;
    }
}

int main() {
    vector<Sample> samples = {
        {1.0, 1, 1.0/5}, {2.0, 1, 1.0/5}, {3.0, -1, 1.0/5}, {4.0, -1, 1.0/5}, {5.0, 1, 1.0/5}
    };

    int numIterations = 10;
    vector<WeakClassifier> classifiers;

    for (int t = 0; t < numIterations; ++t) {
        WeakClassifier classifier = trainWeakClassifier(samples);
        classifiers.push_back(classifier);
        updateWeights(samples, classifier);
        cout << "Iteration " << t + 1 << ": Threshold = " << classifier.threshold
             << ", Direction = " << classifier.direction << ", Alpha = " << classifier.alpha<<endl;
    }

    
    return 0;
}
