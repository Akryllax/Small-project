#include "UniqueIdentifier.h"

std::unordered_map<UniqueIdentifier, std::shared_ptr<std::any>,
                   std::hash<std::string>>
    UniqueIdentifier::associatedObjects_;
