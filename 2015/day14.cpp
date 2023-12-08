/*
Dancer can fly 27 km/s for 5 seconds, but then must rest for 132 seconds.
Cupid can fly 22 km/s for 2 seconds, but then must rest for 41 seconds.
Rudolph can fly 11 km/s for 5 seconds, but then must rest for 48 seconds.
Donner can fly 28 km/s for 5 seconds, but then must rest for 134 seconds.
Dasher can fly 4 km/s for 16 seconds, but then must rest for 55 seconds.
Blitzen can fly 14 km/s for 3 seconds, but then must rest for 38 seconds.
Prancer can fly 3 km/s for 21 seconds, but then must rest for 40 seconds.
Comet can fly 18 km/s for 6 seconds, but then must rest for 103 seconds.
Vixen can fly 18 km/s for 5 seconds, but then must rest for 84 seconds.
*/
#include <iostream>
#include <string>

class Deer {
private:
    std::string name;
    int speed;        
    int flyingTime;   
    int restTime;     
    int distance;     

public:
    Deer(std::string n, int s, int ft, int rt) : name(n), speed(s), flyingTime(ft), restTime(rt), distance(0) {}

    void simulateRace(int totalTime) {
        int cycleTime = flyingTime + restTime;
        int fullCycles = totalTime / cycleTime;
        int remainingTime = totalTime % cycleTime;

        distance = fullCycles * flyingTime * speed;
        distance += std::min(remainingTime, flyingTime) * speed;
    }

    int getDistance() const {
        return distance;
    }

    std::string getName() const {
        return name;
    }
};

int main() {
    Deer comet("Comet", 18, 6, 103);
    Deer dancer("Dancer", 27, 5, 132);
    Deer cupid("cupid", 22, 2, 41);
    Deer rudolph("rudolph", 11, 5, 48);
    Deer donner("donner", 28, 5, 134);
    Deer dasher("dasher", 4, 16, 55);
    Deer blizzer("blizzer", 14, 3, 38);
    Deer prancer("prancer", 3, 21, 40);
    Deer vixen("vixen", 18, 5, 84);

    int raceTime = 2503;

    comet.simulateRace(raceTime);
    dancer.simulateRace(raceTime);
    cupid.simulateRace(raceTime);
    rudolph.simulateRace(raceTime);
    donner.simulateRace(raceTime);
    dasher.simulateRace(raceTime);
    blizzer.simulateRace(raceTime);
    prancer.simulateRace(raceTime);
    vixen.simulateRace(raceTime);

    std::cout << comet.getName() << ": " << comet.getDistance() << " km\n";
    std::cout << dancer.getName() << ": " << dancer.getDistance() << " km\n";
    std::cout << cupid.getName() << ": " << cupid.getDistance() << " km\n";
    std::cout << rudolph.getName() << ": " << rudolph.getDistance() << " km\n";
    std::cout << donner.getName() << ": " << donner.getDistance() << " km\n";
    std::cout << dasher.getName() << ": " << dasher.getDistance() << " km\n";
    std::cout << blizzer.getName() << ": " << blizzer.getDistance() << " km\n";
    std::cout << prancer.getName() << ": " << prancer.getDistance() << " km\n";
    std::cout << vixen.getName() << ": " << vixen.getDistance() << " km\n";


    return 0;
}
