#include "frog.hpp"
#include "inputManager.hpp"
#include "utilities.hpp"
#include "constants.hpp"
#include "collision.hpp"
#include "world.hpp"

#include "Lilypad.hpp"

#include "math.h"
#include <list>
#include <SFML/Graphics.hpp>

Frog::Frog(float x, float y, float size)
{
	position.x = x;
	position.y = y;
	radius = size;

	density = 5.0f;
	mass =  3.1415 * radius * radius * density;

	renderLayer = 1;

	currentCollisionCategory = Entity::Frogs;
	collisionMask = Entity::All;

	sf::Color frogFillColor = sf::Color(80, 130, 80);
	sf::Color frogOutlineColor = sf::Color(70, 130, 70);

	sf::CircleShape frogBodyShape(size);
	frogBodyShape.setFillColor(frogFillColor);

	frogBodyShape.setOrigin(size, size);
	frogBodyShape.setOutlineThickness(size/7);
	frogBodyShape.setOutlineColor(frogOutlineColor);
	frogBodyShape.setPosition(size*2, size*2);


	sf::Color legFillColor = sf::Color(50, 120, 50);
	float legSize = size * 0.3;
	sf::Vector2f leftLegPos = sf::Vector2f(size * 1.6f, size * 2.7f);

	sf::ConvexShape frogLegLeftSimple;
	frogLegLeftSimple.setPointCount(3);
	frogLegLeftSimple.setPoint(0, sf::Vector2f(-2, -1));
	frogLegLeftSimple.setPoint(1, sf::Vector2f(-0.5f, 1));
	frogLegLeftSimple.setPoint(2, sf::Vector2f(-3, 3));
	frogLegLeftSimple.setFillColor(legFillColor);
	frogLegLeftSimple.setOutlineColor(sf::Color(70, 140, 70));
	frogLegLeftSimple.setOutlineThickness(size/7);
	frogLegLeftSimple.setPosition(leftLegPos);


	sf::ConvexShape frogLegLeft1;
	frogLegLeft1.setPosition(leftLegPos);
	frogLegLeft1.setScale(legSize, legSize);
	frogLegLeft1.setFillColor(legFillColor);
	frogLegLeft1.setPointCount(4);
	frogLegLeft1.setPoint(0, sf::Vector2f(1, -1));
	frogLegLeft1.setPoint(1, sf::Vector2f(-2, -3));
	frogLegLeft1.setPoint(2, sf::Vector2f(-1.5f, 0.5f));
	frogLegLeft1.setPoint(3, sf::Vector2f(-0.5f, 1));
	sf::ConvexShape frogLegLeft2;
	frogLegLeft2.setPosition(leftLegPos);
	frogLegLeft2.setScale(legSize, legSize);
	frogLegLeft2.setFillColor(legFillColor);
	frogLegLeft2.setPointCount(4);
	frogLegLeft2.setPoint(0, sf::Vector2f(-2, -3));
	frogLegLeft2.setPoint(1, sf::Vector2f(-3, -1));
	frogLegLeft2.setPoint(2, sf::Vector2f(-3, 1.5f));
	frogLegLeft2.setPoint(3, sf::Vector2f(-1.5f, -0.5f));
	sf::ConvexShape frogLegLeft3;
	frogLegLeft3.setPosition(leftLegPos);
	frogLegLeft3.setScale(legSize, legSize);
	frogLegLeft3.setFillColor(legFillColor);
	frogLegLeft3.setPointCount(3);
	frogLegLeft3.setPoint(0, sf::Vector2f(-3, -1));
	frogLegLeft3.setPoint(1, sf::Vector2f(-5.5f, -1));
	frogLegLeft3.setPoint(2, sf::Vector2f(-3, 1.5f));
	sf::ConvexShape frogLegLeft4;
	frogLegLeft4.setPosition(leftLegPos);
	frogLegLeft4.setScale(legSize, legSize);
	frogLegLeft4.setFillColor(legFillColor);
	frogLegLeft4.setPointCount(3);
	frogLegLeft4.setPoint(0, sf::Vector2f(-4.7f, -2.5f));
	frogLegLeft4.setPoint(1, sf::Vector2f(-4.5f, -0.9f));
	frogLegLeft4.setPoint(2, sf::Vector2f(-4, -1.5f));
	sf::ConvexShape frogLegLeft5;
	frogLegLeft5.setPosition(leftLegPos);
	frogLegLeft5.setScale(legSize, legSize);
	frogLegLeft5.setFillColor(legFillColor);
	frogLegLeft5.setPointCount(3);
	frogLegLeft5.setPoint(0, sf::Vector2f(-3.5f, -2));
	frogLegLeft5.setPoint(1, sf::Vector2f(-4, -1.5f));
	frogLegLeft5.setPoint(2, sf::Vector2f(-3, -1));
	sf::ConvexShape frogLegLeft6;
	frogLegLeft6.setPosition(leftLegPos);
	frogLegLeft6.setScale(legSize, legSize);
	frogLegLeft6.setFillColor(legFillColor);
	frogLegLeft6.setPointCount(3);
	frogLegLeft6.setPoint(0, sf::Vector2f(-4, -1.5f));
	frogLegLeft6.setPoint(1, sf::Vector2f(-4.5f, -0.9f));
	frogLegLeft6.setPoint(2, sf::Vector2f(-3, -1));

	/*frogLegLeft1.setOutlineColor(sf::Color(70, 140, 70));
	frogLegLeft1.setOutlineThickness(size / 70);
	frogLegLeft2.setOutlineColor(sf::Color(70, 140, 70));
	frogLegLeft2.setOutlineThickness(size / 70);
	frogLegLeft3.setOutlineColor(sf::Color(70, 140, 70));
	frogLegLeft3.setOutlineThickness(size / 70);
	frogLegLeft4.setOutlineColor(sf::Color(70, 140, 70));
	frogLegLeft4.setOutlineThickness(size / 70);
	frogLegLeft5.setOutlineColor(sf::Color(70, 140, 70));
	frogLegLeft5.setOutlineThickness(size / 70);*/


	sf::RenderTexture* texture = new sf::RenderTexture();
	texture->create(size*4, size*4);
	//texture->clear(sf::Color(100, 100, 100, 200));
	// texture->clear(sf::Color::Red);
	texture->draw(frogBodyShape);
	texture->draw(frogLegLeft1);
	texture->draw(frogLegLeft2);
	texture->draw(frogLegLeft3);
	texture->draw(frogLegLeft4);
	texture->draw(frogLegLeft5);
	texture->draw(frogLegLeft6);
	texture->display();

	sprite = sf::Sprite(texture->getTexture());
	sprite.setOrigin(size*2, size*2);

	currentState = Entity::inWater;
}

