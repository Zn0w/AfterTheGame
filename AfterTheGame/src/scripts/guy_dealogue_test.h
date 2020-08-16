#pragma once

#include "../ecs/system.h"
#include "../components/script.h"
#include "../components/transform.h"
#include "../components/collider.h"
#include "../components/animation.h"
#include "collision.h"
#include "../game_state/game_state.h"


struct GuyDialogueTestScript : public Script
{
	ColliderComponent* collider;
	DialogueComponent* greet_dialogue;

	GamePhase* game_phase;
	DialogueComponent* current_dialogue;

	bool dialogue_active = false;


	GuyDialogueTestScript(std::vector<ColliderComponent*>& s_colliders, GamePhase* s_game_phase, DialogueComponent* s_current_dialogue)
		: Script(s_colliders), game_phase(s_game_phase), current_dialogue(s_current_dialogue)
	{}

	void init() override
	{
		collider = &entity->get_component<ColliderComponent>();
		greet_dialogue = &entity->get_component<DialogueComponent>();
	}

	void update(float delta) override
	{
		for (ColliderComponent* c : colliders)
		{
			if (c->tag == "player" && collide(collider->rect, c->rect) && !dialogue_active)
			{
				*game_phase = GAME_IN_DIALOG;
				current_dialogue = greet_dialogue;
				dialogue_active = true;
			}
		}
	}
};