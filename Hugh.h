/*
Minification legend:
A - std::vector
B - macro for Filter::IsXXX
C - reference to player self
D - start location
E - set of all unit types
F - vector of all unit types
G - build selector
H - macro to read or write one byte to the learning file
I - attack the given target with the given unit unless it is already doing so
J - map of units to current attack move target
K - macro to get current order target of the unit variable u
L - macro to get whether a given unit is defined and exists
M - else if
N - void
O - current frame count
P - macro to get tile position of the unit variable u
Q - macro to get the type of the unit variable u
R - int used for looping build order
S - BWAPI::Position
T - BWAPI::TilePosition
U - BWAPI::Unit
V - BWAPI::UnitType
W - int
X - reference to current BWAPI game
Y - using
Z - used as a local variable
a - Encoded tile position data
b - build queue timings (frame divided by 68 to minify it)
c - build queue buildings
d - build queue frame when current item was queued
e - build queue unit type of current item in queue
f - build queue location for current item
g - function to set current build queue item
h - target queue (vector)
i - target queue (map)
j - look up int in encoded tile position data
k - look up tile position in encoded tile position data
l - map of which tile positions are occupied by a friendly building
m - queue of available gather targets (mineral patches and assimilators)
n - current used supply
o - insert a single mineral patch or assimilator into the queue
p - add all mineral patches close to a position to the queue
q - map of worker gather assignments
s - remove a worker from a gather assignment
t - nullptr unit
u - reserved for local variables, assumed by some macros to be a unit
v - build worker
w - current provided supply
x - current number of gateways
y - map of latest frame when an enemy unit either attacked or repaired or a friendly unit started an attack
z - map of units that are assigned to attack
*/
#include<BWAPI.h>
#include<fstream>
#define A vector
#define C X->self()

// These next two defines put all unit types into a vector, so we can access a unit type by index instead of requiring the full name
#define E UnitTypes::allUnitTypes()
#define F A<V>(E.begin(),E.end())

// Either reads or writes one byte to the current enemy learning file
#define H(u,z,R)u##fstream("bwapi-data/"#z"/"+X->enemy()->getName()).##z(R,1)

#define K u->getOrderTarget()
#define L(z)(z&&z->exists())
#define M else if
#define N void
#define P u->getTilePosition()
#define Q u->getType()
#define Y using

// This macro reads one byte from the encoded tile positions (see 'a' below)
// 'z' is the index to read relative to the start of the data for the current map and start position
// The formula involving the map hash and start location produces numbers 0-13 for each start position in the map pool
#define j(z)(UCHAR)a[22*((X->mapHash()[9]-4)%12+(D.x-4)%7)+z]-128