Frog::~Frog()
{
}

void Frog::draw(sf::RenderTarget& renderTarget){
	Entity::draw(renderTarget);

	//Update position on screen
	sprite.setPosition(position.x, position.y);
	sprite.setRotation(rotation + 90);
	float scale = std::powf(2, altitude);
	sprite.setScale(scale, scale);

	renderTarget.draw(sprite);
}

void Frog::update(int deltaTime){
	Entity::update(deltaTime);
	timeFromLastSwim += deltaTime;
	
	// rotation = lookAtMouseController.calculate(rotation, utils::toAngle(position - InputManager::instance().getMousePos()), deltaTime);
	
	// rotation = utils::toAngle(InputManager::instance().getMousePos() - position);
	// applyForce(utils::fromAngle(rotation * toRadians) * (float)deltaTime * mass * 0.00001f /** powf(utils::getMagnitude(InputManager::instance().getMousePos() - position), 1) * 0.1f*/);

	if (timeForJumping > 0) {
		timeForJumping -= deltaTime;
		if (timeForJumping <= 0) {
			onEndJump();
		}
	}
	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			trySwim(utils::toAngle(InputManager::instance().getMousePos() - position), mass * 0.01f);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && timeForJumping <= 0 && altitude <= 0) {
			chargeJump(deltaTime);
		}
		else if (chargeTime > 0) {
			jump();
		}
	}
	// trySwim(utils::toAngle(-position), mass * 0.01f);

	// if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	// {
	//     world_->addEntity(new Lilypad(InputManager::instance().getMousePos().x, InputManager::instance().getMousePos().y, 5));
	// }
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		velocity = sf::Vector2f(0, 0);
	} 
}

void Frog::swim(float direction, float force){
	applyForce(utils::fromAngle(direction * toRadians) * force);

	timeFromLastSwim = 0;
}

