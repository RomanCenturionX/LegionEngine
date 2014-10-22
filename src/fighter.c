#include "collision.h"
#include "fighter.h"

Fighter Fighters[MAX_FIGHTERS];

/*
This struct is used to set the animations for the fighters
*/
struct 
{
	int frame;
	int player2_frame;
}F_Sprite;

/*
Initializes the fighter list that holds both of the player characters
*/
void InitFighterList()
{
	int i;
	for(i=0; i<MAX_FIGHTERS;++i)
	{
		Fighters[i].health = NULL;
		Fighters[i].x = NULL;
		Fighters[i].y = NULL;
		Fighters[i].walk_speed = NULL;
		Fighters[i].walk_acc = NULL;
		Fighters[i].jump_speed = NULL;
		Fighters[i].used = 0;
	}
}
/*
Gets the location of the fighter from the fighter list and returns the location
*/
Fighter * getFighter(int player)
{
	if (player >= MAX_FIGHTERS)return NULL;
	return &Fighters[player];
}
/*
Defaults the fighter sprite to have no animations
*/
void InitFighterSprite()
{
	F_Sprite.frame = 0;
	F_Sprite.player2_frame = 0;
}
/*
Sets the first player's data
*/
void InitCombatant(Fighter* f)
{
	f->health = 300;
	f->x = 110;
	f->y = 610;
	f->vy = 15;
	f->walk_acc = 5;
	f->walk_speed = 10;
	f->jump_speed = 50;
	f->hitbox.x = 110;
	f->hitbox.y = 610;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->flags = 0;
	f->anim_flags = 0;
	f->f_jump = 0;
}
/*
Sets the second player's data
*/
void InitCombatant2(Fighter* f)
{
	f->health = 300;
	f->x = 610;
	f->y = 610;
	f->vy = 15;
	f->walk_speed = 10;
	f->walk_acc = 5;
	f->jump_speed = 50;
	f->hitbox.x = 610;
	f->hitbox.y = 610;
	f->hitbox.w = 180;
	f->hitbox.h = 150;
	f->flags = 0;
	f->anim_flags = 0;
	f->f_jump = 0;
}
/*
Gets the key strokes from the user and applys the approriate flags to the player character
*/
void FighterPull(Fighter* f1, Uint8* keys)
{
	if(keys[SDLK_RIGHT] && f1->flags == FIGHTERFLAG_JUMP && f1->f_jump != JUMPFLAG_MOVEL)
	{
		f1->f_jump = JUMPFLAG_MOVER;
	}
	else if(keys[SDLK_LEFT] && f1->flags == FIGHTERFLAG_JUMP && f1->f_jump != JUMPFLAG_MOVER)
	{
		f1->f_jump = JUMPFLAG_MOVEL;
	}
	if(keys[SDLK_RIGHT] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_WALKR;
		f1->anim_flags = ANIMFLAG_WALKR;
	}
	else if(keys[SDLK_DOWN] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_CROUCH;
		f1->anim_flags = ANIMFLAG_CROUCH;
		if(keys[SDLK_n])
			f1->flags = FIGHTERFLAG_BLOCKL;
	}
	else if(keys[SDLK_LEFT] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_WALKL;
		f1->anim_flags = ANIMFLAG_WALKL;
	}
	else if(keys[SDLK_UP] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_JUMP;
		f1->anim_flags = ANIMFLAG_JUMP;
	}
	else if(keys[SDLK_j] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITH;
		f1->anim_flags = ANIMFLAG_LIGHT;
	}
	else if(keys[SDLK_k] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITL;
		f1->anim_flags = ANIMFLAG_MED;
	}
	else if(keys[SDLK_l] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITH;
		f1->anim_flags = ANIMFLAG_HEV;
	}
	else if(keys[SDLK_m] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_HITL;
		f1->anim_flags = ANIMFLAG_LAUNCH;
	}
	else if(keys[SDLK_n] && f1->flags != FIGHTERFLAG_JUMP)
	{
		f1->flags = FIGHTERFLAG_BLOCK;
		f1->anim_flags = ANIMFLAG_BLOCK;
	}	
	else
	{
		if(f1->y == 610 && f1->vy == 15)
		{
			/* If the fighter is at the floor and his velocity is at its max then he is idle*/
			f1->flags = FIGHTERFLAG_IDLE;
			f1->anim_flags = ANIMFLAG_IDLE;
		}
		else
			f1->flags = FIGHTERFLAG_JUMP;
	}
}
/* Same code used for fighter 1 but for fighter 2, not utilized in the demo because it produces some wierd bugs */
void FighterPull2(Fighter* f2, Uint8* keys)
{
	if(keys[SDLK_d] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_WALKL;
		f2->flags = ANIMFLAG_WALKL;
	}
	else if(keys[SDLK_s] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_CROUCH;
		f2->flags = ANIMFLAG_CROUCH;
		if(keys[SDLK_f])
			f2->flags = FIGHTERFLAG_BLOCKL;
	}
	else if(keys[SDLK_a] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_WALKR;
		f2->flags = ANIMFLAG_WALKR;
	}
	else if(keys[SDLK_w] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_JUMP;
		f2->flags = ANIMFLAG_JUMP;
	}
	else if(keys[SDLK_r] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITH;
		f2->flags = ANIMFLAG_LIGHT;
	}
	else if(keys[SDLK_t] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->flags = ANIMFLAG_MED;
	}
	else if(keys[SDLK_y] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->flags = ANIMFLAG_HEV;
	}
	else if(keys[SDLK_g] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_HITL;
		f2->flags = ANIMFLAG_LAUNCH;
	}
	else if(keys[SDLK_f] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_BLOCK;
		f2->flags = ANIMFLAG_BLOCK;
	}
	else
	{
		if(f2->y == 410 && f2->vy == 15)
		{
			f2->flags = FIGHTERFLAG_IDLE;
			f2->anim_flags = ANIMFLAG_IDLE;
		}
		else
			f2->flags = FIGHTERFLAG_JUMP;
	}
}
/*
Draws the player character based on their current flag, FIXME
*/
void DrawFighter1(Fighter* f1, SDL_Surface *buffer)
{
	int frame_count;
	if(f1->anim_flags == ANIMFLAG_WALKL)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		frame_count = 10;
	}
	else if(f1->anim_flags == ANIMFLAG_WALKR)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
		frame_count = 10;
	}
	else if(f1->anim_flags == ANIMFLAG_CROUCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		frame_count = 6;
	}
	else if(f1->anim_flags == ANIMFLAG_JUMP)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderJump.png",183,138);
	}
	else if(f1->anim_flags == ANIMFLAG_LIGHT)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
		frame_count = 9;
	}
	else if(f1->anim_flags == ANIMFLAG_MED)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
		frame_count = 7;
	}
	else if(f1->anim_flags == ANIMFLAG_HEV)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
		frame_count = 13;
	}
	else if(f1->anim_flags == ANIMFLAG_LAUNCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
		frame_count = 8;
	}
	else if(f1->anim_flags == ANIMFLAG_BLOCK)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
		frame_count = 4;
	}
	else
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = NULL;
		f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
		frame_count = 3;
	}
	DrawSprite(f1->sprite,buffer,f1->x, f1->y,F_Sprite.frame);
	F_Sprite.frame = (F_Sprite.frame + 1) % frame_count;
	if(f1->sprite != NULL)
	{
		FreeSprite(f1->sprite);
		f1->sprite = NULL;
	}
}

