/*
 * FallingEntity.h
 *
 * T�m� luokka on yl�luokka kaikille entityille, joita voi vahingoittaa,
 * eli, joilla on health pointit.
 *
 * Esimerkki:
 *		FallingEntity FallingEntity = new FallingEntity();
 *		FallingEntity->damage(100);
 */

#ifndef __FALLINGENTITY_H_DEFINED__
#define __FALLINGENTITY_H_DEFINED__

#include "Window.h"
#include "MovingEntity.h"

#define GRAVITY 13

class FallingEntity : public MovingEntity
{
	public:
		FallingEntity(Rectangle hitbox, float speed);
		~FallingEntity();

		// Makes entity suffer gravity
		void update();

};

#endif //__FALLINGENTITY_H_DEFINED__