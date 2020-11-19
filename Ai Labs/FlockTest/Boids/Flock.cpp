#include "Boid.h"
#include "Flock.h"

using namespace std;

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize()
{
	return flock.size();
}

Boid Flock::getBoid(int i)
{
	return *flock[i];
}

void Flock::addBoid(Boid* b)
{
	flock.push_back(b);
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking() 
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i]->run(flock);
	}
}
// Runs the swarm function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::swarming()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i]->swarm(flock);
	}
}

void Flock::cFormation(int fLeader)
{
	float pi = 3.14;
	int fSize = flock.size();
	for (int i = 0; i < fSize; i++)
	{
		Pvector	sub(0, 0);
		Pvector sum(0, 0);
		int npcRadius = 10;
		int closeEnough = 10;
		float angleAroundCircle = 0.0;
		Pvector targetSlot(0, 0);
		Boid* target = flock[fLeader]; // Our designated leader

		if (i == fLeader) {		//Deal with our leader here
			//lets set the velocity so we can see whats going on.
			flock[i]->velocity.normalize();
			flock[i]->velocity = Pvector(-std::sin(flock[i]->orientation), std::cos(flock[i]->orientation));
			flock[i]->orientation = flock[i]->velocity.getNewOrientation(flock[i]->orientation, flock[i]->velocity);
			flock[i]->applyForce(sum);
			flock[i]->update();
			flock[i]->borders();
		}
		else {				//Find our position in the circle
			angleAroundCircle = (float)i / (fSize - 1);
			angleAroundCircle = angleAroundCircle * pi * 2;
			float radius = npcRadius / sin(pi / (fSize));

			targetSlot = target->location;
			targetSlot.x = targetSlot.x + radius * (float)cos(angleAroundCircle + i * 2 * pi / 4) / angleAroundCircle;//targetSlot.x + radius * cos(angleAroundCircle);
			targetSlot.y = targetSlot.y + radius * (float)sin(angleAroundCircle + i * 2 * pi / 4) / angleAroundCircle; //targetSlot.y + radius * sin(angleAroundCircle);

				//t[i].X = Center.X + Radius * (float)Math.Cos(Angle + i * 2 * MathHelper.PI / 3);
			   //t[i].Y = Center.Y + Radius * (float)Math.Sin(Angle + i * 2 * MathHelper.PI / 3);
			sub = sub.subTwoVector(targetSlot, flock[i]->location);
			float D = sub.magnitude();
			if (D > closeEnough)
			{
				sum = sub;
				sum.normalize();
				sum.mulScalar(flock[i]->maxSpeed);
				flock[i]->applyForce(sum);
				flock[i]->update();
				flock[i]->borders();
			}
			else
				flock[i]->velocity = flock[fLeader]->velocity; //Match the leader's velocity if we are close enough
		}
	}
}