#define B(z)Filter::Is##z
Y namespace BWAPI;Y namespace std;
    Y S=Position;
    Y T=TilePosition;
    Y U=Unit;
    Y V=UnitType;
    Y W=int;
    auto&X=Broodwar;

    // Encoded tile positions
    // VS seems perfectly happy to accept characters in the extended ASCII range, so we just add 128 to each tile position component and put it in a string
    // The start positions are included in a specific order to fit the formula above (see 'j')
    char*a="���������������������������������������������������������̧����������������������֐ՎՎӉ��؎ٌԈ��Հ֝����������������������������������������������������������������������������������������������������������ٔ�����������������������������������������������������������";
    
    // FFE build order
    // First vector is timings, as frame count divided by 99
    // Second vector is what to build, as an index to the unit types vector subtracted by 144
    A<W>b={9,15,15,15,37,32,32,51,37,61,99,35,51,71,73,51,75},c={2,10,6,6,2,5,6,6,3,0,3,8,6,6,2,6};

    A<T>h;
    map<T,U>i,l;
    map<U,U>z,q;
    map<U,W>y;
    map<U,T>J;
    W d,n,w,x,R,O,e;
    char G;
    T f,D;
    U v,t;
    A<U>m;

    // Gets a tile position for the FFE build order
    // The first 11 come from the encoded tile positions, the others are computed as offsets
    T k(W u){return u>13?k(11)+T((u%2?3:-2),0):(u>11?k(4)+T((u%2?2:-2),0):(u>10?k(4)+T(0,D.y<k(4).y?2:-2):T(j(u*2),j(u*2+1))));}

    N o(U u){m.insert(m.begin(),u);}
    N p(T u){for(U z:X->getUnitsInRadius(S(u),400,B(MineralField)))o(z),o(z);}
    N s(U u){if(q[u])o(q[u]),q.erase(u);}
    N g(W u,T Z=T()){e=u;d=O;f=Z.y?d+=99,Z:X->getBuildLocation(F[u],D);}

    // Issues an attack move order for a unit
    // Keeps track of successfully-issued orders to avoid spamming
    // Every 48 frames the order is issued again to nudge stuck units
    N I(U u,T z){(J[u]!=z||O%48==0)&&u->attack(S(z))?J[u]=z:f;}

    struct ExampleAIModule:AIModule{
        N onFrame(){
            O=X->getFrameCount();

            // Frame 0
            if(!O){
                D=C->getStartLocation();
                H(i,read,&G);

                // Push all start locations except our own onto the target queue
                for(T u:X->getStartLocations())u!=D?h.push_back(u):a;

                // Add mineral fields close to each base we are going to take
                G?a:p(k(10));
                p(D);
            }

            // Update the target queue
            // First line removes targets from the queue that are not occupied by an enemy building
            // Second line adds any visible enemy buildings that are not already in the queue
            for(auto u=h.begin();u!=h.end();)u=X->isVisible(*u)&&X->getUnitsOnTile(*u,B(Building)&&B(Enemy)).empty()?i[*u]=t,h.erase(u):u+1;
            for(U u:X->enemy()->getUnits())!i[P]&&Q.isBuilding()?i[P]=u,h.push_back(P):a;

            // Update the next building to construct
            // First line times out a pending building if we've been waiting 240 frames to build it
            // Second line checks if there is a building in our FFE build order we want to build now
            // Third line queues a pylon if we're about to be supply blocked or a gateway if we have money for it
            if(d&&L(l[f])||O-d>240)d=0;
            for(;!G&&R<16;R++)if(!d&&!L(l[k(R)])&&O>b[R]*99)g(c[R]+144,k(R));
            if(!d&&w<400)1.0*n/w>0.8?g(146):a,C->minerals()>200&&x<7?g(149):a;

            w=n=x=R=0;
            for(U u:C->getUnits()){
                // We keep track of supply manually since we can't trust BWAPI
                w+=Q.supplyProvided();
                n+=Q.supplyRequired();

                U Z=u->getClosestUnit(B(Enemy),200);

                // We use this to determine if our workers should attack an enemy unit (they stop moving when attacking)
                Z&&!Z->isMoving()?y[Z]=O:w;

                // Track frame when our units start an attack for goon micro
                u->isStartingAttack()?y[u]=O:w;

                // Move or build with the build worker
                if(d&&u==v)s(u),u->getDistance(S(f))<200?u->build(F[e],f):u->move(S(f));

                M(Q.isBuilding()){
                    l[P]=u;

                    // Count our gateways
                    Q==F[149]?x++:x;

                    // Train a probe, dragoon or zealot as appropriate
                    if((!d||e%3!=0)&&!u->isTraining()){
                        m.size()?u->train(F[1]):a;
                        u->train(C->gas()<50?F[4]:F[7]);
                    }

                    u->upgrade(UpgradeTypes::Singularity_Charge);
                }

                // Probes
                M(Q==F[1]){
                    // Assigns a build worker if we don't already have one
                    !L(v)?v=u:v;

                    // Worker defense, attack a nearby ground enemy if it has been stopped within the last 99 frames
                    if(Z&&(O-y[Z])<99&&!Z->isFlying())s(u),K!=Z?u->attack(Z):a;

                    // If this worker isn't assigned to gather resources, take the next patch
                    M(m.size()&&!q[u])if(u->gather(m[0]))q[u]=m[0],m.erase(m.begin());M(1)u->move(S(k(9)));

                    // Mineral locking
                    M(K&&K->getResources()&&K!=q[u])u->gather(q[u]);
                }

                // Don't issue a command to this unit if it started an attack less than 4 frames ago
                // This is to prevent goons from aborting attacks, but doesn't affect zealots adversely
                M(O-y[u]<4);

                // Kite with dragoons
                M(Z&&u->getDistance(Z)<185&&Q==F[7]&&u->getGroundWeaponCooldown()>3)J[u]=P,u->move(S(P)*2-Z->getPosition());

                // Assign units to attack every 2500 frames
                M(O%2500==0)z[u]=u;

                // If we have nothing in the attack queue, attack somewhere random every 500 frames
                M(h.empty())O%500==0?I(u,T(rand()%128,rand()%128)):a;

                // Attack
                // Size count is just to make sure we have 6 units before the initial attack
                // Dead units aren't removed from the map so this won't cause us to retreat later
                M(z.size()>5&&z[u])I(u,h[0]);

                // Move to the staging area
                M(1)I(u,G?D:k(1));
            }
        }

        N onUnitComplete(U u){
            // Add completed assimilators to the available resources map
            Q==F[147]?o(u),o(u):a;
        }

        N onEnd(bool u){
            H(o,write,u!=!G?"1":"\0");
        }
    };