/*
Performs two of the three tasks at the same time, very inefficent but functional used for player one only
*/
void FighterController1(Fighter* f1, Fighter* f2, SDL_Surface *buffer)
{
	int frame_count, i = 0;
	f1->f_jump = NULL;
	if(f1->flags == FIGHTERFLAG_WALKR)
	{
		/* Walk Right code, prevents the player from walking off of the stage*/
		if(f1->x < 845)
		{
			if(f1->sprite != NULL) FreeSprite(f1->sprite);
			f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
			f1->x = f1->x + f1->walk_acc;
			f1->hitbox.x = f1->x;
			frame_count = 10;
		}
		else
		{
			/* If the player attempts to walk off of the stage set his state to idle*/
			f1->flags = FIGHTERFLAG_IDLE;
			if(f1->sprite != NULL) FreeSprite(f1->sprite);
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			frame_count = 3;
		}
	}
	else if(f1->flags == FIGHTERFLAG_CROUCH)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderCrouch.png",108,68);
		frame_count = 6;
	}
	else if(f1->flags == FIGHTERFLAG_BLOCKL)
	{
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderCrouchBlock.png",98,91);
		frame_count = 4;
	}
	else if(f1->flags == FIGHTERFLAG_WALKL)
	{
		/* Walk left code, prevents the player from walking off of the stage*/
		if(f1->x > 0)
		{
			if(f1->sprite != NULL) FreeSprite(f1->sprite);
			f1->sprite = LoadSprite("images/StriderWalk.png",114,101);
			f1->x = f1->x - f1->walk_acc;
			f1->hitbox.x = f1->x;
			frame_count = 10;
		}
		else
		{
			/* If the player attempts to walk off of the stage he is set to idle*/
			f1->flags = FIGHTERFLAG_IDLE;
			if(f1->sprite != NULL) FreeSprite(f1->sprite);
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			frame_count = 3;
		}
	}
	else if(f1->anim_flags == ANIMFLAG_LIGHT && f1->flags != FIGHTERFLAG_JUMP)
	{
		/* Light Attack: does the pulling, drawing, and logic for the attack */
		int has_hit = 0;
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderLightAttack.png",179,138);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
		{
			f2->health -= 15;
		}
		frame_count = 9;
	}
	else if(f1->anim_flags == ANIMFLAG_MED && f1->flags != FIGHTERFLAG_JUMP)
	{
		/* Medium Attack: does the pulling, drawing, and logic for the attack */
		int has_hit = 0;
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderMediumAttack.png",198,140);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCKL)
		{
			f2->health -= 25;
		}
		frame_count = 7;
	}
	else if(f1->anim_flags == ANIMFLAG_HEV && f1->flags != FIGHTERFLAG_JUMP)
	{
		/* Heavy Attack: does the pulling, drawing, and logic for the attack */
		int has_hit = 0;
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderHeavyAttack.png",206,140);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCK)
		{
			f2->health -= 50;
		}
		frame_count = 13;
	}
	else if(f1->anim_flags == ANIMFLAG_LAUNCH && f1->flags != FIGHTERFLAG_JUMP)
	{
		/* 
		 * Launcher Attack:  Used to knock the player high in the air for air combos
		 * The move is currently a heavily damaging move because the functionality has not
		 * been programmed in yet
		*/
		int has_hit = 0;
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderLauncherAttack.png",198,162);
		has_hit = AABB(f1->hitbox,f2->hitbox);
		if(has_hit == 1 && f2->flags != FIGHTERFLAG_BLOCKL)
		{
			f2->health -= 150;
		}
		frame_count = 8;
	}
	else if(f1->flags == FIGHTERFLAG_BLOCK)
	{
		/* Sets the player's state to block */
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderBlock.png",103,110);
		frame_count = 4;
	}	
	if(f1->flags == FIGHTERFLAG_JUMP)
	{
		/* Does the logic for jumping when the state is jumping */
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
		/* 
		Begining to apply directional jumping, still under construction 
		if(f1->f_jump == JUMPFLAG_MOVER && f1->x < 845 )
		{
			f1->x = f1->x + f1->walk_acc;
			f1->hitbox.x = f1->x;
		}
		else if(f1->f_jump == JUMPFLAG_MOVEL && f1->x > 0)
		{
			f1->x = f1->x - f1->walk_acc;
			f1->hitbox.x = f1->x;
		}
		*/
		f1->y = f1->y - f1->vy;
		f1->vy -= 1;
		f1->hitbox.y = f1->y;
		frame_count = 3;
		if(f1->y >= 610 && f1->vy != 15)
		{
			/* When the player touches the ground the state is set to idle */
			if(f1->sprite != NULL) FreeSprite(f1->sprite);
			f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
			f1->y = 610;
			f1->vy = 15;
			f1->hitbox.y = f1->y;
			frame_count = 3;
			f1->flags = FIGHTERFLAG_IDLE;
		}
	}
	else if(f1->flags == FIGHTERFLAG_IDLE)
	{
		f1->flags = FIGHTERFLAG_NOBLOCK;
		if(f1->sprite != NULL) FreeSprite(f1->sprite);
		f1->sprite = LoadSprite("images/StriderIdle.png",114,92);
		frame_count = 3;
		f1->f_jump = NULL;
	}
	DrawSprite(f1->sprite,buffer,f1->x,f1->y, F_Sprite.frame);
	F_Sprite.frame = (F_Sprite.frame + 1) % frame_count;
	f1->sprite = NULL;
	if(f1->sprite != NULL)
	{
		FreeSprite(f1->sprite);
		/* f1->sprite = NULL; */
	}
}
/* Player 2's fighter controller that does all three tasks at the same time */
void FighterController(Fighter* f1, Fighter* f2, SDL_Surface *buffer, Uint8* keys)
{
	int player2_fc, i = 0;
	f2->flags = FIGHTERFLAG_IDLE;
	if(keys[SDLK_d] && f2->flags != FIGHTERFLAG_JUMP)
	{
		/* Walk Left Code, prevents the player from walking off screen */
		if(f2->x < 845)
		{
			f2->flags = FIGHTERFLAG_WALKL;
			if(f2->sprite != NULL) FreeSprite(f2->sprite);
			f2->sprite = LoadSprite("images/DoomWalkBckReversed.png",153,140);
			f2->last_x = f2->x;
			f2->x = f2->last_x + f2->walk_acc;
			f2->hitbox.x = f2->x;
			player2_fc = 8;
		}
		else
		{
			/* If the player tries to walk off screen display him as idle */
			f2->flags = FIGHTERFLAG_IDLE;
			if(f2->sprite != NULL) FreeSprite(f2->sprite);
			f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			player2_fc = 10;
		}
	}
	else if(keys[SDLK_s] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_CROUCH;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomCrouch.png",129,88);
		player2_fc = 1;
		if(keys[SDLK_f])
		{
			f2->flags = FIGHTERFLAG_BLOCKL;
			f2->sprite = LoadSprite("images/DoomCrouchBlock.png",131,98);
			player2_fc = 3;
		}
	}
	else if(keys[SDLK_a] && f2->flags != FIGHTERFLAG_JUMP)
	{
		/* Walk Right Code, prevents the player from walking off screen */
		if(f2->x > 0)
		{
			f2->flags = FIGHTERFLAG_WALKR;
			if(f2->sprite != NULL) FreeSprite(f2->sprite);
			f2->sprite = LoadSprite("images/DoomWalkFwdReversed.png",154,144);
			f2->last_x = f2->x;
			f2->x = f2->last_x - f2->walk_acc;
			f2->hitbox.x = f2->x;
			player2_fc = 8;
		}
		else
		{
			f2->flags = FIGHTERFLAG_IDLE;
			if(f2->sprite != NULL) FreeSprite(f2->sprite);
			f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			player2_fc = 10;
		}
	}
	else if(keys[SDLK_r] && f2->flags != FIGHTERFLAG_JUMP)
	{
		/* Light Attack Code:  Pulls, draws, and does logic for Doom's light attack */
		f2->flags = FIGHTERFLAG_HITH;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		int has_hit2 = 0;
		f2->sprite = LoadSprite("images/DoomLightAttackReversed.png",215,134);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1 && f1->flags != FIGHTERFLAG_BLOCK)
		{
			f1->health -= 15;
		}
		player2_fc = 2;
	}
	else if(keys[SDLK_t] && f2->flags != FIGHTERFLAG_JUMP)
	{
		/* Medium Attack Code:  Pulls, draws, and does logic for Doom's medium attack */
		f2->flags = FIGHTERFLAG_HITL;
		int has_hit2 = 0;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomMediumAttackReversed.png",219,145);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1 && f1->flags != FIGHTERFLAG_BLOCKL)
		{
			f1->health -= 25;
		}
		player2_fc = 5;
	}
	else if(keys[SDLK_y] && f2->flags != FIGHTERFLAG_JUMP)
	{
		/* Heavy Attack Code:  Pulls, draws, and does logic for Doom's heavy attack */
		f2->flags = FIGHTERFLAG_HITL;
		int has_hit2 = 0;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomHeavyAttackReversed.png",270,173);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1 && f1->flags != FIGHTERFLAG_BLOCKL)
		{
			f1->health -= 50;
		}
		player2_fc = 8;
	}
	else if(keys[SDLK_g] && f2->flags != FIGHTERFLAG_JUMP)
	{
		/* 
		 * Launcher Attack:  Used to knock the player high in the air for air combos
		 * The move is currently a heavily damaging move because the functionality has not
		 * been programmed in yet
		*/
		int has_hit2 = 0;
		f2->flags = FIGHTERFLAG_HITL;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomLauncherAttack.png",286,151);
		has_hit2 = AABB(f2->hitbox,f1->hitbox);
		if(has_hit2 == 1 && f1->flags != FIGHTERFLAG_BLOCKL)
		{
			f1->health -= 150;
		}
		player2_fc = 16;
	}
	else if(keys[SDLK_f]&& f2->flags != FIGHTERFLAG_JUMP)
	{
		/* Sets the fighter's flag to blocking */
		f2->flags = FIGHTERFLAG_BLOCK;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomBlock.png",144,139);
		player2_fc = 4;
	}
	else if(keys[SDLK_w] && f2->flags != FIGHTERFLAG_JUMP)
	{
		f2->flags = FIGHTERFLAG_JUMP;
	}
	if(f2->flags == FIGHTERFLAG_JUMP)
	{
		/* Does the logic for jumping when the state is jumping */
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
		f2->y = f2->y - f2->vy;
		f2->vy -= 1;
		f2->hitbox.y = f2->y;
		player2_fc = 10;
		if(f2->y >= 610 && f2->vy != 15)
		{
			/* When the player touches the ground the state is set to idle */
			if(f2->sprite != NULL) FreeSprite(f2->sprite);
			f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
			f2->y = 610;
			f2->vy = 15;
			f2->hitbox.y = f2->y;
			player2_fc = 10;
			f2->flags = FIGHTERFLAG_IDLE;
		}
	}
	else if(f2->flags == FIGHTERFLAG_IDLE)
	{
		/* Defaults to idle if nothing else */
		f2->flags = FIGHTERFLAG_NOBLOCK;
		if(f2->sprite != NULL) FreeSprite(f2->sprite);
		f2->sprite = LoadSprite("images/DoomIdleReversed.png",180,150);
		player2_fc = 10;
	}
	DrawSprite(f2->sprite,buffer,f2->x, f2->y,F_Sprite.player2_frame);
	F_Sprite.player2_frame = (F_Sprite.player2_frame + 1) % player2_fc;
	/* Frees up the sprite for the next render */
	f2->sprite = NULL;
	if(f2->sprite != NULL)
	{
		FreeSprite(f2->sprite);
	}
}
/*
Frees the memory that is held by the fighter
*/
void FreeFighter(Fighter* f)
{	
	FreeSprite(f->sprite);
	f->sprite = NULL;
	f->health = NULL;
	f->x = NULL;
	f->y = NULL;
	f->vy = NULL;
	f->walk_acc = NULL;
	f->walk_speed = NULL;
	f->jump_speed = NULL;
	f->hitbox.x = NULL;
	f->hitbox.y = NULL;
	f->hitbox.w = NULL;
	f->hitbox.h = NULL;
	f->flags = NULL;
	f->anim_flags = NULL;
	f->f_jump = NULL;
}
/*
Cleans up the fighter list if it hasn't already been cleaned
*/
void CloseFighter()
{
	for(int i = 0; i < MAX_FIGHTERS; ++i)
	{
		FreeFighter(&Fighters[i]);
	}
}
/*
Draws the current health of the fighter
*/
void DrawHealthBar(Fighter* f, SDL_Surface *buffer, int x, int y)
{
	if(f->health != 300)
		for(int h=0; h<f->health + 30;++h)
			for(int g=0; g < 30; ++g)
				DrawPixel(buffer,255,0,0,(30 + h) + x,(30 + g) + y);
	for(int i=0; i<f->health;++i)
		for(int j=0; j < 30; ++j)
			DrawPixel(buffer,0,255,0,(30 + i) + x,(30 + j) + y);
}
