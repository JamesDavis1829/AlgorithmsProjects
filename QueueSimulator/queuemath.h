/*
 * queuemath.h
 *
 *  Created on: Sep 19, 2015
 *      Author: crims_000
 */

#ifndef QUEUEMATH_H_
#define QUEUEMATH_H_

int fact(int number);

double p0(double M,double mu, double lambda);

double powerTo(double number, int power);

double L(double M, double mu, double lambda);

double W(double M, double mu, double lambda);

double Lq(double M, double mu, double lambda);

double Wq(double M, double mu, double lambda);

double rho(double M,double mu, double lambda);

double getNextRandomInterval(double average,double *time);

double getNextRandomService(double average, double time);

double LqWithL(double L, double mu, double lambda);

double LWithP0(double M, double mu, double lambda, double P0);

#endif /* QUEUEMATH_H_ */
