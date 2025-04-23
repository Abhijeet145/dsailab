#include <bits/stdc++.h>

using namespace std;

double euclideanDistance(vector<double> &point1, vector<double> &point2)
{
    double sum = 0.0;
    for (int i = 0; i < 2; i++)
        sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    return sqrt(sum);
}

double manhattanDistance(vector<double> &point1, vector<double> &point2)
{
    double sum = 0.0;
    for (int i = 0; i < 2; i++)
        sum += abs(point1[i] - point2[i]) ;
    return sum;
}

vector<int> assignClusters(vector<vector<double>> &data, vector<vector<double>> &centroids,int dtype)
{
    vector<int> assignments(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        double minDist = numeric_limits<double>::max();
        int closestCentroid = -1;
        for (int j = 0; j < centroids.size(); j++)
        {
            double dist;
            if(dtype == 0)
                dist = euclideanDistance(data[i], centroids[j]);
            else
                dist = manhattanDistance(data[i],centroids[j]);
            if (dist < minDist)
            {
                minDist = dist;
                closestCentroid = j;
            }
        }
        assignments[i] = closestCentroid;
    }
    return assignments;
}

vector<vector<double>> computeCentroids(vector<vector<double>> &data, vector<int> &assignments, int k)
{
    vector<vector<double>> centroids(k, vector<double>(data[0].size(), 0.0));
    vector<int> counts(k, 0);

    for (int i = 0; i < data.size(); i++)
    {
        int cluster = assignments[i];
        for (int j = 0; j < data[i].size(); j++)
            centroids[cluster][j] += data[i][j];
        counts[cluster]++;
    }

    for (int i = 0; i < k; i++)
        if (counts[i] > 0)
            for (int j = 0; j < centroids[i].size(); j++)
                centroids[i][j] /= counts[i];
    return centroids;
}

void printDistanceTable(vector<vector<double>> &data, vector<vector<double>> &centroids,int dist)
{
    cout << "\nDistance Table:\n";
    cout << "\t";
    for (int j = 0; j < centroids.size(); j++)
        cout << "Centroid " << j << "\t";
    cout << "\n";
    for (int i = 0; i < data.size(); i++)
    {
        cout << "Point " << i << "\t";
        for (int j = 0; j < centroids.size(); j++){
            if(dist == 0)
                cout << euclideanDistance(data[i], centroids[j]) << "\t";
            else
                cout << manhattanDistance(data[i], centroids[j]) << "\t";
        }
        cout << "\n";
    }
    cout << "\nCurrent Centroids:\n";
    for (int i = 0; i < centroids.size(); i++)
    {
        cout << "Centroid " << i << ": ";
        for (auto val : centroids[i])
            cout << val << " ";
        cout << "\n";
    }
}

void kMeans(vector<vector<double>> &data, int k, int maxIterations,int dist)
{
    srand(static_cast<unsigned int>(time(0)));
    vector<vector<double>> centroids(k);
    for (int i = 0; i < k; i++)
        centroids[i] = data[rand() % data.size()];
    vector<int> assignments(data.size());
    for (int i = 0; i < maxIterations; i++)
    {
        printDistanceTable(data, centroids,dist);
        assignments = assignClusters(data, centroids,dist);
        vector<vector<double>> newCentroids = computeCentroids(data, assignments, k);
        if (newCentroids == centroids)
        {
            cout << "Converged in " << i + 1 << " iterations.\n";
            break;
        }

        centroids = newCentroids;
    }
    for (int i = 0; i < data.size(); i++)
        cout << "Point " << i << " is in cluster " << assignments[i] << ".\n";
    cout << "\nFinal Centroids:\n";
    for (int i = 0; i < centroids.size(); i++)
    {
        cout << "Centroid " << i << ": ";
        for (double val : centroids[i])
            cout << val << " ";
        cout << "\n";
    }
}

int main()
{
    vector<vector<double>> data = {
        {1.0, 2.0}, {4.0, 1.8}, {5.0, 8.0}, {8.0, 9.0}, {1.0, 6.6}, {9.0, 11.0}, {10.0, 2.0}, {10.0, 8.0}, {9.0, 3.0}};
    int k = 3;
    int maxIterations = 100;
    kMeans(data, k, maxIterations,0);//using Euclidian distance 
    cout <<".\n.\n.\n.\n.\n.\n";
    kMeans(data, k, maxIterations,1);//using Manhattan distance
    return 0;
}
