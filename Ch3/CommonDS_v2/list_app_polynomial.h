#ifndef _LIST_APP_POLYNOMIAL_H
#define _LIST_APP_POLYNOMIAL_H

#include "node_impl_polynomial.h"

typedef Node *Polynomial;

void ZeroPolynomial(Polynomial Poly);
Polynomial AddPolynomial(Polynomial LeftOprand, const Polynomial RightOprand);
Polynomial MultiPolynomial(Polynomial LeftOprand, const Polynomial RightOprand);
void PrintPolynomial(Polynomial Poly);
void MergePolynomial(Polynomial Poly);

#endif