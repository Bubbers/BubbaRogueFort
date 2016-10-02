#include "CrewMember.h"
#include "Stats.h"

CrewMember::CrewMember(std::string name, int maxHealth, CrewType crewType):
    crewType(crewType), Bandit(name, maxHealth) {}

CrewMember::CrewMember(std::string name, int maxHealth, CrewType crewType,
    Stats *stats, std::unordered_map<std::string, Attack>* attacks)
  : crewType(crewType), Bandit(name, maxHealth, stats, attacks) {}

CrewMember::CrewType CrewMember::getCrewType() {
    return crewType;
}
