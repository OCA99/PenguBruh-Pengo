
#include "Score.h"
#include "ModuleParticles.h"
#include "Application.h"

#include <iostream>
#include <math.h>

Score::Score(bool startEnabled) : Module(startEnabled) {}

Score::~Score(){}

void Score::AddScore(int s) {
	score += s;
	if (score > 99999) score = 99999;
	
}

void Score::AddScore(float s) {
	scoreRemainder += fmod(s, 1.0f);
	score += (int)round(floor(s) + floor(scoreRemainder));
	scoreRemainder = fmod(scoreRemainder, 1.0f);
	if (score > 99999) score = 99999;

}

#include <iostream>

void Score::AddScore(int s, int x, int y) {
	score += s;
	if (score > 99999) score = 99999;
	if (s == 100) {
		App->particles->AddParticle(App->particles->score100, x, y);
	}
	else if (s == 400) {
		App->particles->AddParticle(App->particles->score400, x, y);
	}
	else if (s == 1600) {
		App->particles->AddParticle(App->particles->score1600, x, y);
	}
	else if (s == 3200) {
		App->particles->AddParticle(App->particles->score3200, x, y);
	}
	else if (s == 6400) {
		App->particles->AddParticle(App->particles->score6400, x, y);
	}
}

void Score::SetHighscore(int s) {
	highscore = s;
}

void Score::CheckAndSetHighscore() {
	if (score > highscore) {
		highscore = score;
	}
}

void Score::ResetScore() {
	score = 0;
}

