#include "Haversine.h"

double haversine(double lat1, double lat2, double lon1, double lon2) {
    double radians = M_PI / 180.0;
    lat1 = (lat1) * radians;
    lat2 = (lat2) * radians;
    return 6371 * 2 * asin(sqrt(pow(sin((lat2 - lat1) * radians / 2), 2) + pow(sin((lon2 - lon1) * radians / 2), 2) * cos(lat1) * cos(lat2)));
}

double haversine(const Airport& a, const Airport& b) {
    return haversine(a.getLatitude(), b.getLatitude(), a.getLongitude(), b.getLongitude());
}
