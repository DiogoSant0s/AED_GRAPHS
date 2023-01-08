#include "Rectangle.h"

Rectangle::Rectangle(double lat1, double lat2, double lon1, double lon2) {
    this -> lat1 = min(lat1, lat2);
    this -> lat2 = max(lat1, lat2);
    this -> lon1 = min(lon1, lon2);
    this -> lon2 = max(lon1, lon2);
}

Rectangle Rectangle::trimLeft(int cd, double data) const {
    if (cd == 0) {
        return {lat1, data, lon1, lon2};
    }
    return {lat1, lat2, lon1, data};
}

Rectangle Rectangle::trimRight(int cd, double data) const {
    if (cd == 0) {
        return {data, lat2, lon1, lon2};
    }
    return {lat1, lat2, data, lon2};
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double radians = M_PI / 180.0;
    lat1 = (lat1) * radians;
    lat2 = (lat2) * radians;
    return 6371 * 2 * asin(sqrt(pow(sin((lat2 - lat1) * radians / 2), 2) + pow(sin((lon2 - lon1) * radians / 2), 2) * cos(lat1) * cos(lat2)));
}

double haversine(pair<double, double> p1, pair<double, double> p2) {
    return haversine(p1.first, p1.second, p2.first, p2.second);
}

double distance(pair<double, double> point, Rectangle rectangle) {
    if (point.first >= rectangle.lat1 && point.first <= rectangle.lat2 && point.second >= rectangle.lon1 && point.second <= rectangle.lon2)
        return 0;
    else if (point.first < rectangle.lat1 && point.second < rectangle.lon1)
        return haversine(point.first, point.second, rectangle.lat1, rectangle.lon1);
    else if (point.first < rectangle.lat1 && point.second > rectangle.lon2)
        return haversine(point.first, point.second, rectangle.lat1, rectangle.lon2);
    else if (point.first > rectangle.lat2 && point.second < rectangle.lon1)
        return haversine(point.first, point.second, rectangle.lat2, rectangle.lon1);
    else if (point.first > rectangle.lat2 && point.second > rectangle.lon2)
        return haversine(point.first, point.second, rectangle.lat2, rectangle.lon2);
    else if (point.first < rectangle.lat1)
        return haversine(point.first, point.second, rectangle.lat1, point.second);
    else if (point.first > rectangle.lat2)
        return haversine(point.first, point.second, rectangle.lat2, point.second);
    else if (point.second < rectangle.lon1)
        return haversine(point.first, point.second, point.first, rectangle.lon1);
    else
        return haversine(point.first, point.second, point.first, rectangle.lon2);
}