bool Frog::trySwim(float direction, float force){
	rotation = direction;
	if (timeFromLastSwim >= timeForSwim){
		swim(direction, force);

		return true;
	}

	return false;
}

bool Frog::beforeCollision(Entity* withEntity, int deltaTime){
	switch (currentState)
	{
	case inWater:
		if (withEntity->currentCollisionCategory == Entity::Lilypads && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || isSittingOnLilypadsSafe())){
			currentState = Entity::onLilypad;

			collisionMask = collisionMask & ~Entity::Lilypads;
			// collisionMask = Entity::All - Entity::Lilypads;
			// collisionMask = ~Entity::Lilypads;
			// collisionMask = Entity::None | Entity::Lilypads;
			// collisionMask = Entity::Lilypads;
			drag = 1.99999999999f;
		}
		break;
	case onLilypad:
		{
		velocity += withEntity->acceleration;

		bool willFall = !isSittingOnLilypadsSafe();
		// std::cout << willFall << std::endl;
		if(willFall && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)){
			currentState = Entity::inWater;

			collisionMask = collisionMask | Entity::Lilypads;
			drag = 0.1f;
		}
		break;
		}
	case inAir:

		break;
	default:
		break;
	}

	return Entity::beforeCollision(withEntity, deltaTime);
}

void Frog::afterCollision(Entity* withEntity, int deltaTime){
	if (withEntity->currentCollisionCategory == Entity::Flies)
	{
		world_->deleteEntity(withEntity);
		countEatenFlies++;
		std::cout << "Your score is " << countEatenFlies << "!" << std::endl;
	}
}

bool Frog::isSittingOnLilypadsSafe(){
	// std::list<Collision*>::iterator it;
	// for (it = collisionList.begin(); it != collisionList.end(); ++it){
	//     std::cout << (*it)->entity1->mass;
	// }

	// for(auto currentCollision: collisionList)
	// {
	//     std::cout << (currentCollision)->entity1->mass << std::endl;
	// }
	
	// for (size_t i = 0; i != collisionList.size() - 1; ++i){
	//     std::cout << collisionList.
	// }

	// std::list<Collision*>::iterator it = collisionList.begin();
	// it++;
	// std::cout << (*it)->entity1->mass << std::endl ;



	// int one = 1;
	// int* oneptr = &one;
	// int two = 2;
	// int* twoptr = &two;
	// int three = 3;
	// int* threeptr = &three;
	// std::list<int*> intl{oneptr, twoptr, threeptr};

	// std::list<int*>::iterator it1;
	// for (it1 = intl.begin(); it1 != intl.end(); ++it1){
	//     std::cout << **it1 << std::endl;
	// }


	std::list<Collision*>::iterator it;

	for (it = collisionList.begin(); it != collisionList.end(); ++it){
		// std::cout << (*it)->entity1->mass << std::endl;
		Collision* currentCollision = (*it);

		Entity* onLilypadPtr;
		if(currentCollision->entity1->currentCollisionCategory == Entity::Lilypads){
			onLilypadPtr = currentCollision->entity1;
		} else if(currentCollision->entity2->currentCollisionCategory == Entity::Lilypads)
		{
			onLilypadPtr = currentCollision->entity2;
		} else continue;
		
		if (onLilypadPtr->radius - utils::getMagnitude(position - onLilypadPtr->position) > radius/16){
			// std::cout << "Distance: " << onLilypadPtr->radius - utils::getMagnitude(position - onLilypadPtr->position) << std::endl;
			return true;
		}
	}

	return false;
}


void Frog::chargeJump(int deltaTime) {
	rotation = utils::toAngle(InputManager::instance().getMousePos() - position);
	chargeTime += deltaTime;
}

void Frog::jump() {
	float jumpRatio = (float)chargeTime / (float)maxTimeToChargeJump;
	velocity += utils::normalize(InputManager::instance().getMousePos() - position) * jumpRatio * maxJumpVel;
	zVelocity = 0;
	//zAcceleration = 0;
	zVelocity += jumpUpVel * jumpRatio;
	onBeginJump();
	timeForJumping = (int)(0.8f * jumpUpVel * jumpRatio / gravityAcceleration);
	//std::cout << timeForJumping << std::endl;

	chargeTime = 0;
}