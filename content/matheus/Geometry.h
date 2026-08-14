#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define ll long long
#define INF LLONG_MAX
#define NINF LLONG_MIN
#define full(a) a.begin(),a.end()
#define get(a) for(int i=0; i<a.size(); i++){cin>>a[i];}
#define double long double

const double PI = acos(-1);
struct vetor{
    double x,y;
    vetor(double a, double b){
        this->x=a;
        this->y=b;
    }
    vetor()=default;
    vetor operator+(vetor v) const{
        return {x+v.x,y+v.y};
    }
    vetor operator*(double a) const {
        return {x*a,y*a};
    }
    vetor operator-(vetor v) const {
        return{x-v.x,y-v.y};
    }
    vetor operator/(double a)const {
        return {x/a,y/a};
    }
};
double escalarproduct(vetor v, vetor u){
    return (v.x*u.x + v.y*u.y);
}
double mod(vetor v){
    return sqrt(v.x*v.x+v.y*v.y);
}
double sqmod(vetor v){
    return v.x*v.x + v.y*v.y;
}
vetor projOfDir(vetor v,vetor u){
    if(sqmod(u)==0){
        v.x=0;
        v.y=0;
        return v;
    }
    return u *(escalarproduct(v,u)/sqmod(u));
}
vetor rotate(vetor v,double deg){
    double newx = v.x*cos(deg) - v.y*sin(deg);
    double newy = v.x*sin(deg) + v.y*cos(deg);
    v.x=newx;
    v.y=newy;
    return v;
}
double finddeg(double sine, double cosine){
    return atan2(sine,cosine);
}
double toradian(double deg){
    return (deg*PI/180.0);
}

struct line{
    vetor point;
    vetor vd;
    line(vetor a, vetor b){
        this->point=a;
        this->vd=b-a;
    }
};
bool isparallel(line l1,line l2){
    double cross = (l1.vd.x * l2.vd.y)-(l1.vd.y*l2.vd.x);
    return abs(cross)<1e-12;
}
vetor closestPoint(line l, vetor m) {
    vetor am(m-l.point);
    vetor dis=projOfDir(am,l.vd);
    return l.point+dis;
}
double distToPoint(line l,vetor p) {
    vetor close=closestPoint(l,p);
    close = close-p;
    return mod(close); //posso retornar sqmod(close) se eu quiser só comparar distâncias
}
double findt(line l, vetor p){
    vetor w = p-l.point;
    return(escalarproduct(w,l.vd)/sqmod(l.vd)); //t==1 or t==0 on the segment, 0<t<1, inside the segment, else outside;
}
vetor findintersect(line l1, line l2){
    vetor w = l2.point-l1.point;
    double t = (w.x * l2.vd.y - w.y*l2.vd.x)/(l1.vd.x*l2.vd.y - l1.vd.y*l2.vd.x);
    return l1.point + l1.vd*t;
}
struct circle{
    vetor center;
    double r;
    circle() = default;
    circle(vetor c, double radius){
        this->center=c;
        this->r=radius;
    }
    // a point a in circle is given by the formula:
    // X = C.x + r*cos(ang);
    // Y = C.y + r*sin(ang);
};