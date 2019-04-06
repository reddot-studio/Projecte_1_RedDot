#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "Animation.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	graphics = App->textures->Load("Assets/ryo_sprite_sheet.png");

	// Ko'ou Ken particle
	//Charge energy
	pre_koouKen.anim.PushBack({939,940,19,45},-33,-39,2);
	pre_koouKen.anim.PushBack({683,869,23,36},-55,-37,2);
	pre_koouKen.anim.PushBack({707,869,22,36},-49,-21,3);
	pre_koouKen.anim.PushBack({730,878,26,27},-49,-17,1);
	pre_koouKen.anim.PushBack({730,878,26,27},-54,-15,1);
	pre_koouKen.anim.loop = false;
	pre_koouKen.anim.speed = 0.32f;
	////Shoot energy
	koouKen.anim.PushBack({683,912,54,39},-3,-22,5);
	koouKen.anim.PushBack({737,905,72,47},-15,-24,5);
	koouKen.anim.PushBack({809,920,53,31},-2,-19,5);
	koouKen.anim.PushBack({862,930,36,21},9,-16,5);
	koouKen.anim.loop = true;
	koouKen.life = 1000;
	koouKen.speed = { 10,0 };
	koouKen.anim.speed = 1.0f;


	//Hitted particle
	//koouKen.anim.PushBack({942,612,30,37});
	//koouKen.anim.PushBack({973,612,22,37});
	//koouKen.anim.PushBack({942,664,20,37});
	//koouKen.anim.PushBack({962,665,22,36});
	//koouKen.anim.PushBack({985,665,39,36});
	//koouKen.anim.PushBack({998,612,25,50});

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			RectSprites r = p->anim.GetCurrentFrame();
			App->render->Blit(graphics, p->position.x +r.offset.x, p->position.y + r.offset.y, &r);
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		int ticks = SDL_GetTicks();
		int num = ticks - born;
		if (num > life) {
			ret = false;
		}
	}
	else
		if (anim.Finished()) {
			ret = false;
		}
	if (SDL_GetTicks() >= born) {
		position.x += speed.x;
		position.y += speed.y;
	}

	return ret;
}