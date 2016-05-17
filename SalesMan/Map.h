/*
 * Map.h
 *
 *  Created on: Oct 7, 2015
 *      Author: crims_000
 */

#ifndef MAP_H_
#define MAP_H_

typedef struct map *mapP;

struct map* createMap();

double getDistance(struct map* myMap,int source, int destination);

double getDistanceOfTrail(struct map* myMap,int* trail);

void freeMap(struct map* myMap);

void printPresets(struct map* newMap);

int getNumCities(struct map* newMap);

void setBest(struct map* newMap,int* newBest);

int getBestEntry(struct map* newMap, int location);

double getDistanceOfBestTrail(struct map* myMap);

double printBestTrail(struct map* newMap);

void primeGeneration(mapP map);

double runMutation(struct map* nMap);

double findBest(struct map* nMap,int start);

double getDistanceOfTrailGeneration(struct map* myMap,int start);

void printGeneration(struct map* nMap);

void printArrayLocation(struct map* nMap,int start);

#endif /* MAP_H_ */
