
#include <cmath>
#include <iostream>
#include "Filters.h"

void Filters::geographicalLocation(Graph *graph, double lat, double lon) {
    vector<Airport> res; double distance = 40000;
    for (Vertex* vertex: graph->getVertexSet()) {
        Airport airport = vertex->getAirport();
        double dist = harvesineDistance(graph, lat, lon, airport.getLatitude(), airport.getLongitude());

        if (dist < distance) {
            vector<Airport> new_res; new_res.push_back(airport);
            res = new_res;
            distance = dist;
        } else if (dist == distance)
            res.push_back(airport);
    }

    cout << res.size() << endl;
    for (Airport airport: res)
        cout << airport.getCode() << endl;

}

float Filters::harvesineDistance(Graph *graph, double lat1, double lon1, double lat2, double lon2) {
    const double radiusEarth = 6371.0;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double dLat1 = lat1 * M_PI / 180.0;
    double dLat2 = lat2 * M_PI / 180.0;

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
               cos(dLat1) * cos(dLat2) *
               sin(dLon / 2.0) * sin(dLon / 2.0);

    double c = 2.0 * asin(sqrt(a));

    return radiusEarth * c;
}
