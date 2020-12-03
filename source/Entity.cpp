#include "Entity.h"
#include "Environment.h"
#include "Surface.h"
#include "Texture.h"
#include <iostream>

Entity::Entity(Environment *environment) : Base(environment->GetEnginePointer()) {
    this->environment = environment;
}