/********************************************************************************************
* SIDH: an efficient supersingular isogeny cryptography library
* Copyright (c) Microsoft Corporation
*
* Website: https://github.com/microsoft/PQCrypto-SIDH
* Released under MIT license
*
* Abstract: internal header file for function definitions
*********************************************************************************************/  

#ifndef INTERNAL_H
#define INTERNAL_H


/**************** Function prototypes ****************/
/************* Multiprecision functions **************/ 

// Copy wordsize digits, c = a, where lng(a) = nwords
static void copy_words(const digit_t* a, digit_t* c, const unsigned int nwords);

// Compare two byte arrays in constant time
static int8_t ct_compare(const uint8_t *a, const uint8_t *b, unsigned int len) ;

// Conditional move in constant time
static void ct_cmov(uint8_t *r, const uint8_t *a, unsigned int len, int8_t selector);

// Multiprecision addition, c = a+b, where lng(a) = lng(b) = nwords. Returns the carry bit 
static unsigned int mp_add(const digit_t* a, const digit_t* b, digit_t* c, const unsigned int nwords);

// Multiprecision subtraction, c = a-b, where lng(a) = lng(b) = nwords. Returns the borrow bit 
static unsigned int mp_sub(const digit_t* a, const digit_t* b, digit_t* c, const unsigned int nwords);

// 2x434-bit multiprecision subtraction followed by addition with p434*2^448, c = a-b+(p434*2^448) if a-b < 0, otherwise c=a-b 
static void mp_subaddx2_asm(const digit_t* a, const digit_t* b, digit_t* c);

// Multiprecision left shift
static void mp_shiftleft(digit_t* x, unsigned int shift, const unsigned int nwords);

// Multiprecision right shift by one
static void mp_shiftr1(digit_t* x, const unsigned int nwords);

// Multiprecision left right shift by one    
static void mp_shiftl1(digit_t* x, const unsigned int nwords);

// Digit multiplication, digit * digit -> 2-digit result
static void digit_x_digit(const digit_t a, const digit_t b, digit_t* c); 

// Multiprecision comba multiply, c = a*b, where lng(a) = lng(b) = nwords.
static void mp_mul(const digit_t* a, const digit_t* b, digit_t* c, const unsigned int nwords);

/************ Montgomery reduction and conversion functions *************/

// Montgomery reduction, c = a mod p
static void rdc_mont(digit_t* a, digit_t* c);

// Conversion to Montgomery representation
static void to_mont(const digit_t* a, digit_t* mc);
    
// Conversion from Montgomery representation to standard representation
static void from_mont(const digit_t* ma, digit_t* c);
    
// Conversion of a GF(p^2) element to Montgomery representation
static void to_fp2mont(const f2elm_t a, f2elm_t mc);

// Conversion of a GF(p^2) element from Montgomery representation to standard representation
static void from_fp2mont(const f2elm_t ma, f2elm_t c);

// n-way Montgomery inversion
static void mont_n_way_inv(const f2elm_t* vec, const int n, f2elm_t* out);

/************ Elliptic curve and isogeny functions *************/

// Computes the j-invariant of a Montgomery curve with projective constant.
static void j_inv(const f2elm_t A, const f2elm_t C, f2elm_t jinv);

// Simultaneous doubling and differential addition.
static void xDBLADD(point_proj_t P, point_proj_t Q, const f2elm_t XPQ, const f2elm_t ZPQ, const f2elm_t A24);

// Doubling of a Montgomery point in projective coordinates (X:Z).
static void xDBL(const point_proj_t P, point_proj_t Q, const f2elm_t A24plus, const f2elm_t C24);

// Computes [2^e](X:Z) on Montgomery curve with projective constant via e repeated doublings.
static void xDBLe(const point_proj_t P, point_proj_t Q, const f2elm_t A24plus, const f2elm_t C24, const int e);

// Differential addition.
static void xADD(point_proj_t P, const point_proj_t Q, const f2elm_t xPQ);

// Computes the corresponding 4-isogeny of a projective Montgomery point (X4:Z4) of order 4.
static void get_4_isog(const point_proj_t P, f2elm_t A24plus, f2elm_t C24, f2elm_t* coeff);

// Evaluates the isogeny at the point (X:Z) in the domain of the isogeny.
static void eval_4_isog(point_proj_t P, f2elm_t* coeff);

// Tripling of a Montgomery point in projective coordinates (X:Z).
static void xTPL(const point_proj_t P, point_proj_t Q, const f2elm_t A24minus, const f2elm_t A24plus);

// Computes [3^e](X:Z) on Montgomery curve with projective constant via e repeated triplings.
static void xTPLe(const point_proj_t P, point_proj_t Q, const f2elm_t A24minus, const f2elm_t A24plus, const int e);

// Computes the corresponding 3-isogeny of a projective Montgomery point (X3:Z3) of order 3.
static void get_3_isog(const point_proj_t P, f2elm_t A24minus, f2elm_t A24plus, f2elm_t* coeff);

// Computes the 3-isogeny R=phi(X:Z), given projective point (X3:Z3) of order 3 on a Montgomery curve and a point P with coefficients given in coeff.
static void eval_3_isog(point_proj_t Q, const f2elm_t* coeff);

// 3-way simultaneous inversion
static void inv_3_way(f2elm_t z1, f2elm_t z2, f2elm_t z3);

// Given the x-coordinates of P, Q, and R, returns the value A corresponding to the Montgomery curve E_A: y^2=x^3+A*x^2+x such that R=Q-P on E_A.
static void get_A(const f2elm_t xP, const f2elm_t xQ, const f2elm_t xR, f2elm_t A);


#endif
