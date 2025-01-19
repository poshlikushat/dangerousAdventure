#pragma once

void removeEntityFromDungeon(Entity *remove);
void addEntityToDungeon(Entity *e);
Entity *getEntityAt(int x, int y);
void drawEntities(void);
void doEntities(void);
Entity *spawnEntity(void);
void initEntities(void);