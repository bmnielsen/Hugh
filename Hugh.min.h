#include<BWAPI.h>
#include<fstream>
#define A vector
#define C X->self()
#define E UnitTypes::allUnitTypes()
#define F A<V>(E.begin(),E.end())
#define H(u,z,R)u##fstream("bwapi-data/"#z"/"+X->enemy()->getName()).##z(R,1)
#define K u->getOrderTarget()
#define L(z)(z&&z->exists())
#define M else if
#define N void
#define P u->getTilePosition()
#define Q u->getType()
#define Y using
#define j(z)(UCHAR)a[22*((X->mapHash()[9]-4)%12+(D.x-4)%7)+z]-128
#define B(z)Filter::Is##z
Y namespace BWAPI;Y namespace std;Y S=Position;Y T=TilePosition;Y U=Unit;Y V=UnitType;Y W=int;auto&X=Broodwar;char*a="ó§í¥ğ¥ğ£õŠì¨ğ©ò¤ô‚õ¨ü§ÖóÛïÛñİñöøÖîÖñØñõğÖ÷×ıïÉéÇìÆîÆò²éÊíÌíÊôªôËûÌ§‹  ‹¢‹ˆŠ¥§¥‡‚¦†¤‹ÖÕÕÓ‰øØÙŒÔˆğ‡Õ€Ö–œšœ˜š™‰Š —¢• •‡‚›”‘§‹¦¦¤‰ªŒ¬ŠªŠˆ†¥†£ãâáŒâŸó‘ååç—ö‡â€äĞêÌéÌëÎëëñĞåÔæÓèåñÑîØîèªê®ê¬êªõŒì«ì©åªõ„ç¥à£ò§í¥î§ğ§õÅï¢ğ¥ò¥õ½÷×ğÙ”™‘˜—‘‰¯š˜–‡§‹ˆ‹¸¼‹¼‹ºˆ¹º¸‡–…†Œ…µî²ìµì³îŞô´é·ì¸êÖö³ñ¬ó";A<W>b={9,15,15,15,37,32,32,51,37,61,99,35,51,71,73,51,75},c={2,10,6,6,2,5,6,6,3,0,3,8,6,6,2,6};A<T>h;map<T,U>i,l;map<U,U>z,q;map<U,W>y;map<U,T>J;W d,n,w,x,R,O,e;char G;T f,D;U v,t;A<U>m;T k(W u){return u>13?k(11)+T((u%2?3:-2),0):(u>11?k(4)+T((u%2?2:-2),0):(u>10?k(4)+T(0,D.y<k(4).y?2:-2):T(j(u*2),j(u*2+1))));}N o(U u){m.insert(m.begin(),u);}N p(T u){for(U z:X->getUnitsInRadius(S(u),400,B(MineralField)))o(z),o(z);}N s(U u){if(q[u])o(q[u]),q.erase(u);}N g(W u,T Z=T()){e=u;d=O;f=Z.y?d+=99,Z:X->getBuildLocation(F[u],D);}N I(U u,T z){(J[u]!=z||O%48==0)&&u->attack(S(z))?J[u]=z:f;}struct ExampleAIModule:AIModule{N onFrame(){O=X->getFrameCount();if(!O){D=C->getStartLocation();H(i,read,&G);for(T u:X->getStartLocations())u!=D?h.push_back(u):a;G?a:p(k(10));p(D);}for(auto u=h.begin();u!=h.end();)u=X->isVisible(*u)&&X->getUnitsOnTile(*u,B(Building)&&B(Enemy)).empty()?i[*u]=t,h.erase(u):u+1;for(U u:X->enemy()->getUnits())!i[P]&&Q.isBuilding()?i[P]=u,h.push_back(P):a;if(d&&L(l[f])||O-d>240)d=0;for(;!G&&R<16;R++)if(!d&&!L(l[k(R)])&&O>b[R]*99)g(c[R]+144,k(R));if(!d&&w<400)1.0*n/w>0.8?g(146):a,C->minerals()>200&&x<7?g(149):a;w=n=x=R=0;for(U u:C->getUnits()){w+=Q.supplyProvided();n+=Q.supplyRequired();U Z=u->getClosestUnit(B(Enemy),200);Z&&!Z->isMoving()?y[Z]=O:w;u->isStartingAttack()?y[u]=O:w;if(d&&u==v)s(u),u->getDistance(S(f))<200?u->build(F[e],f):u->move(S(f));M(Q.isBuilding()){l[P]=u;Q==F[149]?x++:x;if((!d||e%3!=0)&&!u->isTraining()){m.size()?u->train(F[1]):a;u->train(C->gas()<50?F[4]:F[7]);}u->upgrade(UpgradeTypes::Singularity_Charge);}M(Q==F[1]){!L(v)?v=u:v;if(Z&&(O-y[Z])<99&&!Z->isFlying())s(u),K!=Z?u->attack(Z):a;M(m.size()&&!q[u])if(u->gather(m[0]))q[u]=m[0],m.erase(m.begin());M(1)u->move(S(k(9)));M(K&&K->getResources()&&K!=q[u])u->gather(q[u]);}M(O-y[u]<4);M(Z&&u->getDistance(Z)<185&&Q==F[7]&&u->getGroundWeaponCooldown()>3)J[u]=P,u->move(S(P)*2-Z->getPosition());M(O%2500==0)z[u]=u;M(h.empty())O%500==0?I(u,T(rand()%128,rand()%128)):a;M(z.size()>5&&z[u])I(u,h[0]);M(1)I(u,G?D:k(1));}}N onUnitComplete(U u){Q==F[147]?o(u),o(u):a;}N onEnd(bool u){H(o,write,u!=!G?"1":"\0");}};